

# Misc

- Port [dllmgr] to TypeScript.
    - There's actually no reason not to do this. If the only reason was that running [tsc] would be a pain, then just run an interactive transpile [tsc --watch] and make the window smaller. As the build script grows, it's much better to be able to abstract it away into smaller modules that are all type checked.


# DLL repo source:

- Make it so that referencing a DLL call from inside the same DLL does not result in a reference to the call table.




# DLL build UI:

- show DLL file hash in UI, so when you make an edit, you can see if it changed since the last time (draw it in black if unchanged)

    - or maybe just a "oooo"/"----" string at the end of single line statuses that show which versions changed
        o: cyan
        -: black



# DLL diff script

## "Smart" features (a.k.a. "let's actually make this shit enjoyable to use")

- Get [dllmgr] to signal to [diff_dll] to change DLLs if another one was changed
    - Then no manual intervention needed to switch DLLs
- Add some keystroke or whatever to switch between rom versions
    - If the current pubfn does not exist in that rom version, throw an error, but dont close the entire diff window
- Add some keystroke to go to the next pubfn
- Use some MIPS analyser program to look at a standard DLL and work out the start and end of existing functions. That way, we can easily automatically map our way through DLL diffs without manually specifying ANY offsets
    - No linking of the vanilla DLL needed, since it's linked at 0x00000000 and still valid. But we do need to tell it where .text starts.
    - Run the analyser with dllmgr.js, and get it to dump function offsets in a similar format to _pubfndump.txt (can use the same name, but keep in the expected/ subfolder instead), with each function named something like [func_000], [func_001], etc (decimal not hex)
    - ### We can actually make this MIPS analyser ourselves.
        1. Use the DLL preheader to find the length of .text (* 0x10)
        2. Use the other variables in the preheader to find the location of .text
        3. Use the function pointers in/after the DLL header to identify the location of all public functions.
            - This is used to identify static vs public functions for the dump.
        3. Iterate over every instruction in .text
            1. Skip any NOP instructions you encounter. Keep in mind the length of .text. Once you find a non-NOP instruction, assume that as the start of the current function.
                - This neatly handles the padding issue at the end of .text
            2. Try and cache the highest address you've encountered for the current function. As in, keep going through the function and read the offset of every single branch instruction to update the "max size of curr function" variable. Don't follow the branches though, just parse them and update the variable.
            3. If you encounter any jr $ra but the function is still larger based on previously seen branches, you know you have to keep going
            4. Only stop if you encounter a jr $ra while the max function location is <= your current offset in the file
            5. Add 8 bytes to the location of the jr $ra to mark the end of the curr function
            6. Keep going through [1-6] until you get to the maximum length of .text
        4. Name the functions you've found.
            - Use (decimal) template [fn_priv_00]       for static functions
            - Use (decimal) template [DLL_{dllName}_00] for public functions
        5. Output a function dump. Since this includes both static and public functions, name it something like [_fndump.txt]
- Check if the number of function symbols in vanilla and custom match. Remember to not mark any custom function as static.
    - Vanilla functions should be enumerated with the MIPS analyser. 
    - Custom functions should be enumerated with the public symbol dump. We can't trust an analyser on it, even if it can identify static functions.
        - Actually maybe try the analyser on it, and line up the _pubfndump.txt offsets with the analyser output to provide names for the ones we know, and some placeholder name like [fn_priv_00] for static ones
    - If there's a mismatch between the function counts, we can show the user an error, telling us to add any missing function declarations, and to temporarily remove the [static] keyword from unreferenced static functions. Once a static function is referenced from some included function, it won't be optimised away, and the [static] keyword can be added again. But just for convenience, only add the [static] keyword when you've OK-d most of the DLL. Keep the keyword commented out like [/*static*/] so you remember to remove it at the end.
- Keep some kind of memory on the state of a .c file, and when it is modified, try and autodetect the first function inside which the modification occurred. Then you can use function offsets to automatically go to that function.
    - The benefits of this are potentially enormous. It'll let you seamlessly jump from function to function, even across entire DLLs, with instant diffs every time. No more fiddling with passing args, calculating offsets, etc. The machine will automatically find what you wanted to diff. Dayum.
    - Get [dllmgr] to do any heavy lifting needed for this
    - If the modification was made OUTSIDE a function, don't change anything. Otherwise we'll change shit when we're editing .data
- Allow remembering the last scroll position and restoring it after a build while in the same function
    - This can work really well with the .c modification autodetection.
        - Keep an in-memory offset list of FUNCTIONS for every DLL for every ROMVER, and remember the scroll position for every single one. So as long as the diff window is open, it will be able to restore all your scroll positions automatically, even when switching between different functions and DLLs.
        - Naturally, this will also keep your CURRENT offset after you simply update the current function, even if not "Unchanged"






























