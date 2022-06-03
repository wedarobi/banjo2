const fs = require("fs");



let lines = fs.readFileSync("./dlls.txt")
    .toString()
    .trim()
    .split(/(?:\r?\n)+/)
    .map(line => line.split(/\s+/g)[0])
    .sort()
    .map(name => `/* $ ${name} */`)
    .join("\n")

fs.writeFileSync("./dlls_out.txt", lines);








