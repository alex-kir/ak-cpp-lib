#pragma once
#include <ak/net/socket.h>
namespace ak
{
    namespace net
    {
        class ftp_file_info
        {
        public:
            char is_dir;
            std::string attr;
            std::string uk;
            std::string user;
            std::string group;
            int size;
            std::string monht;
            std::string day;
            std::string time;
            std::string name;
        };

        class ftp_client
        {
            ak::net::socket command, data;
            void pasv();
            //void test_answer(const std::string & answer, const std::string & codes);
            //void test_answer(ak::net::socket & sock, const std::string & codes);

        public:
            void show_answer();
            void connect_(const std::string & host);
            void user_(const std::string & user);
            void pass_(const std::string & pass);
            void retr_(const std::string & r_filename, const std::string & l_filename);
            void stor_(const std::string & l_filename, const std::string & r_filename);
            void appe_(const std::string & l_filename, const std::string & r_filename);
            void list_(std::vector<ftp_file_info> & files);
            void rest_(int pos);
            void rename_(const std::string & from, const std::string & to);

            void connect(const std::string & host, int port);
            void close();
            void type_ascii();
            void type_binary();
        };
    }
}