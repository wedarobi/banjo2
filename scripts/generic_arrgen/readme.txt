
# Description
    Provide a list of bytes, along with a loose struct definition, and this script will generate all the elements of the array in C-style.

# Usage
    To use, put a run file in the <runs/> folder, then run it like so:
        node arrgen.js _example
    or like so:
        node arrgen.js _example.txt

# Structure of run file
    - first line: array of bytes
    - remaining lines: struct members

    (empty lines are ignored, as are lines starting with // (C++ style comments))
