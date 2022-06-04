const fs = require("fs");



let lines = (new Array(199)).fill("")
    .map((val, idx) => `    /* ${idx.toString().padStart(3, " ")} */ { MAP______, ASSET______, 00000000 },`)
    .join("\n")

fs.writeFileSync("./out_a.txt", lines);








