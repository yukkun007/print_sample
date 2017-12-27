/* Copyright 2017 yukkun007 */
#include <windows.h>
#include <tchar.h>
#include <iostream>

//int WINAPI _tWinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
//            LPTSTR lpCmdLine , int nCmdShow ) {
int main() {
    wchar_t defalut_printer[256];
    unsigned long size = _countof(defalut_printer);
    GetDefaultPrinter(defalut_printer, &size);
    std::wcout << L"defalut printer: \"" << defalut_printer << "\"";

    HDC hdc;
    if (!(hdc = CreateDC(NULL, defalut_printer, NULL, NULL))) {
        MessageBox(NULL, L"DCが得られません", L"ERROR", MB_OK);
        return -1;
    }

    DOCINFO doc_info = {0};
    doc_info.cbSize = sizeof(DOCINFO);
    doc_info.lpszDocName = L"test";

    if (StartDoc(hdc, &doc_info) > 0 && StartPage(hdc) > 0) {
        SetMapMode(hdc, MM_LOMETRIC);
        Ellipse(hdc, 0, 0, 500, -500);

        LPCTSTR text = L"this is a pen.";
        TextOut(hdc, 0, 0, text, lstrlen(text));

        EndPage(hdc);
        EndDoc(hdc);
    }
    DeleteDC(hdc);
    return 0;
}
