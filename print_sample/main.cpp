/* Copyright 2017 yukkun007 */
#include <windows.h>
#include <tchar.h>
#include <iostream>

int main() {
    unsigned long size = 0;  // NOLINT (win api)
    wchar_t* defalut_printer = nullptr;
    if (!GetDefaultPrinter(nullptr, &size) &&
        GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        defalut_printer = new wchar_t[size];
        if (!GetDefaultPrinter(defalut_printer, &size)) {
            MessageBox(NULL, L"規定プリンタ名の取得に失敗", L"ERROR", MB_OK);
            return -1;
        }
        std::wcout << L"defalut printer: \"" << defalut_printer << "\"";
    } else {
        MessageBox(NULL, L"予期せぬエラー", L"ERROR", MB_OK);
        return -1;
    }

    HDC hdc;
    if ((hdc = CreateDC(NULL, defalut_printer, NULL, NULL)) == nullptr) {
        MessageBox(NULL, L"DCが得られません", L"ERROR", MB_OK);
        return -1;
    }
    delete []defalut_printer;

    DOCINFO doc_info = {0};
    doc_info.cbSize = sizeof(DOCINFO);
    doc_info.lpszDocName = L"test";

    if (StartDoc(hdc, &doc_info) <= 0 || StartPage(hdc) <= 0) {
        MessageBox(NULL, L"StartDoc/StartPageに失敗", L"ERROR", MB_OK);
        return -1;
    }

    SetMapMode(hdc, MM_LOMETRIC);
    Ellipse(hdc, 0, 0, 500, -500);
    LPCTSTR text = L"this is a pen.";
    TextOut(hdc, 0, 0, text, lstrlen(text));

    EndPage(hdc);
    EndDoc(hdc);
    DeleteDC(hdc);

    return 0;
}
