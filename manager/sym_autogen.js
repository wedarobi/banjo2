/**
 * Based on [searchbase.txt] symbols for a version, try and
 * autogenerate equivalent symbols for all other versions.
 *
 * Very hacky and not guaranteed to work. Be careful.
 * If equivalent addresses cant be found for some symbols,
 * place them manually in the appropriate symbol files,
 * or tweak this script to be able to recognise them better.
 *
 * Note: Success much more likely with function addresses
 * versus data addresses.
 */

const fs = require("fs");


/* constants ***********************************************/

const allRomVers = ["usa", "jpn", "eur", "aus"];
const VERSION_CONSTANTS =
{
    BUILD_IDX:    { usa: 0, jpn: 1, eur: 2, aus: 3, },
};

// TODO: Make a single place to store all file paths
//# placeholder
// function get_paths(romVer)
// {
//     return { dlls: `vers/dlls/${romVer}/misc`, };
// }


/***********************************************************/

const ADDRESS_TYPE =
{
    UNK:  0,
    INST: 1,
    DATA: 2,
};

const RANGES =
{
    INST:
    {
        usa: [ [0x80000000, 0x80000300], [0x80000400, 0x80004240], [0x80012030, 0x80037908], [0x800815C0, 0x80117C60] ],
        jpn: [ [0x80000000, 0x80000300], [0x80000400, 0x80004200], [0x80012030, 0x800370B8], [0x80080D80, 0x80111F40] ],
        eur: [ [0x80000000, 0x80000300], [0x80000400, 0x80004200], [0x80012030, 0x80037098], [0x8008B9D0, 0x8011CD70] ],
        aus: [ [0x80000000, 0x80000300], [0x80000400, 0x80004200], [0x80012030, 0x80037098], [0x8008B9D0, 0x8011CBB0] ],
    },
    DATA:
    {
        usa: [ [0x80000300, 0x80000400], [0x80004240, 0x80012030], [0x80037908, 0x800815C0], [0x80117C60, 0x80137800] ],
        jpn: [ [0x80000300, 0x80000400], [0x80004200, 0x80012030], [0x800370B8, 0x80080D80], [0x80111F40, 0x80131850] ],
        eur: [ [0x80000300, 0x80000400], [0x80004200, 0x80012030], [0x80037098, 0x8008B9D0], [0x8011CD70, 0x8013C680] ],
        aus: [ [0x80000300, 0x80000400], [0x80004200, 0x80012030], [0x80037098, 0x8008B9D0], [0x8011CBB0, 0x8013C380] ],
    },
};

/**
 *
 * @param {string} romVer
 * @param {number} address
 */
function get_address_type(romVer, address)
{
    let type = ADDRESS_TYPE.UNK;

    if (!(allRomVers.includes(romVer)))
        return type;

    //# Initialise matching ranges
    let matchingRanges = {};
    for (let romVer of allRomVers)
        matchingRanges[romVer] = { start: 0, end: 0 };

    let arr;

    for (let _t of ["INST", "DATA"])
    {
        arr = RANGES[_t][romVer];

        for (let [idx, [ start, end ]] of arr.entries())
        {
            if (address >= start && address < end)
            {
                //- Found the range

                //# Remember the type
                type = ADDRESS_TYPE[_t];

                //# Remember the range
                for (let romVer of allRomVers)
                    matchingRanges[romVer] = { start, end };
            }
        }
    }

    return {
        type,
        matchingRanges,
    };
}







const gRootDir = __dirname + path.sep + ".." + path.sep;
const gCurrDir = __dirname + path.sep;




// false for BT, true for BK
const gameIsBk = false;



const baseFolder = gRootDir + "ver";


const ramdumps = fs.readdirSync(baseFolder)
    .filter(x => allRomVers.includes(x))
    .map(romVer => baseFolder + `/${romVer}/baserom.z64`)


var DEBUG = true;
DEBUG = false;

const FATAL = function (msg)
{
    console.log(gct(`FATAL: ${msg}`, "red"));
    process.exit(0);
}

Number.prototype.hex = function ()
{
    return this.toString(16).toUpperCase();
}

Number.prototype.hexp = function ()
{
    return "0x" + this.hex();
}

const debug = function (msg)
{
    if (DEBUG)
        console.log(msg);
}



function gct(msg, colour, underline=false)
{
    let ul = underline ? "4m" : "1m";
    let reset = "\x1b[97;0;1m"; /// standard bright white (force no underline)
    /// the "4m" in "32;0;4m" makes it underline. "1m" makes it non-underline
    let codes = {
        black:  "30",
        red:    "31",
        green:  "32",
        yellow: "33",
        blue:   "34",
        pink:   "35",
        cyan:   "36",
        white:  "37"
    };

    /// default special colour is pink
    let code = colour in codes ? codes[colour] : codes["pink"];
    return `\x1b[${code};${ul}${msg}${reset}`;
}



var mode = 0;

var MODE_INSTRUCTION = mode === 0;
var MODE_DATA        = mode === 1;

var bytesBuf = process.argv.slice(2).map(x => parseInt(x, 16));
var bytes = new Uint8Array(bytesBuf);

