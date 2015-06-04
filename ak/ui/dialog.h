#pragma once

#include <ak/misc/nocopy.h>
#include <ak/bind.h>
#include <ak/event_handler.h>
#include <ak/size.h>
#include <ak/types/types.h>
#include <ak/rectangle.h>
#include <ak/structure.h>
#include <ak/exception.h>
#include <ak/ui/dialog_result.h>
#include <ak/ui/window.h>

#include <string>
#include <map>
#include <vector>

namespace ak
{
	namespace ui
	{
        class dialog : public window
		{
        public:
            void create_toolwnd(const std::string & title, const ak::size<int> & size);
            void create_layred(const ak::rectangle<int> & rect);

            const dialog_result & show_dialog(bool auto_show = false);
		};
    }
}