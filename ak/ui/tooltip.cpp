#pragma once

#include <ak/ui/tooltip.h>

namespace ak
{
    namespace ui
    {

        HWND CreateMyTooltip (HWND hwnd)
        {
            HWND hwndTT;
            HINSTANCE hInst = ::GetModuleHandleA(0);

            // struct specifying control classes to register
            INITCOMMONCONTROLSEX iccex; 
            // struct specifying info about tool in ToolTip control
            TOOLINFOA ti;
            unsigned int uid = 0;       // for ti initialization
            char strTT[30] = "This is your ToolTip string.";
            LPSTR lptstr = strTT;
            RECT rect;                  // for client area coordinates

            /* INITIALIZE COMMON CONTROLS */
            iccex.dwICC = ICC_WIN95_CLASSES;
            iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
            InitCommonControlsEx(&iccex);

            /* CREATE A TOOLTIP WINDOW */
            hwndTT = CreateWindowEx(WS_EX_TOPMOST,
                TOOLTIPS_CLASS,
                NULL,
                WS_POPUP | TTS_NOPREFIX | TTS_BALLOON,		
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                hwnd,
                NULL,
                hInst,
                NULL
                );

            SetWindowPos(hwndTT,
                HWND_TOPMOST,
                0,
                0,
                0,
                0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

            /* GET COORDINATES OF THE MAIN CLIENT AREA */
            GetClientRect (hwnd, &rect);

            /* INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE */
            ti.cbSize = sizeof(TOOLINFO);
            //ti.uFlags = TTF_TRANSPARENT;
            ti.uFlags = TTF_SUBCLASS;
            ti.hwnd = hwnd;
            ti.hinst = hInst;
            ti.uId = uid;
            ti.lpszText = lptstr;
            // ToolTip control will cover the whole window
            ti.rect.left = rect.left;    
            ti.rect.top = rect.top;
            ti.rect.right = rect.right;
            ti.rect.bottom = rect.bottom;

            /* SEND AN ADDTOOL MESSAGE TO THE TOOLTIP CONTROL WINDOW */
            SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);	

            return hwndTT;
        } 

        void tooltip::create(window & wnd, const std::wstring & text)
        {
            hwnd = wnd.get_internal_handle();
            HINSTANCE hInst = GetModuleHandleA(0);

            hwndTT = CreateMyTooltip((HWND)hwnd);
        } 

