import sys
import re
import random
import math

from enum import Enum
from typing import (
    Any,
    Dict,
    List,
    Match,
    NamedTuple,
    NoReturn,
    Optional,
    Set,
    Tuple,
    Union,
    Callable,
    Pattern,
)

from termcolor import colored as coloured
from numpy     import random as rand


class LO_Prim():
    prefix:   str
    lineno:   str
    opcode:   str
    operands: str
    def __init__(self, linearr) -> None:
        self.prefix   = linearr[0]
        self.lineno   = linearr[1]
        self.opcode   = linearr[2]
        self.operands = linearr[3]


class LO_Attr():
    empty: bool
    lineno: str
    lineno_int: int

    is_branch: bool
    branch_target: str
    branch_offset: int
    branch_distance: int
    infinite_loop: bool
    branch_colour: str

    line_idx: int
    nested_level: int

    grouped: bool
    group_id: int
    group_min_offset: int
    group_max_offset: int

    def __init__(self) -> None:
        self.empty            = False
        self.lineno           = ""
        self.lineno_int       = 0
        self.is_branch        = False
        self.branch_target    = ""
        self.branch_offset    = 0
        self.branch_distance  = 0
        self.infinite_loop    = False
        self.line_idx         = 0
        self.nested_level     = 0
        self.branch_colour    = "white"
        self.grouped          = False
        self.group_id         = -1
        self.group_min_offset = -1
        self.group_max_offset = -1


class LineObj():
    BRANCH_OPS = [
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
    ]

    def __init__(self, linearr) -> None:
        self.prim = LO_Prim(linearr)
        self.attr = LO_Attr()

        self.attr.empty      = self.prim.lineno == ""
        ## doesn't have comma
        self.attr.lineno     = re.sub(r":\s*?$", "", self.prim.lineno)
        self.attr.lineno_int = int("0x" + self.attr.lineno, 0) if self.attr.lineno else -1

        self.attr.is_branch       = self.prim.opcode.strip() in LineObj.BRANCH_OPS
        self.attr.branch_target   = re.search(r"0x([0-9a-f]+)", self.prim.operands)[1] if self.attr.is_branch else ""
        self.attr.branch_offset   = int(((int("0x" + self.attr.branch_target, 0) - int("0x" + self.attr.lineno, 0)) / 4) - 1 if self.attr.is_branch else 0)
        self.attr.branch_distance = int(abs(self.attr.branch_offset) + (-1 if self.attr.branch_offset < 0 else 1))
        self.attr.infinite_loop   = self.attr.branch_offset == -1


class NODETYPE(Enum):
    # It marks the first character of the arrow,
    # shown for branching out of a line.
    #
    # Conflicts with [INFINITE_LOOP_MARKER]
    #
    # Should never be overridden
    OUTGOING_FIRST = 1

    # Part of the outgoing arrow body.
    # (dash: vertical)
    #
    # Can be overridden
    OUTGOING_NORMAL_V = 2

    # Used when you have a branch group. If a "T" is placed,
    # you can put an arrow after it in the direction of the target
    GROUP_ARROW_DOWN = 10
    GROUP_ARROW_UP   = 11

    # Part of the outgoing arrow body.
    # (dash: horizontal)
    #
    # Can be overridden
    OUTGOING_NORMAL_H = 5
    INCOMING_NORMAL_H = 9

    OUTGOING_CORNER_UP   = 6
    OUTGOING_CORNER_DOWN = 7
    OUTGOING_CORNER_BOTH = 8

    # The head of an arrow
    #
    # Should never be overridden
    ARROWHEAD = 3

    # Marks the first character of the arrow,
    # shown for an instruction branching out to
    # itself, to show some special icon.
    #
    # Conflicts with [OUTGOING_FIRST]
    #
    # Should never be overridden
    INFINITE_LOOP_MARKER = 4


class Node():
    nodeType: NODETYPE
    ref:      LineObj
    def __init__(self, nodeType: NODETYPE, branchObject: LineObj):
        self.nodeType = nodeType
        self.ref      = branchObject


def line_special_split(line: str):

    out = []

    if not re.search(r'^[0-9a-f]+:', line):
        return ["", "", ""]

    if "&&&" in line:
        a = line.split("&&&")

        out = [a[0]]

        ## Replace operand delimiter
        a[1] = re.sub(r",", ", ", a[1])

        b = re.split(r"\s{2,}", a[1])

        #- Handle instructions with no operands, like NOP
        if len(b) == 1:
            b.append("")

        out += b

        return out

    lineno = re.sub(r":.+$", ":", line)
    remain = line[len(lineno):]

    return [lineno, remain, ""]


