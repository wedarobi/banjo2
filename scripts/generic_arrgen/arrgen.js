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
            let MAP = fetch_enum(type);

            let idx = val - 0xA0;

            if (idx < 0 || idx > MAP.length)
                // FATAL(`Value not a valid MAP: ${val}`);
                return "0x" + val.toString(16).toUpperCase();

            return MAP[idx];
        }
        case "MUSIC":
        {
            let MUSIC = fetch_enum(type);

            if (val === 0x3FFF)
                return "MUSIC_NONE";

            return MUSIC[val];
        }
        case "BCCI":
        {
            let BCCI = fetch_enum(type);

            let key = val.toString(16).toUpperCase().padStart(8, "0");

            return BCCI[key];
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

            case "bcci": width = 32; break;

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

    let basepath = __dirname + "/runs/";

    if (process.argv.length < 3)
        FATAL(`You need to specify the run name to use (i.e. name of txt file)`);

    let runname = process.argv[2];
    runname = runname.replace(/\.txt$/g, "");
    runname += ".txt";


    /**
     * Structure of run file:
     * 
     * first line: array of bytes
     * remaining lines: struct members
     * 
     * (empty lines are ignored, as are lines starting with // (C++ style comments))
     */

    let runpath = basepath + runname;

    if (!fs.existsSync(runpath))
        FATAL(`The given run does not exist: ${runpath}`);

    let run = fs.readFileSync(runpath).toString();

    let runlines = run.split(/\r?\n/g).filter(x => x && !x.startsWith("//"));

    let bytes = runlines[0];
    let members = runlines.slice(1).join("\n");

    // e.g. "u16 unk @10-0"
    //      "TYPE NAME : WIDTH_IN_BITS @ BASE - ZERO_PREPAD"
    console.log(bitwrapper(bytes).codify(members));

}

main();




