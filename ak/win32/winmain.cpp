
#ifndef _CONSOLE
#ifdef _WINDOWS_

void main();

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//int __stdcall WinMain(void*, void*, char*, int)
{
    main();
    return 0;
}

#endif
#endif