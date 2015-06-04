#include <ak/system/virtual_key.h>
namespace ak
{
    namespace system
    {
        virtual_key virtual_key::left_button = VK_LBUTTON;
        virtual_key virtual_key::right_button = VK_RBUTTON;
        virtual_key virtual_key::middle_button = VK_MBUTTON;

        virtual_key virtual_key::shift = VK_SHIFT;
        virtual_key virtual_key::ctrl = VK_CONTROL;
        virtual_key virtual_key::alt = VK_MENU;

        virtual_key virtual_key::v = 'V';
        virtual_key virtual_key::c = 'C';
    }
}