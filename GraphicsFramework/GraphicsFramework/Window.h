#pragma once
#include <windows.h>

class Window
{
private:
    HWND hwnd = nullptr;
    HINSTANCE hInstance = nullptr;

    int width;
    int height;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam
    );

public:
    Window(int width, int height);
    ~Window();

    bool Create();
    bool ProcessMessages();

    HWND GetHWND() const;
};
