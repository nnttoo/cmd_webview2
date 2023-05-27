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

 

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{  
	ArgMap arg = ArgMap::parse(lpCmdLine);  
	std::string url = arg.getVal("title");
	std::cout << "ini url" << std::endl;
	std::cout << url << std::endl;


	std::string fun = arg.getVal("fun"); 
	 

	if (fun == "openwebview") {
		openWebview2(hInstance,arg);
	}
	else if (fun == "openFileDialog") {
		std::wstring result = openFileDialog(arg);
		std::wcout << L"result: " << result << std::endl; 
	}
	else if (fun == "openFolderDialog") {
		std::wstring result = openDirDialog(arg);
		std::wcout << L"result: " << result << std::endl;
	}
		

	return 0;
} 
