#include <Windows.h>
#include "res.h"

INT_PTR CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance,  LPTSTR szCmdLine, int iCmdShow)
{
  HWND hMainWindow = CreateDialogW(hInstance, MAKEINTRESOURCEW(IDD_MAINVIEW), NULL, WindowProc);
  ShowWindow(hMainWindow, iCmdShow);

  MSG msg = {};
  while (GetMessageW(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  return 0;
}
INT_PTR CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  static HBITMAP hBitmap = 0;
  static BITMAP bitmap = {};
  static RECT clientRect = {};
  static HICON hIcon = 0;

  static BOOL bStretch = FALSE;

  switch (uMsg)
  {
  case WM_INITDIALOG:
  {
    hBitmap = static_cast<HBITMAP> (LoadImageW(GetModuleHandleW(0), L"./../source/big_smile_face.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
    hIcon = static_cast<HICON>(LoadImageW(GetModuleHandleW(0), L"./../source/smile_face.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE));
    GetObjectW(hBitmap, sizeof(bitmap), &bitmap);

    HMENU hMenu = LoadMenuW(GetModuleHandleW(0), MAKEINTRESOURCE(IDR_MENU1));
    SetMenu(hwnd, hMenu);


    RECT rect = { 0,0,bitmap.bmWidth,bitmap.bmHeight };
    AdjustWindowRect(&rect, GetWindowLongW(hwnd, GWL_STYLE), FALSE); // pobranie stylu, false - czy okno ma menu

    SetWindowPos(hwnd, 0, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER); // polozenie rozmiar, glebokosc okna(warstwy)
    return TRUE;
  }
  case WM_SIZE:
  {
    clientRect.left = 0;
    clientRect.top = 0;
    clientRect.right = LOWORD(lParam);
    clientRect.bottom = HIWORD(lParam);
  }
  case WM_PAINT:
  {
    HDC hDC; // uchwyt do kontekstu urz¹dzenia
    hDC = GetDC(hwnd); // pobranie uchwytu do kontekstu okna
   // BitBlt(hDC, 0, 0, 800, 600, GetDC(0), 0, 0, SRCCOPY);

    HDC hDCBuff = CreateCompatibleDC(hDC);
    HBITMAP hBuff = CreateCompatibleBitmap(hDC, clientRect.right, clientRect.bottom);
    SelectObject(hDCBuff, hBuff);

    HDC hDCbitmap = CreateCompatibleDC(hDC);
    SelectObject(hDCbitmap, hBitmap);


    if (bStretch == TRUE)
    {
      BitBlt(hDCBuff, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hDCbitmap, 0, 0, SRCCOPY);
    }
    else
    {
      StretchBlt(hDCBuff, 0, 0, clientRect.right, clientRect.bottom,
        hDCbitmap, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
    }


      
    DrawIcon(hDCBuff, 0, 0, hIcon);

    BitBlt(hDC, 0, 0, clientRect.right, clientRect.bottom, hDCBuff, 0, 0, SRCCOPY);
    
    DeleteObject(hBuff);
    DeleteDC(hDCBuff);


    DeleteDC(hDCbitmap);
    ReleaseDC(hwnd, hDC);
    return TRUE;
  }
  case WM_CLOSE:
  {
    DestroyWindow(hwnd);
    PostQuitMessage(0); // do zamykania okna
    return TRUE;
  }

   case WM_COMMAND:
   {
       switch (HIWORD(wParam))
       {
           case BN_CLICKED:
               switch (LOWORD(wParam))
               {
                   case 40001:
                   {
                     bStretch = TRUE;
                       return 0;
                   }
                   case 40002:
                   {
                     bStretch = FALSE;
                       return 0;
                   }

                   default:
                       break;
               }
           default:
               break;
       }

   }
 

  }
  return 0; //DefWindowProcW(hwnd, uMsg, wParam, lParam);

}