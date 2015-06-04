#pragma once

#include <ak/ui/window.h>
#include <ak/rectangle.h>
#include <string>

namespace ak
{
	namespace ui
	{
        class button : public window
		{
		public:
            button & create(const window & parent, int id, const std::string & text, const ak::rectangle<int> & rect);
            button & create_2(const window & parent, int id, const std::string & text, const ak::rectangle<int> & rect);
            button & create_checkbox(const window & parent, int id, const std::string & text, const ak::rectangle<int> & rect);

            bool get_check();
            void set_check(bool c);

		};
	}
}