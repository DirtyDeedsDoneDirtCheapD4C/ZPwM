#include <windows.h>
#include "res.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>


int look(int a)
{
  if (a == 0) return 0;
  else if (a > 0) return 1;
  else if (a < 0) return -1;
}

int wylosowana_liczba;
int counter = 0;
int ngcounter = 1;
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  int your_choice;
  int compare;
  switch (uMsg)
  {
  case WM_CLOSE:
    DestroyWindow(hwndDlg); // zniszczenie okienka amen rip bebe
    PostQuitMessage(0); //umieszczenie w pêtli koumnikatów poleczenia zakoñczenia aplikacji
    return TRUE;

  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED: // zdarzenie klikniêcia na UI
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1: // klik na przycisku



        //////// pobieranie zmiennej z editboxa////////////
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1); // pobranie do kontrolki IDC_EDIT1
        int iTextLength = GetWindowTextLength(hwndEditBox);
        wchar_t szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1);
        ///////////////////////////////////////////////




        ////////// ustalenie wybranej liczby ///////////
        if (szText[1] == NULL) your_choice = (szText[0] - 48);
        else if(szText[2] ==! NULL) MessageBox(hwndDlg, TEXT("Bites the dust"), TEXT("Killer queen"), MB_OK);
        else  your_choice = (szText[0] - 48) * 10 + (szText[1] - 48);
        

        if ((your_choice > 40 || your_choice < 1) || iTextLength>2)
        {
          MessageBox(hwndDlg, TEXT("Liczba po za przedzia³em"), TEXT("Error"), MB_OK);
          break;
        }

        //////// zliczanie ////////////////////////////
        counter++;
        HWND hTip2 = GetDlgItem(hwndDlg, IDC_STATIC1);
        wchar_t buffor2[100];
        wsprintf(buffor2, L"Liczba prób: %d", counter);
        SetWindowText(hTip2, buffor2);
        /////////////////////////////////////////////////

        ///////// sprawdzanie ///////////
        int temp = wylosowana_liczba - your_choice;
        compare = look(temp);

        switch (compare)
        {
        case 0:
        {
          int k =MessageBox(hwndDlg, TEXT("Chcesz graæ dalej?"), TEXT("Wygrana"), MB_YESNO);
          if (k == IDYES)
          {
            wylosowana_liczba = rand() % 40 + 1;
            counter = 0;

            HWND hTip = GetDlgItem(hwndDlg, IDC_STATIC_NG);
            wchar_t buffor[100];
            wsprintf(buffor, L"Wygrane gry: %d", ngcounter);
            SetWindowText(hTip, buffor);
            ngcounter++;
          }
          else
          {
            HWND hTip = GetDlgItem(hwndDlg, IDC_STATIC2);
            wchar_t buffor[100];
            wsprintf(buffor, L"ZWYCIÊSTWO");
            SetWindowText(hTip, buffor);

            DestroyWindow(hwndDlg);
            PostQuitMessage(0);
            return TRUE;
          }
        }
        break;
        case 1:
        {
          HWND hTip = GetDlgItem(hwndDlg, IDC_STATIC2);
          wchar_t buffor[100];
          wsprintf(buffor, L"Za ma³o");
          SetWindowText(hTip, buffor);

        }
        break;
        case -1:
        {
          HWND hTip = GetDlgItem(hwndDlg, IDC_STATIC2);
          wchar_t buffor[100];
          wsprintf(buffor, L"Za du¿o");
          SetWindowText(hTip, buffor);
        }
        break;
        }
        return FALSE;
      }
    }
    return FALSE;
  }
  return FALSE;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)

{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

  srand((UINT)time(NULL));
  wylosowana_liczba = rand() % 40 + 1;

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