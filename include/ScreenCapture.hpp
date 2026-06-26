#pragma once
#include <windows.h>
#include <iostream>
#include <vector>

namespace ssc {
    class ScreenCapture {
    public:

        ScreenCapture() : width(0), height(0) {}
        ScreenCapture(HDC h, HBITMAP b) : hMemoryDC(h), hBitmap(b), width(0), height(0) {}

        ~ScreenCapture() {
            clear();
        }

        void clear() {
            DeleteObject(hBitmap);
            DeleteDC(hMemoryDC);
            hBitmap = nullptr;
            hMemoryDC = nullptr;
        }

        HDC hMemoryDC = nullptr;
        HBITMAP hBitmap = nullptr;
        int width, height;
        std::vector<unsigned char> bits;

    };

    // Capture a given RECT area
    inline bool CaptureRect(const RECT& rc, ScreenCapture& sc) {
        int width = rc.right - rc.left;
        int height = rc.bottom - rc.top;

        HDC hScreenDC = GetDC(nullptr);
        HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
        HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

        SelectObject(hMemoryDC, hBitmap);

        sc.hBitmap = hBitmap;
        sc.hMemoryDC = hMemoryDC;
        sc.width = width;
        sc.height = height;



        if (!BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, rc.left, rc.top, SRCCOPY)) {
            std::cerr << "BitBlt failed.\n";
            ReleaseDC(nullptr, hScreenDC);
            return false;
        }


        ReleaseDC(nullptr, hScreenDC);


        BITMAPINFOHEADER bi = {0};
        auto bmp = sc.hBitmap;

        bi.biSize = sizeof(BITMAPINFOHEADER);
        bi.biWidth = sc.width;
        bi.biHeight = -sc.height; // top-down
        bi.biPlanes = 1;
        bi.biBitCount = 32;
        bi.biCompression = BI_RGB;
        bi.biSizeImage = ((sc.width * bi.biBitCount + 31) / 32) * 4 * sc.height;


        sc.bits.resize(bi.biSizeImage);
        GetDIBits(sc.hMemoryDC, bmp, 0, sc.height, sc.bits.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);


        return true;
    }

}