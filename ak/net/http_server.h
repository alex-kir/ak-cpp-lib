#pragma once
#include <ak/strings/strings.h>
#include <ak/net/request_response_server.h>
namespace ak
{
    namespace net
    {
        class http_server : public request_response_server
        {
            std::map<std::string, ak::notification> responders;

        public:

            notification & responder(const std::string & url)
            {
                return responders[url];
            }
        private:
            void on_incoming_connection(socket & client)
            {
				try
				{
					text_reader tr(client);
					text_writer tw(client);
					std::string line;
					tr.getline(line);
					std::string url = ak::string::trim(line.substr(4, line.size() - 13));
					url = ak::string::to_lower(url);

					do
					{
						tr.getline(line);
					} while (line.size() > 3);

					if (true)
					{
						std::stringstream ss;
						notification_args args;
						args["stream"] = &ss;
						responders[url].notify(args);

						tw << "HTTP/1.1 200 OK" << "\r\n";
						tw << "Date: Fri, 31 Dec 1999 23:59:59 GMT" << "\r\n";
						tw << "Content-Length: " << ss.str().size() << "\r\n";
						tw << "Content-Type: text/html" << "\r\n";
						tw << "\r\n";

						tw << ss.str();
					}
				}
				catch (std::exception ex)
				{
					//ak::console() << ex.what() << "\n";
				}
            }
        };
    }
}

