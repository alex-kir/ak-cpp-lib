#include <ak/net/get_last_error.h>
#include <ak/cast.h>

namespace ak
{
    namespace net
    {
        std::string get_last_error()
        {
            int error = WSAGetLastError();
            char message[1000] = {0,};
            int sz = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, error, LANG_SYSTEM_DEFAULT, message, 999, 0);
            char ansi[1000] = {0,};
            CharToOemA(message, ansi);
            return cast<std::string>(error) + ": " + std::string(ansi);
        }
    }
}