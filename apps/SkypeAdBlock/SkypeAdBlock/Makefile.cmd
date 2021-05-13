:start_compile

@echo off
cls


@set path=
@set path=C:\TDM-GCC-32\bin\;%path%
::@set path=C:\TDM-GCC-32\lib\;%path%


set flags=
set flags=%flags% -mwindows
set flags=%flags% -std=c++0x
::set flags=%flags% -O3 -Os


set includes=
set includes=%includes% -I../../..


set libraries=
set libraries=%libraries% -Lc:\TDM-GCC-32\lib\
set libraries=%libraries% -luser32
set libraries=%libraries% -lgdi32
set libraries=%libraries% -lws2_32
set libraries=%libraries% -lwininet
set libraries=%libraries% -lcomctl32
set libraries=%libraries% -ladvapi32


set sources=
set sources=%sources% main.cpp
set sources=%sources% stdafx.cpp


@echo on


g++ -o skyblock.exe %flags% %includes% %sources% %libraries%


pause

::kill skyblock.exe

goto start_compile