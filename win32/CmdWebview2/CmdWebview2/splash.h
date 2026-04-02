#pragma once 
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <thread>
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

class MySplash
{
private:
    ULONG_PTR token = 0;
    Image* img = nullptr;
    HWND hwnd = nullptr;
    std::thread th;
    std::wstring imgPath;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        MySplash* self;

        if (msg == WM_NCCREATE)
        {
            CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
            self = (MySplash*)cs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)self);
        }

        self = (MySplash*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

        if (!self)
            return DefWindowProc(hWnd, msg, wParam, lParam);

        switch (msg)
        {
        case WM_CREATE:
            self->img = new Image(self->imgPath.c_str());

            if (self->img && self->img->GetLastStatus() == Ok)
            {
                UINT w = self->img->GetWidth();
                UINT h = self->img->GetHeight();

                SetWindowPos(hWnd, NULL, 0, 0, w, h, SWP_NOMOVE);
            }
            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            Graphics g(hdc);

            if (self->img)
                g.DrawImage(self->img, 0, 0);

            EndPaint(hWnd, &ps);
        }
        break;

        case WM_DESTROY:
            if (self->img)
            {
                delete self->img;
                self->img = nullptr;
            }
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    void threadFunc()
    {
        GdiplusStartupInput in;
        GdiplusStartup(&token, &in, NULL);

        HINSTANCE hInst = GetModuleHandle(NULL);

        WNDCLASS wc = {};
        wc.lpfnWndProc = WndProc;
        wc.hInstance = hInst;
        wc.lpszClassName = L"MySplashWnd";

        RegisterClass(&wc);

        hwnd = CreateWindowEx(
            WS_EX_TOPMOST,
            wc.lpszClassName,
            L"",
            WS_POPUP,
            0, 0, 300, 200,
            NULL, NULL, hInst, this
        );

        // center window
        int screenW = GetSystemMetrics(SM_CXSCREEN);
        int screenH = GetSystemMetrics(SM_CYSCREEN);

        RECT rc;
        GetWindowRect(hwnd, &rc);

        int w = rc.right - rc.left;
        int h = rc.bottom - rc.top;

        SetWindowPos(hwnd, NULL,
            (screenW - w) / 2,
            (screenH - h) / 2,
            0, 0,
            SWP_NOSIZE | SWP_NOZORDER);

        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);

        // message loop di thread sendiri
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        GdiplusShutdown(token);
    }

public:
    MySplash(const std::wstring& path)
    {
        imgPath = path;
        th = std::thread(&MySplash::threadFunc, this);
    }

    void close()
    {
        if (hwnd)
        {
            PostMessage(hwnd, WM_CLOSE, 0, 0);
        }

        if (th.joinable())
            th.join();
    }
};


/// helper biar clean
inline MySplash* showSplash(const std::wstring& path)
{
    return new MySplash(path);
}