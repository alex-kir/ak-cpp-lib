#pragma once
#include <string>
#include <sstream>
namespace ak
{
    namespace net
    {
        class http_request
        {
        public:
            http_request(const std::string & host, const std::string & page);
            void port(int p);
            void post_method();
            const std::string & get_response();
            std::stringstream post_data;
        private:
            int _port;
            std::string _host;
            std::string _method;
            std::string _page;
            std::string _response;
        };
    }
}
