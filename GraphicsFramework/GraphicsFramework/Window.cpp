
#include "Window.h"

Window::Window(int width, int height)
    : width(width), height(height)
{
    hInstance = GetModuleHandle(nullptr);
}

Window::~Window()
{
    if (hwnd && IsWindow(hwnd))
    {
        DestroyWindow(hwnd);
    }
}
int Window::GetWidth()
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    return rect.right - rect.left;
}

int Window::GetHeight()
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    return rect.bottom - rect.top;
}

bool Window::Create()
{
    const wchar_t* className = L"DX12Window";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;

    if (!RegisterClass(&wc) &&
        GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
    {
        return false;
    }

    RECT rect = { 0, 0, width, height };

    AdjustWindowRect(
        &rect,
        WS_OVERLAPPEDWINDOW,
        FALSE
    );

    hwnd = CreateWindowEx(0, className,L"DirectX 12 Framework", WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
        rect.right - rect.left,rect.bottom - rect.top,nullptr, nullptr, hInstance, nullptr );

    if (!hwnd)
    {
        return false;
    }
       

    ShowWindow(hwnd, SW_SHOW);

    return true;
}

LRESULT CALLBACK Window::WindowProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Window::ProcessMessages()
{
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) 
        {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

HWND Window::GetHWND() const
{
    return hwnd;
}
