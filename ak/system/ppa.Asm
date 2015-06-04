; Window with per-pixel alpha transparency by Qweerdy
;
; This program uses Thomas' PngLib to load a 32 bit png with a alpha channel and sets this as
; a window's shape and background. To do this it uses the WinXp/2000 only API UpdateLayeredWindow.
;
; Most of this code can be copied at will, since only the PreMul proc is really my work. If you use
; this PreMul proc, please put my name in the source code as a comment when you release it. That's
; all.

.586
.model flat,stdcall
option casemap:none

   include windows.inc
   include user32.inc
   include kernel32.inc
   include gdi32.inc
   include pnglib.inc
   
   includelib user32.lib
   includelib kernel32.lib
   includelib gdi32.lib
   includelib pnglib.lib
   
; Macros

CTEXT MACRO y:VARARG
	LOCAL sym
	CONST segment
		IFIDNI <y>,<>
			sym db 0
		ELSE
			sym db y,0
		ENDIF
	CONST ends
	EXITM <OFFSET sym>
ENDM

; Constants & struct missing from Windows.inc

WS_EX_LAYERED equ 80000h
ULW_COLORKEY equ 1h
ULW_ALPHA equ 2h
ULW_OPAQUE equ 4h
AC_SRC_OVER equ 0h
AC_SRC_ALPHA equ 1h

BLENDFUNCTION STRUCT
	BlendOp BYTE ?
	BlendFlags BYTE ?
	SourceConstantAlpha BYTE ?
	AlphaFormat BYTE ?
BLENDFUNCTION ends

sSIZE STRUCT
	dWidth DWORD ?
	dHeight DWORD ?
sSIZE ends

; Proto's
WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
LoadPng proto :DWORD,:DWORD
PreMul proto :DWORD
UpdateLayeredWindow proto :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD

.data
	ClassName db "MainWinClass",0
	AppName  db "Main Window",0
	ptZero POINT <0,0>
	blender BLENDFUNCTION <AC_SRC_OVER,0,255,AC_SRC_ALPHA>

.data?
	hInstance HINSTANCE ?
	hWin dd ?
	CommandLine LPSTR ?
	hScreenDC dd ?
	hBitmap dd ?
	hMemDC dd ?
	hOldBmp dd ?
	pngSize sSIZE <>

.code


; ---------------------------------------------------------------------------


start:
	invoke GetModuleHandle, NULL
	mov    hInstance,eax
	
	invoke GetCommandLine
	mov    CommandLine,eax
	
	invoke WinMain, hInstance,NULL,CommandLine, SW_SHOWDEFAULT
	invoke ExitProcess,eax

; Standard WinMain, except for WS_EX_LAYERED and WS_POPUP in the CreateWindowEx line.
WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD
	LOCAL wc:WNDCLASSEX
	LOCAL msg:MSG
	
	mov   wc.cbSize,SIZEOF WNDCLASSEX
	mov   wc.style, CS_HREDRAW or CS_VREDRAW
	mov   wc.lpfnWndProc, OFFSET WndProc
	mov   wc.cbClsExtra,NULL
	mov   wc.cbWndExtra,NULL
	push  hInstance
	pop   wc.hInstance
	mov   wc.hbrBackground,COLOR_BTNFACE+1
	mov   wc.lpszMenuName,NULL
	mov   wc.lpszClassName,OFFSET ClassName
	
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov   wc.hIcon,eax
	mov   wc.hIconSm,eax
	
	invoke LoadCursor,NULL,IDC_ARROW
	mov   wc.hCursor,eax
	
	invoke RegisterClassEx, addr wc
	INVOKE CreateWindowEx,WS_EX_LAYERED,ADDR ClassName,ADDR AppName,\
           WS_POPUP,CW_USEDEFAULT,\
           CW_USEDEFAULT,100,100,NULL,NULL,\
           hInst,NULL
	mov   hWin,eax
	
	invoke ShowWindow, hWin,SW_SHOWNORMAL
	invoke UpdateWindow, hWin
	
	.WHILE TRUE
		invoke GetMessage, ADDR msg,NULL,0,0
		.BREAK .IF (!eax)
		invoke TranslateMessage, ADDR msg
		invoke DispatchMessage, ADDR msg
	.ENDW
	
	mov     eax,msg.wParam
	ret
