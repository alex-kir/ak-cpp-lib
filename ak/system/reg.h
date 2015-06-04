#pragma once
#include <string>
#include <vector>
namespace ak
{
    namespace system
    {
        class reg
        {
            void * _key;
        public:
            reg(void * key);
            ~reg(void);
            reg(const reg & key);

            reg open(const std::string & name);

            bool key_at(int index, std::string & key);
            std::vector<std::string> keys();
            bool value_at(int index, std::string & name, std::string & data);
            bool value(const std::string & name, std::string & data);
            void set_value(const std::string & name, const std::string & data);

            /** HKEY_CLASSES_ROOT **/
            static reg HKCR;
            /** HKEY_CURRENT_USER **/
            static reg HKCU;
            /** HKEY_LOCAL_MACHINE **/
            static reg HKLM;
            /** HKEY_USERS **/
            static reg HKU;
            /** HKEY_CURRENT_CONFIG **/
            static reg HKCC;
        };
    }
}