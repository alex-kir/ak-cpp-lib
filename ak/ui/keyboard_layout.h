#pragma once
namespace ak
{
    namespace system
    {
        class keyboard_layout
        {
            void * _kl;
            keyboard_layout(void *);
        public:
            static std::vector<keyboard_layout> all();


        };
    }
}