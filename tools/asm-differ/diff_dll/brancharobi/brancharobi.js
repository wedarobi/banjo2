const fs = require("fs");
const fsp = require("fs/promises");


function log(msg)
{
    console.log(msg);
}

function line_to_obj(linearr)
{
    let _branch_ops =
    [
        "b",
        "beq",
        "bne",
        "beqz",
        "bnez",
        "bgez",
        "bgtz",
        "blez",
        "bltz",
        "bc1t",
        "bc1f",
        "beql",
        "bnel",
        "beqzl",
        "bnezl",
        "bgezl",
        "bgtzl",
        "blezl",
        "bltzl",
        "bc1tl",
        "bc1fl",
    ];

    let o =
    {
        /**
         * Strings that can be used to reconstruct the original line
         */
        prim:
        {
            prefix:   linearr[0],
            lineno:   linearr[1],
            opcode:   linearr[2],
            operands: linearr[3],
        },
        /**
         * Attributes that were parsed from the primitives and
         * should be used for processing
         */
        attr:
        {
            /**
             * If the line is a "removal" or "addition" and hence has no instruction data.
             * The lines of the arrows should be written over these as well.
             */
            empty:           false,
            lineno:          "",
            lineno_int:      0,

            is_branch:       false,
            /**
             * Does not have "0x" prefix, so can be compared with [lineno] directly
             */
            branch_target:   "",

            /**
             * Integer, +1 for each instruction.
             * . -1 means infinite loop, since pc increments by one
             * . negative values means backwards
             */
            branch_offset: 0,
            /**
             * Same as offset, but magnitude (no direction)
             */
            branch_distance: 0,
            /**
             * If the branch jumps to itself (i.e. imm === -1)
             */
            infinite_loop:   false,

            /**
             * The position of this line in the overall line array.
             * Set in another place
             */
            lineIdx: 0,

            /**
             * Branch nesting level.
             * Calculated later, used to store how far the arrow goes
             * out from the instruction, visually
             */
            nestedLevel: 0,

            branch_colour: "white",

            grouped: false,
            groupId: -1,


        },
    };

    o.attr.empty              = o.prim.lineno === "";
    //# doesn't have comma
    o.attr.lineno             = o.prim.lineno.replace(/:\s*?$/, "");
    o.attr.lineno_int         = o.attr.lineno ? parseInt(o.attr.lineno, 16) : -1;

    o.attr.is_branch          = _branch_ops.includes(o.prim.opcode.trim());
    o.attr.branch_target      = o.attr.is_branch ? o.prim.operands.match(/0x([0-9a-f]+)/)[1] : "";
    o.attr.branch_offset      = o.attr.is_branch ? ((parseInt(o.attr.branch_target, 16) - parseInt(o.attr.lineno, 16)) / 4) - 1 : "";
    o.attr.branch_distance    = Math.abs(o.attr.branch_offset) + (o.attr.branch_offset < 0 ? -1 : 1);
    o.attr.infinite_loop      = o.attr.branch_offset === -1;

    return o;
}

let gIdx = 0;

function _split_cb(line)
{
    let a = line.split("=====")[gIdx]

    let i = 0;
    for (; i < a.length; i++)
        if (/^[0-9a-f]+:/.test(a.substr(i)))
            break;

    let prefix = a.substr(0, i);

    let b = a.substr(i);
    let c = b.split("&&&")

    if (c.length < 2)
        return [prefix, "", "", ""];

    let lineno = c[0];
    let instr  = c[1];

    if (!instr)
        return [prefix, lineno, "", ""];

    let d = instr.split(/\s+/g)

    //# longest opcode string(s): "cvt.s.w"-like?
    let opcode = d[0].padEnd(8, " ");

    //# "?." for nop lines
    let operands = d[1]?.replace(/,/g, "  ");

    return [prefix, lineno, opcode, operands];
}

async function main()
{

    let full_dump = (await fsp.readFile("./output_dump.txt"))
        .toString()
        .trim()
        .split(/\r?\n/g);


    let lines_target = full_dump.map(_split_cb);
    gIdx = 1;
    let lines_current = full_dump.map(_split_cb);


    // let out1 = process_lines(lines_target)
    let out2 = process_lines(lines_current)


}




/**
 * Increase the maximum nest level of the board
 *
 * @param {Object[][]} board
 * @param {number} times
 */
