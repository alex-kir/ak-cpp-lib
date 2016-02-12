
// #ifndef _CONSOLE
// #ifdef _WINDOWS_

// void ak_main();

// int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
// //int __stdcall WinMain(void*, void*, char*, int)
// {
//     ak_main();
//     return 0;
// }

// #endif
// #endif

void ak_main();

#ifdef _CONSOLE

int main(int argc, char **argv)
{
	ak_main();
}

#else

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
// int __stdcall WinMain(void*, void*, char*, int)
{
    ak_main();
    return 0;
}


#endif
