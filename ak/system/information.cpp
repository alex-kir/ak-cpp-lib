
#include <ak/system/information.h>
#include <ak/system/win32.h>

namespace ak
{
    namespace system
    {
		size<int> information::screen_size()
		{
            return size<int>(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));
		}

        rectangle<int> information::work_area()
        {
            RECT rt;
            ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
            return rectangle<int>(rt.left, rt.top, rt.right, rt.bottom);
        }

        void information::work_area(const rectangle<int> & rt)
        {
            RECT rt1;
            SetRect(&rt1, rt.left(), rt.top(), rt.right(), rt.bottom());
            if (!SystemParametersInfo(SPI_SETWORKAREA, 0, &rt1, SPIF_SENDCHANGE))
                throw ak::exception() << "SystemParametersInfo() returns FALSE";
        }
    }
}