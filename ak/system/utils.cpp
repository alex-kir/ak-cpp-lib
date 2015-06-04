#include <ak/system/utils.h>
#include <algorithm>

namespace ak
{
    namespace system
    {
        namespace utils
        {
            std::string exe_path()
            {
                char filename[260];
                int n = ::GetModuleFileNameA(NULL, filename, 260);
                std::string filename1 = filename;
                size_t pos = filename1.find_last_of("\\");
                return filename1.substr(0, pos + 1);
            }
        }
    }
}