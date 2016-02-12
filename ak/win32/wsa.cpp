
#include <ak/win32/wsa.h>

namespace ak
{
    namespace win32
    {
        namespace wsa
        {
            void startup()
            {
                WSADATA data;
                ::WSAStartup(MAKEWORD(1, 1), &data);
            }

            void cleanup()
            {
                ::WSACleanup();
            }
        }
    }
}