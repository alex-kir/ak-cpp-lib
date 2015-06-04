#pragma once
#include <ak/sysobj.h>
#include <ak/system/virtual_key.h>
namespace ak
{
    namespace system
    {
        class keyboard_layout : public sysobj
        {
            unsigned char _internal_keystate[256];;
            template<typename T>
            keyboard_layout(const T t);
        public:
            static std::string name(virtual_key vk);
            static std::string name(int lparam);
            inline static std::string name(int scancode, int flag);
        public:
            static std::vector<keyboard_layout> all();
        public:
            wchar_t vk_to_wchar(int vk);
            int wchar_to_vk(wchar_t ch);
            void activate();
        };

        template<typename T>
        keyboard_layout::keyboard_layout(const T t) : sysobj(t)
        {
            std::fill(_internal_keystate, _internal_keystate + 256, 0);
        }

        inline std::string keyboard_layout::name(int scancode, int flag)
        {
            return name((scancode << 16) | (flag << 24));
        }
    }
}