function extend_board(board, times)
{
    for (let i = 0; i < board.length; i++)
        for (let j = 0; j < times; j++)
            board[i].push(null);

    return board;
}

/**
 *
 * @param {Object[][]} board
 * @param {number} size
 */
function ensure_board(board, size)
{
    let len = board[0].length;

    if (len < size)
        board = extend_board(board, size - len);

    return board;
}

const NODETYPE =
{
    /**
     * It marks the first character of the arrow,
     * shown for branching out of a line.
     *
     * Conflicts with [INFINITE_LOOP_MARKER]
     *
     * Should never be overridden
     */
    OUTGOING_FIRST: 1,

    /**
     * Part of the outgoing arrow body.
     * (dash: vertical)
     *
     * Can be overridden
     */
    OUTGOING_NORMAL_V: 2,

    /**
     * Part of the outgoing arrow body.
     * (dash: horizontal)
     *
     * Can be overridden
     */
    OUTGOING_NORMAL_H: 5,

    OUTGOING_CORNER_UP:   6,
    OUTGOING_CORNER_DOWN: 7,
    OUTGOING_CORNER_BOTH: 8,

    /**
     * The head of an arrow
     *
     * Should never be overridden
     */
    ARROWHEAD: 3,

    /**
     * Marks the first character of the arrow,
     * shown for an instruction branching out to
     * itself, to show some special icon.
     *
     * Conflicts with [OUTGOING_FIRST]
     *
     * Should never be overridden
     */
    INFINITE_LOOP_MARKER: 4,
};

