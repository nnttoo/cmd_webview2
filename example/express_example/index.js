let express = require('express');
let path = require('path');

var exec = require('child_process').execFile;
var arc = require('os').arch();

let exeFilePath  = "../../bin/Win32/CmdWebview2.exe";
if(arc=="x64"){
    console.log("using x64")
    exeFilePath = "../../bin/x64/CmdWebview2.exe";
}

function openWebview(address){
    exec(exeFilePath,
        [
            "fun=openwebview",
            "url=" + encodeURIComponent(address),
            "width=1300", 
            "height=600",
            //"kiosk=true",
            //"maximize=true",
            "title=auto",
    
        ], (err, data) => {
            console.log(data)
            server.close();
        })
}

const app = express();
const port = 2020 // random port

app.use(express.static(path.join(__dirname,'html')))

let server = app.listen(port, () => {
    let rport = server.address().port;
    console.log(`Example app listening on port ${rport}`)
    openWebview("http://localhost:" + rport);
  })