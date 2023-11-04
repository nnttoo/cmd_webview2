@echo off

REM Menentukan path ke direktori MSBuild
set "msbuild_path=C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"

REM Menentukan path ke file solusi (sln)
set "solution_path=%~dp0CmdWebview2.sln"

REM Memanggil MSBuild untuk membangun proyek dengan konfigurasi yang tepat
"%msbuild_path%" "%solution_path%" /p:Configuration=Release /p:Platform=x64

if %errorlevel% equ 0 (
    echo Proyek telah berhasil dibangun.
) else (
    echo Proyek gagal dibangun.
)
