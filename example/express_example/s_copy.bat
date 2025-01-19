@echo off

:: ini digunakan untuk mencopy file dari
:: folder release Visual Studio ke folder bin

set binfolder=.\bin
set binWin32=%binfolder%\Win32
set binX64=%binfolder%\x64

mkdir %binfolder%
mkdir %binWin32%
mkdir %binX64%

set projectFolder=..\..\win32\CmdWebview2
set releaseWin32=%projectFolder%\bin\Release\Win32\
set releasex64=%projectFolder%\bin\Release\x64\

copy %releaseWin32%CmdWebview2.exe %binWin32%\CmdWebview2.exe
copy %releaseWin32%WebView2Loader.dll %binWin32%\WebView2Loader.dll
copy %releaseWin32%WebView2Loader.dll %binWin32%\icon.ico

copy %releasex64%CmdWebview2.exe %binX64%\CmdWebview2.exe
copy %releasex64%WebView2Loader.dll %binX64%\WebView2Loader.dll
copy %releasex64%WebView2Loader.dll %binX64%\icon.ico

echo File copied successfully. 
