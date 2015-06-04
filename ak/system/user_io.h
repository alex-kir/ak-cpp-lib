#pragma once
#include <ak/types/types.h>
#include <ak/enumeration.h>
#include <ak/system/virtual_key.h>
namespace ak
{
    namespace system
    {
        using namespace ak::types;
        class user_io
        {
        public:
            static point<int> cursor_position();
            static bool is_cursor_I_beem();

            static point<int> caret_position();

            // true == down; false == up
            static bool key_state(virtual_key vk);
            static void key_state(virtual_key vk, int flags);

            static void key_down(int vk);
            static void key_up(int vk);

            static void key_down_sc(int sc);
            static void key_up_sc(int sc);

            static void key_type(char ch);
            static void key_type(virtual_key vk) { key_down(vk); key_up(vk); }
            static void key_type(virtual_key vk1, virtual_key vk2) { key_down(vk1); key_down(vk2); key_up(vk2); key_up(vk1); }
        };
    }
}