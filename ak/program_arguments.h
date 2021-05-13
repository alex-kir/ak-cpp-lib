#pragma once

#include <ak/exception.h>
#include <ak/strings/strings.h>

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace ak
{
    class program_arguments
    {
        class argument_info
        {
        public:
            argument_info()
            {
                defined = false;
            }
            // input
            std::string name;
            std::vector<std::string> keys;
            std::string desc;
            
            //output
            bool defined;
            std::vector<std::string> values;
        };

        class find_ai_by_key
        {
            const std::string & _key;
        public:
            find_ai_by_key(const std::string & key) : _key(key) { }
            inline bool operator () (const argument_info & ai)
            {
                return std::find(ai.keys.begin(), ai.keys.end(), _key) != ai.keys.end();
            }
        };

        class find_ai_by_name
        {
            const std::string & _name;
        public:
            find_ai_by_name(const std::string & name) : _name(name) { }
            inline bool operator ()(const argument_info & ai)
            {
                return ai.name == _name;
            }
        };

        std::vector<argument_info> _info;
        std::string _help_header, _help_footer;
    public:

        inline void set_help_header(const std::string & help_header)
        {
            _help_header = help_header;
        }

        inline void set_help_footer(const std::string & help_footer)
        {
            _help_footer = help_footer;
        }

        inline void add(const std::string & name, const std::string & keys, const std::string & desc)
        {
            if (std::find_if(_info.begin(), _info.end(), find_ai_by_name(name)) != _info.end())
                throw ak::exception() << name << " name already defined";

            argument_info ai;
            ai.name = name;
            ai.desc = desc;
            ak::string::split(keys, ",", ai.keys, false);
            _info.push_back(ai);
        }

        inline void parse(int argc, char * argv [])
        {
            std::vector<argument_info>::iterator last_ai = _info.end();

            for (int i = 1; i < argc; i++)
            {
                std::string s = argv[i];
                std::vector<argument_info>::iterator ai = std::find_if(_info.begin(), _info.end(), find_ai_by_key(s));
                if (ai != _info.end())
                {
                    ai->defined = true;
                    last_ai = ai;
                }
                else if (last_ai == _info.end())
                    throw ak::exception() << s << " arg no specified";
                else
                {
                    last_ai->values.push_back(s);
                    last_ai = _info.end();
                }
            }
        }

        inline bool defined(const std::string & option)
        {
            std::vector<argument_info>::iterator ai = std::find_if(_info.begin(), _info.end(), find_ai_by_name(option));
            if (ai == _info.end())
                throw ak::exception() << __FUNCTION__;
            return ai->defined;
        }

        inline size_t count(const std::string & option)
        {
            std::vector<argument_info>::iterator ai = std::find_if(_info.begin(), _info.end(), find_ai_by_name(option));
            if (ai == _info.end())
                throw ak::exception() << __FUNCTION__;
            return ai->values.size();
        }

        inline std::string at(const std::string & option, int index)
        {
            std::vector<argument_info>::iterator ai = std::find_if(_info.begin(), _info.end(), find_ai_by_name(option));
            if (ai == _info.end())
                throw ak::exception() << __FUNCTION__;
            return ai->values[index];
        }

        inline std::string value_at(const std::string & option, int index)
        {
            return at(option, index);
        }

        inline std::string value(const std::string & option)
        {
            return at(option, 0);
        }

        template<typename Type>
        inline Type at(const std::string & option, size_t index, const Type & default1)
        {
            std::vector<argument_info>::iterator ai = std::find_if(_info.begin(), _info.end(), find_ai_by_name(option));
            if (ai != _info.end() && index < ai->values.size())
                return ak::cast<Type>(ai->values[index]);
            else
                return default1;
        }

        inline void print_help()
        {
            std::cout << _help_header << std::endl;
            for (size_t i = 0; i < _info.size(); i++)
            {
                int n = 0;
                for (size_t j = 0; j < _info[i].keys.size(); j++)
                {
                    n += (int)_info[i].keys[j].size() + 1;
                    std::cout << _info[i].keys[j] << " " ;
                }

                int m = 20 - n;
                std::cout << std::setw(m < 0 ? 0 : m) << " " << _info[i].desc << std::endl;
            }
            std::cout << _help_footer << std::endl;
        }
    };
}
