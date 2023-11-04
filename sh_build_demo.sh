#!/bin/sh
pkg ./demo/express_demo/package.json


./s_copy_release.sh

binfolder="./bin"
binWin32=$binfolder/Win32

demofolder="./demo_release"

cp $binWin32/CmdWebview2.exe $demofolder/
cp $binWin32/WebView2Loader.dll $demofolder/
cp ./demo/index.bat $demofolder/


# clear demo folder
# rm - r ./demo_release/*
