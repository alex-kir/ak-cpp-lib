#pragma once

#include <ak/ui/window.h>
#include <ak/rectangle.h>
#include <string>

namespace ak
{
	namespace ui
	{
        class label : public window
		{
		public:
            label & create(const window & parent, const std::string & text, const ak::rectangle<int> & rect);
            label & create_icon(const window & parent, const ak::rectangle<int> & rect);
		};
	}
}