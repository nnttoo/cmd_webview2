let express = require('express');
let path = require('path');
let fs = require("fs")

console.log(process.env.mypath);

var exec = require('child_process').execFile;
var arc = require('os').arch();

let exeFilePath = "./bin/Win32/CmdWebview2.exe";
if (arc == "x64") {
    console.log("using x64")
    exeFilePath = "./bin/x64/CmdWebview2.exe";
}

exeFilePath = path.join(process.cwd(),exeFilePath); 
 
function openWebview(address) {
    exec(exeFilePath ,
        [
            "fun=openwebview",
            "wndClassName=aplikasiWebView",
            "url=" + address,
            "width=900",
            "height=600",
            //"kiosk=true",
            //"maximize=true",
            "title=auto",

        ], (err, data) => {
            console.log("error yaaa" + err)
            server.close();
        })
}

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

let server = app.listen(port, () => {
    let rport = server.address().port;
    console.log(`http://localhost:${rport}`) 
    openWebview("http://localhost:" + rport);
})