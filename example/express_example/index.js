let express = require('express');
let path = require('path'); 
let cmdWebview2 = require("node_cmd_webview2");
 

var exec = require('child_process').execFile;
var arc = require('os').arch();

let exeFilePath = "../../bin/Win32/CmdWebview2.exe";
if (arc == "x64") {
    console.log("using x64")
    exeFilePath = "../../bin/x64/CmdWebview2.exe";
}
 

exeFilePath = path.join(__dirname, exeFilePath);

 

function openFileDilog() {
    return new Promise((r, x) => {
        exec(exeFilePath,
            [
                "fun=openFileDialog",
                "wndClassName=aplikasiWebView",
                "filter=Image Files |*.bmp;*.jpg;*.jpeg;*.png;*.gif",

            ], (err, data) => {

                let filepath = "";
                for (let l of data.split("\r\n")) {
                    if (l.startsWith("result:")) {
                        filepath = l.substring(7, l.length);
                    }
                }

                r(filepath);
            })
    })
}
function openFileDilogFolder() {
    return new Promise((r, x) => {
        exec(exeFilePath,
            [
                "fun=openFolderDialog",
                "wndClassName=aplikasiWebView",

            ], (err, data) => {

                let filepath = "";
                for (let l of data.split("\r\n")) {
                    if (l.startsWith("result:")) {
                        filepath = l.substring(7, l.length);
                    }
                }

                r(filepath);
            })
    })
}
 




const app = express();
const port = 0; // 0 random port

app.use(express.static(path.join(__dirname, 'html')))
app.get("/openfiledialog", async (r, x) => {

    let filepath = await openFileDilog();

    x.send(filepath)
})
app.get("/openfolderdialog", async (r, x) => {

    let filepath = await openFileDilogFolder();

    x.send(filepath)
})

let server = app.listen(port, async () => {
    let rport = server.address().port;
    console.log(`http://localhost:${rport}`) 
    await cmdWebview2.openWebview("http://localhost:" + rport);
    server.close();
})