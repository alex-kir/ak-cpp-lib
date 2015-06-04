#pragma once
#include <ak/sysobj.h>
#include <ak/types/types.h>
#include <ak/ui/window_for_messages.h>
#include <string>

namespace ak
{
	namespace ui
	{
        class menu : public sysobj
		{
            window_for_messages wnd;
		public:
            void create();
            void destroy();
            int show(const ak::types::pointi & point);
            void hide();
            void append(const std::string & text, int id);
            void append(menu & sub);
            menu submenu(int i);
            void append();
		};
	}
}