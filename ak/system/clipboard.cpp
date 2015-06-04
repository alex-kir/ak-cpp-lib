#include <ak/system/clipboard.h>

namespace ak
{
    namespace system
    {
        void clipboard::copy(const ak::ui::window & w)
        {
            ::SendMessage(w.object<HWND>(), WM_COPY, 0, 0);
        }

        std::string clipboard::text()
        {
            std::string retval;
            if (::OpenClipboard(NULL))
            {
                HANDLE data = ::GetClipboardData(CF_TEXT);

                if (data != NULL)
                {
                    void * ptr = ::GlobalLock(data);
                    int size = (int)::GlobalSize(data);

                    retval.assign((char*)ptr, size);
                }

                ::CloseClipboard();
            }
            return retval;
        }

        std::wstring clipboard::wtext()
        {
            std::wstring retval;
            if (::OpenClipboard(NULL))
            {
                HANDLE data = ::GetClipboardData(CF_UNICODETEXT);

                if (data != NULL)
                {
                    void * ptr = ::GlobalLock(data);
                    int size = (int)::GlobalSize(data);

                    //retval.assign((wchar_t*)ptr, size / 2);
                    retval = (wchar_t*)ptr;
                }

                ::CloseClipboard();
            }
            return retval;
        }

        void clipboard::wtext(const std::wstring & text)
        {
            if (::OpenClipboard(NULL))
            {
                HANDLE data = GlobalAlloc(0, text.size() * 2 + 2);

                if (data != NULL)
                {
                    wchar_t * ptr = (wchar_t*)::GlobalLock(data);
                    // copy string wih null terminator;
                    for (size_t i = 0; i <= text.size(); i++)
                        ptr[i] = text.c_str()[i];
                    //std::copy(text.begin(), text.end(), ptr);
                }

                ::SetClipboardData(CF_UNICODETEXT, data);

                ::CloseClipboard();
            }
        }

        void clipboard::clear()
        {
            if (::OpenClipboard(NULL))
            {
                ::EmptyClipboard();
                ::CloseClipboard();
            }
        }

        void clipboard::test()
        {
            HWND h = ::GetClipboardOwner();
            if (::OpenClipboard(NULL))
            {
                int zxc = ::CountClipboardFormats();
                zxc = 0;

                UINT dd[] = {2,3,4,5,6,7,8,9,10, 11, 12, 13, 14, 15, 16};
zxc = GetPriorityClipboardFormat(dd,sizeof(dd)/sizeof(dd[0]));

                zxc = ::EnumClipboardFormats(zxc);
                //if (::OpenClipboard(NULL))
                //{
                //    HANDLE data = GlobalAlloc(0, text.size() * 2 + 2);

                //    if (data != NULL)
                //    {
                //        wchar_t * ptr = (wchar_t*)::GlobalLock(data);
                //        // copy string wih null terminator;
                //        for (size_t i = 0; i <= text.size(); i++)
                //            ptr[i] = text.c_str()[i];
                //        //std::copy(text.begin(), text.end(), ptr);
                //    }

                //    ::SetClipboardData(CF_UNICODETEXT, data);

                ::CloseClipboard();
            }
        }
    }
}