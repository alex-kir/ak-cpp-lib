#pragma once

#include <string>

namespace ak
{
	namespace ui
	{
		class messagebox
		{
		public:
			class buttons
			{
			public:
				static int ok;
			};
			class icons
			{
			public:
				static int none;
				static int info;
				static int error;
				static int warning;
			};
		public:
            static int show(const std::string & text, const std::string & caption = std::string(), int butt = buttons::ok, int icon = icons::none);
            static int show(const std::wstring & text, const std::wstring & caption = std::wstring(), int butt = buttons::ok, int icon = icons::none);
		};
	}
}