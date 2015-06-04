#include <ak/ui/message.h>

namespace ak
{
	namespace ui
	{
		int message::buttons::ok = MB_OK;
		int message::icons::error = MB_ICONERROR;

		int message::show(const std::string & text, const std::string & caption, int butt, int icon)
		{
			return MessageBoxA(0, text.c_str(), caption.c_str(), butt | icon);
		}
	}
}
        
