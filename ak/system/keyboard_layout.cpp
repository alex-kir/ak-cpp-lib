#include <ak/system/keyboard_layout.h>
#include <iomanip>
namespace ak
{
    namespace system
    {
        std::vector<keyboard_layout> keyboard_layout::all()
        {
            std::vector<keyboard_layout> kls;
            HKL hkls[10];
            int n = ::GetKeyboardLayoutList(10, hkls);
            for (int i = 0; i < n; i++)
            {
                kls.push_back(keyboard_layout(hkls[i]));
            }
            return kls;
        }

        std::string keyboard_layout::name(virtual_key vk)
        {
            int scancode = ::MapVirtualKey(vk, MAPVK_VK_TO_VSC);
            return name(scancode, 0);
        }

        std::string keyboard_layout::name(int lparam)
        {
            char buff[20];
            int n = ::GetKeyNameTextA(lparam, buff, sizeof(buff));
            return std::string(buff, n);
        }

        wchar_t keyboard_layout::vk_to_wchar(int vk)
        {
            unsigned char keystate[256] = { 0, };
            wchar_t buffw[10];
            _internal_keystate[VK_SHIFT] = ((vk >> 8) << 7);
            int r = ::ToUnicodeEx(vk & 0xff, vk, _internal_keystate, buffw, 9, 0, object<HKL>());
            if (r == 1)
                return buffw[0];
            else
                return 0;
        }

        int keyboard_layout::wchar_to_vk(wchar_t ch)
        {
            return ::VkKeyScanExW(ch, object<HKL>());
        }

        void keyboard_layout::activate()
        {
            ::ActivateKeyboardLayout(object<HKL>(), KLF_SETFORPROCESS);
            //std::stringstream ss;
            //ss << _kl;
            //std::string s = ss.str();
            //char buff[9] = {0,};
            //for (int i = 0; i < 8; i++) buff[i] = s[i];
            ////std::copy(ss.str().begin(), ,buff);
            //::LoadKeyboardLayoutA(buff, KLF_ACTIVATE);
            ////::ActivateKeyboardLayout(HKL_NEXT, KLF_ACTIVATE);
            //std::string err = ak::system::get_last_error(false);
        }
    }
}