#include <ak/win32/misc.h>
#include <ak/system/reg.h>
#include <ak/system/process.h>
namespace ak
{
    namespace win32
    {
        void open_url(const std::string & url)
        {
            std::string cmd;
            ak::system::reg::HKCR.open("http\\shell\\open\\command").value_at(0, std::string(), cmd);
            int pos1 = cmd.find("%1");
            if (pos1 == std::string::npos)
            { // internet explorer
                cmd += " " + url;
            }
            else
            { // firefox
                cmd.replace(pos1, 2, url);
            }
            ak::system::process browser;
            browser.create("", cmd);
        }
    }
}