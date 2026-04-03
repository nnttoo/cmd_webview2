#pragma once

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
#include "logtool.h"


#include "resource.h"
#include "tools.h"
#include "argtools.h"
#include <shlobj.h>

class MyWebView {
	 
	struct WebViewConfig
	{
		int width;
		int height;
		std::wstring url;
		int modewindow;
		int maximized;
		std::wstring title;
		bool isDebugMode = false;
		std::wstring wclassname;
	};

public : 

	wil::com_ptr<ICoreWebView2Controller> webviewController;
	wil::com_ptr<ICoreWebView2> webview;


	void realOpenWebview2(
		HWND hWnd,
		HINSTANCE hInstance,
		WebViewConfig config)
	{

		PWSTR localAppData = nullptr;
		SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppData);

		std::wstring userDataFolder =
			std::wstring(localAppData) +
			L"\\cmdWebView_" + config.wclassname + L".WebView2";

		LogPrint(userDataFolder);

		CreateCoreWebView2EnvironmentWithOptions(nullptr, userDataFolder.c_str(), nullptr,
			Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
				[this,hWnd, config](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {

			// Create a CoreWebView2Controller and get the associated CoreWebView2 whose parent is the main window hWnd
			env->CreateCoreWebView2Controller(hWnd, Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
				[this,hWnd, config](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {



				if (controller != nullptr) {
					this->webviewController = controller;
					this->webviewController->get_CoreWebView2(this->webview.put());
				}

				// Add a few settings for the webview
				// The demo step is redundant since the values are the default settings
				wil::com_ptr<ICoreWebView2Settings> settings;
				this->webview->get_Settings(&settings);
				settings->put_IsScriptEnabled(TRUE);
				settings->put_AreDefaultScriptDialogsEnabled(FALSE);
				settings->put_IsWebMessageEnabled(TRUE);
				settings->put_AreDefaultContextMenusEnabled(FALSE);
				// Resize WebView to fit the bounds of the parent window


				settings->put_AreDevToolsEnabled(config.isDebugMode);
				settings->put_AreDefaultContextMenusEnabled(config.isDebugMode);

				RECT bounds;
				GetClientRect(hWnd, &bounds);

				this->webviewController->put_Bounds(bounds);



				// Schedule an async task to navigate to Bing
				this->webview->Navigate(config.url.c_str());

				// <NavigationEvents>
				// Step 4 - Navigation events
				// register an ICoreWebView2NavigationStartingEventHandler to cancel any non-https navigation
				EventRegistrationToken token;
				this->webview->add_NavigationStarting(Microsoft::WRL::Callback<ICoreWebView2NavigationStartingEventHandler>(
					[](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
					 
					return S_OK;
				}).Get(), &token);

				if (config.title == L"auto") {
					this->webview->add_DocumentTitleChanged(Microsoft::WRL::Callback<ICoreWebView2DocumentTitleChangedEventHandler>(
						[this,hWnd](ICoreWebView2* webview, IUnknown* args) -> HRESULT {
						wil::unique_cotaskmem_string title;
						this->webview->get_DocumentTitle(&title);

						SetWindowTextW(hWnd, title.get()); 
						return S_OK;
					}).Get(), &token);
				}


				return S_OK;
			}).Get());
			return S_OK;
		}).Get());
	}

	HICON LoadIconFromFile(const std::wstring& filePath) {
		return (HICON)LoadImage(NULL, filePath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	}

	void openWebview2(

		HINSTANCE hInstance,
		ArgMap argmap

	) {
		WNDCLASSEX wcex;

		HICON hIcon = LoadIconFromFile(L"icon.ico");


		std::wstring classname = argmap.getVal(L"wndClassName");
		std::wstring wndClassnme = (classname != L"") ? classname : L"mywindowsClassName";

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;

		wcex.hIcon = hIcon;

		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = wndClassnme.c_str();
		wcex.hIconSm = hIcon;


		if (!RegisterClassEx(&wcex))
		{
			MessageBox(NULL,
				_T("Call to RegisterClassEx failed!"),
				_T("Windows Desktop Guided Tour"),
				NULL);

			return;
		}

		std::cout << "mulai membuka windows" << std::endl;
		std::wstring r;

		WebViewConfig config;
		config.wclassname = wndClassnme;
		config.width = ((r = argmap.getVal(L"width")) != L"") ? std::stoi(r) : 800;
		config.height = ((r = argmap.getVal(L"height")) != L"") ? std::stoi(r) : 600;
		config.url = ((r = argmap.getVal(L"url")) != L"") ? r : L"https://github.com/nnttoo/cmd_webview2";
		config.modewindow = ((r = argmap.getVal(L"kiosk")) != L"") ? WS_POPUP : WS_OVERLAPPEDWINDOW;
		config.maximized = ((r = argmap.getVal(L"maximize")) != L"") ? SW_MAXIMIZE : SW_NORMAL;
		config.title = ((r = argmap.getVal(L"title")) != L"") ? r : L"auto";
		config.isDebugMode = ((r = argmap.getVal(L"isDebugMode")) != L"") ? TRUE : FALSE;


		HINSTANCE hInst;
		// Store instance handle in our global variable
		hInst = hInstance;
		HWND hWnd = CreateWindowW(
			wndClassnme.c_str(),
			config.title.c_str(),
			config.modewindow,
			CW_USEDEFAULT, CW_USEDEFAULT,
			config.width, config.height,
			NULL,
			NULL,
			hInstance,
			this
		);

		if (!hWnd)
		{
			MessageBox(NULL,
				_T("Call to CreateWindow failed!"),
				_T("Windows Desktop Guided Tour"),
				NULL);

			return;
		}

		ShowWindow(hWnd, config.maximized);
		UpdateWindow(hWnd);

		realOpenWebview2(
			hWnd,
			hInst,
			config
		);

		// Main message loop:
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return;
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		MyWebView* self = (MyWebView*)GetWindowLongPtr(hWnd, GWLP_USERDATA);;


		switch (message)
		{
		case WM_NCCREATE:
		{
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam; 
			MyWebView* self = (MyWebView*)cs->lpCreateParams; 
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)self);

			return TRUE;
		}
		case WM_SIZE:
			if (self->webviewController != nullptr) {
				RECT bounds;
				GetClientRect(hWnd, &bounds);
				self->webviewController->put_Bounds(bounds);
			};
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}

		return 0;
	}
};

