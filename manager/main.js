const fs     = require("fs");
const fsp    = require("fs/promises");
const cmd    = require("child_process");
const crypto = require("crypto");
const path   = require("path");

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

function spawn(command)
{
    return new Promise((res, rej) =>
    {
        // log(`  ${command}`, "EXEC");
        log(command);

        let cmdlist = command.split(/\s+/);
        let proc;
        if (cmdlist.length <= 1)
            proc = cmd.spawn(cmdlist[0], { detached: true });
        else
            proc = cmd.spawn(cmdlist[0], cmdlist.slice(1), { detached: true });

        // let stdout = "";
        // let stderr = "";

        // proc.stdout.on("data", data =>
        // {
        //     // stdout += data;
        //     process.stdout.write(data);
        // });

        // proc.stderr.on("data", data =>
        // {
        //     // stderr += data;
        //     process.stderr.write(data);
        // });

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


/**
 * Builds the .c file for a DLL and outputs an ELF .o file.
 *
 * @param {string} dll name of dll, as a string. e.g. "cosection"
 */
async function dll_build(dll)
{
    //- Exec

    if (!fs.existsSync("build"))
        fs.mkdirSync("build");

    if (!fs.existsSync(`build/${gRomVer}`))
        fs.mkdirSync(`build/${gRomVer}`);

    if (!fs.existsSync(`build/${gRomVer}/dlls`))
        fs.mkdirSync(`build/${gRomVer}/dlls`);

    const file_in  = gRootDir + `src/dlls/${dll}.c`;
    const file_out = gRootDir + `build/${gRomVer}/dlls/${dll}.o`;

    let cmd = "";
    cmd += `-c -Wab,-r4300_mul -non_shared -G 0 -Xfullwarn -Xcpluscomm -signed `;
    cmd += `-O2 -mips2 -D_FINALROM -DF3DEX2_GBI ${CMD.include} `;
    cmd += `${file_in} -o ${file_out}`;


    await spawn(`${CMD.cc} ${cmd}`);

    return file_out;
}



var gSyscallIdxMap;

function init_gSyscallIdx_map()
{
    const fSyscallIdx = gCurrDir + "enum/syscallidx.txt";

    if (!fs.existsSync(fSyscallIdx))
        FATAL(`File missing: [${fSyscallIdx}]`);

    let lines = fs.readFileSync(fSyscallIdx).toString().split(/\r?\n/g);

    let isUsa = gRomVer === "usa";

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
            o[words[0]] = syscallIdx;
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
                //# Remove leading "." and replace any other "." with _ (e.g. rel.data -> rel_data)
                out[sn.replace(/\./g, "_")] = o;

                break;
            }
        }

        if (!found)
            //# Remove leading "." and replace any other "." with _ (e.g. rel.data -> rel_data)
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

        //# Remove leading "." and replace any other "." with _ (e.g. rel.data -> rel_data)
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
async function dll_process(dll, objFilePath)
{
    // output path
    const binFilePath = objFilePath.replace(/\.o$/, ".bin");

    if (!(dll in gSyscallIdxMap))
        FATAL(`DLL [${dll}] not in curr rom version [${gRomVer}]`);

    let syscallIdx = gSyscallIdxMap[dll];

    //- Fetch the encryption key needed to encrypt symbolRefs with bootcode
    let encryptionKey = gBaserom.readUint16BE(0x40 + (syscallIdx * 4) + 2);
    // console.log(encryptionKey.hex())

    //- Prepare to read from the ELF .o file

    /** @type {Buffer} */
    let elf = fs.readFileSync(objFilePath);

    let preheader = Buffer.alloc(0x10).fill(0);
    //# This is all written in-game, we don't need to touch it
    let header    = Buffer.alloc(0x28).fill(0);

    preheader.writeUint8(dll.length + 1, 0xE); // length of name including null byte
    preheader.writeUint8(0x82,           0xF); // constant (bitfield?) identical for all DLLs





    // DBG_elf_printSectionHeaders(elf);




    let sections = elf_get_sections(elf, [
            ".text",     ".rodata",     ".data", ".bss", ".symtab",
        ".rel.text", ".rel.rodata", ".rel.data",
    ]);

    console.log(sections)


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
    {
        //- Finding pub fns
        {
            let pubFns = [];


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
                console.log(pubFns)

                //- Pub functions all found!

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
        //# Also, .bss doesn't have relocs dummy
        let sectionsWithRelocs = [ "_text", "_rodata", "_data" ];

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

                    //# Location from start of binary
                    // let abs_offset = sections[rel_swr].loc + r_offset;
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

        console.log(symbolRefs.map(r => r.hex()))
    }















}


var gRomVer;
/** @type {Buffer} */
var gBaserom;

async function main()
{
    // if (!path.resolve(".").endsWith(path.sep + "bt"))
    //     //! Dumb hacky check, update it at some point
    //     //! Or just make it so cwd doesn't matter
    //     FATAL("Make sure to call this from the repo base path!");

    const argv = process.argv.slice(2);

    // if (!argv.length)
    //     FATAL(`ERR: Provide filename of ROM to use as a target!`);

    //- Get version for ROM you want to work with
    {
        let romVerStr = argv[0];
        if (!(["usa", "jpn", "eur", "aus"].includes(romVerStr)))
            FATAL("argv[0]: Pass the rom version (usa/jpn/eur/aus)");

        gRomVer = romVerStr;
    }

    //- Load the baserom
    {
        let baseromPath = gRootDir + `ver/${gRomVer}/baserom.z64`;

        if (!fs.existsSync(baseromPath))
            FATAL(`No baserom for the curr rom version: ${baseromPath}`);

        gBaserom = fs.readFileSync(baseromPath);
    }



    // Initialise the syscall map
    init_gSyscallIdx_map();


    // console.log(gSyscallIdxMap)



    // const inputFilenameFull = argv[0];
    // const inputFilename     = path.basename(inputFilenameFull);

    const filenames =
    {
        // original: inputFilename,
        // baserom:  `bk_orig.z64`,
        // patch:    `${inputFilename}.xdelta`,
        // test:     `TESTFILE`,
    };



    // log(`> Preparing environment...`);
    {

    }

    // log(`> Compiling...`);
    {
        // cosection, chmrtannoy
        let dllName = "chmrtannoy";

        let file_o = await dll_build(dllName);

        await dll_process(dllName, file_o);


    }


    log(`Done!`);
}

main();