        void tooltip::update(const std::wstring & text)
        {
            _text = text;
            unsigned int uid = 0;       // for ti initialization
            HINSTANCE hInst = GetModuleHandleW(0);

            TOOLINFOW ti;

            ti.cbSize = sizeof(ti);
            //ti.uFlags = TTF_TRANSPARENT;
            ti.uFlags = TTF_SUBCLASS;
            ti.hwnd = (HWND)hwnd;
            ti.hinst = hInst;
            ti.uId = uid;
            ti.lpszText = (wchar_t*)_text.c_str();
            // ToolTip control will cover the whole window
            //ti.rect.left = rect.left;    
            //ti.rect.top = rect.top;
            //ti.rect.right = rect.right;
            //ti.rect.bottom = rect.bottom;


            SendMessageW((HWND)hwndTT, TTM_UPDATETIPTEXT, 0, (LPARAM) (LPTOOLINFOW) &ti);	


            SendMessage((HWND)hwndTT,     (UINT) TTM_SETTITLE,     (WPARAM) TTI_INFO,    (LPARAM) "Translate" ); 
            SendMessage((HWND)hwndTT,     (UINT) TTM_UPDATE,     (WPARAM) 0,    (LPARAM) 0 ); 

            //HWND hwnd = (HWND)wnd.get_internal_handle();
            //HINSTANCE hInst = GetModuleHandleW(0);

            //// struct specifying control classes to register
            ////INITCOMMONCONTROLSEX iccex; 
            //// struct specifying info about tool in ToolTip control
            //TOOLINFO ti;
            //unsigned int uid = 0;       // for ti initialization
            //LPTSTR lptstr = const_cast<wchar_t*>(text.c_str());
            //RECT rect;                  // for client area coordinates

            ///* INITIALIZE COMMON CONTROLS */
            ////iccex.dwICC = ICC_WIN95_CLASSES;
            ////iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
            ////InitCommonControlsEx(&iccex);

            ///* CREATE A TOOLTIP WINDOW */
            ////hwndTT = CreateWindowEx(WS_EX_TOPMOST,
            ////    TOOLTIPS_CLASS,
            ////    NULL,
            ////    WS_POPUP | TTS_NOPREFIX | TTS_BALLOON,		
            ////    CW_USEDEFAULT,
            ////    CW_USEDEFAULT,
            ////    CW_USEDEFAULT,
            ////    CW_USEDEFAULT,
            ////    hwnd,
            ////    NULL,
            ////    hInst,
            ////    NULL
            ////    );

            //SetWindowPos((HWND)hwndTT,
            //    HWND_TOPMOST,
            //    0,
            //    0,
            //    0,
            //    0,
            //    SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

            ///* GET COORDINATES OF THE MAIN CLIENT AREA */
            //GetClientRect (hwnd, &rect);

            ///* INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE */
            //ti.cbSize = sizeof(TOOLINFO);
            ////ti.uFlags = TTF_TRANSPARENT;
            //ti.uFlags = TTF_SUBCLASS;
            //ti.hwnd = hwnd;
            //ti.hinst = hInst;
            //ti.uId = uid;
            //ti.lpszText = lptstr;
            //// ToolTip control will cover the whole window
            //ti.rect.left = rect.left;    
            //ti.rect.top = rect.top;
            //ti.rect.right = rect.right;
            //ti.rect.bottom = rect.bottom;

            ///* SEND AN ADDTOOL MESSAGE TO THE TOOLTIP CONTROL WINDOW */
            //SendMessage((HWND)hwndTT, TTM_UPDATE, 0, (LPARAM) (LPTOOLINFO) &ti);	

        } 


        //HWND WINAPI CreateTT(HWND hwndOwner)
        //{


        //    // Create the ToolTip control.
        //    hwndTT = CreateWindow(TOOLTIPS_CLASS, TEXT(""),
        //        WS_POPUP,
        //        CW_USEDEFAULT, CW_USEDEFAULT,
        //        CW_USEDEFAULT, CW_USEDEFAULT,
        //        NULL, (HMENU)NULL, g_hinst,
        //        NULL);

        //    // Prepare TOOLINFO structure for use as tracking ToolTip.
        //    ti.cbSize = sizeof(TOOLINFO);
        //    ti.uFlags = TTF_IDISHWND | TTF_TRACK | TTF_ABSOLUTE;
        //    ti.hwnd   = hwndOwner;
        //    ti.uId    = (UINT)g_hwndMain;
        //    ti.hinst  = g_hinst;
        //    ti.lpszText  = LPSTR_TEXTCALLBACK;
        //    ti.rect.left = ti.rect.top = ti.rect.bottom = ti.rect.right = 0; 

        //    // Add the tool to the control, displaying an error if needed.
        //    if(!SendMessage(hwndTT,TTM_ADDTOOL,0,(LPARAM)&ti)){
        //        MessageBox(hwndOwner,"Couldn't create the ToolTip control.",
        //            "Error",MB_OK);
        //        return NULL;
        //    }

        //    // Activate (display) the tracking ToolTip. Then, set a global
        //    // flag value to indicate that the ToolTip is active, so other
        //    // functions can check to see if it's visible.
        //    SendMessage(hwndTT,TTM_TRACKACTIVATE,(WPARAM)TRUE,(LPARAM)&ti);
        //    g_bIsVisible = TRUE;

        //    return(hwndTT);    
        //} 

