#include <windows.h>
#include "res.h"

HINSTANCE g_hInstance;
HINSTANCE g2_hInstance;

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
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
        MessageBox(hwndDlg,TEXT("KOKOSZ"),TEXT("SLAM"),MB_OK);
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);
        return TRUE;
      }
    }
    return FALSE;
  case WM_CLOSE:
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
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
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
        MessageBox(hwndDlg, TEXT("Super atak"), TEXT("KAJKO SLASH"), MB_OK);
        return TRUE;
      }
    }
    return FALSE;
  case WM_CLOSE:
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
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