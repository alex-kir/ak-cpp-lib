#pragma once
#include <ak/enumeration.h>
namespace ak
{
    namespace system
    {
        class virtual_key : public ak::enumeration
        {
        public:
            virtual_key(int val) : ak::enumeration(val) { }

            static virtual_key left_button;
            static virtual_key right_button;
            static virtual_key middle_button;

            static virtual_key shift;
            static virtual_key ctrl;
            static virtual_key alt;

            static virtual_key v;
            static virtual_key c;
        };
    }
}