#include <windows.h>
#include "res.h"

HINSTANCE g_hInstance;
HINSTANCE g2_hInstance;
bool kajko=false;
bool kokosz=false;

void end(bool kajko, bool kokosz)
{
  if (kajko == true && kokosz ==true) PostQuitMessage(0);
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_INITDIALOG:
  {
    HICON hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_KAJKO));
    SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    
    HMENU hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_KAJKOMENU));
    SetMenu(hwndDlg, hMenu);
    
    return FALSE;
  }
  case WM_CLOSE:
    DestroyWindow(hwndDlg);
    kajko = true;
    end(kajko, kokosz);
    return TRUE;
  }
  return FALSE;
}
INT_PTR CALLBACK DialogProc2(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_INITDIALOG:
  {
    HICON hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_KOKOSZ));
    SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

    HMENU hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDR_KOKOSZMENU));
    SetMenu(hwndDlg, hMenu);

    return FALSE;
  }
  case WM_CLOSE:
    DestroyWindow(hwndDlg);
    kokosz = true;
    end(kajko, kokosz);
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine , int iCmdShow)

{
  g_hInstance = hInstance;
  g2_hInstance = hInstance;
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

  HWND hwndMainWindow2 = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW2), NULL, DialogProc2);
  ShowWindow(hwndMainWindow2, iCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}

/*NAPISAÆ PROGRAM "JAK¥ LICZBÊ MAM NA MYŒLI" "WYBIERZ LICZBÊ Z ZAKRESU 1-40"
CZY LICZBA JEST WIÊKSZA OD TEGO ?*/