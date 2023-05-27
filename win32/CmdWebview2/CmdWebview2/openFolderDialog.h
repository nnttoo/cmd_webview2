#pragma once


#include <windows.h> 
#include "argtools.h"
#include "tools.h" 
#include <shlobj.h>

std::wstring openFileDialog(
    ArgMap argmap

) {
    std::wstring result;
    // Inisialisasi dialog
    OPENFILENAME ofn;
    TCHAR szFile[260] = { 0 }; 

    std::string filter = argmap.getVal("filter");
    std::wstring wfilter = L"All Files (*.*)\0*.*\0"; 
    std::vector<std::string> split = SplitString(filter, '|');

    if (split.size() > 0) {
        wfilter = ConvertToWideString(split[0]);
        wfilter += L"\0";
        wfilter += ConvertToWideString(split[1]);
        wfilter += L"\0";
    }

      


    std::wcout << wfilter << std::endl;
    std::cout << filter << std::endl;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = wfilter.c_str();
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Membuka dialog File Open
    if (GetOpenFileName(&ofn) == TRUE) { 

        result = ofn.lpstrFile; 
    }


    return result;

}

std::wstring openDirDialog() {
    BROWSEINFO bi;
    TCHAR szDir[MAX_PATH];

    ZeroMemory(&bi, sizeof(bi));
    bi.hwndOwner = NULL;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szDir;
    bi.lpszTitle = TEXT("Pilih Direktori");
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

    std::wstring result;
    // Membuka dialog File Dialog
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != NULL) {
         

        // Mengambil path direktori terpilih
        if (SHGetPathFromIDList(pidl, szDir)) {

            result = szDir; 
        }
        // Hapus PIDL setelah digunakan
        CoTaskMemFree(pidl);
    }

    return result;
     
}