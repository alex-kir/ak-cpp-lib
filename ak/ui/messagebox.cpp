#include <ak/ui/messagebox.h>

namespace ak
{
	namespace ui
	{
		int messagebox::buttons::ok = MB_OK;
		int messagebox::icons::none = 0;
        int messagebox::icons::info = MB_ICONINFORMATION;
		int messagebox::icons::error = MB_ICONERROR;
		int messagebox::icons::warning = MB_ICONWARNING;

		int messagebox::show(const std::string & text, const std::string & caption, int butt, int icon)
		{
			return MessageBoxA(::GetForegroundWindow(), text.c_str(), caption.c_str(), butt | icon);
		}

		int messagebox::show(const std::wstring & text, const std::wstring & caption, int butt, int icon)
		{
            return MessageBoxW(::GetForegroundWindow(), text.c_str(), caption.c_str(), butt | icon);
		}
	}
}
        