function get_node(nodeType, branchObject)
{
    return {
        /**
         * Used to tell what kind of ASCII character should
         * occupy this place in the final output.
         */
        nodeType,
        /**
         * A reference to the original branch object
         */
        ref: branchObject,
    };
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

const BRANCH_COLOURS =
[
    "red", "green", "yellow", "blue", "pink", "cyan",
];

function gct(msg, colour, underline=false)
{
    let ul = underline ? "4m" : "1m";
    let reset = "\x1b[97;0;0m";

    let code = colour in COLOUR_CODES
        ? COLOUR_CODES[colour]
        : COLOUR_CODES["white"];

    return `\x1b[${code};${ul}${msg}${reset}`;
}

function process_lines(inputLines)
{
    let info = inputLines.map((line, i) =>
    {
        let o = line_to_obj(line);
        //# Set line index here, since we know it
        o.attr.lineIdx = i;
        return o;
    });

    /**
     * An array of arrays, represents the "board" of lines we want to fill
     */
    let board = new Array(info.length);
    for (let i = 0; i < board.length; i++)
        board[i] = [];


    let branches     = info.filter(o => o.attr.is_branch);

    //- Set random branch colours
    for (let i = 0; i < branches.length; i++)
        branches[i].attr.branch_colour = BRANCH_COLOURS[~~(Math.random() * BRANCH_COLOURS.length)];

    //- Merge branches that share the same branch target
    {
        let targetOffsetMap = {};

        for (let branch of branches)
        {
            //# Init
            if (!(branch.attr.branch_target in targetOffsetMap))
                targetOffsetMap[branch.attr.branch_target] = [];

            //# Push self to map
            targetOffsetMap[branch.attr.branch_target].push(branch);
        }

        let groupId = 0;
        for (let offset in targetOffsetMap)
        {
            //- Process single group

            groupId++;

            let arr = targetOffsetMap[offset];

            if (arr.length === 1)
                //# Not a group
                continue;

            let minOffset = Infinity;
            let maxOffset = -1;

            //# Find the min and max bounds of all the combined branches
            for (let branch of arr)
            {
                // let offset = ~~(branch.attr.lineno_int / 4);
                let offset = branch.attr.lineIdx;

                minOffset = Math.min(minOffset, offset);
                maxOffset = Math.max(maxOffset, offset);

                let target = offset + (branch.attr.branch_offset < 0
                    ? -branch.attr.branch_distance
                    :  branch.attr.branch_distance);
                minOffset = Math.min(minOffset, target);
                maxOffset = Math.max(maxOffset, target);
            }

            //# Found the bounds. Now update all with the same values
            let distance = maxOffset - minOffset;
            for (let branch of arr)
            {
                branch.attr.grouped         = true;
                branch.attr.groupId         = groupId;
                branch.attr.branch_distance = distance;
            }
        }
    }

    //- Sort branches in order of branch distance
    {
        branches.sort((a, b) =>
        {
            if (false);

            //# Has more precedence than a "0 distance" branch to the next instruction
            else if ( a.attr.infinite_loop && !b.attr.infinite_loop)  return -1;
            else if (!a.attr.infinite_loop &&  b.attr.infinite_loop)  return  1;

            //# Direction doesn't really matter
            else if (a.attr.branch_distance < b.attr.branch_distance) return -1;
            else if (a.attr.branch_distance > b.attr.branch_distance) return  1;

            //# Check direction now, just to be deterministic
            else if (a.attr.branch_offset   < b.attr.branch_offset)   return -1;
            else if (a.attr.branch_offset   > b.attr.branch_offset)   return  1;

            //# Earlier lines first, just to be deterministic
            else if (a.attr.lineno_int      < b.attr.lineno_int)      return -1;
            else if (a.attr.lineno_int      > b.attr.lineno_int)      return  1;

            //# This conditional branch shouldn't ever be executed, but anyway
            else                                                      return  0;
        });
    }

    /**
     * Make this sensible, setting it too high will affect performance
     */
    const MAX_NESTED_LEVEL = 40;

    /**
     * We process the branch information as if it were flipped horizontally.
     * Extending the nested layers to the right (pushing) is easier than
     * working to the left.
     */

    for (let branch of branches)
    {
        let startIdx = branch.attr.lineIdx;

        //- Set starting node
        {
            ensure_board(board, 1);

            board[startIdx][0] = get_node(branch.attr.infinite_loop ? NODETYPE.INFINITE_LOOP_MARKER : NODETYPE.OUTGOING_FIRST, branch);
        }
    }

    for (let branch of branches)
    {
        if (branch.attr.infinite_loop)
            //# Nothing else to do, we're already done for this branch
            continue;

        let startIdx  = branch.attr.lineIdx;
        let endIdx    = startIdx + branch.attr.branch_offset + 1;
        let increment = startIdx < endIdx ? 1 : -1;


        //- Fix the ending indices by accounting for the line gaps
        {
            for (let i = startIdx; i !== endIdx + increment; i += increment)
                if (info[i].attr.empty)
                    endIdx += increment;
        }

        /**
         * Calculate the maximum nested level encountered; we need
         * to go 1 (or 2) more
         *
         * Corresponds to the index of the arrays inside the board.
         * Minimum level is 0: the first level.
         */
        let maxLevel = 0;

        /**
         * Starting with the shortest branches (i.e. in current
         * sort order), calculate the right nested level,
         * and place nodes all along the track of the arrow
         */
        {
            //- Calculate nested level
            for (let i = startIdx; i !== endIdx + increment; i += increment)
            {
                for (let j = 0; j < MAX_NESTED_LEVEL; j++)
                {
                    if (i === endIdx && j === 0 && maxLevel < 1)
                    {
                        //- Special case check for base element
                        //# Move the nest up by one if the base element is special
                        if ([NODETYPE.OUTGOING_FIRST, NODETYPE.INFINITE_LOOP_MARKER].includes(board[i][j]?.nodeType))
                        {
                            maxLevel++; //# sets to 1
                            break;
                        }
                    }

                    //! This runs all the way until the max nested level anyway, should we just init the board fully from the start?
                    ensure_board(board, j + 1);

                    if (board[i][j] !== null)
                        maxLevel = Math.max(maxLevel, j);
                }
            }

            let nestedLevel = maxLevel + 1;

            branch.attr.nestedLevel = nestedLevel;

            let showArrow = true;

            //- Merge groups
            {
                for (let i = 0; i < 2; i++)
                {
                    let node = board[endIdx][i];

                    if (node?.nodeType === NODETYPE.ARROWHEAD
                     && node.ref.attr.groupId === branch.attr.groupId)
                    {
                        //- Found an arrowhead from the same group, synchronise!

                        branch.attr.branch_colour = node.ref.attr.branch_colour;
                        branch.attr.nestedLevel   = node.ref.attr.nestedLevel;

                        nestedLevel = branch.attr.nestedLevel;

                        //# No need to show an arrow, another branch in the same group showed one
                        showArrow = false;
                    }
                }
            }

            //- Set nodes along the path
            {
                //# Set nodes at the start line
                {
                    //# Always start as 1, since we've already set the OUTGOING_FIRST
                    for (let i = 1; i < nestedLevel; i++)
                        if (board[startIdx][i] === null)
                            board[startIdx][i] = get_node(NODETYPE.OUTGOING_NORMAL_H, branch);

                    board[startIdx][nestedLevel] = get_node(increment < 0 ? NODETYPE.OUTGOING_CORNER_UP : NODETYPE.OUTGOING_CORNER_DOWN, branch);
                }

                //# Set nodes at the end line
                {
                    let baseLevel = 1;

                    {
                        for (let i = 0; i < board[endIdx].length; i++)
                        {
                            if (![NODETYPE.OUTGOING_FIRST, NODETYPE.INFINITE_LOOP_MARKER, NODETYPE.ARROWHEAD].includes(board[endIdx][i]?.nodeType))
                            {
                                baseLevel = i;
                                break;
                            }
                        }
                    }

                    if (showArrow)
                        board[endIdx][baseLevel] = get_node(NODETYPE.ARROWHEAD, branch);

                    for (let i = baseLevel + 1; i < nestedLevel; i++)
                        board[endIdx][i] = get_node(NODETYPE.OUTGOING_NORMAL_H, branch);

                    board[endIdx][nestedLevel] = get_node(increment < 0 ? NODETYPE.OUTGOING_CORNER_DOWN : NODETYPE.OUTGOING_CORNER_UP, branch);
                }

                //# Set nodes in the middle
                for (let i = startIdx + increment; i != endIdx; i += increment)
                {
                    //# Check for a node by a group member
                    {
                        let node = board[i][nestedLevel];
                        if (node
                            && node.ref.attr.groupId === branch.attr.groupId
                            && [NODETYPE.OUTGOING_CORNER_UP, NODETYPE.OUTGOING_CORNER_DOWN].includes(node.nodeType))
                        {
                            //- Found!
                            board[i][nestedLevel] = get_node(NODETYPE.OUTGOING_CORNER_BOTH, branch);

                            //# Don't do anything else
                            continue;
                        }
                    }

                    board[i][nestedLevel] = get_node(NODETYPE.OUTGOING_NORMAL_V, branch);
                }
            }
        }
    }

    DEBUG_view_board(board, info);



}

const USE_LTR_MODE = true;

function ASCII_get_for_node(node)
{
    let nodeType = node.nodeType;
    let colour   = node.ref.attr.branch_colour;

    const PLACEHOLDER = " ";

    const LTR = [
    /* 00 */ PLACEHOLDER,
    /* 01 */ "─",
    /* 02 */ "│",
    /* 03 */ "→",
    /* 04 */ "◊",
    /* 05 */ "─",
    /* 06 */ "└",
    /* 07 */ "┌",
    /* 08 */ "├",
    ];

    const RTL = [
    /* 00 */ PLACEHOLDER,
    /* 01 */ "─",
    /* 02 */ "│",
    /* 03 */ "←",
    /* 04 */ "◊",
    /* 05 */ "─",
    /* 06 */ "┘",
    /* 07 */ "┐",
    /* 08 */ "┤",
    ];

    return gct((USE_LTR_MODE ? LTR : RTL)[nodeType], colour);
}

function strip_colour(str)
{
    if (!str)
        return "";

    return str.replace(/\x1b[^m]+m/g, "");
}

function DEBUG_view_board(board, info)
{
    let res = "";


    //- Find max depth of arrows
    let maxLevel = 0;
    {
        for (let [idx, line] of board.entries())
        {
            for (let [depth, cell] of line.entries())
            {
                if (cell)
                    maxLevel = Math.max(maxLevel, depth + 1);
            }
        }
    }

    for (let [idx, line] of board.entries())
    {
        //# prepad
        res += "   ";

        // for (let i = 0; i < maxLevel; i++) //= RTL mode
        for (let i = maxLevel - 1; i >= 0; i--) //= LTR mode
        {
            let cell = line[i];

            if (!cell)
            {
                res += " ";
                continue;
            }

            //# There's a node at this cell
            let node = cell;
            foundNonemptyCell = true;

            res += ASCII_get_for_node(node);
        }

        //# instruction data
        {
            let prefix   = info[idx].prim.prefix;
            let opcode   = info[idx].prim.opcode;
            let operands = info[idx].prim.operands;

            if (!prefix)   prefix   = "";
            if (!opcode)   opcode   = "";
            if (!operands) operands = "";

            res += ` ${prefix}${opcode} ${operands.trim()}`.padEnd(28, " ");
        }

        res += "\r\n";
    }

    process.stdout.write(res);
}


main();

