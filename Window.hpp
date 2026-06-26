#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include "ScreenCapture.hpp"

namespace ssc {
    struct window {
        std::string title;
        HWND hwnd = nullptr;
        WINDOWINFO info;
    };

    static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
        int length = GetWindowTextLength(hWnd);
        char* buffer = new char[length + 1];
        GetWindowText(hWnd, buffer, length + 1);
        std::string windowTitle(buffer);
        delete[] buffer;

        auto& w = *reinterpret_cast<window*>(lparam);

        if (IsWindowVisible(hWnd) && length != 0 && windowTitle == w.title) {
            w.hwnd = hWnd;
        }

        return true;
    }

    inline bool GetWindowIfExists(window& w) {
        EnumWindows(enumWindowCallback, reinterpret_cast<LPARAM>(&w));
        return w.hwnd != nullptr;
    }


    inline void CaptureWindow(window& w, ScreenCapture& sc) {
        GetWindowInfo(w.hwnd, &w.info);
        RECT rc = w.info.rcWindow;
        CaptureRect(rc,sc);
    }
}
