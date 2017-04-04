#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include "resource.h"

static HMODULE hmod;

HWND myhwnd;
int err;

INT_PTR CALLBACK DialogDomainProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			return TRUE;
		case IDOK:
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			return TRUE;
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hDlg, TEXT("Close the program?"), TEXT("Close"),
			MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			DestroyWindow(hDlg);
		}
		return TRUE;

	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}

	return FALSE;
}

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

__declspec(dllexport) int __stdcall showDialog(void)
{
	myhwnd = (HWND)DialogBoxParam((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogDomainProc, 0);
	if (!myhwnd)
		err = GetLastError();
	ShowWindow(myhwnd, SW_SHOW);

	MessageBoxW(NULL, L"Messagebox from DLL shown", L"Messagebox from DLL shown", 0);
	return 42;
}

