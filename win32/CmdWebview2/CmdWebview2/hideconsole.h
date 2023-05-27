#pragma once

#include <Windows.h>
#include "argtools.h"

HWND GetConsoleWindowByID(int processId)
{
    HWND hwndConsole = GetConsoleWindow();
    DWORD dwConsoleProcessId;

    // Mendapatkan process ID dari jendela console utama
    GetWindowThreadProcessId(hwndConsole, &dwConsoleProcessId);

    // Memeriksa apakah process ID cocok dengan ID yang diberikan
    if (dwConsoleProcessId == static_cast<DWORD>(processId))
    {
        // Mengembalikan HWND jika cocok
        return hwndConsole;
    }

    // Jika tidak cocok, mencari jendela console dengan process ID yang sesuai
    HWND hwnd = NULL;
    while ((hwnd = FindWindowEx(NULL, hwnd, TEXT("ConsoleWindowClass"), NULL)) != NULL)
    {
        GetWindowThreadProcessId(hwnd, &dwConsoleProcessId);
        if (dwConsoleProcessId == static_cast<DWORD>(processId))
        {
            // Mengembalikan HWND jika cocok
            return hwnd;
        }
    }

    // Jika tidak ditemukan jendela console dengan process ID yang sesuai
    return NULL;
}


void hideConsole(ArgMap argmap) {

	std::string pid = argmap.getVal("pid");
	if (pid != "") {
		int ipid = std::stoi(pid);
        std::cout << "ini pidnya " << pid << std::endl;
        HWND cwind = GetConsoleWindowByID(ipid);
        if (cwind != NULL) {
            ShowWindow(cwind, SW_HIDE);
        }
        else {
        std::cout << "hwindow null" << std::endl;
        }
        

	} 

}