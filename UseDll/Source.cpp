#include <stdio.h>
#include <windows.h>


FARPROC FShow;
HINSTANCE hGetProcIDDLL;
int err;

int main()
{
	printf("this is from .exe file");

	hGetProcIDDLL = LoadLibrary(L"DllResource.dll");
	if (!hGetProcIDDLL)
	{
		err = GetLastError();
		return EXIT_FAILURE;
	}

	FShow = GetProcAddress(hGetProcIDDLL, "showDialog");
	if (!FShow) {
		err = GetLastError();
		return EXIT_FAILURE;
	}
	err = FShow();

	return err;
}

