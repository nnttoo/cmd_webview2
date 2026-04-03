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

	std::wstring filter = argmap.getVal(L"filter");
	std::wstring wfilter = L"All Files (*.*)\0*.*\0";
	std::vector<std::wstring> split = SplitStringW(filter, '|');

	if (split.size() > 0) {
		wfilter = split[0];
		wfilter += L"\0";
		wfilter += split[1];
		wfilter += L"\0";
	}




	/*
	Find window owner by class name
	*/
	std::wstring classname = argmap.getVal(L"wndClassName");
	std::wstring wndClassnme = (classname != L"") ? classname : L"mywindowsClassName";
	HWND hWndOwner = FindWindowW(wndClassnme.c_str(), NULL);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWndOwner;
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

std::wstring openDirDialog(
	ArgMap argmap
) {
	BROWSEINFO bi;
	TCHAR szDir[MAX_PATH];


	std::wstring classname = argmap.getVal(L"wndClassName");
	std::wstring wndClassnme = (classname != L"") ? classname : L"mywindowsClassName";
	HWND hWndOwner = FindWindowW(wndClassnme.c_str(), NULL);

	ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = hWndOwner;
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

std::wstring closeWebViewWindow(
	ArgMap argmap
) {

	std::wstring classname = argmap.getVal(L"wndClassName");
	std::wstring controlcmd = argmap.getVal(L"controlcmd");
	if (classname == L"") return L"noclassname";



	HWND hWndOwner = FindWindowW(classname.c_str(), NULL);

	std::wstring result = L"window not found";
	if (hWndOwner != NULL) {
		if (controlcmd == L"close") {

			PostMessage(hWndOwner, WM_CLOSE, 0, 0);
		}
		else if (controlcmd == L"maximize") {
			ShowWindow(hWndOwner, SW_MAXIMIZE);
			SetForegroundWindow(hWndOwner);
		}
		else if (controlcmd == L"minimize") {
			ShowWindow(hWndOwner, SW_MINIMIZE);
		}

		else if (controlcmd == L"move") {
			std::wstring top = argmap.getVal(L"top");
			std::wstring left = argmap.getVal(L"left");

			if (top != L"" && left != L"") {
				int itop = std::stoi(top);
				int ileft = std::stoi(left);
				{
					SetWindowPos(hWndOwner, NULL, ileft, itop, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
					SetForegroundWindow(hWndOwner);
				}
			} 
			 
		}

		else if (controlcmd == L"resize") {
			std::wstring height = argmap.getVal(L"height");
			std::wstring width = argmap.getVal(L"width");

			if (height != L"" && width != L"") {
				int iheight = std::stoi(height);
				int iwidth = std::stoi(width);
				{
					SetWindowPos(hWndOwner, NULL, 0, 0, iwidth, iheight, SWP_NOMOVE | SWP_NOZORDER);
					SetForegroundWindow(hWndOwner);
				}
			}

		}
		result = L"success";
	}

	return result;

}