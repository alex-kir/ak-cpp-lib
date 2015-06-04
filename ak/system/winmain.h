
#pragma once

#ifndef _CONSOLE

void main();

//int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
int __stdcall WinMain(void*, void*, char*, int)
{
    main();
    return 0;
}

#endif