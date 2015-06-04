#include <ak/net/ftp_client.h>
#include <ak/text/text.h>
#include <ak/cast.h>
#include <iostream>
#include <fstream>

namespace ak
{
    namespace net
    {
        void ftp_client::show_answer()
        {
            text_reader rsock(command);
            std::string answer;
            do
            {
                rsock.readline(answer);
                std::cout << answer << std::endl;
            }while(command.select(1000));
        }

        void ftp_client::connect(const std::string & host, int port)
        {
            command.connect(host, port);
        }

        void ftp_client::connect_(const std::string & h)
        {
            int port = 21;
            std::string host = h;
            size_t pos = host.find(":");
            if (pos != std::string::npos)
            {
                port = ak::cast<int>(host.substr(pos + 1));
                host = host.substr(0, pos);
            }
            connect(host, port);
            show_answer();
        }

        void ftp_client::close()
        {
            command.close();
        }

        void ftp_client::user_(const std::string & user)
        {
            text_writer wcommand(command);
            wcommand << "USER " << (user.empty() ? "anonymous" : user)<< "\n";
            show_answer();
        }

        void ftp_client::pass_(const std::string & pass)
        {
            text_writer wcommand(command);
            wcommand << "PASS " << pass << "\n";
            show_answer();
        }

        void ftp_client::retr_(const std::string & r_filename, const std::string & l_filename)
        {
            pasv();

            text_writer wcommand(command);
            wcommand << "RETR " << r_filename << "\n";
            show_answer();

            std::fstream f(l_filename.c_str(), std::ios::out + std::ios::binary);
            if (f.is_open())
            {
                int len = 0;
                while(data.is_connected())
                {
                    char buff[65536];
                    int l = data.read(buff, 65536);
                    f.write(buff, l);
                    len += l;
                    std::cout << "\r" << len;
                }
                std::cout << "\rcomplete" << std::endl;
                f.close();
            }
            else
            {
                std::cout << "failed" << std::endl;
            }
            show_answer();
        }

        void ftp_client::stor_(const std::string & l_filename, const std::string & r_filename)
        {
            pasv();

            text_writer wcommand(command);
            wcommand << "STOR " << r_filename << "\n";
            show_answer();

            std::ifstream f(l_filename.c_str(), std::ios::in + std::ios::binary);
            if (f.is_open())
            {
                int len = 0;
                while(data.is_connected())
                {
                    char buff[65536];
                    f.read(buff, 65536);
                    int l = (int)f.gcount();
                    if (l == 0)
                        break;
                    data.write(buff, l);
                    len += l;
                    std::cout << "\r" << len;
                }
                std::cout << "\rcomplete" << std::endl;
                data.close();
                f.close();
            }
            else
            {
                std::cout << "failed" << std::endl;
            }
            show_answer();
        }

        void ftp_client::appe_(const std::string & l_filename, const std::string & r_filename)
        {
            pasv();

            text_writer wcommand(command);
            wcommand << "APPE " << r_filename << "\n";
            show_answer();

            std::ifstream f(l_filename.c_str(), std::ios::in + std::ios::binary);
            if (f.is_open())
            {
                int len = 0;
                while(data.is_connected())
                {
                    char buff[65536];
                    f.read(buff, 65536);
					int l = (int)f.gcount();
                    if (l == 0)
                        break;
                    data.write(buff, l);
                    len += l;
                    std::cout << "\r" << len;
                }
                std::cout << "\rcomplete" << std::endl;
                data.close();
                f.close();
            }
            else
            {
                std::cout << "failed" << std::endl;
            }
            show_answer();
        }

        void ftp_client::rename_(const std::string & from, const std::string & to)
        {
            text_writer wcommand(command);
            wcommand << "RNFR " << from << "\n";
            show_answer();
            wcommand << "RNTO " << to << "\n";
            show_answer();
        }

        void ftp_client::rest_(int pos)
        {
            text_writer wcommand(command);
            wcommand << "REST " << ak::cast<std::string>(pos) << "\n";
            show_answer();
        }

        void ftp_client::list_(std::vector<ftp_file_info> & files)
        {
            pasv();

            text_writer wcommand(command);
            std::string answer;

            wcommand << "LIST\n";
            show_answer();

            text_reader rdata(data);
            while (data.is_connected() && data.select(1000))
            {
                rdata.readline(answer);
                if (!answer.empty())
                {
                    ftp_file_info fi;
                    std::stringstream ss(answer);
                    ss >> fi.is_dir >> fi.attr >> fi.uk >> fi.user >> fi.group
                        >> fi.size >> fi.monht >> fi.day >> fi.time >> fi.name;
                    files.push_back(fi);
                }
            }

            show_answer();
        }

        void ftp_client::pasv()
        {
            text_writer wcommand(command);
            text_reader rcommand(command);
            std::string answer;

            wcommand << "PASV\n";
            rcommand.readline(answer);
            show_answer();


            std::string s1("1234567890");
            for (size_t i = 0; i < answer.size(); i++)
                if (s1.find(answer[i]) == std::string::npos)
                    answer[i] = ' ';

            std::stringstream ss1(answer);
            std::stringstream ss2;
            int code, ip1, ip2, ip3, ip4, p1, p2;
            ss1 >> code >> ip1 >> ip2 >> ip3 >> ip4 >> p1 >> p2;
            ss2 << ip1 << "." << ip2 << "." << ip3 << "." << ip4;

            std::string host = ss2.str();
            int port = p1 * 256 + p2;
            data.connect(host, port);
        }

        void ftp_client::type_ascii()
        {
            text_writer wcommand(command);
            wcommand << "TYPE A\n";
            show_answer();
        }

        void ftp_client::type_binary()
        {
            text_writer wcommand(command);
            wcommand << "TYPE I\n";
            show_answer();
        }
    }
}