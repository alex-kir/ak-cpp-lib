
#include <ak/win32/wsa.h>

namespace ak
{
    namespace win32
    {
        namespace wsa
        {
            void startup()
            {
                ::WSAStartup(MAKEWORD(1, 1), &WSADATA());
            }

            void cleanup()
            {
                ::WSACleanup();
            }
        }
    }
}