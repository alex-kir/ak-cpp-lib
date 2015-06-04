#pragma once

#include <ak/ui/window.h>
#include <string>

namespace ak
{
	namespace ui
	{
        class tooltip
		{
            void * hwndTT;
            void * hwnd;
            std::wstring _text;
		public:
            void create(window & wnd, const std::wstring & text);
            void update(const std::wstring & text);
		};
	}
}