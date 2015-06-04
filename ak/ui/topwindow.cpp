#include <ak/ui/topwindow.h>

namespace ak
{
    namespace ui
    {
        topwindow topwindow::foreground()
        {
            return topwindow(::GetForegroundWindow());
        }

        void topwindow::maximize()
        {
            ::ShowWindow(object<HWND>(), SW_MAXIMIZE);
        }
        void topwindow::minimize()
        {
            ::ShowWindow(object<HWND>(), SW_MINIMIZE);
        }
        void topwindow::restore()
        {
            ::ShowWindow(object<HWND>(), SW_RESTORE);
        }
		
		BOOL CALLBACK _topwindow_all_enumerator(HWND h, std::vector<topwindow> * pww)
		{
			pww->push_back(topwindow(window(h)));
			return true;
		}

		std::vector<topwindow> topwindow::all()
		{
			std::vector<topwindow> ww;
			::EnumWindows((WNDENUMPROC)_topwindow_all_enumerator, (LPARAM)&ww);
			return ww;
		}
    }
}