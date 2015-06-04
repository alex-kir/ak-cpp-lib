#include <ak/system/reg.h>
#include <ak/system/win32.h>
#include <ak/exception.h>

namespace ak
{
    namespace system
    {

        reg reg::HKCR(HKEY_CLASSES_ROOT);
        reg reg::HKCU(HKEY_CURRENT_USER);
        reg reg::HKLM(HKEY_LOCAL_MACHINE);
        reg reg::HKU (HKEY_USERS);
        reg reg::HKCC(HKEY_CURRENT_CONFIG);

        reg::reg(void * key)
        {
            _key = key;
        }

        reg::~reg(void)
        {
            if (_key)
                ::RegCloseKey((HKEY)_key);
        }

        reg reg::open(const std::string & name)
        {
            if (_key)
            {
                void * key = 0;
                if (ERROR_SUCCESS != ::RegOpenKeyA((HKEY)_key, name.c_str(), (PHKEY)&key))
                    key = 0;
                return key;
            }
            return 0;
        }

        bool reg::key_at(int index, std::string & key)
        {
            if (_key)
            {
                char str[10000];
                unsigned long sz = 9999;
                if (ERROR_SUCCESS == ::RegEnumKeyExA((HKEY)_key, index, str, &sz, 0, 0, 0, 0))
                {
                    key.assign(str, sz);
                    return true;
                }
            }
            return false;
        }

        std::vector<std::string> reg::keys()
        {
            std::vector<std::string> kk;
            std::string k;
            for (int i = 0; key_at(i, k); i++)
                kk.push_back(k);
            return kk;
        }

        bool reg::value_at(int index, std::string & name, std::string & data)
        {
            if (_key)
            {
                char strn[10000];
                unsigned long szn = 9999;
                unsigned char strd[10000];
                unsigned long szd = 9999;
                unsigned long type;
                if (ERROR_SUCCESS == RegEnumValueA((HKEY)_key, index, strn, &szn, NULL, &type, strd, &szd))
                {
                    name = strn;
                    data = (char*)strd;
                    return true;
                }
            }
            return false;
        }

        void reg::set_value(const std::string & name, const std::string & data)
        {
            if (_key)
            {
                LONG rv = ::RegSetValueExA((HKEY)_key, name.c_str(), 0, REG_SZ, (const BYTE *)data.c_str(), (DWORD)(data.size() + 1));
                if (rv != ERROR_SUCCESS)
                    throw ak::exception() << "reg::set_value()\n   rv != ERROR_SUCCESS";
            }
        }

        bool reg::value(const std::string & name, std::string & data)
        {
            throw ak::exception() << "reg::value() - not implemented";
            //std::string name1;
            //std::string data1;
            //for (int i=0; value_at(i, name1, data1); i++)
            //{
            //    if (name == name1)
            //    {
            //        data = data1;
            //        return true;
            //    }
            //}
            //return false;
        }

    }
}