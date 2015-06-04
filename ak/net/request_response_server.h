#pragma once
#include <ak/text/text.h>
namespace ak
{
    namespace net
    {
        class request_response_server
        {
        private:
            socket_accepter server;
            ak::system::bg_method async;
            std::string host;
            bool stopped;
            int port;

        public:
            request_response_server()
            {
                port = 0;
                stopped = false;
            }

            ~request_response_server()
            {
                stop();
                async.wait();
            }
            
            std::string get_host() { return host; }

            int get_port() { return port; }

            void create(const std::string & host, int portmin, int portmax)
            {
                this->host = host;
                for (port = portmin; port <= portmax; port++)
                {
                    try
                    {
                        server.bind(host, port);
                        break;
                    }
                    catch(std::exception&)
                    {
                    }
                }

                if (!server.is_connected())
                    ak::exception() << "http_server::runasync() : connection failed";
            }

            void run()
            {
                running(notification_args());
            }

            void runasync()
            {
                async.create(this, &ak::net::request_response_server::running, true);
            }

            void stop()
            {
                stopped = true;
            }

        protected:
            virtual void on_incoming_connection(socket & client)
            {

            }

        private:
            void running(const notification_args & args)
            {
                while (!stopped)
                {
                    if (!server.select(1))
                        continue;
                    socket client;
                    server.accept(client);

                    if (client.is_connected())
                    {
                        on_incoming_connection(client);
                    }
                    client.close();
                }
            }
        };
    }
}

