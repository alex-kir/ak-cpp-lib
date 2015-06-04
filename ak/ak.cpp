
#include <ak/ak.h>

// windows system specific

#include <ak/win32/win32.cpp>

// 
#include <ak/system/get_last_error.cpp>
//#include <ak/system/handle.cpp>
//#include <ak/system/handle_rw.cpp>
//#include <ak/system/pipe.cpp>
#include <ak/system/thread.cpp>
#include <ak/system/process.cpp>
#include <ak/system/user_io.cpp>
//#include <ak/system/clipboard.cpp>
//#include <ak/system/virtual_key.cpp>
#include <ak/system/reg.cpp>
//#include <ak/system/utils.cpp>
//#include <ak/system/keyboard_layout.cpp>
//#include <ak/system/information.cpp>
//#include <ak/system/hook.cpp>
//#include <ak/system/module.cpp>
//#include <ak/system/mutex.cpp>
//#include <ak/system/application.cpp>
//
//
////#include <ak/system/md5.cpp>
//
#include <ak/net/net.cpp>
//
//
//#include <ak/ui/messagebox.cpp>
//#include <ak/ui/window_utils.cpp>
//#include <ak/ui/dc.cpp>
//#include <ak/ui/tooltip.cpp>
//#include <ak/ui/menu.cpp>
#include <ak/ui/icon.cpp>
//
//#include <ak/ui/control.cpp>
#include <ak/ui/window.cpp>
#include <ak/ui/topwindow.cpp>
#include <ak/ui/window_for_messages.cpp>
#include <ak/ui/notify_icon.cpp>
//#include <ak/ui/dialog.cpp>
//#include <ak/ui/button.cpp>
//#include <ak/ui/label.cpp>
//#include <ak/ui/combobox.cpp>
//#include <ak/ui/groupbox.cpp>
//#include <ak/ui/textbox.cpp>
//
//
//#include <ak/notification.cpp>
//
//#include <ak/reflection/reflection.h>

#include <ak/console.cpp>

#ifdef AK_RUBY
#   include <ak/ruby/rb.cpp>
#   include <ak/ruby/console.cpp>
#endif

#pragma comment (lib, "user32.lib")
#pragma comment (lib, "gdi32.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "wininet.lib")
#pragma comment (lib, "comctl32.lib")