def generate_branching_arrows(input: List):

    def split_cb(line):
        i = 0
        for j in range(len(line)):
            if (re.search(r'^[0-9a-f]+:', line[j:])):
                i = j
                break

        prefix = line[0:i]

        b = line[i:]
        c = line_special_split(b)

        if len(c) < 3:
            return (prefix, "", "", "")

        lineno   = c[0]
        opcode   = c[1].ljust(8, " ") ## longest opcode string(s): "cvt.s.w"-like?
        operands = c[2]

        if not opcode:
            return (prefix, lineno, "", "")

        return (prefix, lineno, opcode, operands)


    lines_0: List[LineObj] = []
    lines_1: List[LineObj] = []
    lines_2: List[LineObj] = []

    for (i, e) in enumerate(input):
        s = e.base if e.base else ""
        lo = LineObj(split_cb(s))
        lo.attr.line_idx = i
        lines_0.append(lo)

    for (i, e) in enumerate(input):
        s = e.fmt2 if e.fmt2 else ""
        lo = LineObj(split_cb(s))
        lo.attr.line_idx = i
        lines_1.append(lo)

    for (i, e) in enumerate(input):
        s = e.key2 if e.key2 else ""
        lo = LineObj(split_cb(s))
        lo.attr.line_idx = i
        lines_2.append(lo)

    lines_0 = process_lines(lines_0)
    lines_1 = process_lines(lines_1)
    lines_2 = process_lines(lines_2)

    for i in range(len(input)):
        input[i].base = " " + lines_0[i]
        input[i].fmt2 = " " + lines_1[i]
        input[i].key2 = " " + lines_2[i]

    return input


def extend_board(board, times):
    for i in range(len(board)):
        for _ in range(times):
            board[i].append(None)

def ensure_board(board, size):
    length = len(board[0])

    if length < size:
        extend_board(board, size - length)


BRANCH_COLOURS = [
    "red", "green", "yellow", "blue", "magenta", "cyan", "white",
]

def gct(msg: str, colour: str):
    return coloured(msg, colour)


