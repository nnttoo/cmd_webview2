#!/bin/sh

# ini digunakan untuk mencopy file dari
# folder relese visual studio ke folder bin

binfolder="./node_cmd_webview2/bin"
binWin32=$binfolder/Win32
binX64=$binfolder/x64

mkdir $binfolder
mkdir $binWin32
mkdir $binX64


projectFolder="./win32/CmdWebview2"
releaseWin32=$projectFolder/Win32/Release
releasex64=$projectFolder/x64/Release


cp $releaseWin32/CmdWebview2.exe $binWin32/CmdWebview2.exe
cp $releaseWin32/WebView2Loader.dll $binWin32/WebView2Loader.dll


cp $releasex64/CmdWebview2.exe $binX64/CmdWebview2.exe
cp $releasex64/WebView2Loader.dll $binX64/WebView2Loader.dll