#include <windows.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>


int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int CmdShow)

{

  int iRetKey = MessageBox(0, TEXT("Pomyœl liczbê z przedzia³u od 1 do 40"), TEXT("Giereczka"), MB_OK);

  int max = 40;
  int min = 0;
  int temp = max;

  if (iRetKey == IDOK)
  {
   // int temp = (max - min) / 2;
    srand(time(NULL));
      temp = rand();
    while (1)
    {
      wchar_t buffer[256];
      wsprintf(buffer, L"Czy twoja liczba jest wieksza od: %d", temp);
      int iRetKey = MessageBox(0, buffer, TEXT("Giereczka"), MB_YESNOCANCEL);

      if (iRetKey == IDYES)
      {
        min = temp;
        temp = (max - min) / 2;
        temp = min + temp;

      }
      else if (iRetKey == IDNO)
      {
        max = temp;
        temp = (max - min) / 2;
        temp = max - temp;
      }
      else if (iRetKey == IDCANCEL || min == max)
      {
        wsprintf(buffer, L"Wygranko, wiêc twoja liczba: %d", temp);
        MessageBox(0, buffer, TEXT("WYGRANKO"), MB_OK);
        return 0;
      }
    }

  }
}
