#include <ak/net/http_request.h>

namespace ak
{
    namespace net
    {
        const char _UserAgent[] = {"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; InfoPath.1)"};

        http_request::http_request(const std::string & host, const std::string & page)
            : _host(host), _page(page), _method("GET"), _port(INTERNET_DEFAULT_HTTP_PORT)
        { }

        void http_request::port(int p)
        {
            _port = p;
        }

        void http_request::post_method()
        {
            _method = "POST";
        }

        const std::string & http_request::get_response()
        {
            _response = "";

            HINTERNET hInternet = ::InternetOpenA(_UserAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

            if (hInternet == NULL)
                throw ak::exception() << __FUNCTION__ << "{ hInternet == NULL }";

            HINTERNET hConnect = ::InternetConnectA(hInternet, _host.c_str(), _port,
                NULL,NULL, INTERNET_SERVICE_HTTP, 0, 1u);

            if (hConnect == NULL)
                throw ak::exception() << __FUNCTION__ << "{ hConnect == NULL }";

            HINTERNET hRequest = ::HttpOpenRequestA(hConnect, _method.c_str(), _page.c_str(),
                NULL, NULL, 0, INTERNET_FLAG_KEEP_CONNECTION, 1);

            if (hRequest == NULL)
                throw ak::exception() << __FUNCTION__ << "{ hRequest == NULL }";

            if (::HttpSendRequestA(hRequest, NULL, 0, (void*)post_data.str().c_str(), (DWORD)post_data.str().size()))
            {
                for (;;)
                {
                    char szData[1024];
                    DWORD dwBytesRead;
                    BOOL bRead = ::InternetReadFile(hRequest, szData, sizeof(szData) - 1, &dwBytesRead);

                    if (bRead == FALSE || dwBytesRead == 0)
                        break;

                    _response += std::string(szData, dwBytesRead);
                }
            }

            ::InternetCloseHandle(hRequest);
            ::InternetCloseHandle(hConnect);
            ::InternetCloseHandle(hInternet);

            return _response;
        }
    }
}
