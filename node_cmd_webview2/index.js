
let path = require('path'); 
var exec = require('child_process').execFile;
var arc = require('os').arch();
let exeFilePath = "./bin/Win32/CmdWebview2.exe";
if (arc == "x64") {
    console.log("using x64")
    exeFilePath = "./bin/x64/CmdWebview2.exe";
}


exeFilePath = path.join(__dirname, exeFilePath);
 
module.exports = {
    openWebview : (address)=>{
        console.log(exeFilePath);
        return new Promise((r,x)=>{
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
                    console.log("data dari web "+ data) 
                    r(data);
                })
        })
        
    } 
}