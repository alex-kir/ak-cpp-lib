#pragma once
#include <string>
namespace ak
{
    namespace string
    {
        inline std::string utf_to_uri(const std::string & utf)
        {
            static const std::string chars = " \"#%&'*,:;<>?[]^`{|}";
            std::stringstream uri;
            for (int i = 0; i < (int)utf.size(); i++)
            {
                if (utf[i] >= 0 && chars.find(utf[i]) == std::string::npos)
                    uri << utf[i];
                else
                    uri << "%" << std::hex << (((int)utf[i]) & 0xff);
            }
            return uri.str();
        }
    }
}

