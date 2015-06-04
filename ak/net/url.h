#pragma
#include <ak/string.h>
namespace ak
{
    namespace net
    {
        inline void explode_http_url(const std::string & url, std::string & host, int & port, std::string & resource)
        {
            port = 80;
            std::string protocol;
            // extract protocol
            //-----------------
            size_t pos = url.find("://");
            size_t pos2 = 0;
            if (pos != std::string::npos)
            {
                protocol = url.substr(0, pos);
                ak::string::to_lower(protocol);
                pos2 = pos + 3;
            }

            // extract host and resource
            //--------------------------
            pos = url.find("/", pos2);
            if (pos == std::string::npos)
                pos = url.size();
            host = url.substr(pos2, pos - pos2);
            resource = url.substr(pos);
            if (resource.empty())
                resource = "/";

            // extract port and correct host
            //------------------------------
            pos = host.find(":");
            if (pos != std::string::npos)
            {
                port = atoi(host.substr(pos + 1).c_str());
                host = host.substr(0, pos);
            }
        }
    }
}