// remove possible hardcoded addresses, which may be different per version
function instruction_sanitise(instruction)
{
    switch (instruction >>> 0x1A) // upper 6 bits
    {
        case 0x0C >>> 2: // jal
        case 0x08 >>> 2: // j
            return instruction & 0xFF000000;

        case 0x3C >>> 2: // lui
        case 0x82 >>> 2: // lbu
        case 0x90 >>> 2: // lbu
        case 0xA0 >>> 2: // sb
        case 0xA2 >>> 2: // ""
        case 0x84 >>> 2: // lh
        case 0x94 >>> 2: // lhu
        case 0xA4 >>> 2: // sh
        // case 0x8C: //! special treatment for [lw]
        case 0xAC >>> 2: // sw
        case 0x24 >>> 2: // addiu (not sp)
        case 0x25 >>> 2: // ""
        case 0x26 >>> 2: // ""
        case 0xC4 >>> 2: // lwc1
        case 0xE6 >>> 2: // swc1
            return instruction & 0xFFFF0000;

        default: break;
    }

    if ((instruction >>> 0x1A) === (0x8C >>> 2))
    {
        // [lw]: need to filter out large values.
        // this isnt foolproof, since small numbers can also be version specific,
        // but we can just avoid those imputs in the first place
        if (((instruction & 0xFFFF) >>> 0) > 0x100)
        {
            // sanitise
            return instruction & 0xFFFF0000;
        }
    }

    // no need to sanitise, return
    return instruction;
}

function instruction_compare(inst1, inst2)
{
    return instruction_sanitise(inst1) === instruction_sanitise(inst2);
}

function get_word_at_bytearr(arr, idx)
{
    let val = arr[idx + 0x00] << 0x18 |
              arr[idx + 0x01] << 0x10 |
              arr[idx + 0x02] << 0x08 |
              arr[idx + 0x03] << 0x00;

    return val >>> 0;
}

function process_match_instruction()
{
    if (bytes.length <= 3)
    {
        FATAL(`Not enough bytes to scan in INSTRUCTION mode!`);
    }
    else if (bytes.length % 4)
    {
        // FATAL("Data length must be a multiple of 4 in INSTRUCTION mode!");
        console.log(`Data length was not a multiple of 4, despite INSTRUCTION mode. Trimming to multiple of 4 and trying anyway!`);
        bytes = bytes.slice(0, bytes.length - (bytes.length % 4));
    }

    console.log("");

    var addrs =
    {
        usa: "",
        jpn: "",
        eur: "",
        aus: "",
    };

    var ok = true;

    for (let romVer in addrs)
    {
        //# Find the right ramdump for the this region

        let file = ramdumps.filter(x => x.includes(`/${romVer}/`))[0];

        debug(`Reading file and ${a}...`);
        let buf = fs.readFileSync(file);
        let arr = new Uint8Array(buf);

        debug(`Scanning file and ${a}...`);
        let foundCount = 0;
        for (let i = 0; i < 0x400000; i += 4)
        {
            let j = i;

            while (instruction_compare(
                get_word_at_bytearr(arr,   j),
                get_word_at_bytearr(bytes, j - i))
            )
            {
                j += 4;

                if (j - i >= bytes.length)
                {
                    //- Matched all bytes

                    let v = (0x80000000 + i) >>> 0;
                    debug(`Matched for ${romVer}: ${v.hex()}`)
                    addrs[romVer] = v.hex();
                    foundCount++;

                    break;
                }
            }
        }

        if (foundCount === 1)
        {
            console.log(gct(`Found single match for ${romVer}: `, "green") + addrs[romVer]);
        }
        else if (foundCount === 0)
        {
            FATAL(gct(`Found no matches for ${romVer}... either I'm broken, or the data was bad!`, "pink"));
        }
        else
        {
            // FATAL(`Found multiple matches for ${a}... not continuing! Try more specific input data!`);
            console.log(gct(` ! WARN ! : Found multiple matches for ${romVer}, but using this one: `, "red") + addrs[romVer]);
        }
    }

    //- to get here, we must've had a single match for each version anyway

    {
        let allSame = true;

        let vals = Object.keys(addrs).map(x => addrs[x]);

        if (vals.length)
        {
            let oneVal = vals[0];

            for (let val of vals)
                if (val !== oneVal)
                    allSame = false;

            if (allSame)
                console.log(`\n> ${gct("novam", "yellow")}(${Object.keys(addrs).map(x => gct(parseInt(addrs[x], 16).hexp(), "cyan"))[0].toString()});\n`);
            else
                console.log(`\n> ${gct("VER_SWITCH", "yellow")}(${Object.keys(addrs).map(x => gct(parseInt(addrs[x], 16).hexp(), "cyan")).join(", ")});\n`);
        }
    }
}



async function main()
{
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    FATAL(`Still in development`);



    if (false)
    {
        let res = get_address_type("usa", 0x80010200);

        for (let romVer of allRomVers)
        {
            res.matchingRanges[romVer].start = res.matchingRanges[romVer].start.toString(16).toUpperCase();
            res.matchingRanges[romVer].end   = res.matchingRanges[romVer].end  .toString(16).toUpperCase();
        }

        console.log(res)
    }





    if (!bytes.length)
        FATAL("No data to test!");

    console.log(`Scanning with ${bytes.length} bytes...`);

    if (MODE_INSTRUCTION)
        process_match_instruction();
    else if (MODE_DATA)
        FATAL("Unimplemented mode.")

    console.log("Done!");









}





main();


















