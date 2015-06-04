#pragma once
namespace ak
{
    namespace misc
    {
        class nocopy
        {
        private:
            nocopy(const nocopy &);
            void operator = (const nocopy &);
        public:
            nocopy() { };
        };
    }
}