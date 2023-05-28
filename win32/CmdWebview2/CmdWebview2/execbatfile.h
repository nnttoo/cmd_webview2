#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>

bool FileExists(const std::wstring& filePath)
{
    std::ifstream file(filePath);
    return file.good();
}

int runBatFile() {


    std::cout << "jalani file" << std::endl;

    // Mendapatkan path eksekusi
    wchar_t  exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);

    // Manipulasi path untuk mendapatkan path ke file batch di folder yang sama
    std::wstring exeDir = exePath;
    size_t lastSlashIndex = exeDir.find_last_of(L"\\/");
    std::wstring batPath = exeDir.substr(0, lastSlashIndex + 1) + L"index.bat";

    // Memeriksa keberadaan file batch
    if (!FileExists(batPath))
    {
        std::cout << "File batch tidak ditemukan." << std::endl;
        return 0;
    }

    // Struktur untuk menyimpan informasi proses
    STARTUPINFO si;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    PROCESS_INFORMATION pi;
     

    // Membersihkan struktur
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Membuat proses baru untuk menjalankan file batch
    if (CreateProcess(NULL, const_cast<wchar_t*>(batPath.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
    {
        std::cout << "menunggu file" << std::endl; 

        // Menutup handle proses dan thread
        //WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    { 
        // Gagal membuat proses
        std::cout << "Gagal menjalankan file batch. Error: " << GetLastError() << std::endl;
    }

    return 0;

}