WinMain endp

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	
	.IF uMsg==WM_DESTROY
		invoke PostQuitMessage,NULL
	.ELSEIF uMsg==WM_CREATE
		; Load the Png file from the resource
		invoke LoadPng,1,addr pngSize
		mov hBitmap,eax
		; "Pre-multiply" the bitmap (UpdateLayeredWindow needs this if you want it to look OK.)
		invoke PreMul,hBitmap
		; Get a screen DC, since UpdateLayeredWindow wants one.
		invoke GetDC,0
		mov hScreenDC,eax
		; Create a new DC to select our bitmap into, since UpdateLayeredWindow doesn't accept
		; bare bitmaps.
		invoke CreateCompatibleDC,eax
		mov hMemDC,eax
		invoke SelectObject,eax,hBitmap
		mov hOldBmp,eax
		; Resize the window to the size of the Png
		invoke SetWindowPos,hWnd,0,0,0,pngSize.dWidth,pngSize.dHeight,SWP_NOMOVE or SWP_NOZORDER
		; Call UpdateLayeredWindow. The commented invoke is how you would normally call it,
		; the rest is just to be nice to the people who don't have XP or Win2k
		
		;invoke UpdateLayeredWindow,hWnd,hScreenDC,NULL,addr pngSize,hMemDC,\
		;							addr ptZero,0,addr blender, ULW_ALPHA
		
		invoke GetModuleHandle,CTEXT("User32")
		invoke GetProcAddress,eax,CTEXT("UpdateLayeredWindow")
		.if eax==NULL
			invoke MessageBox,hWnd,CTEXT("Couldn't find UpdateLayeredWindow API. You need Windows XP or 2000 to run this program."),0,MB_OK
		.else
			push ULW_ALPHA
			push offset blender
			push 0
			push offset ptZero
			push hMemDC
			push offset pngSize
			push NULL
			push hScreenDC
			push hWnd
			call eax
		.endif
		
		; Clean up
		invoke SelectObject,hMemDC,hOldBmp
		invoke DeleteDC,hMemDC
		invoke ReleaseDC,hWnd,hScreenDC
		invoke DeleteObject,hBitmap
	.ELSEIF uMsg==WM_LBUTTONDOWN
		; Move the window when holding down left mouse button
        invoke  SendMessage,hWnd,WM_NCLBUTTONDOWN,HTCAPTION,lParam
    .ELSEIF uMsg==WM_RBUTTONUP
    	; Close the window when clicking right mouse button
   		invoke PostMessage,hWnd,WM_CLOSE,0,0
   	.ELSE
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam		
		ret
	.ENDIF
	
	xor eax,eax
	ret
WndProc endp

; This code is largely ripped from loadfromresource example in PngLib
LoadPng proc ID:dword,pSize:dword

; In: 	ID: 	Resource ID of PNG file to load
; Out:	pSize:	Struct that this points to is filled with width & height of PNG
;		eax		Contains the handle to the new DIB
	
LOCAL pngInfo:PNGINFO

	; --- Initialize structure ---
	invoke	PNG_Init, addr pngInfo
	
	; --- Load PNG resource ---
	invoke	PNG_LoadResource, addr pngInfo, hInstance, ID
	.IF		!eax
		xor		eax, eax
		jmp		@cleanup
	.ENDIF
	
	; --- Decode PNG data ---
	invoke	PNG_Decode, addr pngInfo
	.IF		!eax
		xor		eax, eax
		jmp		@cleanup
	.ENDIF
	
	; --- Create bitmap from PNG ---
	invoke	PNG_CreateBitmap, addr pngInfo, hWin, PNG_OUTF_AUTO, FALSE
	.IF		!eax
		xor		eax, eax
		jmp		@cleanup
	.ENDIF
	
	mov edi,pSize
	.if edi!=0
		lea esi,pngInfo
		movsd
		movsd
	.endif
	
	@cleanup:
	push	eax	
	
	; --- Cleanup ---
	invoke	PNG_Cleanup, addr pngInfo
	
	pop		eax
	ret				; Returns 0 if something went wrong, else bitmap handle

LoadPng endp

; Premultiply image colors with alpha value. This is needed to get nice looking colors according
; to MSDN. Formula: color = color * alpha / 256. Note that this doesn't work if the image isn't
; in 32 bits RGBA format (24 bits plus alpha channel).
PreMul proc hBmp:dword
LOCAL bminfo:BITMAP
	
	invoke GetObject,hBmp,sizeof bminfo,addr bminfo
	cmp bminfo.bmBitsPixel,32
	jne Abort
	mov esi,bminfo.bmBits
	mov edi,esi
yloop:
	mov ecx,bminfo.bmWidth
	xloop:
		mov eax,dword ptr [esi]
		mov edx,eax
		shr eax,24
		mov bl,al
		add esi,4
		mul dl
		shr eax,8
		stosb
		mov al,bl
		shr edx,8
		mul dl
		shr eax,8
		stosb
		mov al,bl
		shr edx,8
		mul dl
		shr eax,8
		stosb
		inc edi
		dec ecx
		jnz xloop
	dec bminfo.bmHeight
	jnz yloop
Abort:
	ret

PreMul endp

end start
