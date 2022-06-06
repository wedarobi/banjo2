const fs = require("fs");



const gRootDir = __dirname + path.sep + ".." + path.sep;
const gCurrDir = __dirname + path.sep;




async function main()
{
    fs.rmSync(gRootDir + "build",    { recursive: true });
    fs.rmSync(gRootDir + "expected", { recursive: true });
}

main();









