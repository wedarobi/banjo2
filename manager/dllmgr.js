const path = require("path");

/**
 * An absolute path to the repo root, given that this
 * file lives 1 folder down from it.
 */
const gRootDir = path.resolve(__dirname + path.sep + ".." + path.sep) + path.sep;
const gCurrDir = path.resolve(__dirname + path.sep) + path.sep;
//# rp: root path
const rp = p => path.resolve(gRootDir + p);



const fs     = require("fs");
const fsp    = require("fs/promises");
const cmd    = require("child_process");
const crypto = require("crypto");
const zlib   = require("node:zlib");


//- Local pako, with modified zlib implementation
const pako = require(rp("tools/pako/index"));

const stringSimilarity = require("string-similarity");
// const cparser          = require("node-c-parser");
// const c_ast            = require("c-ast");



/* constants ***********************************************/

const allRomVers = ["usa", "jpn", "eur", "aus"];
const VERSION_CONSTANTS =
{
    DLL_CALL_TBL: { usa: 0x80082540, jpn: 0x80081CD0, eur: 0x8008C920, aus: 0x8008C920, },
    BUILD_IDX:    { usa: 0, jpn: 1, eur: 2, aus: 3, },
};

// TODO: Make a single place to store all file paths
//# placeholder
// function get_paths(romVer)
// {
//     return { dlls: `vers/dlls/${romVer}/misc`, };
// }

/***********************************************************/




const FATAL = msg =>
{
    console.error(msg);
    process.exit(1);
}

const ERROR = msg =>
{
    console.error(msg);
}

const log = (msg, prefix="INFO") =>
{
    // console.log(`[${prefix}] ${msg}`);
    console.log(msg);
}

const rlog = (msg) =>
{
    process.stdout.write(msg + "\r");
}

function DEBUG_LOG(msg)
{
    if (false)
        console.log(msg);
}

function spawn(command, directPrint=true, ignoreStderr=false)
{
    return new Promise((res, rej) =>
    {
        // log(`  ${command}`, "EXEC");
        DEBUG_LOG(command);

        let cmdlist = command.split(/\s+/);
        let proc;
        if (cmdlist.length <= 1)
            proc = cmd.spawn(cmdlist[0], { detached: true });
        else
            proc = cmd.spawn(cmdlist[0], cmdlist.slice(1), { detached: true });

        let stdout = "";
        let stderr = "";

        proc.stdout.on("data", data =>
        {
            if (directPrint)
                process.stdout.write(data);
            else
                stdout += data;
        });

        proc.stderr.on("data", data =>
        {
            if (directPrint)
                process.stderr.write(data);
            else
                stderr += data;
        });

        proc.on("close", code =>
        {
            if (!directPrint)
            {
                if (code && !ignoreStderr)
                    return rej(stderr);

                return res(stdout);
            }
            else
            {
                if (code)
                    return rej();

                return res();
            }
        });

        proc.on("error", err =>
        {
            ERROR(err);
            log(`Not spawning for ["${command}"]`);
            return rej();
        });
    });
}

function get_hash(buf)
{
    return crypto.createHash("sha256").update(buf).digest("hex").toUpperCase();
}

Number.prototype.hex  = function() { return        this.toString(16).toUpperCase(); }
Number.prototype.hexp = function() { return "0x" + this.toString(16).toUpperCase(); }

Buffer.prototype.clone = function()
{
    let buf = Buffer.alloc(this.byteLength);
    this.copy(buf);
    return buf;
}

function sleep(ms)
{
    return new Promise(r => setTimeout(r, ms));
}

const COLOUR_CODES =
{
    black:  "30",
    red:    "31",
    green:  "32",
    yellow: "33",
    blue:   "34",
    pink:   "35",
    cyan:   "36",
    white:  "37"
};

function gct(msg, colour, underline=false)
{
    let ul = underline ? "4m" : "1m";
    //# standard bright white (force no underline)
    let reset = "\x1b[97;0;1m";

    let code = colour in COLOUR_CODES
        ? COLOUR_CODES[colour]
        //# default special colour is pink
        : COLOUR_CODES["pink"];

    return `\x1b[${code};${ul}${msg}${reset}`;
}

function str_contains_colour(str, colour)
{
    return str.includes(`\x1b[${COLOUR_CODES[colour]};`);
}

function calc_max_width_for_box_contents(msgArr)
{
    function removeColour(str)
    {
        return str.replace(/\x1b.*?m/g, "");
    }

    let spacing = 1;
    let max_width = 0;

    for (let str of msgArr)
    {
        let fstr = removeColour(str);

        if (fstr.length > max_width)
            max_width = fstr.length;
    }

    //# Ignore, since we only want INTERNAL width
    // max_width += spacing * 2;

    return max_width;
}

/**
 * This function takes an array of strings and puts them in a nice ascii box.
 * @param {String[]} msgArr
 */
function print_lines_in_box(msgArr, colour="white")
{
    function removeColour(str)
    {
        return str.replace(/\x1b.*?m/g, "");
    }

    let os = ""; /// out_str
    let chars = "┌─┐│└─┘".split("");
    let spacing = 1;
    let spacer = "";
    let tmp; /// Temp string for adding colour to box
    for (let i = 0; i < spacing; i++) spacer += " ";
    let max_width = 0;
    for ( let str of msgArr ) {
        let fstr = removeColour(str);
        if ( fstr.length > max_width ) {
            max_width = fstr.length;
        }
    }
    max_width += spacing * 2;

    /// Print first line
    tmp = "";
    tmp += chars[0];
    for ( let i = 0; i < max_width; i++ ) tmp += chars[1];
    tmp += chars[2] + "\n";
    os += gct(tmp, colour);

    /// Print the strings
    for ( let str of msgArr ) {
        os += `${gct(chars[3], colour)}${spacer}${str}`;
        for ( let i = 0; i < max_width - removeColour(str).length - spacing; i++) os += " ";
        os += `${gct(chars[3], colour)}\n`;
    }

    /// Print last line
    tmp = "";
    tmp += chars[4];
    for ( let i = 0; i < max_width; i++ ) tmp += chars[5];
    tmp += chars[6] + "\n";
    os += gct(tmp, colour);

    process.stdout.write(os);
}

function ensureFile(path)
{
    if (!fs.existsSync(path))
        fs.writeFileSync(path, "");
}

function ensureDir(path)
{
    if (!fs.existsSync(path))
        fs.mkdirSync(path);
}


const CMD =
{
    cc:        gRootDir + "tools/ido5.3_recomp/cc",
    // include:   "-I . -I include -I include/2.0L -I include/2.0L/PR",
    include:   `-I ${rp(".")} -I ${rp("include")} -I ${rp("include/2.0L")} -I ${rp("include/2.0L/PR")}`,
    objdump:   "mips-linux-gnu-objdump",
    as:        "mips-linux-gnu-as",
    ld:        "mips-linux-gnu-ld",
};

async function dll_get_if_to_skip_build(dll, romVer)
{
    ensureDir("build");
    ensureDir(`build/${romVer}`);
    ensureDir(`build/${romVer}/dlls`);

    const file_in  = gRootDir + `src/dlls/${dll}.c`;
    const file_out = gRootDir + `build/${romVer}/dlls/${dll}.lpo`;

    return fs.existsSync(file_in)
        && fs.existsSync(file_out)
        && (await fsp.stat(file_in)).mtimeMs < (await fsp.stat(file_out)).mtimeMs;
}

/**
 * Builds the .c file for a DLL and outputs an ELF .o file.
 *
 * @param {string} dll name of dll, as a string. e.g. "cosection"
 */
async function dll_build(dll, romVer, toSkip=false)
{
    //- Exec

    const file_in  = gRootDir + `src/dlls/${dll}.c`;
    const file_out = gRootDir + `build/${romVer}/dlls/${dll}.o`;

    if (!toSkip)
    {
        let cmd = "";
        cmd += ` -c -Wab,-r4300_mul -non_shared -G 0 -Xfullwarn -Xcpluscomm`;
        /**
         * 649: "Missing member name in struct/union"
         * 807: ?
         * 838: "Microsoft extension" > nested structs/unions (?)
         * 624: "Trailing comma in enumerator list"
         */
        cmd += ` -woff 649,807,838,624`;
        cmd += ` -O2 -mips2 -D_FINALROM -DF3DEX2_GBI ${CMD.include}`;
        cmd += ` ${file_in} -o ${file_out}`;

        //- Env vars
        let env = "";
        {
            //- Pass "VERSION_USA" etc macros
            env += `-DVERSION_${romVer.toUpperCase()}=1`;
        }

        await spawn(`${CMD.cc} ${cmd} ${env}`);
    }

    return file_out;
}

function ALIGN(value, pad)
{
    let modResult = value % pad;

    if (modResult)
        value += pad - modResult;

    return value;
}

/**
 * Map between <DLL_name, syscallIdx>
 */
var allDllNames = new Set();
var gCurrentlyLoadedSyscallIdxMap = "";

var gSyscallIdxMap_rv = {};

/**
 * Map between <DLL_name, callTableOffset>
 *
 * WARN: Only usable inside certain functions, it's only updated for a version on-demand
 */
var gCallTableOffsetMap;

async function init_gSyscallIdx_map(romVer)
{
    if (romVer in gSyscallIdxMap_rv)
        //# Already loaded
        return;

    const fSyscallIdx = gCurrDir + "enum/syscallidx.txt";

    if (!fs.existsSync(fSyscallIdx))
        FATAL(`File missing: [${fSyscallIdx}]`);

    let lines = (await fsp.readFile(fSyscallIdx)).toString().split(/\r?\n/g);

    let isUsa = romVer === "usa";

    //- We want to create a map between <DLL_name, syscallIdx> with the following loop
    let o = {};
    let syscallIdx = -1; // First entry is 0, and we increment at the start of the loop

    for (let [lineNo, line] of lines.entries())
    {
        syscallIdx++;

        if (line === "")
            continue;

        let words = line.split(/\s+/g);
        if (words.length === 1 || isUsa) // USA contains all known DLLs
        {
            let dllName = words[0];

            allDllNames.add(dllName);

            o[dllName] = syscallIdx;
            continue;
        }

        // "0": USA-only, ignore idx for other vers
        // "1": USA-only, count idx for other vers
        let type = words[1];

        if (type === "0")
        {
            // Ignore idx completely, pretend like it never existed by decrementing
            syscallIdx--;
            continue;
        }

        if (type === "1")
        {
            // Count idx, but don't remember the name
            continue;
        }
    }

    gSyscallIdxMap_rv[romVer] = o;

    gCurrentlyLoadedSyscallIdxMap = romVer;
}

async function init_gCallTableOffset_map(romVer)
{
    const fCallTableOffset = gCurrDir + `enum/calltableoffset/${romVer}.txt`;

    if (!fs.existsSync(fCallTableOffset))
        FATAL(`File missing: [${fCallTableOffset}]`);

    let lines = (await fsp.readFile(fCallTableOffset)).toString().split(/\r?\n/g);

    //- We want to create a map between <DLL_name, callTableOffset> with the following loop
    let o = {};

    for (let line of lines)
    {
        if (line === "")
            continue;

        let words = line.split(/\s+/g);

        o[words[0]] = parseInt(words[1], 16);
    }

    gCallTableOffsetMap = o;
}

/**
 * Both returned buffers include the preheader.
 * 
 * cmp: encrypted preheader + compressed stream
 * 
 * dec: decrypted preheader + decompressed stream
 * 
 * @param {string} dllName 
 * @param {string} romVer 
 * @param {boolean} toSkip 
 * @returns 
 */
async function dll_dump_and_get_vani_from_baserom(dllName, romVer)
{
    let cmp, dec;

    let cmp_fn = gRootDir + `expected/${romVer}/dlls/${dllName}.dll`;
    let dec_fn = gRootDir + `expected/${romVer}/dlls/${dllName}.bin`;

    let exists_cmp = fs.existsSync(cmp_fn);
    let exists_dec = fs.existsSync(dec_fn);

    if (exists_cmp && exists_dec)
    {
        //- Fetch from disk
        cmp = await fsp.readFile(cmp_fn);
        dec = await fsp.readFile(dec_fn);
    }
    else
    {
        //- Generate

        let syscallIdx = gSyscallIdxMap_rv[romVer][dllName];

        let dllTableStart =
        {
            usa: 0x1E899B0,
            jpn: 0x1E308D0,
            eur: 0x1E8DA70,
            aus: 0x1E18A80,
        };
    
        let dllOffsetStart = gBaseroms[romVer].readUint32BE(dllTableStart[romVer] + ((syscallIdx - 1) * 4));
        let dllOffsetEnd   = gBaseroms[romVer].readUint32BE(dllTableStart[romVer] + ((syscallIdx    ) * 4));
    
        // console.log(dllOffsetStart.hex())
        // console.log(dllOffsetEnd.hex())
    
        let size = dllOffsetEnd - dllOffsetStart;
    
        if (!size)
            //# dll missing
            return null;
    
        //- Grab file from baserom
    
        let preheader = gBaseroms[romVer].slice(
            dllTableStart[romVer] + dllOffsetStart,
            dllTableStart[romVer] + dllOffsetStart + 0x10,
        );
    
        //= Both preheader and compressed body combined
        cmp = gBaseroms[romVer].slice(
            dllTableStart[romVer] + dllOffsetStart,
            dllTableStart[romVer] + dllOffsetEnd,
        );
    
        //- Decompress the raw vanilla stream
        {
            let dllUncompressed = await zlib_inflateRaw_async(cmp.slice(0x12));
    
            //# Splice vanilla preheader onto vanilla decompressed file
            dec = Buffer.alloc(preheader.byteLength + dllUncompressed.byteLength);
            preheader      .copy(dec);
            dllUncompressed.copy(dec, 0x10);
    
            //# Decrypt preheader
            // await dll_preheader_encryption_toggle(dllUncompressed);
            await dll_preheader_encryption_toggle(dec);
        }
    
        //= Dump to [expected] folder
        {
            ensureDir(gRootDir + `expected`);
            ensureDir(gRootDir + `expected/${romVer}`);
            ensureDir(gRootDir + `expected/${romVer}/dlls`);
    
            await fsp.writeFile(cmp_fn, cmp);
            await fsp.writeFile(dec_fn, dec);
        }
    }

    return { cmp, dec };
}