        //void tooltip::create()
        //{
        //    Sleep(2000);
        //    //HWND hwnd = (HWND)0x0003005E;//::GetForegroundWindow();
        //    HWND hwnd = 0;
        //    HINSTANCE ghThisInstance = ::GetModuleHandleA(0);

        //    // struct specifying control classes to register
        //    INITCOMMONCONTROLSEX iccex; 
        //    HWND hwndTT;                 // handle to the ToolTip control
        //    // struct specifying info about tool in ToolTip control
        //    TOOLINFO ti;
        //    unsigned int uid = 0;       // for ti initialization
        //    char strTT[] = {"This is your ToolTip string."};
        //    LPTSTR lptstr = strTT;
        //    RECT rect;                  // for client area coordinates

        //    /* INITIALIZE COMMON CONTROLS */
        //    iccex.dwICC = ICC_WIN95_CLASSES;
        //    iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        //    InitCommonControlsEx(&iccex);

        //    /* CREATE A TOOLTIP WINDOW */
        //    hwndTT = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
        //                    WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,
        //                    CW_USEDEFAULT, CW_USEDEFAULT,
        //                    CW_USEDEFAULT, CW_USEDEFAULT,
        //                    NULL, NULL, NULL,
        //                    NULL);


        //    SetWindowPos(hwndTT,
        //        HWND_TOPMOST,
        //        0,
        //        0,
        //        100,
        //        100,
        //        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

        //    /* GET COORDINATES OF THE MAIN CLIENT AREA */
        //    GetClientRect (hwnd, &rect);

        //    /* INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE */
        //    ti.cbSize = sizeof(TOOLINFO);
        //    ti.uFlags = TTF_ABSOLUTE | TTF_TRACK;
        //    ti.hwnd = hwnd;
        //    ti.hinst = ghThisInstance;
        //    ti.uId = uid;
        //    ti.lpszText = lptstr;
        //    // ToolTip control will cover the whole window
        //    ti.rect.left = 0;    
        //    ti.rect.top = 0;
        //    ti.rect.right = 1600;
        //    ti.rect.bottom = 1000;

        //    /* SEND AN ADDTOOL MESSAGE TO THE TOOLTIP CONTROL WINDOW */
        //    SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);

        //    SendMessage(hwndTT, TTM_ACTIVATE, TRUE, 0);
        //    //::ShowWindow(hwndTT, SW_SHOW);

        //    //INITCOMMONCONTROLSEX icex;
        //    ////HWND        hwndTT;
        //    ////TOOLINFO    ti;
        //    //// Load the ToolTip class from the DLL.
        //    //icex.dwSize = sizeof(icex);
        //    //icex.dwICC  = ICC_BAR_CLASSES;

        //    //if(!InitCommonControlsEx(&icex))
        //    //    return;

        //    //window::create(TOOLTIPS_CLASSA, "kdfksjhdgflaskdjhg", 0, WS_POPUP, 0, ak::size<unsigned int>(0, 0));

        //    //if (get_internal_handle())
        //    //{
        //    //    // Do the standard ToolTip coding. 
        //    //    TOOLINFOA ti;

        //    //    wm.create();
        //    //    //HWND hw = (HWND)window_utils::foreground().get_internal_handle();
        //    //    HWND hw = (HWND)wm.get_internal_handle();

        //    //    ti.cbSize = sizeof(ti);
        //    //    ti.uFlags = TTF_TRANSPARENT | TTF_CENTERTIP;
        //    //    ti.hwnd = hw;
        //    //    ti.uId = 0;
        //    //    ti.hinst = NULL;
        //    //    ti.lpszText = LPSTR_TEXTCALLBACKA;

        //    //    GetClientRect(hw, &ti.rect);
        //    //    //SetRect(&ti.rect, 500, 500, 700, 700);
        //    //    int res = SendMessageA((HWND)get_internal_handle(), TTM_ADDTOOL, 0, (LPARAM)&ti);
        //    //}
        //}

    }
}