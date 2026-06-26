#pragma once
#include <windows.h>
#include "../ScreenCapture.hpp"
#include <vector>

namespace ssc {
    struct Monitor {
        HMONITOR hMonitor;
        RECT rcMonitor;
    };

    // Callback for EnumDisplayMonitors
    inline BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC, LPRECT lprcMonitor, LPARAM dwData) {
        auto monitors = reinterpret_cast<std::vector<Monitor>*>(dwData);
        Monitor info;
        info.hMonitor = hMonitor;
        info.rcMonitor = *lprcMonitor;
        monitors->push_back(info);
        return TRUE;
    }


    inline std::vector<Monitor> GetMonitors() {
        std::vector<Monitor> monitors;
        EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(&monitors));

        return monitors;
    }

    inline void CaptureMonitor(Monitor& monitor,ScreenCapture& sc) {
        RECT rcVirtual;
        rcVirtual.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
        rcVirtual.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
        rcVirtual.right = rcVirtual.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
        rcVirtual.bottom = rcVirtual.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);

        HBITMAP bitmap;

        CaptureRect(monitor.rcMonitor,sc);

    }
}