/**
 * Pass null for the buffer to dump vanilla instead.
 * 
 * @param {string} dllName
 * @param {string} romVer
 * @param {Buffer} dllBufDec custom (decrypted preheader + decompressed body) dll to dump. OPTIONAL. If not provided, will do dumps for vanilla.
 * @returns {Promise<boolean>} TRUE if successful, else FALSE
 */
async function dll_make_fndumps(dllName, romVer, dllBufDec)
{
    let dec;
    let path;

    if (!dllBufDec)
    {
        let bufs = await dll_dump_and_get_vani_from_baserom(dllName, romVer);
        if (!bufs)
            //# Could not make fndumps
            return false;
    
        dec = bufs.dec;
        path = `expected/${romVer}/dlls`;
    }
    else
    {
        dec = dllBufDec;
        path = `build/${romVer}/dlls`;
    }

    //- Perform fndump
    await dll_analysis_text_dump(await dll_analyse_text(dec), gRootDir + path);
}

/**
 * Get a similarity score for a new DLL file, by comparing it to the one
 * inside the current baserom.
 *
 * @param {string} dllName
 * @param {Buffer} newDllFile the built DLL. format: encrypted preheader + decompressed body
 * @param {string} romVer
 * @param {boolean} compressed if true, compare compressed version instead
 */
async function dll_get_similarity(dllName, newDllFile, romVer, compressed=false)
{
    let bufs = await dll_dump_and_get_vani_from_baserom(dllName, romVer);

    if (!bufs)
        //# dll missing, or we just wanted to dump them
        return { found: false, similarity: 0 };

    let { cmp: buf_vani_cmp, dec: buf_vani_dec } = bufs;

    let buf_vani, buf_cust;
    {
        if (compressed)
        {
            buf_vani = buf_vani_cmp;
            buf_cust = newDllFile;
        }
        else
        {
            buf_vani = buf_vani_dec;

            //# Decrypt preheader to temp buffer
            let dec = newDllFile.clone();
            await dll_preheader_encryption_toggle(dec);

            buf_cust = dec;
        }
    }

    //- Execute compare
    let similarity;
    {
        let s_v = buf_vani.toString("hex");
        let s_c = buf_cust.toString("hex");

        similarity = s_v === s_c
            //# Matches perfectly
            ? 1
            //# Similarity score for mismatching buffers must not exceed 0.999
            : Math.min(0.999, stringSimilarity.compareTwoStrings(s_v, s_c));
    }

    return { found: true, similarity, };
}

/**
 * If a source (.c) file for a DLL exists, but is EMPTY, we
 * initialise it with placeholder function names.
 * 
 * Uses vanilla fndump files.
 * 
 * @param {string} dllName 
 * @param {string} romVer 
 */
async function dll_source_initialise(dllName, romVer="usa")
{
    let dst_fn    = gRootDir + `src/dlls/${dllName}.c`;
    let fndump_fn = gRootDir + `expected/${romVer}/dlls/${dllName}_fndump.txt`;

    if (!fs.existsSync(dst_fn) || (await fsp.stat(dst_fn)).size > 0)
        //# Doesn't exist, or if it does exist, has stuff inside it
        return false;

    if (!fs.existsSync(fndump_fn))
        //# Vanilla fndump does not exist
        return false;

    //- Required files exist, do the thing

    let header = `
        #include "include/2.0L/ultra64.h"

        #include "include/functions.h"
        #include "include/variables.h"
        #include "include/dlls.h"
    `.replace(/^ +/g, "")
     .replace(/\n +/g, "\n")
     .trim() + "\n".repeat(5);

    let fn_dump = (await fsp.readFile(fndump_fn))
        .toString()
        .trim()
        .split(/(?:\r?\n)+/g)
        .map(line =>
        {
            let es = line.split(/\s+/g);
            return { name: es[0], offset: es[1], size: es[2] };
        });

    let body = "";

    {
        let cntPubs = 0;
        let cntPrvs = 0;

        for (let fn of fn_dump)
        {
            let isPub = fn.name.startsWith("pub");
    
            let name = isPub
                ? `DLL_${dllName}_${(cntPubs++).toString().padStart(2, "0")}`
                : `fn_priv_${(cntPrvs++).toString().padStart(2, "0")}`;
    
            body += `void ${name}(void)\n{\n    // TODO\n\n\n}\n\n`;
        }
    }

    //- Write
    {
        let out = header + body;

        await fsp.writeFile(dst_fn, out);
    }

    return true;
}

