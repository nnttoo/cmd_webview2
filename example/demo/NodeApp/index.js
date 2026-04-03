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
let exeFilePath = path.join(__dirname, "../CmdWebview2.exe");
console.log("fileexepath : ", exeFilePath);
if (arc == "x64") {
    console.log("using x64")
    exeFilePath = path.join(__dirname, "../CmdWebview2.exe");
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
            //"isDebugMode=true"

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

function sleep(n) {
    return new Promise((r, x) => {
        setTimeout(() => {
            r();
        }, n);
    })
}


let timePing = Date.now();

async function runCheck() {
    console.log("run check");
    while (true) {
        if (Date.now() > timePing + (1000 * 10)) {
            break;
        }

        await sleep(1000);
    }
    console.log("process exit");
    process.exit();
}
runCheck();

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


app.get("/pingserver", async (r, x) => {

    timePing = Date.now();

    x.send("ok")
})

app.get("/closewindow", async (r, x) => {

    exec(
        exeFilePath,
        [
            "fun=controlwindow",
            "wndClassName=aplikasiWebView",
            "controlcmd=close",

        ],
        (err, data) => {
            console.log(data);
        });

    x.send("ok")
});


app.get("/movewindow", async (r, x) => {

    exec(exeFilePath,
        [
            "fun=controlwindow",
            "wndClassName=aplikasiWebView",
            "controlcmd=move",
            "top=0",
            "left=0",

        ], (err, data) => {
            console.log(data);
        });

    x.send("ok")
})


app.get("/resize", async (r, x) => {

    exec(exeFilePath,
        [
            "fun=controlwindow",
            "wndClassName=aplikasiWebView",
            "controlcmd=resize",
            "width=600",
            "height=600",

        ], (err, data) => {
            console.log(data);
        });

    x.send("ok")
})
app.get("/maximize", async (r, x) => {

    exec(exeFilePath,
        [
            "fun=controlwindow",
            "wndClassName=aplikasiWebView",
            "controlcmd=maximize" 

        ], (err, data) => {
            console.log(data);
        });

    x.send("ok")
})

app.get("/minimize", async (r, x) => {

    exec(exeFilePath,
        [
            "fun=controlwindow",
            "wndClassName=aplikasiWebView",
            "controlcmd=minimize" 

        ], (err, data) => {
            console.log(data);
        });

    x.send("ok")
})

let server = app.listen(port, () => {
    let rport = server.address().port;
    console.log(`http://localhost:${rport}`)
    openWebview("http://localhost:" + rport);
})