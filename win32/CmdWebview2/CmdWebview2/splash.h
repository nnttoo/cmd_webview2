#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <thread>
#include <atomic>

#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

static constexpr LPCWSTR splashScreenClassName = L"mysplashclassname";
class MySplash
{
private:
    ULONG_PTR token = 0;
    Image* img = nullptr;
    HWND hwnd = nullptr; 
    std::wstring imgPath; 

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        MySplash* self = (MySplash*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

        if (msg == WM_NCCREATE)
        {
            CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
            self = (MySplash*)cs->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)self);
        }

        if (!self)
            return DefWindowProc(hWnd, msg, wParam, lParam);

        switch (msg)
        {
        case WM_CREATE:
        {
            self->img = new Image(self->imgPath.c_str());

            if (self->img && self->img->GetLastStatus() == Ok)
            {
                UINT w = self->img->GetWidth();
                UINT h = self->img->GetHeight();
                // Ambil ukuran layar
                int screenW = GetSystemMetrics(SM_CXSCREEN);
                int screenH = GetSystemMetrics(SM_CYSCREEN);

                // Hitung posisi tengah
                int posX = (screenW - (int)w) / 2;
                int posY = (screenH - (int)h) / 2;

                // Atur posisi DAN ukuran sekaligus di sini
                SetWindowPos(hWnd, NULL, posX, posY, (int)w, (int)h, SWP_NOZORDER);
            }
        }
        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            Graphics g(hdc);

            if (self->img)
            {
                // Ambil ukuran area dalam jendela (client area)
                RECT rc;
                GetClientRect(hWnd, &rc);

                // Konversi RECT ke Gdiplus::Rect
                Rect destRect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);

                // Gambar ulang dengan memaksa ukuran sesuai destRect
                g.DrawImage(self->img, destRect);
            }

            EndPaint(hWnd, &ps);
        }
        break;

        case WM_CLOSE:
            DestroyWindow(hWnd);
            return 0;

        case WM_DESTROY: 
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

public:
    void showAndWait()
    {
        GdiplusStartupInput in;
        GdiplusStartup(&token, &in, NULL);

        HINSTANCE hInst = GetModuleHandle(NULL);

        WNDCLASS wc = {};
        wc.lpfnWndProc = WndProc;
        wc.hInstance = hInst;
        wc.lpszClassName = splashScreenClassName;

        RegisterClass(&wc);

        hwnd = CreateWindowEx(
            WS_EX_TOPMOST | WS_EX_APPWINDOW,
            wc.lpszClassName,
            L"",
            WS_POPUP,
            0, 0, 100, 100,
            NULL, NULL, hInst, this
        );

        // center
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

        MSG msg;
        while ( GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (img)
        {
            delete img;
            img = nullptr;
        }

        GdiplusShutdown(token);
    }

    MySplash(const std::wstring& path)
    {
        imgPath = path; 
    }
     
};
inline void showSplashScreen(const std::wstring& path) {
    MySplash mySplash = MySplash(path);
    mySplash.showAndWait();
}
inline void closeSplashScreen() {
    HWND hWndOwner = FindWindowW(splashScreenClassName, NULL);
    if (hWndOwner != NULL) {
        PostMessage(hWndOwner, WM_CLOSE, 0, 0);
    }
}