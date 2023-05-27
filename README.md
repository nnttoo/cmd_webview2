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
./CmdWebview2.exe \fun=openwebview url=https://quran-terjemah.org
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

You can see a complete example in the example folder.

# Changing the Icon

To change the icon on the webview window, you can use the tool [Resource Hacker](http://www.angusj.com/resourcehacker/).
