#pragma once
#include <ak/rectangle.h>

namespace ak
{
    namespace system
    {
        class information
        {
        public:
            static size<int> screen_size();

            static rectangle<int> work_area();
            static void work_area(const rectangle<int> & rt);
        };
    }
}