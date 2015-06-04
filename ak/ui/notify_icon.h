#pragma once
#include <ak/ui/window.h>
#include <ak/ui/icon.h>
#include <ak/notification.h>
//#include <ak/event_handler.h>
#include <ak/types/types.h>
#include <vector>
namespace ak
{
    namespace ui
    {
        class notify_icon
        {
        private:
            window _message_wnd;
            std::string _tip;
            icon _ico;

        public:
            ak::notifications on_mouse_left_down;
            ak::notifications on_mouse_left_up;
            ak::notifications on_mouse_left_dblclk;
            ak::notifications on_mouse_right_down;
            ak::notifications on_mouse_right_up;
            ak::notifications on_mouse_right_dblclk;
            ak::notifications on_contextmenu;

        public:
            notify_icon();
            ~notify_icon();

            notify_icon & set_tip(const std::string & tip);
            notify_icon & set_icon(const icon & ico);
            bool show();
            void hide();
            void refresh();
        };
    }
}