def process_lines(info: List[LineObj]):
    board: List[List[Node]] = [[] for _ in range(len(info))]

    branches: List[LineObj] = []
    for o in info:
        if o.attr.is_branch:
            branches.append(o)

    #- Set branch colours
    if True:
        #- Set branch colours randomly
        # for i in range(len(branches)):
        #     branches[i].attr.branch_colour = BRANCH_COLOURS[math.floor(random.random() * len(BRANCH_COLOURS))]

        #- Set branch colours semi-deterministically
        # seed  = 0xDEADB00B
        # state = rand.RandomState(rand.MT19937(rand.SeedSequence(seed)))
        # for i in range(len(branches)):
        #     branches[i].attr.branch_colour = BRANCH_COLOURS[math.floor(state.random() * len(BRANCH_COLOURS))]

        #- Set branch colours deterministically, based on target line index (crucially: always shared between target and current)
        for i in range(len(branches)):
            val = math.floor(rand.RandomState(rand.MT19937(rand.SeedSequence(branches[i].attr.line_idx * 3))).random() * len(BRANCH_COLOURS))
            branches[i].attr.branch_colour = BRANCH_COLOURS[val]

    #- Group branches together that share the same branch target
    if True:
        targetOffsetMap: Dict[str, List[LineObj]] = {}

        for branch in branches:
            ## Init
            if not branch.attr.branch_target in targetOffsetMap:
                targetOffsetMap[branch.attr.branch_target] = []

            ## Push self to map
            targetOffsetMap[branch.attr.branch_target].append(branch)

        group_id = 0
        if True:
            for offset in targetOffsetMap:
                #- Process single group

                group_id += 1

                arr = targetOffsetMap[offset]

                if len(arr) == 1:
                    ## Not a group
                    continue

                min_offset = math.inf
                max_offset = -1

                for branch in arr:
                    offset = branch.attr.line_idx

                    min_offset = min(min_offset, offset)
                    max_offset = max(max_offset, offset)

                    target = offset + (-branch.attr.branch_distance if branch.attr.branch_offset < 0 else branch.attr.branch_distance)
                    min_offset = min(min_offset, target)
                    max_offset = max(max_offset, target)

                ## Found the bounds. Now update all with the same values
                distance = max_offset - min_offset

                for branch in arr:
                    branch.attr.grouped          = True
                    branch.attr.group_id         = group_id
                    branch.attr.branch_distance  = distance
                    branch.attr.group_min_offset = min_offset
                    branch.attr.group_max_offset = max_offset


    #- Sort branches in order of branch distance
    if True:
        def sorter1(branch: LineObj):
            ## Has more precedence than a "0 distance" branch to the next instruction
            if branch.attr.infinite_loop:
                return -1

            return branch.attr.branch_distance

        def sorter2(branch: LineObj):
            return branch.attr.branch_offset

        def sorter3(branch: LineObj):
            return branch.attr.lineno_int

        branches.sort(key=sorter3)
        branches.sort(key=sorter2)
        branches.sort(key=sorter1)


    ## Make this sensible, setting it too high will affect performance
    MAX_NESTED_LEVEL = 40

    for branch in branches:
        start_idx = branch.attr.line_idx

        #- Set starting node
        ensure_board(board, 1)

        board[start_idx][0] = Node(NODETYPE.INFINITE_LOOP_MARKER if branch.attr.infinite_loop else NODETYPE.OUTGOING_FIRST, branch)

    for branch in branches:
        if branch.attr.infinite_loop:
            ## Nothing else to do, we're already done for this branch
            continue

        start_idx = branch.attr.line_idx
        end_idx   = start_idx + branch.attr.branch_offset + 1
        increment = 1 if start_idx < end_idx else -1

        #- Fix the ending indices by accounting for the line gaps
        ## Ending indices use branch imm, which doesn't account for gaps made during the diff
        i = start_idx
        while i != end_idx + increment:
            if info[i].attr.empty:
                end_idx += increment

            i += increment


        # Calculate the maximum nested level encountered; we need
        # to go 1 (or 2) more
        #
        # Corresponds to the index of the arrays inside the board.
        # Minimum level is 0: the first level.
        max_level = 0

        # Starting with the shortest branches (i.e. in current
        # sort order), calculate the right nested level,
        # and place nodes all along the track of the arrow

        #- Calculate nested level
        for i in range(start_idx, end_idx + increment, increment):
            for j in range(MAX_NESTED_LEVEL):
                if i == end_idx and j == 0 and max_level < 1:
                    #- Special case check for base element
                    ## Move the nest up by one if the base element is special
                    if board[i][j] is not None and board[i][j].nodeType in [NODETYPE.OUTGOING_FIRST, NODETYPE.INFINITE_LOOP_MARKER]:
                        max_level += 1
                        break
                
                #! This runs all the way until the max nested level anyway, should we just init the board fully from the start?
                ensure_board(board, j + 1)

                if board[i][j] is not None:
                    max_level = max(max_level, j)


        #- Calculate nested level for entire branch group, if applicable
        if branch.attr.grouped:
            for i in range(branch.attr.group_min_offset, branch.attr.group_max_offset):
                for j in range(MAX_NESTED_LEVEL):
                    ensure_board(board, j + 1)

                    if board[i][j] is not None:
                        max_level = max(max_level, j)


        nested_level = max_level + 1

        branch.attr.nested_level = nested_level

        show_arrow = True


        #- Merge groups
        for i in range(2):
            node = board[end_idx][i]

            if node is not None and node.nodeType == NODETYPE.ARROWHEAD and node.ref.attr.group_id == branch.attr.group_id:
                #- Found an arrowhead from the same group, synchronise!

                branch.attr.branch_colour = node.ref.attr.branch_colour
                branch.attr.nested_level  = node.ref.attr.nested_level

                nested_level = branch.attr.nested_level

                ## No need to show an arrow, another branch in the same group showed one
                show_arrow = False


        #- Set nodes along the path
        if True:
            ## Set nodes at the start line
            if True:
                ## Always start at 1, since we've already set the OUTGOING_FIRST
                for i in range(1, nested_level):
                    if board[start_idx][i] is None:
                        board[start_idx][i] = Node(NODETYPE.OUTGOING_NORMAL_H, branch)

                board[start_idx][nested_level] = Node(NODETYPE.OUTGOING_CORNER_UP if increment < 0 else NODETYPE.OUTGOING_CORNER_DOWN, branch)

            ## Set nodes at the end line
            if True:
                base_level = 1

                for i in range(len(board[end_idx])):
                    if board[end_idx][i] is None or board[end_idx][i].nodeType not in [NODETYPE.OUTGOING_FIRST, NODETYPE.INFINITE_LOOP_MARKER, NODETYPE.ARROWHEAD]:
                        base_level = i
                        break

                if show_arrow:
                    board[end_idx][base_level] = Node(NODETYPE.ARROWHEAD, branch)

                for i in range(base_level + 1, nested_level):
                    board[end_idx][i] = Node(NODETYPE.INCOMING_NORMAL_H, branch)

                board[end_idx][nested_level] = Node(NODETYPE.OUTGOING_CORNER_DOWN if increment < 0 else NODETYPE.OUTGOING_CORNER_UP, branch)

            ## Set nodes in the middle
            for i in range(start_idx + increment, end_idx, increment):
                ## Check for a node by a group member
                node = board[i][nested_level]

                ## Set vertical line node if the space is free
                if node is None:
                    board[i][nested_level] = Node(NODETYPE.OUTGOING_NORMAL_V, branch)
                ## Merge with other branches with the same destination
                elif node.ref.attr.group_id == branch.attr.group_id and node.nodeType in [NODETYPE.OUTGOING_CORNER_UP, NODETYPE.OUTGOING_CORNER_DOWN]:
                    #- Found!

                    ## Mark the intersection with a "T"
                    # board[i][nested_level] = Node(NODETYPE.OUTGOING_CORNER_BOTH, branch)

                    ## Mark the intersection with a symbol that clearly shows the direction of the target
                    board[i][nested_level] = Node(NODETYPE.GROUP_ARROW_UP if increment < 0 else NODETYPE.GROUP_ARROW_DOWN, branch)

    return render_board(board, info)


