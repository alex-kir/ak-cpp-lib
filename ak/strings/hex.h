#pragma once
#include <sstream>
#include <iomanip>

namespace ak
{
    namespace strings
    {
        template<class T>
        std::string bytes_to_hex(const T & data)
        {
            std::stringstream ss;
            byte* ptr = reinterpret_cast<byte*>(const_cast<T*>(&data));
            //ss << "[" << sizeof(T) << "]0x";
            for (int i = 0; i < sizeof(T); i++)
                ss << std::setfill('0') << std::setw(2) << std::hex << (((int)ptr[i]) & 0xff);
            return ss.str();
        }

        template<class T>
        std::wstring bytes_to_whex(const T & data)
        {
            std::wstringstream ss;
            byte* ptr = reinterpret_cast<byte*>(const_cast<T*>(&data));
            //ss << "[" << sizeof(T) << "]0x";
            for (int i = 0; i < sizeof(T); i++)
                ss << std::setfill(L'0') << std::setw(2) << std::hex << (((int)ptr[i]) & 0xff);
            return ss.str();
        }
    }
}