function remove_c_comments_from_src(src)
{
    //# Multiline
    src = src.replace(/\/\*.+\*\//gm, "");

    //# Single line
    src = src.replace(/\/\/.+(\r?\n)/gm, "$1");

    return src;
}

/**
 * Get a list of functions from a C source file and
 * also give their start and end offsets.
 *
 * We do this manually instead of with e.g. pycparser
 * mainly for performance; it's much, much faster this way.
 *
 * -> remove all comments
 * -> run through the C preprocessor
 * -> parse function names and match their start and end squiggly brackets
 * @param {string} src
 * @param {string} dllName
 * @param {string} romVer
 */
async function dll_src_extract_function_offsets(src, dllName, romVer)
{
    //- Remove comments
    src = remove_c_comments_from_src(src);

    //- Scan
    let functionInfoObjs = [];
    {
        //- Run through the preprocessor
        let pp_output;
        {
            let defines  = `-D_LANGUAGE_C -DF3DEX2_GBI -DVERSION_${romVer.toUpperCase()}=1`;
            let includes = "";
            includes += " -I/home/user/n64/decomp/bt";
            includes += " -I/home/user/n64/decomp/bt/include";
            includes += " -I/home/user/n64/decomp/bt/include/2.0L";
            try
            {
                pp_output = await spawn(`gcc -E ${defines} ${includes} src/dlls/${dllName}.c`, false);
            }
            catch (err)
            {
                //! Handle errors?

                throw err;
            }
        }

        //- Process and filter the output of the preprocessor
        let functionsNames;
        {
            let re = new RegExp(`^# \\d+ "src\/dlls\/${dllName}\.c" \\d+$`, "g");

            //- Get the contents of the preprocessor output that excludes all other included files
            //# We mostly wanted to get rid of #if/#ifdef/#ifndef stuff so we're ready
            //# We don't care about defs
            let filtered = "";
            {
                let lines = pp_output.split(/\r?\n/g);
                let arr = [];

                for (let i = lines.length - 1; i >= 0; i--)
                {
                    let line = lines[i];

                    if (re.test(line))
                        //# Found the final relevant preprocessor line, get out
                        break;

                    arr.push(line);
                }

                filtered = arr.reverse().join("\n");
            }

            //- Look through the preprocessor output for things that look like top-level function definitions
            {
                let re = /\b[A-Za-z0-9_]+(?<!\bwhile|\bfor|\bif|\bswitch|\bcase)\s*?\([^\(\);]+\)\s*?{/gm;

                let m = filtered.match(re);
                if (!m)
                    m = [];

                functionsNames = m.map(e => e.split(/[\s\(]+?/g)?.[0]).filter(x => x);
            }
        }

        // TODO: Validate length of functionsNames against expected number of functions from parsed DLL file

        //- Calculate function start offsets
        //# (with regex)
        {
            for (let fn of functionsNames)
            {
                let re  = new RegExp(`\\b${fn}\\s*?\\([^\(\);]+\\)\\s*?{`, "g");
                let rem = re.exec(src);

                if (rem && rem.length === 1)
                {
                    let start = rem.index;

                    {
                        /**
                         * # Move function start to the start of the line.
                         *
                         * ! Yes, this is an ugly hack
                         *   and it WON'T WORK as intended (it won't respond to
                         *   editing the return type) if the return type is
                         *   on a separate line to the function name token.
                         *
                         * But im not sure how to identify return types
                         * without using pycparser or some other slow "full
                         * C code parser"
                         */

                        for (let i = start - 1; i >= 0; i--)
                        {
                            if (src[i] === "\n")
                            {
                                //# Found start of line, treat as start of function
                                start = i + 1;
                                break;
                            }
                        }
                    }

                    functionInfoObjs.push({
                        name:  fn,
                        start,
                        //= This needs to be calculated properly later
                        end:   0,
                    });
                }
            }
        }

        //- Calculate function end offsets
        //# (with string iteration and by processing nested bracket pairs)
        {
            for (let i = 0; i < functionInfoObjs.length; i++)
            {
                let o = functionInfoObjs[i];

                let start = o.start;

                let brackets =
                {
                    //# ()
                    round:
                    {
                        done: false,
                        nest: 0,
                    },
                    //# {}
                    squiggly:{
                        done: false,
                        nest: 0,
                    },
                };

                for (let j = start; j < src.length; j++)
                {
                    let c = src[j];

                    if (!brackets.round.done)
                    {
                        if (c === "(")
                        {
                            brackets.round.nest++;
                        }
                        else if (c === ")")
                        {
                            if (--brackets.round.nest === 0)
                                brackets.round.done = true;
                        }

                        continue;
                    }

                    if (!brackets.squiggly.done)
                    {
                        if (c === "{")
                        {
                            brackets.squiggly.nest++;
                        }
                        else if (c === "}")
                        {
                            if (--brackets.squiggly.nest === 0)
                            {
                                brackets.squiggly.done = true;

                                //- Save end offset
                                functionInfoObjs[i].end = j + 1;

                                //= We've found the bounds of this function, cease!
                                break;
                            }
                        }

                        continue;
                    }
                }
            }
        }
    }

    return functionInfoObjs;
}


var gDllSourceCache = {};
/**
 * Needed to preserve the autodiff in some cases where
 * a simple touch won't work since the offsets need
 * to be updated (e.g. when editing .data)
 */
var gDllCacheLastInfo = {
    dll:   "",
    fname: "",
    fidx:  "",
};

async function dll_cache_source_update_locations(dllName, romVer)
{
    let filename = gRootDir + `src/dlls/${dllName}.c`;

    //- Update new src
    {
        let src = (await fsp.readFile(filename)).toString();
        let fns;
        try
        {
            fns = await dll_src_extract_function_offsets(src, dllName, romVer);
        }
        catch (err)
        {
            console.log(`[ERR]: CPP quit early, not updating src cache for: ${dllName}`);
            console.error(err);
            return;
        }

        //- No errors, proceed

        //# Init
        {
            if (!(dllName in gDllSourceCache))
                gDllSourceCache[dllName] = {};

            if (!(romVer in gDllSourceCache[dllName]))
            {
                gDllSourceCache[dllName][romVer] = {
                    src: "",
                    fns: [],
                }
            };
        }

        //# Commit
        gDllSourceCache[dllName][romVer].src = remove_c_comments_from_src(src);
        gDllSourceCache[dllName][romVer].fns = fns;
    }
}


/**
 * Compare the contents of two DLL source .c files:
 * -> detect the location of the difference
 * -> see which function it was made inside of
 * == if it wasn't made inside a function, make no change
 * == otherwise, make a dump with [string fnname, int fnidx, bool prv/pub] for the diff tool
 */
async function dll_source_edit_location_dump(dllName, romVer)
{
    if (!(dllName in gDllSourceCache))
        FATAL(`DLL source cache does not contain an entry for: ${dllName}!`);

    let filename = gRootDir + `src/dlls/${dllName}.c`;
    let newSrc = (await fsp.readFile(filename)).toString();

    newSrc = remove_c_comments_from_src(newSrc);

    let info = gDllSourceCache[dllName][romVer];

    let diffIdx;
    {
        let o_len = info.src.length;
        let n_len = newSrc.length;

        let len = Math.min(o_len, n_len);

        let i = 0;
        for (; i < len; i++)
        {
            let o_c = info.src[i];
            let n_c = newSrc[i];

            if (o_c !== n_c)
                //# Break on first difference
                break;
        }

        diffIdx = i;
    }

    //- Find which function the difference occurred in, if any
    {
        let found = false;

        let fidx  = -1;
        let fname = "";

        for (let [idx, f] of info.fns.entries())
        {
            if (diffIdx >= f.start && diffIdx <= f.end)
            {
                //- Found!
                found = true;

                //# Update cached values
                gDllCacheLastInfo.dll   = dllName;
                gDllCacheLastInfo.fidx  = idx;
                gDllCacheLastInfo.fname = f.name;
            }
        }

        if (dllName === gDllCacheLastInfo.dll)
        {
            fidx  = gDllCacheLastInfo.fidx;
            fname = gDllCacheLastInfo.fname;
        }

        //- If found function changed, dump
        //# If not found, we don't dump. This is fine; it won't update the diff either.
        const dumppath = gCurrDir + `watches/_curr_dll_fn_${romVer}.txt`;
        if (found || fname !== "")
        {
            //- Read previously calculated function dumps
            //# Read binary offset info
            let res = "";
            {
                res += `${dllName}`
                res += `\n${fname}`;

                let vani_info_fn = gRootDir + `expected/${romVer}/dlls/${dllName}_fndump.txt`;
                let cust_info_fn = gRootDir +    `build/${romVer}/dlls/${dllName}_fndump.txt`;

                //= Neither of these should happen, we can just quit cause it makes no sense
                //= for these to be missing after the user triggers a build of this dll
                if (!fs.existsSync(vani_info_fn) || !fs.existsSync(cust_info_fn))
                {
                    log(`[ERR]: The necessary fndump files are missing for: ${dllName}!`);
                    return false;
                }

                let vani_info = (await fsp.readFile(vani_info_fn)).toString().trim().split(/\r?\n/g);
                let cust_info = (await fsp.readFile(cust_info_fn)).toString().trim().split(/\r?\n/g);

                if (vani_info.length !== cust_info.length || vani_info.length !== info.fns.length)
                {
                    //- We have a length mismatch! We cannot continue!
                    log(`[ERR]: #fns mismatch between dumps for: ${romVer}/${dllName}! (${vani_info.length} v ${cust_info.length} v ${info.fns.length}) Aborting info dump!`);

                    return false;
                }

                //# info: NAME OFFSET SIZE

                res += `\nvani: ${vani_info[fidx]}`;
                res += `\ncust: ${cust_info[fidx]}`;
                res += `\n${fidx+1} ${info.fns.length}`;
            }

            //- Dump it
            await fsp.writeFile(dumppath, res);
        }
        else
        {
            //- Touch the file, but don't modify it

            /**
             * TODO: Actually find the range of the LAST USED function, and update
             * This is needed if we change data, and shift the offset of a function
             * currently shown in the diff window.
             * The touch will update it, but the offsets won't be updated in the file,
             * so we will see a bunch of diffs in the window until we go into a function
             * and trigger a watch change from there.
             */

            let now = new Date();
            await fsp.utimes(dumppath, now, now);

            // log(`[DBG]: Changed function not found!`);
            // log(`diffIdx: ${diffIdx}`);
            // log(`info.fns: ${JSON.stringify(info.fns, null, 2)}`);
        }
    }

    return true;
}

function buf_cstr_to_str(inBuf)
{
    let str = [];

    for (let i = 0; i < inBuf.byteLength && inBuf.readUint8(i) !== 0; i++)
        str.push(String.fromCharCode(inBuf.readUint8(i)));

    return str.join("");
}

// function buf_str_to_cstr(str, outBuf)
// {

// }

/**
 * symbolRef type pseudo enum
 */
const SR_TYPE = {
    PTR:  0,
    JUMP: 1,
    HI:   2,
    LO:   3,
};

function new_symbolRef(offset, srType)
{
    return (offset & 0xFFFF) | srType;
}

/**
 *
 * @param {Buffer} elf
 */
function DBG_elf_printSectionHeaders(elf)
{
    {
        // [elf.h]
        // typedef struct {
        // 0x00
        //     uint8_t    e_ident[16];
        // 0x10
        //     uint16_t   e_type;
        //     uint16_t   e_machine;
        //     uint32_t   e_version;
        // 0x18
        //     Elf32_Addr e_entry;
        //     Elf32_Off  e_phoff;
        // 0x20
        //     Elf32_Off  e_shoff;
        //     uint32_t   e_flags;
        //     uint16_t   e_ehsize;
        //     uint16_t   e_phentsize;
        //     uint16_t   e_phnum;
        //     uint16_t   e_shentsize;
        // 0x30
        //     uint16_t   e_shnum;
        //     uint16_t   e_shstrndx;
        // 0x34
        //  } Elf32_Ehdr;

        // typedef struct {
        // 0x00
        //     uint32_t   sh_name;
        //     uint32_t   sh_type;
        //     uint32_t   sh_flags;
        //     Elf32_Addr sh_addr;
        // 0x10
        //     Elf32_Off  sh_offset;
        //     uint32_t   sh_size;
        //     uint32_t   sh_link;
        //     uint32_t   sh_info;
        // 0x20
        //     uint32_t   sh_addralign;
        //     uint32_t   sh_entsize;
        // 0x28
        //  } Elf32_Shdr;

        //  typedef struct {
        // 0x00
        //     uint32_t   st_name;
        //     Elf32_Addr st_value;
        // 0x08
        //     uint32_t   st_size;
        // 0x0C
        //     uint8_t    st_info;
        //     uint8_t    st_other;
        // 0x0E
        //     uint16_t   st_shndx;
        // 0x10
        //  } Elf32_Sym;

        //  typedef struct {
        //     Elf32_Addr r_offset;
        //     uint32_t   r_info;
        // 0x08
        //  } Elf32_Rel;

        // print section headers

        let shdrs      = 0 + elf.readUint32BE(0x20);
        let shnum      = 0 + elf.readUint16BE(0x30);
        let shstrndx   = 0 + elf.readUint16BE(0x32);

        let locStrings = shdrs + (shstrndx * 0x28) + 0;

        for (let i = 0; i < shnum; i++)
        {
            let offset = i * 0x28; // sizeof(Elf32_Shdr) : size of section header

            let loc = shdrs + offset;

            let sectionNameIdx = elf.readUint32BE(loc);

            let nameOffset = elf.readUint32BE(locStrings + 0x10) + sectionNameIdx;

            let nameBuf = Buffer.alloc(0x200).fill(0); // enough to fit all names pretty much

            let j = nameOffset;

            while (true)
            {
                let byte = elf.readUint8(j);
                if (byte === 0)
                    break;

                nameBuf.writeUInt8(byte, j - nameOffset);

                j++;
            }

            console.log(nameBuf.toString());
        }
    }
}

/**
 * When a string is in the .strtab section (from e.g. .symtab)
 *
 * @param {Buffer} elf
 * @param {string} st_name
 * @returns
 */
function elf_get_string_strtab(elf, st_name)
{
    // let shdrs      = 0 + elf.readUint32BE(0x20);
    // let shstrndx   = 0 + elf.readUint16BE(0x32);

    let sections = elf_get_sections(elf, [".strtab"]);

    if (!sections._strtab)
    {
        //# Could not find name section
        return "";
    }

    let nameOffset = sections._strtab.loc + st_name;

    let nameBuf = Buffer.alloc(0x200).fill(0); // enough to fit all names pretty much

    let j = nameOffset;

    while (true)
    {
        let byte = elf.readUint8(j);
        if (byte === 0)
            break;

        nameBuf.writeUInt8(byte, j - nameOffset);

        j++;
    }

    return nameBuf.slice(0, j - nameOffset).toString();
}

/**
 * When a string is in the .shstrtab section (from e.g. elfSectionHeaders)
 * @param {Buffer} elf
 * @param {string} st_name
 * @returns
 */
function elf_get_string_shstrtab(elf, st_name)
{
    let shdrs      = 0 + elf.readUint32BE(0x20);
    let shstrndx   = 0 + elf.readUint16BE(0x32);

    let locStrings = shdrs + (shstrndx * 0x28) + 0;

    let nameOffset = elf.readUint32BE(locStrings + 0x10) + st_name;

    let nameBuf = Buffer.alloc(0x200).fill(0); // enough to fit all names pretty much

    let j = nameOffset;

    while (true)
    {
        let byte = elf.readUint8(j);
        if (byte === 0)
            break;

        nameBuf.writeUInt8(byte, j - nameOffset);

        j++;
    }

    return nameBuf.slice(0, j - nameOffset).toString();
}

/**
 *
 * @param {Buffer}   elf
 * @param {string[]} sectionNameArr
 * @returns {Record<string, any>}
 */
function elf_get_sections(elf, sectionNameArr)
{
    let shdrs      = 0 + elf.readUint32BE(0x20);
    let shnum      = 0 + elf.readUint16BE(0x30);
    let shstrndx   = 0 + elf.readUint16BE(0x32);

    let locStrings = shdrs + (shstrndx * 0x28) + 0;

    let os = [];

    for (let i = 0; i < shnum; i++)
    {
        let offset = i * 0x28; // sizeof(Elf32_Shdr) : size of section header

        let loc = shdrs + offset;

        let sectionNameIdx = elf.readUint32BE(loc);

        let nameOffset = elf.readUint32BE(locStrings + 0x10) + sectionNameIdx;

        let nameBuf = Buffer.alloc(0x200).fill(0); // enough to fit all names pretty much

        let j = nameOffset;

        while (true)
        {
            let byte = elf.readUint8(j);
            if (byte === 0)
                break;

            nameBuf.writeUInt8(byte, j - nameOffset);

            j++;
        }

        let name = nameBuf.slice(0, j - nameOffset).toString();

        os.push({
            name,
            loc:   elf.readUint32BE(loc + 0x10),
            size:  elf.readUint32BE(loc + 0x14),
            shndx: i,
        });
    }

    //- Now only return info for the sections we requested
    //# If a section isn't found, return `null` for it

    let out = {};

    for (let sn of sectionNameArr)
    {
        let found = false;

        for (let o of os)
        {
            if (sn === o.name)
            {
                found = true;
                //# Replace "." with _ (e.g. .rel.data -> _rel_data)
                out[sn.replace(/\./g, "_")] = o;

                break;
            }
        }

        if (!found)
            //# Replace "." with _ (e.g. .rel.data -> _rel_data)
            out[sn.replace(/\./g, "_")] = null;
    }

    return out;
}

/**
 *
 * @param {Buffer}   elf
 * @param {string[]} symNameArr
 * @returns {Record<string, any>}
 */
function elf_get_syms(elf, symNameArr)
{
    let sections = elf_get_sections(elf, [".symtab"]);

    if (!sections._symtab)
    {
        //# Could not find symbol table. Return an object where everything is null

        let out = {};

        for (let symName of symNameArr)
            out[symName] = null;

        return out;
    }

    let elementSize = 0x10;

    let out = {};

    for (let i = 0; i < sections._symtab.size / elementSize; i++)
    {
        let base = sections._symtab.loc + (i * elementSize);

        let st_name = elf.readUint32BE(base + 0x00);

        let name = elf_get_string_strtab(elf, st_name);

        //# Replace "." with _ (e.g. .rel.data -> _rel_data)
        out[name.replace(/\./g, "_")] =
            symNameArr.includes(name)
            ?
            {
                name,
                st_value: elf.readUint32BE(base + 0x04),
                st_size:  elf.readUint32BE(base + 0x08),
                st_info:  elf.readUint8(   base + 0x0C),
                st_other: elf.readUint8(   base + 0x0D),
                st_shndx: elf.readUint16BE(base + 0x0E),
                shndx:    i,
            }
            :
            null;
    }

    return out;
}

/**
 * Read a (decompressed) DLL file and get information about its structure
 * @param {string} dll name of the DLL
 * @param {string} romVer 
 * @param {boolean} vanilla if true, fetch from the "expected" folder. Else, from the "build" folder.
 */
async function dll_get_structure(dll, romVer, vanilla=false)
{
    // await update_rom_version(romVer);

    // let syscallIdx = gSyscallIdxMap_rv[romVer][dll];

    //- Fetch the encryption key needed to encrypt symbolRefs with bootcode
    // let encryptionKey = gBaseroms[romVer].readUint16BE(0x40 + (syscallIdx * 4) + 2);

    let filepath = vanilla
        //# vani
        ? `expected/${romVer}/dlls/${dll}.bin`
        //# cust
        : `build/${romVer}/dlls/${dll}bin`;

    let b = await fsp.readFile(filepath);

    //- Calculate checksum
    // let checksum = dll_get_checksum(b.slice(0x10));
    // b.writeUint32BE(b.readUint32BE(0x00) ^ checksum[0], 0x00);
    // b.writeUint32BE(b.readUint32BE(0x08) ^ checksum[1], 0x08);

    {
        let sizes =
        {
            text:      b.readUint16BE(0x00) * 0x10,
            data:      b.readUint16BE(0x04) * 0x10,
            rodata:    b.readUint16BE(0x02) * 0x10,
            bss:       b.readUint16BE(0x06) * 0x10,
            name:      b.readUint8(0x0E),
            //# number of functions
            functions: b.readUint16BE(0x08),
            //# number of symrefs
            symrefs:   b.readUint16BE(0x0A),
        };

        let offsets;
        {
            let size_preheader = 0x10;
            let size_header    = 0x24;
            let size_funcptrs  = (b.readUint16BE(0x08) + 1) * 4;
            let size_symrefs   = b.readUInt16BE(0x0A) * 2;
            let size_dllname   = b.readUInt8(0x0E);

            let text = size_preheader
                     + size_header
                     + size_funcptrs
                     + ALIGN(size_dllname, 4)
                     + size_symrefs;

            text = ALIGN(text, 0x10);

            let rodata = text + sizes.text;
            let data   = rodata + sizes.rodata;

            offsets =
            {
                text,
                data,
                rodata,
                name:         size_preheader + size_header + size_funcptrs,
                symrefs:      size_preheader + size_header + size_funcptrs + ALIGN(size_dllname, 4),
                callrouter:   0x10,
                syscallidx:   0x2C,
                calltableidx: 0x2E,
                pubfnarr:     0x38,
            };
        }

        return {
            offsets,
            sizes,
        };
    }
}

/**
 * Convert an ELF .o file into the final format that Tooie expects.
 *
 * Process:
 * ?. Get the syscallIdx for the DLL. This is needed for bootcode encryption
 * ?. Generate needed symbolRefs from the ELF info and encrypt them with appropriate bootcode
 * ?. Fill in rest of header: add space for .text addr and all public function pointers, and for the name of the DLL, padded to 4, and the symbolrefs.
 * ?. Generate header placeholder (does NOT include the "16 bytes with 82 at the end"; that's the preheader). Pad the whole thing to 16.
 * ?. Combine header with DLL contents
 * ?. Compress header+DLL with matching gzip compression
 * ?. Generate preheader and encrypt it
 * ?. Combine preheader with compressed contents
 * -> Done!
 *
 * @param {string} dll         name of dll, as a string. e.g. "cosection"
 * @param {string} objFilePath the path to the .o file to use as input
 */
async function dll_process(dll, objFilePath, romVer, toSkip=false)
{
    // output path
    const binFilePath = objFilePath.replace(/\.o$/, ".bin");

    const pubFnDumpPath = objFilePath.replace(/\.o$/, "_pubfndump.txt");

    if (!(dll in gSyscallIdxMap_rv[romVer]))
        FATAL(`DLL [${dll}] not in curr rom version [${romVer}]`);

    let syscallIdx = gSyscallIdxMap_rv[romVer][dll];

    //- Fetch the encryption key needed to encrypt symbolRefs with bootcode
    let encryptionKey = gBaseroms[romVer].readUint16BE(0x40 + (syscallIdx * 4) + 2);
    // console.log(encryptionKey.hex())

    //- Prepare to read from the ELF .o file

    /** @type {Buffer} */
    let elf = await fsp.readFile(objFilePath);

    let preheader = Buffer.alloc(0x10).fill(0);
    //# This is all written in-game, we don't need to touch it
    let header    = Buffer.alloc(0x28).fill(0);

    preheader.writeUint8(dll.length + 1, 0xE); // length of name including null byte
    preheader.writeUint8(0x82,           0xF); // constant (bitfield?) identical for all DLLs





    // DBG_elf_printSectionHeaders(elf);




    let sections = elf_get_sections(elf, [
            ".text",     ".rodata",     ".data",     ".bss", ".symtab",
        ".rel.text", ".rel.rodata", ".rel.data", ".rel.bss",
    ]);

    // console.log(sections)


    /**
     * // TODO:
     * To find the locations of all pub functions in a DLL,
     *   1. Find the section header index (shndx) for .text
     *   2. Iterate over all .symtab entries where st_info (u8 @ 0x0C in .symtab entry) == 0x12 (function call?)
     *      Note: You can also find all where st_info == 0x03 (section) to find specifically included sections (.text, .rodata, etc)
     *   3. Check that st_shndx is equal to the value you want the relocation in (.text for function calls, .data for whatever, etc)
     *      Note: External references should have an index of 0, so this will exclude external function calls (and maybe variables too?)
     *   4. This should give you a list of all pub fns. Get st_value (u32 @ 0x04) for the offset of the function from the start (?)
     *
     * // Maybe check if st_size (u32 @ 0x08) is 0 as well. This is guaranteed to be 0 for external function calls.
     * //   st_shndx might not be zero if you're calling something within the same DLL! Verify this!
     *
     *
     */
    let pubFns = [];
    {
        //- Finding pub fns
        {
            if (sections._text && sections._symtab)
            {
                const symtabEntrySize = 0x10;

                // let { text: { shndx } } = sections;

                // let nSyms = sections._symtab.size;
                let nSyms = sections._symtab.size / symtabEntrySize;

                // console.log(nSyms)

                for (let i = 0; i < nSyms; i++)
                {
                    let symloc = sections._symtab.loc + (i * symtabEntrySize);

                    let st_name   = elf.readUint32BE(symloc + 0x00);
                    let st_value  = elf.readUint32BE(symloc + 0x04);
                    let st_size   = elf.readUint32BE(symloc + 0x08);
                    let st_info   = elf.readUint8(   symloc + 0x0C);
                    let st_shndx  = elf.readUint16BE(symloc + 0x0E);

                    if (st_info === 0x12 && st_size > 0 && st_shndx === sections._text.shndx)
                    {
                        //- Found a pub fn!
                        pubFns.push({
                            name: elf_get_string_strtab(elf, st_name),
                            loc:  st_value,
                            size: st_size,
                        });
                    }
                }

                //# Sort pub functions by offset
                pubFns.sort((a, b) => a.loc - b.loc);

                //!
                DEBUG_LOG(pubFns)

                //- Pub functions all found!

                //= We can't dump pub fns to disk yet, because we haven't determined the header size

            }
        }
    }

    /** @type {number[]} */
    let symbolRefs = [];
    {
        //- Finding symbol refs

        /**
         * MIPS relocation types (https://irix7.com/techpubs/007-4658-001.pdf @ p45-47)
         *
         *   2: ptr. used by:
         *      > switch offsets in .rodata (and relocations in .rel.rodata)
         *      > hardcoded pointers stored in .data (with relocations in .rel.data)
         *   4: jump targets. used by:
         *      > local jumps
         *   5: addr hi.
         *   6: addr lo.
         */

        const elementSize = 0x08;

        //# The order of the sections matter. Rare did it in this order.
        let sectionsWithRelocs = [ "_text", "_rodata", "_data", "_bss" ];

        let pubFnNames = pubFns.map(e => e.name);

        let symbols = elf_get_syms(elf,
            [
                ...sectionsWithRelocs.map(x => x.replace(/^_/g, ".")),
                ...pubFnNames,
            ]
        );

        //- We only look at relocations that are in sections that interest us
        //# This avoids looking at e.g. external function calls that the linker can handle
        let validSectionIds = [];
        {
            if (symbols?._text?.shndx)   validSectionIds.push(symbols._text.shndx);
            if (symbols?._rodata?.shndx) validSectionIds.push(symbols._rodata.shndx);
            if (symbols?._data?.shndx)   validSectionIds.push(symbols._data.shndx);
            if (symbols?._bss?.shndx)    validSectionIds.push(symbols._bss.shndx);

            //- We also need to process internal relocations for any pub funcs
            for (let name of pubFnNames)
                validSectionIds.push(symbols[name].shndx);
        }

        //- Needed to calculate the offset after [objcopy]
        let runningSectionSize = 0;

        for (let swr of sectionsWithRelocs)
        {
            let rel_swr = "_rel" + swr;

            if (sections[rel_swr] && sections._text)
            {
                for (let i = 0; i < sections[rel_swr].size / elementSize; i++)
                {
                    let r_offset = elf.readUint32BE(sections[rel_swr].loc + (i * elementSize) + 0x00);
                    let r_info   = elf.readUint32BE(sections[rel_swr].loc + (i * elementSize) + 0x04);

                    //# Location from start of final processed binary
                    let abs_offset = runningSectionSize + r_offset;

                    if (!validSectionIds.includes(r_info >> 8))
                        //# Ignore, go to next
                        continue;

                    //- Convert ELF MIPS "relocation type" (0-37) to tooie's "relocation type" (0-3)

                    switch (r_info & 0xFF)
                    {
                        case 2: symbolRefs.push(new_symbolRef(abs_offset, SR_TYPE.PTR));  break;
                        case 4: symbolRefs.push(new_symbolRef(abs_offset, SR_TYPE.JUMP)); break;
                        case 5: symbolRefs.push(new_symbolRef(abs_offset, SR_TYPE.HI));   break;
                        case 6: symbolRefs.push(new_symbolRef(abs_offset, SR_TYPE.LO));   break;
                        //! Not recognised! Ignore without doing anything
                        default: break;
                    }
                }

                runningSectionSize += sections[swr].size;
            }
        }

        //- Encrypt the symbolRefs
        symbolRefs = symbolRefs.map(r => r ^ encryptionKey);

        DEBUG_LOG(symbolRefs.map(r => r.hex()))
    }

    //- Write some preheader data
    //# Write section sizes
    preheader.writeUint16BE(sections._text   ? ~~(sections._text.size   / 0x10) : 0, 0x0);
    preheader.writeUint16BE(sections._rodata ? ~~(sections._rodata.size / 0x10) : 0, 0x2);
    preheader.writeUint16BE(sections._data   ? ~~(sections._data.size   / 0x10) : 0, 0x4);
    preheader.writeUint16BE(sections._bss    ? ~~(sections._bss.size    / 0x10) : 0, 0x6);
    //# Write numFunctions
    preheader.writeUint16BE(pubFns.length, 0x8);
    //# Write numSymbolRefs
    preheader.writeUint16BE(symbolRefs.length, 0xA);
    //# Write sizeData1? not sure what this is
    preheader.writeUint16BE(0, 0xC); //! always 0?

    //- Allocate and write the final buffers: [function pointer, dll name, symbolref]
    //# They should be appended to the header in the same order
    let buf_functions = Buffer.alloc(pubFns.length * 4).fill(0);
    {
        for (let [i, p] of pubFns.entries())
            buf_functions.writeUint32BE(p.loc, i * 4);
    }
    let buf_dllname = Buffer.alloc(ALIGN(dll.length + 1, 0x04)).fill(0);
    {
        for (let i = 0; i < dll.length; i++)
            buf_dllname.writeUInt8(dll.charCodeAt(i), i);
    }
    let buf_symbolRefs = Buffer.alloc(symbolRefs.length * 2).fill(0);
    {
        //! Do not align this. Only align (to 0x10) after combining it with the header etc.

        for (let [i, sr] of symbolRefs.entries())
            buf_symbolRefs.writeUint16BE(sr, i * 2);
    }

    let finalBinary; //# size is known at this point, but who cares, dont alloc yet
    {
        //- Run elf through the linker, objcopy it, then read the result

        let out = `build/${romVer}/dlls/${dll}.out`;

        {
            if (!toSkip)
            {
                let path_dllSyms = `ver/${romVer}/syms/DLL.txt`;

                let LINKER_INCLUDES = "";
                LINKER_INCLUDES += ` -T misc/linkerscript/dll.ld`;
                LINKER_INCLUDES += ` -T ver/${romVer}/syms/undefined.txt`;
                LINKER_INCLUDES += ` -T ver/${romVer}/syms/auto_fns.txt`;
                LINKER_INCLUDES += ` -T ver/${romVer}/syms/auto_vars.txt`;

                /**
                 * A very hacky way of excluding call table symbols from the
                 * DLLs to which they belong.
                 * This, or some other solution like writing out a file that
                 * excludes its own symbols, is required for matching.
                 */
                LINKER_INCLUDES += " " + (await fsp.readFile(path_dllSyms))
                    .toString()
                    .trim()
                    .split(/\r?\n/)
                    .filter(line => !line.startsWith(`DLL_${dll}_`))
                    // .map(line => {
                    //     let s = line.split(/\s+/g);
                    //     return `--defsym=${s[0]}=${s[2].substr(0, 10)}`;
                    // })
                    .map(line => "--defsym=" + line.replace(/[\s;]+/g, ""))
                    .join(" ");
                // LINKER_INCLUDES += ` -T ${path_dllSyms}`;

                let FILE_OBJECT = `build/${romVer}/dlls/${dll}.o`;
                let FILE_LINKED = `build/${romVer}/dlls/${dll}.lpo`;

                await spawn(`mips-linux-gnu-ld ${LINKER_INCLUDES} ${FILE_OBJECT} -o ${FILE_LINKED}`);
                await spawn(`mips-linux-gnu-objcopy -I elf32-tradbigmips -O binary ${FILE_LINKED} ${out}`);
            }
        }

        if (!fs.existsSync(out))
            FATAL(`Build failed: objcopy result missing for: ${dll}`);

        let binary = await fsp.readFile(out);
        {
            //- Fix linking "errors"
            /**
             * We were forced to link at 0x80000000 due to relocation errors, so
             * now we go through and relocate 0x80000000 based pointers (including hi's)
             * to 0x00000000.
             *
             * We can just do this with the symbol refs we have already calculated
             */

            for (let [i, sr] of symbolRefs.entries())
            {
                sr ^= encryptionKey;

                let offset = sr & 0xFFFC;
                let type   = sr & 3;

                switch (type)
                {
                    case SR_TYPE.PTR:
                    {
                        binary.writeUint32BE((binary.readUint32BE(offset) & 0x7FFFFFFF) >>> 0, offset);

                        break;
                    }
                    case SR_TYPE.HI:
                    {
                        offset += 2;

                        binary.writeUint16BE(binary.readUint16BE(offset) & 0x7FFF, offset);

                        break;
                    }
                    default:
                        break;
                }
            }
        }

        //- Combine all sections

        {
            //- Alloc final buffer

            let size_00_preheader  = preheader.byteLength;
            let size_01_header     = header.byteLength;
            let size_02_pubfns     = buf_functions.byteLength;
            let size_03_dllname    = buf_dllname.byteLength;
            let size_04_symbolrefs = buf_symbolRefs.byteLength;

            let size_05_fullheader = size_00_preheader + size_01_header + size_02_pubfns + size_03_dllname + size_04_symbolrefs;
            size_05_fullheader = ALIGN(size_05_fullheader, 0x10);

            // let size_06_binary = (preheader.readUint16BE(0x0) << 4)
            //                    + (preheader.readUint16BE(0x2) << 4)
            //                    + (preheader.readUint16BE(0x4) << 4)
            //                    + (preheader.readUint16BE(0x6) << 4);
            let size_06_binary = binary.byteLength;

            let fullSize = size_05_fullheader + size_06_binary;

            finalBinary = Buffer.alloc(fullSize).fill(0);

            //- Write final buffer

            let runningSize = 0;

            preheader     .copy(finalBinary, runningSize, 0); runningSize += size_00_preheader;
            header        .copy(finalBinary, runningSize, 0); runningSize += size_01_header;
            buf_functions .copy(finalBinary, runningSize, 0); runningSize += size_02_pubfns;
            buf_dllname   .copy(finalBinary, runningSize, 0); runningSize += size_03_dllname;
            buf_symbolRefs.copy(finalBinary, runningSize, 0); runningSize += size_04_symbolrefs;

            //# Set directly, cause of padding
            runningSize = size_05_fullheader;

            binary.copy(finalBinary, runningSize, 0);


            //= Write pub func dump - used by diff script to find functions without a .map file
            //# We can do this now because we can calculate the full header size
            {
                //# Deprecated by the MIPS analyser and C source parser
                // if (!toSkip)
                // {
                //     await fsp.writeFile(pubFnDumpPath,
                //         pubFns.map(p => `${p.name} 0x${(p.loc + size_05_fullheader).hex()} 0x${p.size.hex()}`).join("\n")
                //     );
                // }
            }
        }

        if (!toSkip)
        {
            //- Write final buffer out
            await fsp.writeFile(binFilePath, finalBinary);
        }
    }

    return [binFilePath, finalBinary];
}

/**
 * 
 * @param {Buffer} buffer decompressed DLL, with no preheader
 * @returns 
 */
function dll_get_checksum(buffer)
{
    let checksum = [0, 0];
    {
        for (let i = 0; i < buffer.byteLength; i++)
        {
            let byte = buffer.readUint8(i);
            // checksum[0] += byte;
            // checksum[1] ^= byte << (checksum[0] & 0x17);

            //= Safeguard against JS f64 inaccuracies
            checksum[0] = ((checksum[0] + byte) & 0xFFFFFFFF) >>> 0;
            checksum[1] ^= byte << (checksum[0] & 0x17);
        }
    }

    return checksum;
}

/**
 * Encrypt if decrypted, or decrypt if encrypted
 * @param {Buffer|null} rawFile 
 */
async function dll_preheader_encryption_toggle(rawFile=null)
{
    if (!rawFile)
        return ERROR(`Invalid handle, cannot encrypt preheader!`);

    if (rawFile.readUint8(0xF) !== 0x82)
        return ERROR(`Cannot toggle preheader encryption: missing preheader!`);

    //- Calculate checksum
    let checksum = dll_get_checksum(rawFile.slice(0x10));

    rawFile.writeUInt32BE(rawFile.readUint32BE(0x0) ^ checksum[0], 0x0);
    rawFile.writeUInt32BE(rawFile.readUint32BE(0x8) ^ checksum[1], 0x8);
}

/**
 * 
 * @param {zlib.InputType} buf 
 * @param {zlib.ZlibOptions} options 
 * @returns {Promise<Buffer>}
 */
function zlib_deflateRaw_async(buf, options)
{
    return new Promise((resolve, reject) =>
    {
        zlib.deflateRaw(buf, options, (err, res) => err ? reject(err) : resolve(res));
    });
}

/**
 * 
 * @param {zlib.InputType} buf 
 * @param {zlib.ZlibOptions} options 
 * @returns {Promise<Buffer>}
 */
 function zlib_inflateRaw_async(buf, options)
 {
     return new Promise((resolve, reject) =>
     {
         zlib.inflateRaw(buf, options, (err, res) => err ? reject(err) : resolve(res));
     });
 }

/**
 * Give a path to a file a new extension
 * @param {string} fullpath 
 * @param {string} newext 
 * @returns 
 */
function path_replace_ext(fullpath, newext)
{
    let dot = ".";

    if (!newext)
        dot = "";

    return fullpath.replace(/\.[^\.]+$/g, dot + newext.replace(/^\.+/g, ""));
}

/**
 * Dump the zlib window magic for the given DLL.
 * Required to achieve matching compression with pre-1996 zlib!
 * 
 * Pre-1996 zlib had a bug that left garbage bytes over in the
 * window. The bytes that were present in the previously file
 * (in decompressed form) at the offset corresponding to the
 * end of the current file (in decompressed form) must be
 * placed at the end of the window to achieve byte-matching
 * compression.
 * 
 * While it would be fantastic to fetch these bytes directly
 * from the relevant preceding file, and while it CAN be done
 * for a majority of the DLLs in the game, this doesn't seem to
 * be possible for ALL of them, e.g. one of them is "gzreg".
 * We know that some DLLs were removed from retail, since
 * some indices between gzreg and the preceding DLL are skipped
 * over. My theory is that one of these missing DLLs was
 * large enough to leave its garbage data behind past the
 * end of gzreg. Since the file was not included in retail,
 * it is impossible for us to extract its garbage bytes.
 * 
 * So, the second-best way is to use the original DEFLATE
 * streams produced by Rare to determine the magic instead.
 * Kinda hacky and not "pure" in the decomp sense, but we don't
 * want to directly hardcode the needed magic for each DLL
 * (Revo will fo sho beat my ass). Therefore this is what we
 * need to do.
 * 
 * @param {string} romVer 
 * @param {string} dllName 
 * @param {string} dst_magic_fn filename to dump the magic to
 */
async function zlib_window_magic_dump(romVer, dllName, dst_magic_fn)
{
    let vani_cmp_fn = gRootDir + `expected/${romVer}/dlls/${dllName}.dll`;
    let vani_dec_fn = gRootDir + `expected/${romVer}/dlls/${dllName}.bin`;

    let vani_cmp_fn_tmp = gRootDir + `expected/${romVer}/dlls/${dllName}.cmp`;

    /**
     * @param {boolean} result 
     * @returns 
     */
    async function cleanup(result)
    {
        if (fs.existsSync(vani_cmp_fn_tmp))
            await fsp.unlink(vani_cmp_fn_tmp);

        return result;
    }

    if (!fs.existsSync(vani_cmp_fn) || !fs.existsSync(vani_dec_fn))
    {
        ERROR(`Vanilla DLL file [${romVer}/${dllName}] needed for zlib magic but missing, proceeding anyway!`);
        return await cleanup(false);
    }

    //- Copy DEFLATE stream out for infgen
    {
        let tmp = await fsp.readFile(vani_cmp_fn);
        await fsp.writeFile(vani_cmp_fn_tmp, tmp.slice(0x12));
    }

    //- Use infgen to disassemble the stream
    let cmd = gRootDir + `tools/infgen -r ${vani_cmp_fn_tmp}`;

    let output = await spawn(cmd, false, true);

    //- Find the final match line; this is the one relevant for the zlib window bug
    let ig_len  = 0;
    let ig_dist = 0;
    {
        let m = output.match(/\r?\nmatch (\d+) (\d+)(?![\s\S]*\r?\nmatch)/);
        if (m && m.length === 3)
        {
            ig_len  = parseInt(m[1]);
            ig_dist = parseInt(m[2]);
        }
        else
        {
            ERROR(`infgen failed for DLL file [${romVer}/${dllName}], proceeding anyway!`);
            return await cleanup(false);
        }
    }

    let garbage_bytes;
    {
        let dec = await fsp.readFile(vani_dec_fn);

        if (dec.byteLength === 0)
        {
            ERROR(`Vanilla DLL file (dec) [${romVer}/${dllName}] needed for zlib magic but missing, proceeding anyway!`);
            return await cleanup(false);
        }

        let curr  = dec.byteLength - ig_len;
        let start = curr - ig_dist + ig_len;

        //# Amount of available bytes after desired match location
        let remaining = dec.byteLength - start;

        //# Fetch "enough" bytes to reproduce the bug
        let max_limit = 0x30; //# should be enough
        let end = start + Math.min(max_limit, remaining);

        //# Copy
        garbage_bytes = Buffer.alloc(end - start);
        dec.copy(garbage_bytes, 0, start, end);
    }

    //# Dump it
    await fsp.writeFile(dst_magic_fn, garbage_bytes);

    return await cleanup(true);
}

async function zlib_window_magic_get(romVer, dllName)
{
    let dst_magic_fn = gRootDir + `expected/${romVer}/dlls/${dllName}.zlibmagic`;

    //- Dump if we don't have it yet
    if (!fs.existsSync(dst_magic_fn))
        if (!await zlib_window_magic_dump(romVer, dllName, dst_magic_fn))
            //# Could not dump, ignore
            return null;

    let garbage_bytes = await fsp.readFile(dst_magic_fn);

    return new Uint8Array(garbage_bytes.buffer);
}

/**
 * Pack a raw dll file with the compression and encryption bs that Tooie expects.
 *
 * @param {string} dllName
 * @param {string} rawFilePath
 * @param {Buffer} rawFile the raw dll file (already compiled and linked and everything)
 */
async function dll_compress(rawFilePath, dllName, romVer, rawFile=null, toSkip=false)
{
    if (!rawFile)
        rawFile = await fsp.readFile(rawFilePath);

    if (rawFile.readUint8(0xF) !== 0x82)
        FATAL(`Cannot package DLL: missing preheader!`);

    //# Dump just for fun
    let bodyWithPreOutPath  = rawFilePath + ".raw";

    let bodyOutPath  = path_replace_ext(rawFilePath, ".body");
    let gzInPath     = path_replace_ext(rawFilePath, ".nopre");
    let gzOutPath    = path_replace_ext(rawFilePath, ".gz");
    let finalOutPath = path_replace_ext(rawFilePath, ".dll");

    let finalOut;

    //- Compress
    {
        /** @type {Buffer} */
        let gzOut;

        /**
         * There's no real difference.
         *
         * The 25-year old zlib binary and the node.js implementation both seem
         * to produce identical outputs. Choose whichever you prefer.
         */
        const USE_ZLIB_BINARY = false;

        if (USE_ZLIB_BINARY)
        {
            // const bin = `${gRootDir}tools/mcompress/bin/minigzip`;
            const bin = `${gRootDir}tools/mcompress/bin/mcompress`;

            if (!toSkip)
            {
                // if (!fs.existsSync(bin))
                //     FATAL(`Couldn't find [minigzip] (zlib:1.0.6) binary! Either provide it, or switch to using internal zlib.`);

                //# zlib binary overwrites file completely, so make a copy
                await fsp.writeFile(gzInPath, rawFile.slice(0x10));

                // await spawn(`${bin} ${path.resolve(gzInPath)}`);
                await spawn(`${bin} -l 9 -g bt -i ${path.resolve(gzInPath)} -o ${path.resolve(gzOutPath)}`);

                // console.log(out)

                // if (!fs.existsSync(gzOutPath + ".gz"))
                //     FATAL(`Could not find: ${gzOutPath}.gz`);

                //# zlib binary appends .gz to the end of everything, cut it
                // await fsp.rename(gzOutPath + ".gz", gzOutPath);
            }

            gzOut = await fsp.readFile(gzOutPath);
        }
        else
        {
            //# Use raw JS zlib deflate routine (we can easily tweak it)
            gzOut = Buffer.from(
                pako.deflateRaw(
                    new Uint8Array(rawFile.slice(0x10)),
                    { level: 9 },
                    await zlib_window_magic_get(romVer, dllName),
                ).buffer
            );
        }

        //# Cleanup
        {
            if (fs.existsSync(gzInPath))
                await fsp.unlink(gzInPath);

            if (fs.existsSync(gzOutPath))
                await fsp.unlink(gzOutPath);
        }

        //= Postprocess the zlib-compressed file
        {
            //# Trim the file buffer appropriately

            if (USE_ZLIB_BINARY)
            {
                // /**
                //  * The zlib binary [minigzip] prepends a header and appends
                //  * a checksum. We need to trim both off, and also prepend
                //  * the 2-byte decompressed size value.
                //  */

                // let start = 0x08;
                // //# Where the checksum starts. We need to zero this area.
                // let tail  = gzOut.byteLength - 8;
                // let end   = tail;

                // //# Calculate padding requirements
                // while (end % 4)
                //     end++;

                // //# Write decompressed size (2 bytes)
                // {
                //     let decompressedSize = (ALIGN(rawFile.byteLength, 0x10) - 0x10) / 0x10;
                //     gzOut.writeUint16BE(decompressedSize, start);
                // }

                // for (let i = tail; i < end; i++)
                //     //# Zero-fill
                //     gzOut.writeUint8(0, i);

                // //# Perform final slice
                // gzOut = gzOut.slice(start, end);
            }
            else
            {
                /**
                 * node:zlib.deflateRawSync() only returns the stream, no extraneous
                 * checksums or headers, so we don't need to trim it.
                 *
                 * We just need to prepend the decompressed size.
                 */

                let decompressedSizeLength = 0x02;

                let start = 0;
                let end = gzOut.byteLength + decompressedSizeLength;

                //# Calculate padding requirements
                while (end % 4)
                    end++;

                //# Alloc extended buffer. Needs to be extended for extra padding.
                let newBuf = Buffer.alloc(end).fill(0);

                //# Write decompressed size (2 bytes)
                {
                    let decompressedSize = (ALIGN(rawFile.byteLength, 0x10) - 0x10) / 0x10;
                    newBuf.writeUint16BE(decompressedSize, start);
                }

                //# Copy across into new buffer
                gzOut.slice(start).copy(newBuf, decompressedSizeLength);

                //# Store reference
                gzOut = newBuf;
            }
        }

        //- Get ready to splice on encrypted preheader

        finalOut = Buffer.alloc(gzOut.byteLength + 0x10).fill(0);

        {
            rawFile.copy(finalOut, 0, 0, 0x10);
            gzOut  .copy(finalOut, 0x10, 0);
        }

        if (!toSkip)
        {
            //- Write final
            await fsp.writeFile(finalOutPath, finalOut);
        }
    }

    return [ finalOutPath, finalOut ];
}


var gRomVer;
/** @type {Record<string, Buffer>} */
var gBaseroms = {};

/**
 *
 * @param {string} newRomVer
 */
async function update_rom_version(newRomVer)
{
    //- Get version for ROM you want to work with
    {
        let romVerStr = newRomVer;
        if (!(allRomVers.includes(romVerStr)))
            FATAL("Invalid rom version (usa/jpn/eur/aus)");

        gRomVer = romVerStr;
    }

    //- Load the baserom
    if (!gBaseroms[gRomVer])
    {
        let baseromPath = gRootDir + `ver/${gRomVer}/baserom.z64`;

        if (!fs.existsSync(baseromPath))
            FATAL(`No baserom for the curr rom version: ${baseromPath}`);

        gBaseroms[gRomVer] = await fsp.readFile(baseromPath);
    }

    //- Initialise the syscall map
    await init_gSyscallIdx_map(gRomVer);
}

/**
 * Parses the [include/dlls.h] file and generates the linker symbols
 * needed for all DLLs declarations automatically.
 */
async function HELPER_parse_out_dll_linker_symbols()
{
    const fn_dlls_h = gRootDir + `include/dlls.h`;

    const dlls_h = (await fsp.readFile(fn_dlls_h)).toString();

    for (let romVer of allRomVers)
    {
        if (!(romVer in VERSION_CONSTANTS.DLL_CALL_TBL))
            FATAL(`DLL_CALL_TBL constant missing for romVer: ${romVer}`);

        await init_gCallTableOffset_map(romVer);

        //# The linker requires it to exist at least, so we ensure it
        let outpath = gRootDir + `ver/${romVer}/syms/DLL.txt`;
        ensureFile(outpath);

        const dllCallTblStart = VERSION_CONSTANTS.DLL_CALL_TBL[romVer] >>> 0;

        {
            /**
             * The name of the currently recognised DLL
             */
            let currDllName = "";
            /**
             * The current call table address we are at
             */
            let currCtoAddr = 0x00000000;

            /**
             * Arbitrary, but large enough to cover all symbols
             */
            const lookahead = 100;

            let waiting = false;

            let symbols = [];

            for (let i = 0; i < dlls_h.length; i++)
            {
                if (dlls_h.substr(i, 5) === "/* $ ")
                {
                    //# New DLL, initialise vars
                    currDllName = dlls_h.substr(i + 5, lookahead).split(/\s+/g)[0];
                    currCtoAddr = (dllCallTblStart + (gCallTableOffsetMap[currDllName] * 8)) >>> 0;

                    //# We +8 whenever we encounter a declaration, so prime for the first one by a -8
                    currCtoAddr -= 8;

                    waiting = false;

                    continue;
                }

                if (dlls_h.substr(i, 4) === "\n/*@")
                {
                    //# New public function, initialise
                    let magic = dlls_h.substr(i + 4, lookahead).split(/\s+/g)[0];

                    //# Grab the character corresponding to the current build version
                    let magicCharForCurrVer = magic.substr(VERSION_CONSTANTS.BUILD_IDX[romVer], 1);

                    if (magicCharForCurrVer === "-")
                        //# Doesn't apply, skip
                        waiting = false;

                    else if (magicCharForCurrVer === "o")
                    {
                        //# Applies, now wait until we find the symbol
                        waiting = true;

                        currCtoAddr += 8;
                    }

                    continue;
                }

                if (waiting && dlls_h.substr(i, lookahead * 2).startsWith(`DLL_${currDllName}_`))
                {
                    let symbol = dlls_h.substr(i, lookahead * 2).split(/[\s\r\n(<]+/g)[0];

                    symbols.push({
                        symbol,
                        addr: currCtoAddr,
                    });

                    //# Prime for the next declaration for the same DLL
                    waiting = false;
                }
            }

            //- Write all symbols to file
            {
                let lengthOfLongestSymbol = symbols.reduce((acc, e) => Math.max(acc, e.symbol.length), 0);
                let data = symbols.map(e => `${e.symbol.padEnd(lengthOfLongestSymbol + 2, " ")} = 0x${e.addr.toString(16).toUpperCase()};`)

                await fsp.writeFile(outpath, data.join("\n"));
            }
        }
    }
}

/**
 * Parse the [include/functions.h] and [include/variables.h]
 * files and parse out magic comments and declarations into
 * linker symbols.
 *
 * TODO: Also use version recognition and try and automatically
 * generate equivalent symbols for other versions through
 * baserom analysis.
 *
 * This only needs to be repeated if one of the headers
 * is detected to have been modified since the last
 * time this was run.
 */
async function HELPER_parse_out_static_linker_symbols()
{
    let files =
    [
        "include/functions.h",
        "include/variables.h",
    ];

    let outputs =
    [
        "auto_fns.txt",
        "auto_vars.txt",
    ];

    if (files.length !== outputs.length)
        FATAL("[parse out syms] Length mismatch");

    for (let i = 0; i < files.length; i++)
    {
        let MODE_FUNC = i === 0;
        let MODE_VARS = i === 1;

        let file    = files[i];
        let outname = outputs[i];

        let fn_header = gRootDir + file;
        let header    = (await fsp.readFile(fn_header)).toString();

        for (let [romIdx, romVer] of allRomVers.entries())
        {
            let outpath = gRootDir + `ver/${romVer}/syms/${outname}`;
            ensureFile(outpath);

            //# Check if file was modified
            if ((await fsp.stat(outpath)).mtimeMs >= (await fsp.stat(fn_header)).mtimeMs)
                //# Header file was not modified since last time, skip
                continue;

            //- Parse out the addresses now

            /**
             * Arbitrary, but large enough to cover all symbols and all rom version vectors from < to >: "<0x, 0x, 0x, 0x>"
             * Increase if we add more rom versions later
             */
            const lookahead = 120;

            let waiting = false;

            let symbols = [];

            let currAddress = "";

            for (let i = 0; i < header.length; i++)
            {
                if (header.substr(i, 5) === "/*<0x")
                {
                    //# Parse out all addresses <usa,jpn,eur,aus>
                    //# We try and leave support for future versions

                    let segment = header.substr(i + 2, lookahead);

                    let m = segment.match(/^<(.+?)>/);
                    if (!m || m.length < 2)
                        FATAL(`[parse out syms] Detected sym comment, but could not parse!`);

                    //# Multiple matches may occur, just take the first
                    let vector = m[1].split(/, ?/g).map(e => e.trim());

                    if (vector.length < allRomVers.length)
                        FATAL(`[parse out syms] Sym comment doesn't cover enough versions!`);

                    //# Store until we see the name token
                    currAddress = vector[romIdx];
                    //# Wait for name
                    waiting = true;

                    continue;
                }

                if (!waiting)
                    continue;

                let next = header.substr(i, lookahead * 2);
                {
                    if (MODE_FUNC)
                    {
                        //# Don't bother to test first, just go for the match
                        let m = next.match(/^([a-z0-9_]+?)\s*\(/im);
                        if (m && m.length >= 2)
                        {
                            //# Found start of name token, process it

                            let symbol = m[1];

                            symbols.push({
                                symbol,
                                addr: currAddress.replace(/^0x/g, ""),
                            });

                            currAddress = "";

                            //# Prime for the next comment
                            waiting = false;
                        }
                    }
                    else if (MODE_VARS)
                    {
                        //# Don't bother to test first, just go for the match
                        let m = next.match(/([a-z0-9_]+?)\s*?(?:\[.*?\])?;\s*?/im);
                        if (m && m.length >= 2)
                        {
                            //# Found start of name token, process it

                            let symbol = m[1];

                            symbols.push({
                                symbol,
                                addr: currAddress.replace(/^0x/g, ""),
                            });

                            currAddress = "";

                            //# Prime for the next comment
                            waiting = false;
                        }
                    }
                    else
                    {
                        waiting = false;
                    }
                }
            }

            //- Write all symbols to file
            {
                let lengthOfLongestSymbol = symbols.reduce((acc, e) => Math.max(acc, e.symbol.length), 0);
                let data = symbols.map(e => `${e.symbol.padEnd(lengthOfLongestSymbol + 2, " ")} = 0x${e.addr.toString(16).toUpperCase()};`)

                await fsp.writeFile(outpath, data.join("\n"));
            }
        }
    }
}

const MATCH_COLOURS =
{
    //# matching
    OK:  "green",
    //# compressed
    CMP: "yellow",
    //# non-matching
    BAD: "red",
    //# completely unknown file
    UNK: "pink",
};

/**
 * Order log result strings by the colour of the initial dot etc.
 *
 * The higher the number, the lower it'll be on the list.
 *
 * @param {string} str
 * @returns
 */
function _order_colours(str)
{
    switch (str.substr(0, 5))
    {
        case `\x1b[${COLOUR_CODES[MATCH_COLOURS.OK ]};`: return 10;
        case `\x1b[${COLOUR_CODES[MATCH_COLOURS.CMP]};`:
        {
            //# The more % signs, the more builds at least succeeded, so show them higher
            let countPercentChars = str.match(/%/g)?.length;
            if (!countPercentChars)
                countPercentChars = 0;

            let countOKs = str.match(/OK/g)?.length;
            if (!countOKs)
                countOKs = 0;

            /**
             * [countOKs * (allRomVers.length + 1)]:
             * If any romver gives an OK, make it appear above any that do not have a single OK.
             */
            return 4000 - countPercentChars - (countOKs * (allRomVers.length + 1));
        }
        //# Unknown DLLs should be at the very bottom
        case `\x1b[${COLOUR_CODES[MATCH_COLOURS.UNK]};`: return 8000;
        case `\x1b[${COLOUR_CODES[MATCH_COLOURS.BAD]};`:
        {
            //# The more % signs, the more builds at least succeeded, so show them higher
            let countPercentChars = str.match(/%/g)?.length;
            if (!countPercentChars)
                countPercentChars = 0;

            let countOKs = str.match(/OK/g)?.length;
            if (!countOKs)
                countOKs = 0;

            /**
             * [countOKs * (allRomVers.length + 1)]:
             * If any romver gives an OK, make it appear above any that do not have a single OK.
             */
            return 7000 - countPercentChars - (countOKs * (allRomVers.length + 1));
        }
        default:
            return 0;
    }
}

/**
 *
 * @param {string[]} rArr
 * @returns
 */
function _order_dll_result_strings_by_status(rArr)
{
    //# We've already sorted by last modified time
    //# We assume we're using a stable sort that maintains this order

    //# Now sort by version results (percentage and colours / match status)
    rArr.sort((a, b) => _order_colours(a) - _order_colours(b));

    return rArr;
}

/**
 * Store the last build hash of a DLL file, to check
 * if the output has changed.
 *
 * Record<dllName, Record<romVer, hash>>
 */
var gDllHashMap = {};
var gDllLastModified = {};


/**
 * 
 * @param {string[]} dllNames 
 */
async function dlls_update_last_modified_times(dllNames)
{
    (await Promise.all(dllNames.map(dllName =>
    {
        let fn = gRootDir + `src/dlls/${dllName}.c`;
        return fsp.stat(fn);
    })))
    .map(s => s.mtimeMs)
    .forEach((mtimeMs, i) => gDllLastModified[dllNames[i]] = mtimeMs);
}

/**
 * 
 * @param {string[]} dllNames 
 */
async function dll_full_build_multi(dllNames)
{
    await HELPER_parse_out_dll_linker_symbols();
    await HELPER_parse_out_static_linker_symbols();

    await dlls_update_last_modified_times(dllNames);

    // const SHOW_FILE_SIZES = false;

    let results_raw = [];

    /**
     *
     * Record<dllName, oooo_type_string>
     * @type {Record<string, string>}
    */
    let hashdiffs = {};

    /**
     * If even one version of a DLL is not skipped, we want
     * to remember that.
     */
    let ifDllNotSkipped = [];

    /**
     * Estimate total amount of completed bytes
     */
    let computedTotalSize = { usa: 0, jpn: 0, eur: 0, aus: 0 };

    //# Don't optimise this
    for (let romVer of allRomVers)
        await update_rom_version(romVer);

    //- Sort DLLs by last modified (newest first)
    dllNames.sort((a, b) => gDllLastModified[b] - gDllLastModified[a]);

    //- Optimise across allRomVers with Promise.all
    // for (let [rvIdx, romVer] of allRomVers.entries())
    await Promise.all(allRomVers.map((romVer, rvIdx) => new Promise(async (resolve, reject) =>
    {
        //- Optimise across all DLLs for a specific version with Promise.all
        // for (let [idx, dllName] of dllNames.entries())
        await Promise.all(dllNames.map((dllName, idx) => new Promise(async (resolve, reject) =>
        {
            if (!(dllName in gDllHashMap))
                gDllHashMap[dllName] = {};

            if (!(romVer in gDllHashMap[dllName]))
                gDllHashMap[dllName][romVer] = "";

            let lastHash = gDllHashMap[dllName][romVer];

            const CELL_PADDING = 17;

            const CELL_PREPAD = rvIdx === 0 ? 0 : 3;

            try
            {
                let fn_c = gRootDir + `src/dlls/${dllName}.c`;

                let toSkip = !arg_forceCompileAll && await dll_get_if_to_skip_build(dllName, romVer);

                if (!ifDllNotSkipped[idx])
                    ifDllNotSkipped[idx] = 0;

                ifDllNotSkipped[idx] |= !toSkip;

                //# Init results strings
                {
                    if (!results_raw[idx])
                        results_raw[idx] = {};

                    if (!(romVer in results_raw[idx]))
                        results_raw[idx][romVer] = "";
                }

                //# Make fndumps for vani
                await dll_make_fndumps(dllName, romVer, null);
                //# Populate source file with initial structure, if empty
                await dll_source_initialise(dllName, romVer);

                if (!fs.existsSync(fn_c) || (await fsp.stat(fn_c)).size === 0 || !allDllNames.has(dllName))
                {
                    //= Placeholder DLL, don't waste time processing it
                    results_raw[idx][romVer] += "".padStart(CELL_PADDING, " ");

                    return resolve();
                }

                let fn_o = await dll_build(dllName, romVer, toSkip);

                let [fn_raw, file_raw] = await dll_process(dllName, fn_o, romVer, toSkip);

                //# Make fndumps for cust
                await dll_make_fndumps(dllName, romVer, null);

                //# Encrypt header
                await dll_preheader_encryption_toggle(file_raw);

                //- Make [expected] dumps before proceeding, needed for zlib magic
                // await dll_dump_and_get_vani_from_baserom(dllName, romVer);

                //# Outputs compressed files
                let [fn_cmp, file_cmp] = await dll_compress(fn_raw, dllName, romVer, file_raw, toSkip);

                /**
                 * Used to know whether to override the raw status with
                 * the compressed status.
                 *
                 * If true, uses compression's status instead.
                 */
                let rawIsMatching = false;

                let resultToAppend = "";

                let errors = false;

                for (let USE_COMPRESSION of [false, true])
                {
                    let file = USE_COMPRESSION ? file_cmp : file_raw;

                    // let similarity = await dll_get_similarity_and_make_fndumps(dllName, file, romVer, USE_COMPRESSION, toSkip);
                    let similarity = await dll_get_similarity(dllName, file, romVer, USE_COMPRESSION);
                    let endPad = 10;

                    //- Increment total byte percentage
                    if (!USE_COMPRESSION)
                    {
                        // computedTotalSize[romVer] += Math.min(similarity.similarity, 1) * file_raw.byteLength;

                        let text_size = file_raw.readUint16BE(0x00) * 0x10;
                        computedTotalSize[romVer] += Math.min(similarity.similarity, 1) * text_size;
                    }

                    //- Diff script helpers (live update)
                    if (!USE_COMPRESSION)
                    {
                        // TODO: Verify this order later

                        if (gDllSourceCache?.[dllName]?.[romVer])
                            //# Old source exists, can compare and dump
                            errors |= await dll_source_edit_location_dump(dllName, romVer) === false;

                        await dll_cache_source_update_locations(dllName, romVer);
                    }

                    //- If the uncompressed version is matching, compress it and check for matching again in next inner iteration
                    if (!USE_COMPRESSION && similarity.found && similarity.similarity === 1)
                    {
                        rawIsMatching = true;

                        //# Defer to the compressed result
                        continue;
                    }

                    if (!USE_COMPRESSION || rawIsMatching)
                    {
                        resultToAppend = gct(`${romVer.substr(0, 2)}-${gSyscallIdxMap_rv[romVer][dllName].hex().padStart(3, "0")} `, "black").padStart(CELL_PREPAD, " ") + " ";

                        resultToAppend += similarity.found && similarity.similarity === 1
                            ? gct(`OK`.padEnd(endPad, " "), MATCH_COLOURS.OK)
                            : gct(`${(similarity.similarity * 100).toFixed(1)}%`.padEnd(endPad), USE_COMPRESSION ? MATCH_COLOURS.CMP : MATCH_COLOURS.BAD)
                    }
                }

                results_raw[idx][romVer] += resultToAppend;

                //= Hash check
                {
                    let hash = get_hash(file_cmp);

                    if (!(dllName in hashdiffs) || !hashdiffs[dllName])
                        hashdiffs[dllName] = "";

                    hashdiffs[dllName] +=
                        errors
                        ? gct("x", "red")
                        : hash !== lastHash
                            ? gct("o", "cyan")
                            : gct("-", "black");

                    gDllHashMap[dllName][romVer] = hash;
                }
            }
            catch (err)
            {
                if (err)
                    console.error(err);

                //# Append empty space
                results_raw[idx][romVer] += "".padStart(CELL_PADDING, " ");

                //= Pass
            }

            return resolve();
        })));

        return resolve();
    })));

    let results_out = [];

    for (let [idx, dllName] of dllNames.entries())
    {
        const pad = 25;

        let dllNameShort = dllName.length >= pad
            ? dllName.substr(0, pad - 3) + ".."
            : dllName;

        let combined = "";

        for (let romVer of allRomVers)
            combined += results_raw[idx][romVer];

        results_out[idx] =
            gct(
                `${dllNameShort}`.padEnd(pad, " "),
                !allDllNames.has(dllName)
                    //# Not a known DLL. Wrong filename?
                    ? MATCH_COLOURS.UNK
                    : ifDllNotSkipped[idx]
                        //# A build of the DLL was attempted
                        ? "cyan"
                        //# This DLL was not built this time, the results from the previous build were reused
                        : "black"
            )
            + combined;
    }

    const LEGEND_MARK = "●";

    var numDlls =
    {
        OK:  0,
        CMP: 0,
        BAD: 0,
        UNK: 0,
    };

    //# We don't want too many OK lines, too messy
    //= Set to 0 to disable
    const LIMIT_RESULTS_OK = 3;

    //- Postprocess results
    {
        //# Check if compression worked for all builds
        {
            let results = results_out;

            let filtered_results = [];
            let overflowed = false;

            for (let i = 0; i < results.length; i++)
            {
                let filter_passed = true;

                let str = results[i];

                let colour =
                      str_contains_colour(str, MATCH_COLOURS.BAD) ? MATCH_COLOURS.BAD
                    : str_contains_colour(str, MATCH_COLOURS.CMP) ? MATCH_COLOURS.CMP
                    : str_contains_colour(str, MATCH_COLOURS.OK ) ? MATCH_COLOURS.OK
                    : str_contains_colour(str, MATCH_COLOURS.UNK) ? MATCH_COLOURS.UNK
                    : MATCH_COLOURS.BAD;

                switch (colour)
                {
                    case MATCH_COLOURS.OK:  numDlls.OK++;  break;
                    case MATCH_COLOURS.CMP: numDlls.CMP++; break;
                    case MATCH_COLOURS.BAD: numDlls.BAD++; break;
                    case MATCH_COLOURS.UNK: numDlls.UNK++; break;
                }

                results[i] = `${gct(LEGEND_MARK + " ", colour)}` + str;

                if (LIMIT_RESULTS_OK > 0)
                {
                    if (colour === MATCH_COLOURS.OK)
                    {
                        if (numDlls.OK > LIMIT_RESULTS_OK)
                        {
                            filter_passed = false;
                            overflowed    = true;
                        }
                    }
                }

                if (filter_passed)
                    filtered_results.push(results[i]);
            }

            if (overflowed)
            {
                //# Add the "+ XX more" line
                filtered_results.push(
                    gct(
                        `+ ${numDlls.OK - LIMIT_RESULTS_OK} more `
                            .padEnd(
                                calc_max_width_for_box_contents(filtered_results),
                                "─"
                            ),
                        "green"
                    )
                );
            }

            results_out = filtered_results;
        }
    }

    /**
     * approx .text ranges:
     * 
     * core0 (add range) (without RSP code)
     *     usa 80012030 -> 80037880
     *     jpn 80012030 -> 80037030
     *     eur 80012030 -> 80037010
     *     aus 80012030 -> 80037010
     * 
     * core2 (add range)
     *     usa 800815C0 -> 80117C20
     *     jpn 80080D80 -> 80111F00
     *     eur 8008B9D0 -> 8011CD30
     *     aus 8008B9D0 -> 8011CB70
     * 
     * dll call table (subtract range)
     *     usa 80082540 -> 8008A990
     *     jpn 80081CD0 -> 80089CE0
     *     eur 8008C920 -> 80094940
     *     aus 8008C920 -> 80094930
     * 
     **************************************
     * 
     * approx TOTAL SIZE OF core .text:
     *   usa: 735840
     *   jpn: 713072
     *   eur: 713504
     *   aus: 713072
     * 
     * ************************************
     * 
     * approx TOTAL SIZE OF ALL .text:
     *   usa: 2854960 (2.72 MB)
     *   jpn: 2820048 (2.68 MB)
     *   eur: 2823184 (2.69 MB)
     *   aus: 2820512 (2.68 MB)
     */

    //# hardcoded total byte size of all DLLs
    // let totalVanillaSizeAllDll  = { usa: 2593440, jpn: 2579552, eur: 2582544, aus: 2580048 };
    // let totalVanillaSizeAllCore = { usa:  877760 }; //= just fill in the others roughly
    //- .text only (core0 minus RSP code, and core2)
    let totalVanillaSizeAllDll  = { usa: 2119120, jpn: 2106976, eur: 2109680, aus: 2107440 };
    let totalVanillaSizeAllCore = { usa:  735840, jpn:  713072, eur:  713504, aus:  713072 };

    //- Print results
    {
        //= Raw
        {
            let strs = [];

            if (dllNames.length === 1)
            {
                ///- Show compact log line for single DLL
                let _2 = hashdiffs[dllNames[0]]
                if (!_2)
                    //# Generate dummy string of "?" with the length of the total number of versions
                    _2 = allRomVers.map(x => "?").join("");

                log(`  ${results_out[0]} ${_2}`);
            }
            else
            {
                //- Show a large stylised box for multiple DLLs

                let str_counts = "";

                //# If string does not contain any colour codes
                let headerPad = 27;
                //# If contains colour codes
                // headerPad += 16 * /* num gct() calls -> */ 7;

                let remainingDllCount;
                {
                    //= The build with the most DLLs is "usa"
                    await init_gSyscallIdx_map("usa");

                    remainingDllCount = [...allDllNames].length - dllNames.length;
                }

                //- Calculate total percentage
                let totalPercentagesDll  = {};
                let totalPercentagesGame = {};
                {
                    for (let r in totalVanillaSizeAllDll)
                    {
                        totalPercentagesDll[r]  = (computedTotalSize[r] / totalVanillaSizeAllDll[r]) * 100;
                        totalPercentagesGame[r] = (computedTotalSize[r] / (totalVanillaSizeAllDll[r] + totalVanillaSizeAllCore[r])) * 100;
                    }
                }

                let header = `Status${str_counts}`.padEnd(headerPad, " ");
                header += gct(numDlls.OK, MATCH_COLOURS.OK);
                header += gct(" matching   ", "black");
                if (numDlls.CMP)
                {
                    header += gct(numDlls.CMP, MATCH_COLOURS.CMP);
                    header += gct(" compression   ", "black");
                }
                if (numDlls.BAD)
                {
                    header += gct(numDlls.BAD, MATCH_COLOURS.BAD);
                    header += gct(" non-matching   ", "black");
                }
                if (numDlls.UNK)
                {
                    header += gct(numDlls.UNK, MATCH_COLOURS.UNK);
                    header += gct(" unknown   ", "black");
                }
                header += gct(remainingDllCount, "black");
                header += gct(" unlisted   ", "black");

                strs.push(header);
                strs.push(..._order_dll_result_strings_by_status(results_out.filter(x => x)));

                //# Add a spacer line
                strs.push(gct("─".repeat(calc_max_width_for_box_contents(strs)), "red"));

                //- Percentages
                {
                    function sprint_percentage(val)
                    {
                        let str = val.toFixed(5);

                        let pivot = 6; //# Position from end that the colour will change at

                        let str1 = str.substr(0,           str.length - pivot);
                        let str2 = str.substr(str1.length, pivot);

                        // return gct(str1, "white") + gct(str2, "black") + gct("%", "black");
                        // return gct(str1 + str2 + "%", "red");
                        return str1 + str2 + "%";
                    }

                    function sz(val)
                    {
                        return (val / (1024 * 1024)).toFixed(3) + " MB";
                    }

                    //= DLLs

                    let ptitle = "PROGRESS (.text)  ";

                    {
                        let p = [];

                        for (let r of allRomVers)
                        {
                            let ps = "";
                            ps += gct(`${r.substr(0, 2)}: `, "black");
                            // ps += `${sz(computedTotalSize[r])}/${sz(totalVanillaSizeAllDll[r])}`;
                            // ps += " ("
                            ps += sprint_percentage(totalPercentagesDll[r]);
                            // ps += ")"
                            p.push(ps);
                        }
    
                        let title = gct(ptitle, "red") + gct("DLLs only", "black") + gct(" -> ", "black");
                        strs.push(title + p.join(gct(" ", "black")));
                    }

                    //= Out of entire game
                    {
                        let p = [];

                        for (let r of allRomVers)
                        {
                            let ps = "";
                            ps += gct(`${r.substr(0, 2)}: `, "black");
                            // ps += `${sz(computedTotalSize[r])}/${sz(totalVanillaSizeAllCore[r] + totalVanillaSizeAllDll[r])}`;
                            // ps += " ("
                            ps += sprint_percentage(totalPercentagesGame[r]);
                            // ps += ")"
                            p.push(ps);
                        }

                        let title = " ".repeat(ptitle.length) + gct("banjo2", "green") + gct("    -> ", "black");
                        strs.push(title + p.join(gct(" ", "black")));
                    }
                }

                print_lines_in_box(strs, "yellow");
            }
        }
    }
}

const OPCODE =
{
    nop:      0,
    beq:      1,
    beql:     2,
    bgez:     3,
    bgezal:   4,
    bgezall:  5,
    bgezl:    6,
    bltz:     7,
    bltzal:   8,
    bltzall:  9,
    bltzl:   10,
    bgtz:    11,
    bgtzl:   12,
    blez:    13,
    blezl:   14,
    bne:     15,
    bnel:    16,
    bc1f:    17,
    bc1fl:   18,
    bc1t:    19,
    bc1tl:   20,
    jr_ra:   99,
};

function MIPS_instruction_parse(instr)
{
    let opcode1   = (instr >>> (32 - 6)) & 0b111111;
    let opcode2_b = (instr >>> 16) & 0b11111;

    let opcode = "";

    let type_branch = true;

    //= Switch on opcode
    switch (opcode1)
    {
        case 0b000100: opcode = OPCODE.beq;  break;
        case 0b010100: opcode = OPCODE.beql; break;
        case 0b000001:
        {
            switch (opcode2_b)
            {
                case 0b00001: opcode = OPCODE.bgez;    break;
                case 0b10001: opcode = OPCODE.bgezal;  break;
                case 0b10011: opcode = OPCODE.bgezall; break;
                case 0b00011: opcode = OPCODE.bgezl;   break;
                case 0b00000: opcode = OPCODE.bltz;    break;
                case 0b10000: opcode = OPCODE.bltzal;  break;
                case 0b10010: opcode = OPCODE.bltzall; break;
                case 0b00010: opcode = OPCODE.bltzl;   break;
                default:
                {
                    type_branch = false;
                    break;
                }
            }
            break;
        }
        case 0b000111: opcode = OPCODE.bgtz;  break;
        case 0b010111: opcode = OPCODE.bgtzl; break;
        case 0b000110: opcode = OPCODE.blez;  break;
        case 0b010110: opcode = OPCODE.blezl; break;
        case 0b000101: opcode = OPCODE.bne;   break;
        case 0b010101: opcode = OPCODE.bnel;  break;
        case 0b010001:
        {
            if (((instr >>> 21) & 0b11111) !== 0b01000)
            {
                type_branch = false;
                break;
            }

            switch (instr >>> 16 & 3)
            {
                case 0: opcode = OPCODE.bc1f;  break;
                case 1: opcode = OPCODE.bc1t;  break;
                case 2: opcode = OPCODE.bc1fl; break;
                case 3: opcode = OPCODE.bc1tl; break;
            }
            break;
        }
        default:
        {
            type_branch = false;
            break;
        }
    }

    //= Switch on complete instruction
    switch (instr)
    {
        case 0x03E00008: opcode = OPCODE.jr_ra; break;
    }

    //- Prep results

    let res = {};

    res.opcode = opcode;

    //# [branches] Calculate branch target
    if (type_branch)
    {
        let target = instr & 0xFFFF;

        if (target >= 0x8000)
            target -= 0x10000;

        target += 1; //# branch imm is offset by one instruction
        target *= 4; //# branch imm counts every four bytes

        res.branch_target = target;
    }

    return res;
}

/**
 * Use analysis of MIPS instructions in a DLL file and detect the offsets
 * and sizes of all functions.
 *
 * @param {Buffer} dllFile Decompressed DLL with decrypted preheader.
 * @returns {Promise<Array<Record<string, boolean|string|number>>} information about all functions found in .text
 */
function dll_analyse_text(dllFile)
{
    return new Promise(async (resolve, reject) =>
    {
        //= Checks
        {
            if (!Buffer.isBuffer(dllFile) || dllFile.byteLength < 0x20)
                return reject(`Invalid DLL file: not a Buffer.`);

            if (dllFile.readUint8(0x0F) !== 0x82)
                return reject(`Cannot analyse DLL: missing preheader!`);

            if (dllFile.readUInt32BE(0x10) !== 0)
                return reject(`DLL was compressed, we don't take these.`);
        }

        //- Calculate the offset of the start of .text
        let text_offset;
        let dllName;
        {
            let size_preheader = 0x10;
            let size_header    = 0x24;
            let size_funcptrs  = (dllFile.readUint16BE(0x08) + 1) * 4;
            let size_symrefs   = dllFile.readUInt16BE(0x0A) * 2;
            let size_dllname   = dllFile.readUInt8(0x0E);

            text_offset = size_preheader
                        + size_header
                        + size_funcptrs
                        + ALIGN(size_dllname, 4)
                        + size_symrefs;

            text_offset = ALIGN(text_offset, 0x10);

            //# Read DLL name
            {
                let start = size_preheader + size_header + size_funcptrs;
                dllName = buf_cstr_to_str(dllFile.slice(start, start + size_dllname));
            }
        }

        //- Calculate the offsets of all pub fns
        let pubFnOffsets = [];
        {
            let num_funcptrs = dllFile.readUint16BE(0x08);
            let offset       = 0x10 + 0x24 + 0x04;

            for (let i = 0; i < num_funcptrs; i++)
                pubFnOffsets.push(text_offset + dllFile.readUint32BE(offset + (i * 4)));
        }

        let text_size  = dllFile.readUint16BE(0x00) * 0x10;
        let text_start = text_offset;
        let text_end   = text_start + text_size;

        // log(`=============================`)
        // log(`dllName: ${dllName}`)
        // log(`pubFnOffsets: ${pubFnOffsets.map(x => x.hex()).join(" ")}`)
        // log(`text_start.hex(): ${text_start.hex()}`)
        // log(`text_size.hex(): ${text_size.hex()}`)
        // log(`-----------------------------`)

        //- Process the .text segment
        let functions = [];
        {
            let insideFunction = false;

            //# indices
            let curr_func_pub_idx    = -1;
            let curr_func_prv_idx    = -1;

            //# attributes
            let curr_func_name       = "";
            let curr_func_start      = 0;
            let curr_func_end        = 0;
            let curr_func_is_public  = false;

            //# temp vars
            let curr_func_max_offset = 0;

            for (let i = text_start; i < text_end; i += 4)
            {
                let pc = i;

                let instr = dllFile.readUint32BE(pc);

                if (!insideFunction)
                {
                    if (instr === 0)
                        //# Ignore NOPs
                        continue;

                    //- Not a NOP, assume as start of a new function

                    insideFunction = true;
                    curr_func_start = pc;

                    //# Set name of the new func
                    {
                        if (pubFnOffsets.includes(curr_func_start))
                        {
                            curr_func_is_public = true;

                            curr_func_pub_idx++;
                            curr_func_name = `pub_${curr_func_pub_idx.toString().padStart(3, "0")}`;
                        }
                        else
                        {
                            curr_func_is_public = false;

                            curr_func_prv_idx++;
                            curr_func_name = `prv_${curr_func_prv_idx.toString().padStart(3, "0")}`;
                        }
                    }
                }

                //- Inside a function now

                //# Set max to curr offset
                if (pc > curr_func_max_offset)
                    curr_func_max_offset = pc;

                //# Parse the instruction
                {
                    let instr_o = MIPS_instruction_parse(instr);

                    let branch = false;
                    let jr_ra  = false;

                    //# Check if branch or [jr $ra]
                    switch (instr_o.opcode)
                    {
                        case OPCODE.beq:
                        case OPCODE.beql:
                        case OPCODE.bgez:
                        case OPCODE.bgezal:
                        case OPCODE.bgezall:
                        case OPCODE.bgezl:
                        case OPCODE.bltz:
                        case OPCODE.bltzal:
                        case OPCODE.bltzall:
                        case OPCODE.bltzl:
                        case OPCODE.bgtz:
                        case OPCODE.bgtzl:
                        case OPCODE.blez:
                        case OPCODE.blezl:
                        case OPCODE.bne:
                        case OPCODE.bnel:
                            branch = true;
                            break;

                        case OPCODE.jr_ra:
                            jr_ra = true;
                            break;

                        case OPCODE.nop:
                        default:
                            break;
                    }

                    if (branch)
                    {
                        let target = pc + instr_o.branch_target;

                        //# Update function max size
                        if (target > curr_func_max_offset)
                            curr_func_max_offset = target;
                    }

                    if (jr_ra)
                    {
                        if (curr_func_max_offset > pc)
                            //= The function goes on, don't get out yet, go to next instruction
                            continue;

                        //- The function is over. Prepare for next
                        {
                            curr_func_end = i + 8;

                            //# Account for delay slot; the loop iterator will account for incrementing pc
                            pc += 4;
                            i  += 4;

                            insideFunction = false;

                            functions.push({
                                public: curr_func_is_public,
                                name:   curr_func_name,
                                offset: curr_func_start,
                                size:   curr_func_end - curr_func_start,
                            });
                        }
                    }
                }
            }
        }

        //# Return found functions
        return resolve({
            dllName,
            functions,
        });
    });
}

/**
 * Take the output of [dll_analyse_text()] and dump it to disk
 * in a specially formatted text file
 *
 * @param {Record<string, string|Array<Record<string, boolean|string|number>>} dllInfo
 * @param {string} outputPath
 */
async function dll_analysis_text_dump(dllInfo, outputPath)
{
    let res = dllInfo.functions.map(d => `${d.name} ${d.offset.hexp()} ${d.size.hexp()}`);

    await fsp.writeFile(outputPath.replace(/\/+$/g) + `/${dllInfo.dllName}_fndump.txt`, res.join("\r\n"));
}

const MIPS_regs = new Set(
[
    "zero", "at", "v0", "v1",
    "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9",
    "k0", "k1", "gp", "sp", "fp", "ra",
]);

function asm_operand_sanitise(operand)
{
    //# simple register
    if (MIPS_regs.has(operand))
        return "$" + operand

    //# dereferencing register
    if (/\(.+\)+$/.test(operand))
    {
        let m = operand.match(/\((.+)\)+$/);
        if (!m || m.length < 2)
            FATAL(`[asm] regex match failed for dereferenced operand: ${operand}`);

        let prefix = operand.replace(/\(.+$/g, "");

        return prefix + "($" + m[1] + ")";
    }

    //# no match
    return operand;
}

/**
 * Filter output to make it ld-friendly
 * @param {string} line 
 */
function asm_line_sanitise(line)
{
    let isEmpty = line.trim() === "";

    let parts = line.split(/\t/g).map(e => e.trim());

    while (parts.length < 3)
        parts.push("")

    let lineno     = parts[0];
    let instr      = parts[1];
    let operandgrp = parts[2];

    //- Sanitise operands (prefix $ to regs)
    let operands = operandgrp.split(",");
    operands = operands.map(asm_operand_sanitise);

    //- Fix branch labels
    if (instr.startsWith("b"))
    {
        let branch_target = operands.pop();
        branch_target = branch_target.replace(/^0x(?:0)*/g, "_");
        operands.push(branch_target);
    }

    return (!isEmpty ? "_" : "") + lineno + "\t" + instr + "\t" + operands.join(",");
}

async function dll_permute_session_start()
{
    /**
     * Autodetect the last edited function, and trigger a permute session for it.
     * 
     * We use the _curr_dll_fn txt files that we dumped for the diff script
     * to detect the last used function.
     */


    const romVer = "usa"; //!

    await update_rom_version(romVer);

    const readpath = gCurrDir + `watches/_curr_dll_fn_${romVer}.txt`;

    let infoArr = (await fsp.readFile(readpath)).toString().split(/(?:\r?\n)+/g);

    /**
     * EXAMPLE:
     **************************
     * gzreg
     * print_enabled_bits
     * vani: prv_000 0x220 0xCC
     * cust: prv_000 0x220 0xCC
     * 1 5
     */
    let info;
    {
        let dll    = infoArr[0];
        let fnName = infoArr[1];

        let fnCounters = infoArr[4].split(" ");
        let fnIdx = parseInt(fnCounters[0]);
        let fnCnt = parseInt(fnCounters[1]);

        let vani = infoArr[2].substr(6).split(" ");
        let cust = infoArr[3].substr(6).split(" ");

        info =
        {
            dll,
            fnName,

            vani:
            {
                name:   vani[0],
                offset: parseInt(vani[1], 16),
                size:   parseInt(vani[2], 16),
            },
            cust:
            {
                name:   cust[0],
                offset: parseInt(cust[1], 16),
                size:   parseInt(cust[2], 16),
            },

            fnIdx,
            fnCnt,

            //# start of .text
            textOffset: 0,
        };
    }

    //# pmu: permuter
    let pmuBaseFolder = gRootDir + `tools/decomp-permuter2/`;
    // let pmuBaseFolder = gRootDir + `tools/decomp-permuter/`;
    let pmuDumpFolder = pmuBaseFolder + `nonmatchings/`;

    ensureDir(pmuDumpFolder);

    let identifier = `${info.dll}---${info.fnName}`;

    //- Ensure (clean) folder
    let pmuFuncFolder = pmuDumpFolder + identifier + path.sep;
    {
        if (fs.existsSync(pmuFuncFolder))
        {
            //# We need to delete it
            try
            {
                await fsp.rm(pmuFuncFolder, { recursive: true });
            }
            catch (err)
            {
                //# Could not remove!
                FATAL(`Could not remove folder contents: ${pmuFuncFolder}`);
            }
        }

        await fsp.mkdir(pmuFuncFolder);
    }

    //- Create required files
    {
        //# compile.sh
        {
            let file = "";
            file += `#!/usr/bin/env bash\n`;
            file += `INPUT="$(realpath "$1")"\n`;
            file += `OUTPUT="$(realpath "$3")"\n`;
            file += `cd ${gRootDir}\n`;
            file += `${CMD.cc} -c -Wab,-r4300_mul -non_shared -G 0 -Xfullwarn -Xcpluscomm -woff 649,807,838,624 -O2 -mips2 -D_FINALROM -DF3DEX2_GBI ${CMD.include} -DVERSION_${romVer.toUpperCase()} "$INPUT" -o "$OUTPUT"\n`;

            let target = pmuFuncFolder + "compile.sh";

            await fsp.writeFile(target, file);

            await spawn(`chmod +x ${target}`);
        }

        //# function.txt
        {
            // await fsp.writeFile(pmuFuncFolder + "function.txt", info.fnName);
        }

        //# settings.toml
        {
            let contents = "";
            contents += `func_name = "${info.fnName}"\n`;
            contents += `compiler_type = "ido"\n`;

            await fsp.writeFile(pmuFuncFolder + "settings.toml", contents);
        }

        //# target.o
        {
            let targetInput = gRootDir + `expected/${romVer}/dlls/${info.dll}.bin`;

            let targetTmp = `${pmuFuncFolder}target.bin`;
            let targetAsm = `${pmuFuncFolder}target.s`;
            let targetObj = `${pmuFuncFolder}target.o`;

            //# Copy the desired function
            let buf = await fsp.readFile(targetInput);
            {
                let start = info.vani.offset;
                let size  = info.vani.size;

                buf = buf.slice(start, start + size);
            }
            await fsp.writeFile(targetTmp, buf);

            /** @type {string} */
            let stdout;
            let stdout_filtered;

            //# Disassemble
            let cmd_disasm = `${CMD.objdump} -dDz -bbinary -mmips -EB ${targetTmp}`;
            stdout = await spawn(cmd_disasm, false);
            stdout_filtered = stdout
                .split(/\r?\n/g)
                .slice(7)
                .map(line => line.substring(0, line.indexOf(":") + 1) + "\t" + line.replace(/^.+[0-9a-f]{8} \t/g, ""))
                .map(line => line.trim())
                .map(asm_line_sanitise)

            //- Transform assembly further
            {
                //# Add prelude
                stdout_filtered.unshift(
                    `.global ${info.fnName}`,
                    `.text`,
                    `${info.fnName}:`,
                );
            }

            await fsp.writeFile(targetAsm, stdout_filtered.join("\n"));

            //# Assemble
            let cmd_asm = `${CMD.as} -march=vr4300 -mabi=32 ${targetAsm} -o ${targetObj}`;
            stdout = await spawn(cmd_asm, false);

            //# Remove tmp
            await fsp.unlink(targetTmp);
        }

        //# base.c
        {
            let targetInput  = gRootDir + `src/dlls/${info.dll}.c`;
            let targetOutput = pmuFuncFolder + `base.c`;

            //- Transform file
            let b;
            {
                b = (await fsp.readFile(targetInput)).toString();

                //# Make the function non-static if it is static
                // b = b.replace(new RegExp(`static\\s+([^\\n]*)${info.fnName}`), `$1${info.fnName}`);

                //# Make functions non-static if they are
                b = b.replace(new RegExp(`static\\s+([^\\n]*[^ (]+\\s*\\()`), `$1`);
            }

            await fsp.writeFile(targetOutput, b);
        }
    }
}

const argv = process.argv.slice(2);

function _ARG(letter)
{
    return argv.filter(x => new RegExp("^-[A-Za-z0-9]*?" + letter + "[A-Za-z0-9]*?").test(x)).length > 0;
}

const arg_toWatch          = _ARG("w");
const arg_noInitialCompile = _ARG("n");
const arg_forceCompileAll  = _ARG("f");


async function main()
{
    // const argv = process.argv.slice(2);

    // if (!argv.length)
    //     FATAL(`ERR: Provide filename of ROM to use as a target!`);

    //- Set version for ROM you want to work with
    gRomVer = "usa"; //= default

    await update_rom_version(gRomVer);


    let dllNames =
    [
        // "glreflight",
        // "bamoveledge",
        // "cosection",
        // "chlavaarchgrillswitch",

        //- All non-flag arguments (dll names)
        ...(argv.filter(x => !x.startsWith("-"))),
    ];

    //= If no dll names were provided on the command line, do all
    if (!dllNames.length)
        dllNames = fs.readdirSync(gRootDir + "src/dlls")
            .filter(x => x.endsWith(".c"))
            .map(name => name.replace(/\.c$/g, ""));

    // if (arg_toWatch && dllNames.length > 1)
    //     FATAL(`Cannot watch more than one DLL file!`);

    if (!arg_noInitialCompile)
    {
        log(`Building ${dllNames.length} DLL(s) for ${allRomVers.length} ROM version(s)...`);
        await dll_full_build_multi(dllNames);
    }

    //- Watch for changes
    if (arg_toWatch)
    {
        let   lastModTime = 0;
        const delay = 0.5;

        const cb = async (e, fn) =>
        {
            let dll = fn.replace(/\.c$/g, "");

            let now = (new Date()).getTime();

            if (now < lastModTime + delay * 1000)
                //# Too quick, debounce and reject
                return;

            lastModTime = now;

            if (!fs.existsSync(gRootDir + `src/dlls/${fn}`))
                //# Callback was called due to deletion, not creation/edit. Ignore.
                return;

            //# rlog: Allow the next printed line to overwrite it
            rlog(gct(`  Detected change, rebuilding: ${gct(dll, "yellow")}`, "black"));

            await dll_full_build_multi([dll]);
        };

        {
            //# shadowed vars
            let   lastModTime = 0;
            const delay = 0.5;

            fs.watch(gRootDir + `src/dlls`, {}, async (e, fn) =>
            {
                let now = (new Date()).getTime();

                if (now < lastModTime + delay * 1000)
                    //# Too quick, debounce and reject
                    return;

                lastModTime = now;

                await sleep(500);

                if (e === "rename" && fn.endsWith(".c") && fs.existsSync(gRootDir + `src/dlls/${fn}`))
                    //# New .c file was added
                    fs.watch(gRootDir + `src/dlls/${fn}`, cb);
            });
        }

        for (let dll of dllNames)
        {
            fs.watch(gRootDir + `src/dlls/${dll}.c`, {}, cb);
        }

        log(gct(`  Autobuild enabled, watching for file changes...`, "black"));
    }
    else
    {
        log(`Done!`);
    }
}

main();
// dll_permute_session_start();




