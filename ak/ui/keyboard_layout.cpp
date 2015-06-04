#include <ak/system/keyboard_layout.h>
namespace ak
{
    namespace system
    {
        keyboard_layout::keyboard_layout(void * kl)
        {
            _kl = kl;
        }

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

    }
}