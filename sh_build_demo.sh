#!/bin/sh

# file ini berguna untuk membuild express_demo
# sehingga hasilnya akan berada di folder demo_release
# yang bisa dijalankan sebagaimana aplikasi pada umumnya

# This file is used to build the express_demo
# so that the result will be in the demo_release folder
# which can be run like a typical application


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
