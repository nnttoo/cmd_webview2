// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <wrl.h>
#include <wil/com.h> 
#include <sstream>
// <IncludeHeader>
// include WebView2 header
#include "WebView2.h"
// </IncludeHeader>
#include <vector>
#include <iostream> 
#include "tools.h"
#include "resource.h"
#include "argtools.h"
#include "openWebview2.h"
#include "openFolderDialog.h" 
#include "execbatfile.h"
#include "./splash.h"



int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	 

	ArgMap arg = ArgMap::parse(lpCmdLine);
	std::wstring url = arg.getVal(L"url");
	std::cout << "url" << std::endl;
	std::wcout << url << std::endl;


	std::wstring fun = arg.getVal(L"fun");

	if (fun == L"openwebview") {

		closeSplashScreen(); 
		MyWebView mweb = MyWebView();

		mweb.openWebview2(hInstance, arg);
	}
	else if (fun == L"openFileDialog") {
		std::wstring result = openFileDialog(arg);
		std::wcout << L"result: " << result << std::endl;
	}
	else if (fun == L"openFolderDialog") {
		std::wstring result = openDirDialog(arg);
		std::wcout << L"result: " << result << std::endl;
	}

	else if (fun == L"controlwindow") {
		std::wstring result = closeWebViewWindow(arg);
		std::wcout << L"result: " << result << std::endl;
	}
	else {
		 
		
		runBatFile(); 
		if (FileExists(L"splash.png"))
		{

			showSplashScreen(L"splash.png");
		}
		

	}

	return 0;
}
