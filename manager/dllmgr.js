const fs     = require("fs");
const fsp    = require("fs/promises");
const cmd    = require("child_process");
const crypto = require("crypto");
const path   = require("path");
const zlib   = require("node:zlib");

const stringSimilarity = require("string-similarity");



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

function spawn(command)
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
            // stdout += data;
            process.stdout.write(data);
        });

        proc.stderr.on("data", data =>
        {
            // stderr += data;
            process.stderr.write(data);
        });

        proc.on("close", code =>
        {
            if (code)
                return rej();

            return res();
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

Number.prototype.hex = function()
{
    return this.toString(16).toUpperCase();
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

/**
 * This function takes an array of strings and puts them in a nice ascii box.
 * @param {String[]} msgArr
 */
function print_lines_in_box(msgArr, colour="white")
{
    function removeColour (str)
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


/**
 * An absolute path to the repo root, given that this
 * file lives 1 folder down from it.
 */
const gRootDir = __dirname + path.sep + ".." + path.sep;
const gCurrDir = __dirname + path.sep;

const CMD =
{
    cc:        "tools/ido5.3_recomp/cc",
    include:   "-I . -I include -I include/2.0L -I include/2.0L/PR",
};

async function dll_get_if_to_skip_build(dll)
{
    ensureDir("build");
    ensureDir(`build/${gRomVer}`);
    ensureDir(`build/${gRomVer}/dlls`);

    const file_in  = gRootDir + `src/dlls/${dll}.c`;
    const file_out = gRootDir + `build/${gRomVer}/dlls/${dll}.lpo`;

    return fs.existsSync(file_in)
        && fs.existsSync(file_out)
        && (await fsp.stat(file_in)).mtimeMs < (await fsp.stat(file_out)).mtimeMs;
}

/**
 * Builds the .c file for a DLL and outputs an ELF .o file.
 *
 * @param {string} dll name of dll, as a string. e.g. "cosection"
 */
async function dll_build(dll, toSkip=false)
{
    //- Exec

    const file_in  = gRootDir + `src/dlls/${dll}.c`;
    const file_out = gRootDir + `build/${gRomVer}/dlls/${dll}.o`;

    if (!toSkip)
    {
        let cmd = "";
        cmd += ` -c -Wab,-r4300_mul -non_shared -G 0 -Xfullwarn -Xcpluscomm -signed`;
        /**
         * 649: "Missing member name in struct/union"
         * 807: ?
         * 838: "Microsoft extension" > nested structs/unions (?)
         */
        cmd += ` -woff 649,807,838`;
        cmd += ` -O2 -mips2 -D_FINALROM -DF3DEX2_GBI ${CMD.include}`;
        cmd += ` ${file_in} -o ${file_out}`;

        //- Env vars
        let env = "";
        {
            //- Pass "VERSION_USA" etc macros
            env += `-DVERSION_${gRomVer.toUpperCase()}=1`;
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
var gSyscallIdxMap;
var allDllNames = new Set();

/**
 * Map between <DLL_name, callTableOffset>
 *
 * WARN: Only usable inside certain functions, it's only updated for a version on-demand
 */
var gCallTableOffsetMap;

async function init_gSyscallIdx_map(romVer)
{
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

    gSyscallIdxMap = o;
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
 * Get a similarity score for a new DLL file, by comparing it to the one
 * inside the current baserom.
 *
 * @param {string} dllName
 * @param {Buffer} newDllFile the encrypted header, along with the decompressed file contents
 * @param {boolean} compressed if true, compare compressed version instead
 */
async function get_similarity_dll(dllName, newDllFile, compressed=false, toSkip=false)
{
    let syscallIdx = gSyscallIdxMap[dllName];

    let dllTableStart =
    {
        usa: 0x1E899B0,
        jpn: 0x1E308D0,
        eur: 0x1E8DA70,
        aus: 0x1E18A80,
    };

    let dllOffsetStart = gBaserom.readUint32BE(dllTableStart[gRomVer] + ((syscallIdx - 1) * 4));
    let dllOffsetEnd   = gBaserom.readUint32BE(dllTableStart[gRomVer] + ((syscallIdx    ) * 4));

    // console.log(dllOffsetStart.hex())
    // console.log(dllOffsetEnd.hex())

    let size = dllOffsetEnd - dllOffsetStart;

    if (!size)
    {
        // dll missing
        return { found: false, similarity: 0, };
    }

    //- Grab file from baserom

    let preheader = gBaserom.slice(
        dllTableStart[gRomVer] + dllOffsetStart,
        dllTableStart[gRomVer] + dllOffsetStart + 0x10,
    );

    let dllCompressed = gBaserom.slice(
        dllTableStart[gRomVer] + dllOffsetStart + 0x10,
        dllTableStart[gRomVer] + dllOffsetEnd,
    );

    let buf_vani;
    let buf_cust = newDllFile;

    if (!compressed)
    {
        //= The input file was raw (apparently). Decompress and compare raw bytes instead.

        //- Decompress the raw vanilla stream
        let dllUncompressed = zlib.inflateRawSync(dllCompressed.slice(0x02));

        //- Splice vanilla preheader onto vanilla decompressed file
        buf_vani = Buffer.alloc(preheader.byteLength + dllUncompressed.byteLength);
        preheader.copy(buf_vani);
        dllUncompressed.copy(buf_vani, 0x10);

        //= Copy to [expected] folder
        if (!toSkip)
        {
            // fs.writeFileSync("./tmp.vani.bin", buf_vani);
            // FATAL("./tmp.vani.bin");

            ensureDir(gRootDir + `expected`);
            ensureDir(gRootDir + `expected/${gRomVer}`);
            ensureDir(gRootDir + `expected/${gRomVer}/dlls`);

            await fsp.writeFile(gRootDir + `expected/${gRomVer}/dlls/${dllName}.raw`, buf_vani);
        }
    }
    else
    {
        //= Both preheader and compressed body combined

        buf_vani = gBaserom.slice(
            dllTableStart[gRomVer] + dllOffsetStart,
            dllTableStart[gRomVer] + dllOffsetEnd,
        );

        //= Copy to [expected] folder
        if (!toSkip)
        {
            // fs.writeFileSync("./tmp.vani.bin", buf_vani);
            // FATAL("./tmp.vani.bin");

            ensureDir(gRootDir + `expected`);
            ensureDir(gRootDir + `expected/${gRomVer}`);
            ensureDir(gRootDir + `expected/${gRomVer}/dlls`);

            await fsp.writeFile(gRootDir + `expected/${gRomVer}/dlls/${dllName}.dll`, buf_vani);
        }
    }


    //- Execute compare
    let similarity = stringSimilarity.compareTwoStrings(
        buf_vani.toString(),
        buf_cust.toString()
    );

    return { found: true, similarity, };
}

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
async function dll_process(dll, objFilePath, toSkip=false)
{
    // output path
    const binFilePath = objFilePath.replace(/\.o$/, ".bin");

    const pubFnDumpPath = objFilePath.replace(/\.o$/, "_pubfndump.txt");

    if (!(dll in gSyscallIdxMap))
        FATAL(`DLL [${dll}] not in curr rom version [${gRomVer}]`);

    let syscallIdx = gSyscallIdxMap[dll];

    //- Fetch the encryption key needed to encrypt symbolRefs with bootcode
    let encryptionKey = gBaserom.readUint16BE(0x40 + (syscallIdx * 4) + 2);
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

        let symbols = elf_get_syms(elf, sectionsWithRelocs.map(x => x.replace(/^_/g, ".")));

        //- We only look at relocations that are in sections that interest us
        //# This avoids looking at e.g. external function calls that the linker can handle
        let validSectionIds = [];
        if (symbols?._text?.shndx)   validSectionIds.push(symbols._text.shndx);
        if (symbols?._rodata?.shndx) validSectionIds.push(symbols._rodata.shndx);
        if (symbols?._data?.shndx)   validSectionIds.push(symbols._data.shndx);
        if (symbols?._bss?.shndx)    validSectionIds.push(symbols._bss.shndx);

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

        let out = `build/${gRomVer}/dlls/${dll}.out`;

        {
            let LINKER_INCLUDES = "";
            LINKER_INCLUDES += ` -T misc/linkerscript/dll.ld`;
            LINKER_INCLUDES += ` -T ver/${gRomVer}/syms/undefined.txt`;
            LINKER_INCLUDES += ` -T ver/${gRomVer}/syms/DLL.txt`;

            let FILE_OBJECT = `build/${gRomVer}/dlls/${dll}.o`;
            let FILE_LINKED = `build/${gRomVer}/dlls/${dll}.lpo`;

            if (!toSkip)
            {
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
                if (!toSkip)
                {
                    await fsp.writeFile(pubFnDumpPath,
                        pubFns.map(p => `${p.name} 0x${(p.loc + size_05_fullheader).hex()} 0x${p.size.hex()}`).join("\n")
                    );
                }
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

async function dll_preheader_encrypt(rawFilePath, rawFile=null)
{
    if (!rawFile)
        rawFile = await fsp.readFile(rawFilePath);

    if (rawFile.readUint8(0xF) !== 0x82)
        FATAL(`Cannot package DLL: missing preheader!`);

    //- Calculate checksum
    let checksum = [0, 0];
    {
        let start = 0x10;

        for (let i = start; i < rawFile.byteLength; i++)
        {
            let byte = rawFile.readUint8(i);
            // checksum[0] += byte;
            // checksum[1] ^= byte << (checksum[0] & 0x17);

            //= Safeguard against JS f64 inaccuracies
            checksum[0] = ((checksum[0] + byte) & 0xFFFFFFFF) >>> 0;
            checksum[1] ^= byte << (checksum[0] & 0x17);
        }
    }

    rawFile.writeUInt32BE(rawFile.readUint32BE(0x0) ^ checksum[0], 0x0);
    rawFile.writeUInt32BE(rawFile.readUint32BE(0x8) ^ checksum[1], 0x8);
}

/**
 * Pack a raw dll file with the compression and encryption bullshit that Tooie expects.
 *
 * @param {string} rawFilePath
 * @param {Buffer} rawFile the raw dll file (already compiled and linked and everything)
 */
async function dll_compress(rawFilePath, rawFile=null, toSkip=false)
{
    if (!rawFile)
        rawFile = await fsp.readFile(rawFilePath);

    if (rawFile.readUint8(0xF) !== 0x82)
        FATAL(`Cannot package DLL: missing preheader!`);

    //# Dump just for fun
    let bodyWithPreOutPath  = rawFilePath + ".raw";

    let bodyOutPath  = rawFilePath + ".body";
    let gzOutPath    = rawFilePath + ".gz";
    let finalOutPath = rawFilePath + ".dll";

    let finalOut;

    //- Compress
    {
        if (!toSkip)
        {
            //- Remove preheader before compression
            await fsp.writeFile(bodyWithPreOutPath, rawFile);

            //- Remove preheader before compression
            await fsp.writeFile(bodyOutPath, rawFile.slice(0x10));
        }

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
            const bin = `${gRootDir}tools/mcompress/bin/minigzip`;

            if (!toSkip)
            {
                if (!fs.existsSync(bin))
                    FATAL(`Couldn't find [minigzip] (zlib:1.0.6) binary! Either provide it, or switch to using internal zlib.`);

                //# zlib binary overwrites file completely, so make a copy
                await fsp.writeFile(gzOutPath, rawFile.slice(0x10));

                await spawn(`${bin} ${path.resolve(gzOutPath)}`);
                //# zlib binary appends .gz to the end of everything, cut it
                await fsp.rename(gzOutPath + ".gz", gzOutPath);
            }

            gzOut = await fsp.readFile(gzOutPath);
        }
        else
        {
            gzOut = zlib.deflateRawSync(rawFile.slice(0x10));

            if (!toSkip)
            {
                //# (async) Write just for fun
                fs.writeFile(gzOutPath, gzOut, () => {});
            }
        }


        //= Postprocess the zlib-compressed file
        {
            //# Trim the file buffer appropriately

            if (USE_ZLIB_BINARY)
            {
                /**
                 * The zlib binary [minigzip] prepends a header and appends
                 * a checksum. We need to trim both off, and also prepend
                 * the 2-byte decompressed size value.
                 */

                let start = 0x08;
                //# Where the checksum starts. We need to zero this area.
                let tail  = gzOut.byteLength - 8;
                let end   = tail;

                //# Calculate padding requirements
                while (end % 4)
                    end++;

                //# Write decompressed size (2 bytes)
                {
                    let decompressedSize = (ALIGN(rawFile.byteLength, 0x10) - 0x10) / 0x10;
                    gzOut.writeUint16BE(decompressedSize, start);
                }

                for (let i = tail; i < end; i++)
                    //# Zero-fill
                    gzOut.writeUint8(0, i);

                //# Perform final slice
                gzOut = gzOut.slice(start, end);
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
            gzOut.copy(finalOut, 0x10, 0);
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
/** @type {Buffer} */
var gBaserom;

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
    {
        let baseromPath = gRootDir + `ver/${gRomVer}/baserom.z64`;

        if (!fs.existsSync(baseromPath))
            FATAL(`No baserom for the curr rom version: ${baseromPath}`);

        gBaserom = await fsp.readFile(baseromPath);
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
        case `\x1b[${COLOUR_CODES[MATCH_COLOURS.CMP]};`: return 20;
        //# Unknown DLLs should be at the very bottom
        case `\x1b[${COLOUR_CODES[MATCH_COLOURS.UNK]};`: return 2000;
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
             * [countOKs * (allRomVers.length + 1)]: If any romver gives an OK, make it appear
             * any red DLLs that do not have a single OK.
             */
            return 1000 - countPercentChars - (countOKs * (allRomVers.length + 1));
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
    return rArr.sort((a, b) =>
    {
        a = _order_colours(a);
        b = _order_colours(b);

        if      (a < b) return -1;
        else if (a > b) return 1;
        else            return 0;
    });
}

/**
 * Store the last build hash of a DLL file, to check
 * if the output has changed.
 * 
 * Record<dllName, Record<romVer, hash>>
 */
var gDllHashMap = {};

async function dll_full_build_multi(dllNames)
{
    await HELPER_parse_out_dll_linker_symbols();

    // const SHOW_FILE_SIZES = false;

    let results_raw = [];
    let results_cmp = [];

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

    for (let [rvIdx, romVer] of allRomVers.entries())
    {
        await update_rom_version(romVer);

        for (let [idx, dllName] of dllNames.entries())
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

                let toSkip = !arg_forceCompileAll && await dll_get_if_to_skip_build(dllName);

                if (!ifDllNotSkipped[idx])
                    ifDllNotSkipped[idx] = 0;

                ifDllNotSkipped[idx] |= !toSkip;
                
                //# Init results strings
                if (!results_raw[idx])
                    results_raw[idx] = "";


                if (!fs.existsSync(fn_c) || (await fsp.stat(fn_c)).size === 0 || !allDllNames.has(dllName))
                {
                    //= Placeholder DLL, don't waste time processing it
                    results_raw[idx] += "".padStart(CELL_PADDING, " ");
                    results_cmp[idx] += "".padStart(CELL_PADDING, " ");

                    continue;
                }


                let fn_o = await dll_build(dllName, toSkip);

                let [fn_raw, file_raw] = await dll_process(dllName, fn_o, toSkip);

                await dll_preheader_encrypt(fn_raw, file_raw);


                //# Outputs compressed files
                let [fn_cmp, file_cmp] = await dll_compress(fn_raw, file_raw, toSkip);

                /**
                 * Used to know whether to override the raw status with
                 * the compressed status.
                 * 
                 * If true, uses compression's status instead.
                 */
                let rawIsMatching = false;

                let resultToAppend = "";

                for (let USE_COMPRESSION of [false, true])
                {
                    let file = USE_COMPRESSION ? file_cmp : file_raw;

                    if (file === undefined)
                    {
                        log(dllName)
                        log(USE_COMPRESSION)
                    }

                    let similarity = await get_similarity_dll(dllName, file, USE_COMPRESSION, toSkip);
                    let endPad = 10;

                    if (!USE_COMPRESSION && similarity.found && similarity.similarity === 1)
                    {
                        rawIsMatching = true;

                        //# Defer to the compressed result
                        continue;
                    }

                    if (!USE_COMPRESSION || rawIsMatching)
                    {
                        resultToAppend = gct(`${gRomVer.substr(0, 2)}-${gSyscallIdxMap[dllName].hex().padStart(3, "0")} `, "black").padStart(CELL_PREPAD, " ") + " ";

                        resultToAppend += similarity.found && similarity.similarity === 1
                            ? gct(`OK`.padEnd(endPad, " "), MATCH_COLOURS.OK)
                            : gct(`${(similarity.similarity * 100).toFixed(1)}%`.padEnd(endPad), USE_COMPRESSION ? MATCH_COLOURS.CMP : MATCH_COLOURS.BAD)
                    }
                }

                results_raw[idx] += resultToAppend;

                //= Hash check
                {
                    let hash = get_hash(file_cmp);

                    if (!(dllName in hashdiffs) || !hashdiffs[dllName])
                        hashdiffs[dllName] = "";

                    hashdiffs[dllName] += hash !== lastHash
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
                results_raw[idx] += "".padStart(CELL_PADDING, " ");

                //= Pass
            }
        }
    }


    for (let [idx, dllName] of dllNames.entries())
        results_raw[idx] =
            gct(
                `${dllName.substr(0, 23)}`.padEnd(25, " "),
                !allDllNames.has(dllName)
                    //# Not a known DLL. Wrong filename?
                    ? MATCH_COLOURS.UNK
                    : ifDllNotSkipped[idx]
                        //# A build of the DLL was attempted
                        ? "cyan"
                        //# This DLL was not built this time, the results from the previous build were reused
                        : "black"
            )
            + results_raw[idx];

    const LEGEND_MARK = "●";

    var numDlls =
    {
        OK:  0,
        CMP: 0,
        BAD: 0,
        UNK: 0,
    };

    //- Postprocess results
    {
        //# Check if compression worked for all builds
        {
            let results = results_raw;

            for (let i = 0; i < results.length; i++)
            {
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
            }
        }
    }

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

                log(`  ${results_raw[0]} ${_2}`);
            }
            else
            {
                //- Show a large stylised box for multiple DLLs

                let str_counts = "";
                // str_counts    += gct("  < ", "black");
                // str_counts    += gct(numDlls.OK, MATCH_COLOURS.OK);
                // str_counts    += gct(" / ", "black");
                // str_counts    += gct(numDlls.CMP, MATCH_COLOURS.CMP);
                // str_counts    += gct(" / ", "black");
                // str_counts    += gct(numDlls.BAD, MATCH_COLOURS.BAD);
                // str_counts    += gct(" >", "black");

                // let str_counts = ` ${gct("<", "black")} ${gct(numDlls.OK, MATCH_COLOURS.OK)} / ${gct(numDlls.CMP, MATCH_COLOURS.CMP)} / ${gct(numDlls.BAD, MATCH_COLOURS.BAD)} >`;

                //# If string does not contain any colour codes
                let headerPad = 27;
                //# If contains colour codes
                // headerPad += 16 * /* num gct() calls -> */ 7;

                let remainingDllCount;
                {
                    //= The build with the most DLLs is "usa"
                    await init_gSyscallIdx_map("usa");

                    remainingDllCount = Object.keys(gSyscallIdxMap).length - dllNames.length;
                }

                let header = `Status${str_counts}`.padEnd(headerPad, " ");
                header += gct(numDlls.OK,           MATCH_COLOURS.OK);
                header += gct(" matching   ",       "black");
                header += gct(numDlls.CMP,          MATCH_COLOURS.CMP);
                header += gct(" compression   ",    "black");
                header += gct(numDlls.BAD,          MATCH_COLOURS.BAD);
                header += gct(" non-matching   ",   "black");
                if (numDlls.UNK)
                {
                    header += gct(numDlls.UNK,     MATCH_COLOURS.UNK);
                    header += gct(" unknown   ",   "black");
                }
                header += gct(remainingDllCount,    "black");
                header += gct(" unlisted   ",       "black");
    
                strs.push(header);
                strs.push(..._order_dll_result_strings_by_status(results_raw.filter(x => x)));

                print_lines_in_box(strs, "yellow");
            }
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

    update_rom_version(gRomVer);


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
            .map(name => name.replace(/\.c$/g, ""));

    // if (arg_toWatch && dllNames.length > 1)
    //     FATAL(`Cannot watch more than one DLL file!`);

    if (!arg_noInitialCompile)
    {
        log(`Building ${dllNames.length} DLL(s)...`);
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

