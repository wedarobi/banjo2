const fs = require("fs");


function ERROR(msg)
{
    console.error(`[ERROR]: ${msg}`);
    process.exit(1);
}

function FATAL(msg)
{
    console.error(`[FATAL]: ${msg}`);
    process.exit(1);
}

function load_json_with_comments(path)
{
    let file = fs.readFileSync(path).toString();

    //# CRLF -> LF
    file = file.replace(/\r/g, "");

    //# Remove comments
    let sanitised = file;
    {
        //# EOL comments
        sanitised = sanitised.replace(/\/\/[^\n]+\n/gm, "\n");
        //# Multiline comments
        sanitised = sanitised.replace(/\/\*[^*]*\*+(?:[^/*][^*]*\*+)*\//gm, "");
    }

    return JSON.parse(sanitised);
}

var gEnum = {};

function fetch_enum(name)
{
    if (name in gEnum)
        //- Already loaded
        return gEnum[name];

    let path = `./ENUM/${name}.json`;

    if (!fs.existsSync(path))
        FATAL(`JSON enum does not exist for: ${name} at: ${path}`);

    gEnum[name] = load_json_with_comments(path);

    return gEnum[name];
}

/**
 * Takes a value e.g. 1a7, and turns it into a "good value" e.g. "MAP_1A7_JRL_MAIN_AREA"
 * @param {number} val number to de-hardcode
 * @param {string} type
 * @param {number} base
 * @returns {string}
 */
function dehardcode_val(val, { type=undefined, base=16, prepadwidth=0 }={})
{

    //- Handled custom types will RETURN HERE
    switch (type)
    {
        case "MAP":
        {
            let MAP = fetch_enum("MAP");

            let idx = val - 0xA0;

            if (idx < 0 || idx > MAP.length)
                // FATAL(`Value not a valid MAP: ${val}`);
                return "0x" + val.toString(16).toUpperCase();

            return MAP[idx];
        }
        case "MUSIC":
        {
            let MUSIC = fetch_enum("MUSIC");

            if (val === 0x3FFF)
                return "MUSIC_NONE";

            return MUSIC[val];
        }
        default: break;
    }

    //# Unhandled type, treat generically

    switch (base)
    {
        case 16:
            return "0x" + val.toString(16).toUpperCase().padStart(prepadwidth, "0");
        case 2:
            return "0b" + val.toString(2).padStart(prepadwidth, "0");
        default:
            return val.toString().padStart(prepadwidth, " ");
    }
}

/**
 * Declare a member of a struct
 * @param {string} type  mnemonic for type. e.g. u16, MAP, u32, s8, etc. affects the output format
 * @param {string} name  name of the struct member
 * 
 * @param {number} width width of the member in bits. can be inferred by type if not specified.
 * @param {number} base  the base to output the value as when stringifying
 * 
 * @returns 
 */
function _member(type, name, { width=undefined, base=16, prepadwidth=0 }={})
{
    if (width === undefined)
    {
        switch (type.toLowerCase())
        {
            case "s8":   width = 8;  break;
            case "u8":   width = 8;  break;
            case "s16":  width = 16; break;
            case "u16":  width = 16; break;
            case "s32":  width = 32; break;
            case "u32":  width = 32; break;
            case "s64":  width = 64; break;
            case "u64":  width = 64; break;
            case "int":  width = 32; break;
            case "long": width = 32; break;
            case "f32":  width = 32; break;
            case "f64":  width = 64; break;
            case "WORD": width = 32; break;
            case "HALF": width = 16; break;
            case "BYTE": width = 8;  break;

            case "vec2f": width = 32 * 2; break;
            case "vec3f": width = 32 * 3; break;

            default:
            {
                FATAL(`Could not autodetect width for member: ${type} ${name}`);
            }
        }
    }

    return { name, type, width, base, prepadwidth };
}

/**
 * Allow declaring a member with natural C syntax
 * 
 * Also allows specifying the stringify base as e.g.: "@16" or "@ 16"
 *   Can prepad base with zeros like so: "@16-4" which would give values like 0x0003, 0x0004, etc.
 *     Note: with base 10, prepads with spaces not zeroes
 * 
 * @param {string} declaration e.g. "MAP map : 16" or "int height", can end in semicolon
 */
function member(declaration)
{
    //# Remove semicolons
    declaration = declaration.replace(/;+$/, "");

    //- Process base
    let base = 16;
    let prepadwidth = 0;
    {
        let m;

        m = declaration.match(/@\s*(\d+)-(\d+)/);
        if (m)
        {
            //# Includes base and prepad width
            base        = parseInt(m[1]);
            prepadwidth = parseInt(m[2]);
        }
        else
        {
            m = declaration.match(/@\s*(\d+)/);
            if (m)
            {
                //# Includes base
                base = parseInt(m[1]);
            }
        }

        //# Remove base
        declaration = declaration.replace(/\s*@.*$/g, "").trim();
    }

    //- Process width in bits
    let width = undefined;
    {
        let m = declaration.match(/:\s*(\d+)/);
        if (m)
            //# Includes width
            width = parseInt(m[1]);

        //# Remove width
        declaration = declaration.replace(/\s*:.*$/g, "").trim();
    }

    //- Extract name token
    //# Do this first, since type can be multiple words long
    let name = declaration.replace(/^.+ /g, "").trim();
    
    //- Extract type
    //# Do this last, since type can be multiple words long
    let type = declaration.replace(/ .+$/g, "").trim();

    return _member(type, name, { width, base, prepadwidth });
}

/**
 * Parse a byte string and then incrementally return bits as requested.
 * @param {string} bytes e.g. "00 d6 00 01 01 a7 " ...
 */
function bitwrapper(bytes)
{
    let _arr = bytes.trim().split(/\s+/g).map(e => parseInt(e, 16));

    return {
        //# current offset (in bits)
        _curr: 0,
        //# array of bytes
        _arr,
        //# total size in bits
        _size: _arr.length * 8,

        /**
         * Return a value from the array from offset
         * @param {number} offset 
         * @param {number} width 
         * @returns 
         */
        _extract(offset, width)
        {
            let out = 0;

            for (let remaining = width; remaining > 0; remaining--)
            {
                let byte = offset >> 3;
                let bit  = offset & 7;

                let val = this._arr[byte];

                out |=  (val >>> (7 - bit)) & 1;
                out <<= 1;

                offset++;
            }

            return out >>> 1;
        },

        /**
         * Return a value from the current position, and increment the offset
         * @param {number} width 
         * @returns 
         */
        pull(width)
        {
            let out = this._extract(this._curr, width);

            this._curr += width;

            return out;
        },

        get remainingBitsInArr()
        {
            return this._size - this._curr;
        },

        /**
         * Stringify the current array into a C array, based on a struct definition
         * @param {string} members lines of member declarations that makes up an element of the array
         * 
         * e.g. "u16 unk @10-0"
         *      "TYPE NAME : WIDTH_IN_BITS @ BASE - ZERO_PREPAD"
         * 
         * e.g. codify(`MAP map : 16; \n u16 unk @10; u32 ptr @16-8`);
         */
        codify(members)
        {
            //# Convert each line into a member()
            let memberArr = members.trim().split(/(?:\r?\n)/g).map(e => e.trim());

            let structdef = memberArr.map(member);

            //# total size of struct in bits
            let structSize = structdef.reduce((a, e) => a + e.width, 0);

            let out = [];

            while (this.remainingBitsInArr >= structSize)
            {
                let e = [];

                for (let member of structdef)
                {
                    let val = this.pull(member.width);

                    let valstr = dehardcode_val(val,
                        {
                            type:        member.type,
                            base:        member.base,
                            prepadwidth: member.prepadwidth,
                        }
                    );

                    e.push(valstr);
                }

                out.push(e);
            }

            //- Calculate padding for each member
            let padding = (new Array(memberArr.length)).fill(0);
            {
                for (let i = 0; i < padding.length; i++)
                {
                    for (let e of out)
                    {
                        //# Take into account the ", " delimiter that we'll add later
                        let delimiterPad = i < padding.length - 1 ? 2 : 0;

                        padding[i] = Math.max(padding[i], e[i].length + delimiterPad);
                    }
                }
            }

            //- Generate element string
            let lines = [];
            {
                for (let e of out)
                {
                    let line = [];

                    for (let [idx, str] of e.entries())
                    {
                        let paddedstr = str;

                        if (idx < e.length - 1)
                            paddedstr += ", ";

                        paddedstr = paddedstr.padEnd(padding[idx], " ");

                        line.push(paddedstr);
                    }

                    lines.push(line.join(""));
                }
            }

            //- Stringify all
            {
                //# Calculate the index of the current line, autopadded to the right width
                const p = i => i.toString().padStart(~~Math.log10(out.length) + 1, " ");

                return lines.map((line, i) => `/* ${p(i)} */ { ${line} },`).join("\n");
            }
        },
    };
}

async function main()
{

    let bytes = "00 a1 01 ed 00 00 00 a2 01 ed 00 00 00 a3 01 ed 00 00 00 a4 01 ed 00 00 00 a5 01 ed 00 00 00 a6 01 ed 00 00 00 a7 01 ed 00 00 01 8b 01 f4 00 00 01 93 ff fc 00 00 00 a8 01 ed 00 00 00 a9 01 ed 00 00 00 aa 01 ed 00 00 00 ab 01 ed 00 00 00 ac 01 ed 00 00 01 8c ff fc 00 00 01 8d ff fc 00 00 01 94 ff fc 00 00 01 95 ff fc 00 00 01 8e ff fc 00 00 01 8f ff fc 00 00 01 96 ff fc 00 00 01 97 ff fc 00 00 01 90 ff fc 00 00 01 98 ff fc 00 00 01 7e ff fc 00 00 01 99 ff fc 00 00 01 91 ff fc 00 00 01 92 ff fc 00 00 01 9c 02 08 00 00 01 9d 02 08 00 00 01 67 ff fc 00 00 01 68 ff fc 00 00 01 69 ff fc 00 00 01 6a ff fc 00 00 00 ad 00 d0 00 00 00 ae 00 c9 00 02 00 af 00 c9 00 01 01 73 00 cc 00 00 01 41 00 c9 00 02 01 58 01 9c 00 00 00 b8 00 e5 00 03 00 b9 00 e5 00 03 00 ba 00 e5 00 06 00 bb 00 e5 00 05 00 c6 00 e5 00 08 00 c8 00 e5 00 08 00 c9 00 e5 00 08 00 bc 00 e5 00 06 00 c4 00 e5 00 03 00 c5 00 e5 00 06 00 b6 00 dc 00 00 00 b7 00 68 00 00 01 77 00 e5 00 06 01 78 00 e5 00 06 01 79 00 e5 00 06 01 7a 00 e5 00 06 01 7f 00 e5 00 08 00 c7 00 f9 00 0b 00 ca 00 f9 00 0c 00 cb 00 f9 00 0e 00 cc 00 f9 00 0c 00 cd 00 f9 00 0c 00 ce 00 f9 00 0d 00 cf 00 f9 00 0d 00 d0 00 f9 00 0e 00 d1 00 f9 00 0d 00 d2 00 f9 00 0c 00 d3 00 f9 00 0d 00 d4 00 f9 00 11 00 d7 00 f9 00 0c 00 d8 00 f9 00 11 00 da 00 f9 00 0c 00 db 00 f9 00 0c 00 dc 02 14 00 45 01 63 00 f9 00 0c 00 d9 00 68 00 00 00 e9 00 dc 00 00 01 21 00 f9 00 0e 01 6f 00 f9 00 0b 01 70 00 f9 00 0b 00 d6 01 01 00 13 01 24 01 01 00 13 00 d5 00 dc 00 00 00 dd 01 01 00 1a 00 de 01 01 00 1a 00 df 01 01 00 1a 00 e0 01 01 00 1a 01 86 01 01 00 1a 00 e1 01 01 00 14 01 3b 01 01 00 14 00 e2 01 01 00 1c 00 e3 01 01 00 1c 00 e4 01 01 00 1c 01 7b 01 01 00 1c 00 e5 01 01 00 1c 01 7c 01 01 00 1c 00 e6 01 01 00 16 01 3c 01 01 00 16 00 e7 01 01 00 18 00 ea 01 01 00 18 00 eb 01 01 00 18 00 ec 01 01 00 18 00 f9 01 01 00 17 01 76 00 68 00 00 00 ed 01 15 00 1f 00 ee 01 15 00 1f 00 ef 00 68 00 00 00 f1 ff fc 00 00 00 f4 01 15 00 1d 00 f6 01 15 00 1d 00 f7 01 15 00 1d 00 f8 01 15 00 1d 00 fa 01 15 00 1d 00 fc 01 15 00 1d 00 ff 01 15 00 1f 01 20 00 dc 00 00 01 25 01 15 00 1d 01 26 01 15 00 1d 01 81 01 15 00 1d 01 82 01 15 00 1d 01 a7 01 15 00 1d 01 a6 01 15 00 1d 01 a8 01 15 00 1d 01 a9 01 15 00 1d 01 12 01 49 00 26 01 13 01 28 00 00 01 14 01 49 00 26 01 15 01 49 00 27 01 16 01 49 00 27 01 17 01 49 00 27 01 18 01 49 00 27 01 19 01 49 00 27 01 1a 01 49 00 26 01 1b 01 49 00 27 01 1e 00 dc 00 00 01 22 00 dc 00 00 01 23 01 49 00 27 01 83 01 49 00 27 01 71 00 68 00 00 01 00 00 fd 00 29 01 01 00 fd 00 2a 01 02 00 fd 00 2a 01 03 00 fd 00 2a 01 04 00 fd 00 2b 01 05 00 fd 00 2b 01 06 00 fd 00 2a 01 07 00 fd 00 2a 01 08 00 fd 00 2a 01 09 00 fd 00 2a 01 0a 00 fd 00 2a 01 0b 00 fd 00 2a 01 0c 00 fd 00 2b 01 0d 00 fd 00 2b 01 0e 00 fd 00 2b 01 0f 00 fd 00 2b 01 10 00 fd 00 2b 01 11 00 fd 00 2b 01 1f 00 dc 00 00 01 72 00 68 00 00 01 7d 00 fd 00 2a 01 62 02 19 00 00 01 87 00 fd 00 2b 01 27 01 05 00 2c 01 28 01 05 00 2f 01 29 01 05 00 2d 01 2a 01 05 00 30 01 2b 01 05 00 2d 01 2c 01 05 00 30 01 2d 01 05 00 2d 01 31 01 35 00 00 01 32 01 05 00 30 01 33 01 05 00 2d 01 34 00 68 00 00 01 35 00 dc 00 00 01 80 01 04 00 2d 01 2e 01 04 00 2d 01 2f 01 04 00 2d 01 30 01 04 00 2d 01 36 01 5d 00 32 01 37 01 5d 00 35 01 38 01 5d 00 36 01 39 01 5d 00 36 01 3a 01 5d 00 33 01 3d 01 5d 00 34 01 3e 00 68 00 00 01 3f 00 68 00 00 01 40 00 dc 00 00 01 85 01 5d 00 35 01 61 01 5d 00 32 01 88 01 5d 00 36 01 5d 01 d5 00 39 01 5e 01 d5 00 3a 01 5f 01 f9 00 00 01 60 01 d5 00 3a 01 89 01 f9 00 00 01 8a 01 d5 00 39 01 9a 01 d5 00 39 01 42 01 65 00 37 01 43 01 88 00 00 01 44 01 71 00 00 01 9b 01 75 00 00 01 45 01 69 00 00 01 46 01 69 00 00 01 47 01 69 00 00 01 48 01 69 00 00 01 49 01 69 00 00 01 4a 01 69 00 00 01 4b 01 69 00 00 01 4c 01 69 00 00 01 4d 01 69 00 00 01 4e 01 69 00 00 01 4f 01 61 00 3b 01 52 01 61 00 3b 01 54 01 61 00 3b 01 55 01 61 00 3b 01 5a 01 61 00 3b 01 5c 01 61 00 3b 01 50 01 fc 00 00 01 51 01 79 00 00 01 53 01 7d 00 00 01 57 00 dc 00 00 01 56 00 68 00 00 01 5b 00 c9 00 02 01 64 02 19 00 00 01 65 02 14 00 45 01 66 00 e5 00 06 01 85 01 5c 00 35 ff fa 01 01 00 18 ff f9 00 f9 00 0c ff f8 00 fd 00 2a ff f7 01 49 00 26 ff f6 01 61 00 3b ff f5 01 05 00 2d ff f4 01 05 00 30 00 00 00 00 00 00";

    console.log(

        // e.g. "u16 unk @10-0"
        //      "TYPE NAME : WIDTH_IN_BITS @ BASE - ZERO_PREPAD"
        bitwrapper(bytes).codify(`
            MAP _ : 16;
            MUSIC _ : 14;
            int _ : 2 @10;
            u16 _ @16-2;
        `
    ));

}

main();




