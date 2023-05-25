var exec = require('child_process').execFile;

exec("../win32/CmdWebview2/x64/Debug/CmdWebview2.exe",
    [
        "fun=openwindow",
        "url=https://quran-terjemah.org",
        "width=1300",
        "max", 

    ], (err, data) => {
        console.log(data)
    })