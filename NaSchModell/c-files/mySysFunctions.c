#include "..\h-files\naschmodell.h"

void clearKeyboardBuffer(void)
{
   int i;
   while (_kbhit() == 1 && (i = _getch()) != '\n' && i != EOF);
}

int input(const short int siX, const short int siY)
{
   int iKEY_STATE = 0;
   short int siToggle = 0;

   _gotoxy(siX, siY);
   clearKeyboardBuffer();

   while (1)
   {

      iKEY_STATE = GetKeyState(VK_CAPITAL);

      if (0x0001 & iKEY_STATE)
      {
         _gotoxy(150, 4 + MENUHEIGHT + BOARDHEIGHT);
         printf("[ Caps Lock ]");
         do
         {
            _gotoxy(151 + siToggle * 10, 4 + MENUHEIGHT + BOARDHEIGHT);
            siToggle = (siToggle + 1) % 2;
            Sleep(GLOBAL_CURSOR_BLINK_RATE / 2);
            iKEY_STATE = GetKeyState(VK_CAPITAL);
         }
         while (0x0001 & iKEY_STATE);

         _gotoxy(150, 4 + MENUHEIGHT + BOARDHEIGHT);
         printf("             ");
         _gotoxy(siX, siY);
         clearKeyboardBuffer();
      }

      if (_kbhit() == 1)
      {
         int iOpt = _getch();
         clearKeyboardBuffer();
         return iOpt;
      }
   }

}

int testConsoleSize(void)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   int iColumns, iRows;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   iColumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
   iRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

   if (iRows < 40 || iColumns < 207)
   {
      _gotoxy(5, 5);
      printf("ERROR: Konsole zu klein! Min-WIDTH x Min-HEIGHT: 207x40 ");
      _getch();
      return -1;
   }

   return 0;
}

void initGlobalCursorBlinkRate(void)
{
   char value[12];
   DWORD BufferSize = 12;
   RegGetValue(HKEY_CURRENT_USER, "Control Panel\\Desktop", "CursorBlinkRate", REG_SZ, NULL, (PVOID)&value, &BufferSize);
   GLOBAL_CURSOR_BLINK_RATE = atoi(value);
}