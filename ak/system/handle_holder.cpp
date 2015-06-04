#include <ak/system/handle_holder.h>

namespace ak
{
    namespace system
    {
        handle_holder::handle_holder(void * h)
        {
            _h = h;
        }

        handle_holder::~handle_holder()
        {
            if (_h)
                CloseHandle(_h);
        }
    }
}