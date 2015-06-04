#pragma once
#include <ak/sysobj.h>
namespace ak
{
    namespace system
    {
        class module : public sysobj
        {
        public:
            static module get_or_load(const std::string & name);
            void * getproc(const std::string & name);
            template<typename T>
            T getproc(const std::string & name)
            {
                return (T)getproc(name);
            }
            template<typename T>
            static T getproc(const std::string & mname, const std::string & fname)
            {
                return get_or_load(mname).getproc<T>(fname);
            }
        public:
            static void inject(int pid, const std::string & name);
        };
    }
}