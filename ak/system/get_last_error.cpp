#include <ak/system/get_last_error.h>

namespace ak
{
    namespace system
    {
        std::string get_last_error(bool convert)
        {
            DWORD err = ::GetLastError();
            char message[1000] = {0,};
            char msgAnsi[1000] = {0,};
            int sz = ::FormatMessageA(
                FORMAT_MESSAGE_FROM_SYSTEM,
                0, err, LANG_SYSTEM_DEFAULT,
                message, 999, 0);
            if (convert)
            {
                ::CharToOemA(message, msgAnsi);
                return std::string(msgAnsi);
            }
            else
            {
                return std::string(message);
            }
        }
    }

}