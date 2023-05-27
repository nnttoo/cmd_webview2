var exec = require('child_process').execFile;

var arc = require('os').arch();

let exeFilePath  = "../bin/Win32/CmdWebview2.exe";
if(arc=="x64"){
    console.log("using x64")
    exeFilePath = "../bin/x64/CmdWebview2.exe";
}

 
let cmd = "openweb";
if(process.argv.length > 2){

    cmd = process.argv[2];
}


if(cmd == "openweb"){
    exec(exeFilePath,
    [
        "fun=openwebview",
        "url=https://quran-terjemah.org",
        "width=1300", 
        "height=600",
        //"kiosk=true",
        //"maximize=true",
        "title=Windows%20Title%20Test",

    ], (err, data) => {
        console.log(data)
    })
} else if(cmd == "openfile"){
    exec(exeFilePath,
    [
        "fun=openFileDialog", 
        "filter=" + encodeURIComponent("Image Files |*.bmp;*.jpg;*.jpeg;*.png;*.gif"),

    ], (err, data) => { 

       let filepath = "";
       for(let l of data.split("\r\n")){
            if(l.startsWith("result:")){
                filepath = l.substring(7, l.length);
            }
       } 

        console.log(filepath);
    })

} else if(cmd == "opendir"){
    exec(exeFilePath,
    [
        "fun=openFolderDialog",  

    ], (err, data) => { 

       let filepath = "";
       for(let l of data.split("\r\n")){
            if(l.startsWith("result:")){
                filepath = l.substring(7, l.length);
            }
       } 

        console.log(filepath);
    })

}

// run with command :
// node index.js openfile