def ASCII_get_for_node(node: Node):
    nodeType = node.nodeType
    colour   = node.ref.attr.branch_colour

    PLACEHOLDER = ""

    # C_OUTGOING_LINE_H = "­"; ## lightly dashed
    C_OUTGOING_LINE_H = "─"

    LTR = [
        PLACEHOLDER,
        C_OUTGOING_LINE_H,
        "│",
        "→",
        "◊",
        C_OUTGOING_LINE_H,
        "└",
        "┌",
        "├",
        "─",
        "┟",
        "┞",
    ]

    RTL = [
        PLACEHOLDER,
        C_OUTGOING_LINE_H,
        "│",
        "←",
        "◊",
        C_OUTGOING_LINE_H,
        "┘",
        "┐",
        "┤",
        "─",
        "┧",
        "┦",
    ]

    return gct(LTR[nodeType.value], colour)


def strip_colour(string: str):
    if not string:
        return ""

    return re.sub(r"\x1b[^m]+m", "", string, flags="g")


def render_board(board: List[List[Node]], info: List[LineObj]) -> List[str]:
    out = []

    max_level = 0
    for (idx, line) in enumerate(board):
        for (depth, cell) in enumerate(line):
            if cell:
                max_level = max(max_level, depth + 1)

    for (idx, line) in enumerate(board):
        res = ""

        branch = ""

        for i in range(max_level - 1, -1, -1):
            cell = line[i]

            if cell is None:
                branch += " "
                continue

            ## There's a node at this cell
            node = cell

            branch += ASCII_get_for_node(node)

        ## instruction data
        if True:
            prefix   = info[idx].prim.prefix
            lineno   = info[idx].prim.lineno
            opcode   = info[idx].prim.opcode
            operands = info[idx].prim.operands

            if not prefix:   prefix   = ""
            if not lineno:   lineno   = ""
            if not opcode:   opcode   = ""
            if not operands: operands = ""

            res += branch + f" {prefix}{lineno} {opcode} {operands.strip()}".ljust(28, " ")
        
        out.append(res)

    return out


def DEBUG_view_board(board: List[List[Node]], info: List[LineObj]):
    res = ""

    max_level = 0
    for (idx, line) in enumerate(board):
        for (depth, cell) in enumerate(line):
            if cell:
                max_level = max(max_level, depth + 1)

    for (idx, line) in enumerate(board):
        ## prepad
        res += "   "

        for i in range(max_level - 1, -1, -1):
            cell = line[i]

            if cell is None:
                res += " "
                continue

            ## There's a node at this cell
            node = cell

            res += ASCII_get_for_node(node)

        ## instruction data
        if True:
            prefix   = info[idx].prim.prefix
            lineno   = info[idx].prim.lineno
            opcode   = info[idx].prim.opcode
            operands = info[idx].prim.operands

            if not prefix:   prefix   = ""
            if not lineno:   lineno   = ""
            if not opcode:   opcode   = ""
            if not operands: operands = ""

            res += f" {prefix}{opcode} {operands.strip()}".ljust(28, " ")
        
        res += "\r\n"

    sys.stdout.write(res)


if __name__ == "__main__":
    pass

