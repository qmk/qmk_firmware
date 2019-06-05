const fs = require("fs");
const strict = process.argv[2] === "--strict";
const walk = function(dir, filter) {
    var results = [];
    var list = fs.readdirSync(dir);
    list.forEach(function(file) {
        file = dir + "/" + file;
        var stat = fs.statSync(file);
        if (stat && stat.isDirectory()) {
            /* Recurse into a subdirectory */
            results = results.concat(walk(file, filter));
        } else {
            /* Is a file */
            if (file.toLowerCase().endsWith(filter.toLowerCase())) {
                results.push(file);
            }
        }
    });
    return results;
};
const regexExclude = /keymaps\/(.*)via\//g;
const containsSRC = [];
const filesToScan = walk("./keyboards", "rules.mk");
for (const f of filesToScan) {
    if(regexExclude.test(f)){
        continue;
    }
    let content = fs.readFileSync(f, "utf-8");
    content = content.replace(/\\\n/g, "");
    const lines = content.split("\n");
    for (const l of lines) {
        if (l.startsWith("SRC =")) {
            const basepath = f.replace("./keyboards/", "");
            const imports = l
                .replace("SRC =", "")
                .replace(/\t/g, "")
                .split(" ");
            for (const i of imports) {
                const p = i.split("/");
                if (p[0] === "keyboards" && p[1] !== basepath.split("/")[0]) {
                    containsSRC.push(f);
                }
            }
        }
    }
}
if (containsSRC.length > 0) {
    console.log(JSON.stringify(containsSRC));
    console.log(`${containsSRC.length} files contains SRC illegal refs`);
    if (strict) {
        console.log(`Error!!`);
        process.exit(1);
    } else {
        console.log(`Non strict, exiting silently!`);
    }
} else {
    console.log(`All files are OK!`);
}
