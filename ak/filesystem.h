#pragma once

#include <ak/exception.h>

#include <io.h>
#include <vector>
#include <string>
#include <fstream>


namespace ak
{
    namespace filesystem
    {
        static void directories(const std::string & path, std::vector<std::string> & dirslist, int lvl = 255)
        {
            dirslist.push_back(path);
            _finddata_t fileinfo;
            intptr_t find_ptr = _findfirst((path + "\\*").c_str(), &fileinfo);
            if (find_ptr == -1) return;
            do 
            {
                std::string filename = fileinfo.name;
                if (filename != "." && filename != "..")
                {
                    if (fileinfo.attrib & _A_SUBDIR)
                    {
                        if (lvl > 0)
                            directories(path + "\\" + filename, dirslist, lvl - 1);
                        else
                            dirslist.push_back(path + "\\" + filename);
                    }
                }
            } while(_findnext(find_ptr, &fileinfo) == 0);
            _findclose(find_ptr);
        }

        static void files(const std::string & path, const std::string & mask, std::vector<std::string> & fileslist)
        {
            _finddata_t fileinfo;
            intptr_t find_ptr = _findfirst((path + mask).c_str(), &fileinfo);
            if (find_ptr == -1) return;
            do 
            {
                std::string filename = fileinfo.name;
                if (filename != "." && filename != "..")
                {
                    if (!(fileinfo.attrib & _A_SUBDIR))
                    {
                        fileslist.push_back(path + "\\" + filename);
                    }
                }
            } while(_findnext(find_ptr, &fileinfo) == 0);
            _findclose(find_ptr);
        }

        
        template<typename CHAR>
        static void append_text(const std::basic_string<CHAR> & filename, const std::basic_string<CHAR> & contents)
        {
            std::ofstream fout(filename.c_str(), std::ios::app);
            fout << contents;
            fout.close();
        }

        static void append_text(const char * filename, const char * content)
        {
            append_text<char>(filename, content);
        }

        template<typename CHAR>
        static void read_lines(const std::basic_string<CHAR> & filename, std::vector<std::basic_string<CHAR> > & lines)
        {
            lines.clear();
            std::ifstream fin(filename.c_str());
            if (!fin)
                throw ak::exception() << "file does not open (" << filename << ")";

            while(!fin.eof())
            {
                std::string line;
                std::getline(fin, line);
                lines.push_back(line);
            }
            fin.close();
        }

        template<typename CHAR>
        static void write_lines(const std::basic_string<CHAR> & filename, std::vector<std::basic_string<CHAR> > & lines)
        {
            std::ofstream file(filename.c_str());
            if (!file)
                throw ak::exception() << "file does not open (" << filename << ")";

            for (int i = 0, n = lines.size(); i < n; i++)
            {
                file << lines[i] << std::endl;
            }
            file.close();
        }

        inline static void read_bytes(const std::string & filename, std::vector<unsigned char> & bytes)
        {
            std::ifstream file(filename.c_str(), std::ios_base::binary);
            if (!file)
                throw ak::exception() << "file does not open (" << filename << ")";

            bytes.resize(1024);
            int m = 0;
            while(true)
            {
                if (m == bytes.size())
                    bytes.resize(bytes.size() * 2);
                file.read((char*)&bytes[m], bytes.size() - m);
                int n = (int)file.gcount();
                if (n == 0)
                    break;
                m += n;
            }
            bytes.resize(m);
            file.close();

        }

        inline static void write_bytes(const std::string & filename, const std::vector<unsigned char> & bytes)
        {
            std::ofstream file(filename.c_str(), std::ios_base::binary);
            if (!file)
                throw ak::exception() << "file does not open (" << filename << ")";
            file.write((char*)&bytes[0], bytes.size());
            file.close();
        }

        inline static std::string read_text(const std::string & filename)
        {
            std::vector<unsigned char> bytes;
            read_bytes(filename, bytes);
            std::string str;
            str.assign((char*)&bytes[0], bytes.size());
            return str;
        }

        inline static void write_text(const std::string & filename, const std::string & text)
        {
            std::ofstream file(filename.c_str(), std::ios_base::binary);
            if (!file)
                throw ak::exception() << "file does not open (" << filename << ")";
            file.write((char*)text.c_str(), text.size());
            file.close();
        }


        inline bool file_exist(const std::string & filename)
        {
            _finddata_t fileinfo;
            intptr_t find_ptr = _findfirst(filename.c_str(), &fileinfo);
            if (find_ptr == -1L)
                return false;
            _findclose(find_ptr);
            return true;
        }

        inline time_t file_c_time(const std::string & filename)
        {
            _finddata_t fileinfo;
            intptr_t find_ptr = _findfirst(filename.c_str(), &fileinfo);
            if (find_ptr == -1L)
                throw ak::exception() << "file_c_time: file not found";
            _findclose(find_ptr);
            return fileinfo.time_create;
        }

        inline time_t file_m_time(const std::string & filename)
        {
            _finddata_t fileinfo;
            intptr_t find_ptr = _findfirst(filename.c_str(), &fileinfo);
            if (find_ptr == -1L)
                throw ak::exception() << "file_c_time: file not found";
            _findclose(find_ptr);
            return fileinfo.time_write;
        }

        inline time_t file_a_time(const std::string & filename)
        {
            _finddata_t fileinfo;
            intptr_t find_ptr = _findfirst(filename.c_str(), &fileinfo);
            if (find_ptr == -1L)
                throw ak::exception() << "file_c_time: file not found";
            _findclose(find_ptr);
            return fileinfo.time_access;
        }
    }
}
