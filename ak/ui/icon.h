#pragma once
#include <ak/sysobj.h>
namespace ak
{
    namespace ui
    {
        class icon : public sysobj
        {
        public:
            void release();
            void load_from_file(const std::string & filename);
            void load_from_resource(int res_id);

            static icon system_icon_asterisk();
        };
    }
}