import express from "express";
import path from "path";
import fs from "fs";
import { execFile } from "child_process";
import { arch } from "os";
import { fileURLToPath } from "url";

const arc = arch();


const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

var exec = execFile; 
//D:\MyFolder\NodejsModule\WebView2Cmd\cmd_webview2\bin\Win32
let exeFilePath = path.join(__dirname, "../../bin/Win32/CmdWebview2.exe");
console.log("fileexepath : ", exeFilePath);
if (arc == "x64") {
    console.log("using x64")
    exeFilePath = path.join(__dirname, "../../bin/x64/CmdWebview2.exe");
}


function openWebview(address) {
    exec(exeFilePath,
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

function closeWindowWebView() {
    return new Promise((r, x) => {
        exec(exeFilePath,
            [
                "fun=closewindow",
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

app.get("/closewindow", async (r, x) => {

    let filepath = await closeWindowWebView();

    x.send(filepath)
})

let server = app.listen(port, () => {
    let rport = server.address().port;
    console.log(`http://localhost:${rport}`)
    openWebview("http://localhost:" + rport);
})