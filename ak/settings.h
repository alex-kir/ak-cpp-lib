#pragma once

#include <sstream>
#include <fstream>
#include <ak/system/process.h>
#include <ak/filesystem.h>
#include <ak/text/string.h>

namespace ak
{
    class settings
    {
        std::map<std::string, std::string> values;
        std::map<std::string, std::string> defaults;

    public:
        settings()
        {
            load();
        }

        void load()
        {
            try
            {
                std::string cfg = ak::system::process().exepath() + ".cfg";
                std::vector<std::string> lines;
                ak::filesystem::read_lines(cfg, lines);

                for (int i = 0, n = lines.size(); i < n; i++)
                {
                    std::string key = ak::text::string(lines[i]).before("=").trim();
                    if (key.empty())                
                        continue;
                    std::string value = ak::text::string(lines[i]).after("=").trim();

                    values[key] = value;
                }
            }
            catch(std::exception)
            {
            }
        }

        void save()
        {
            try
            {
                std::string cfg = ak::system::process().exepath() + ".cfg";
                std::vector<std::string> lines;

                std::map<std::string, std::string> tosave = defaults;
                for (std::map<std::string, std::string>::const_iterator it = values.begin(); it != values.end(); it++)
                {
                    tosave[it->first] = it->second;
                }

                for (std::map<std::string, std::string>::const_iterator it = tosave.begin(); it != tosave.end(); it++)
                {
                    lines.push_back(it->first + "=" + it->second);
                }
                ak::filesystem::write_lines(cfg, lines);
            }
            catch(std::exception)
            {
            }

        }

        template<typename T>
        T get(const std::string & key)
        {
            if (values.find(key) != values.end())
                return ak::cast<T>(values[key]);
            if (defaults.find(key) != defaults.end())
                return ak::cast<T>(defaults[key]);
            return T();
        }

        template<typename T>
        void set(const std::string & key, const T & data)
        {
            values[key] = ak::cast<std::string, T>(data);
        }

        template<typename T>
        void setdefault(const std::string & key, const T & data)
        {
            defaults[key] = ak::cast<std::string, T>(data);
        }

        std::vector<std::string> keys()
        {
            std::vector<std::string> retval;
            for (std::map<std::string, std::string>::const_iterator it = defaults.begin(); it != defaults.end(); it++)
            {
                retval.push_back(it->first);
            }
            return retval;
        }
    };
}