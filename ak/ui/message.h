#pragma once

#include <string>

namespace ak
{
	namespace ui
	{
		class message
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
				static int error;
			};
		public:
			static int show(const std::string & text, const std::string & caption, int butt, int icon);
		};
	}
}