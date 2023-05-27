# cmd_webview2

The **Cmd Webview2** package provides convenience for using Microsoft Edge WebView2 through the command line or various other programming languages that mostly support command line execution.

This package is inspired by [webview/webview](https://github.com/webview/webview) and [electron](https://www.electronjs.org/) but focuses more on ease of use, as all its features can be accessed simply by typing commands in cmd.exe.

CmdWebview has a very small file size, you just need to copy the bin folder which is only around 300KB in size.

There are several main features, including:

- Opening a webview, equipped with kiosk/frameless mode
- Opening a file dialog with filters
- Opening a folder dialog

There are several examples in the example folder for usage with Node.js.


# Usage

To use this package, you need to download and install the Microsoft Edge WebView2 runtime:

[Webview2 Runtime](https://developer.microsoft.com/en-us/microsoft-edge/webview2/)

Next, type the command:

```sh
./CmdWebview2.exe fun=openwebview url=https://quran-terjemah.org
```
 

example 1

```sh
./CmdWebview2.exe fun=openwebview url=https://google.com width=900 height=500
```
 

example 2
```sh
./CmdWebview2.exe fun=openwebview url=https://google.com width=900 height=500 kiosk=true maximize=true
```

example 3
```sh
#!/bin/sh
./bin/x64/CmdWebview2.exe \
fun=openwebview \
url=https://quran-terjemah.org \
width=900 \
height=500 \
title=Title%20must%20use%20URLencode
```
# Use with nodejs

Nodejs open webview
```js
    var exec = require('child_process').execFile;
    var arc = require('os').arch();

    let exeFilePath  = "../bin/Win32/CmdWebview2.exe";
    if(arc=="x64"){
        console.log("using x64")
        exeFilePath = "../bin/x64/CmdWebview2.exe";
    }

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
```


Nodejs open file dialog
```js
    var exec = require('child_process').execFile;
    var arc = require('os').arch();

    let exeFilePath  = "../bin/Win32/CmdWebview2.exe";
    if(arc=="x64"){
        console.log("using x64")
        exeFilePath = "../bin/x64/CmdWebview2.exe";
    }

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
```

You can see a complete example in the example folder.

# Changing the Icon

To change the icon you can open this project with visual studio in the win32 folder, or you can use a tool like: [Resource Hacker](http://www.angusj.com/resourcehacker/).

# screenshot

![alt ss](https://github.com/nnttoo/cmd_webview2/blob/main/ss.png?raw=true)
