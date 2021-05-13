#pragma once
//#include <atlbase.h>
//#include <comdef.h>
//#include <dshow.h>
//#pragma comment (lib, "strmiids.lib")
//#import "qedit.dll" named_guids

//#include <comdef.h>

#pragma warning(push)
#pragma warning(disable: 4192 4278)
#import "qedit.dll" named_guids
#pragma warning(pop)
#pragma comment(lib, "strmiids.lib")
#include <dshow.h>

#include <ak/strings/utf8.h>

#define AK_WIN32_COM_ENABLED ak::win32::COM_initializer __com_initializer;
#define AK_WIN32_COM_SMARTPTR(INTERFACE_NAME) _COM_SMARTPTR_TYPEDEF(INTERFACE_NAME, __uuidof(INTERFACE_NAME));

namespace DexterLib // NOTE: I don't remember what is but the name is not random
{

    //AK_WIN32_COM_SMARTPTR(ICreateDevEnum);
    //AK_WIN32_COM_SMARTPTR(IEnumMoniker);
    //AK_WIN32_COM_SMARTPTR(IMoniker);
    //AK_WIN32_COM_SMARTPTR(IBaseFilter);
    //AK_WIN32_COM_SMARTPTR(IGraphBuilder);
    //AK_WIN32_COM_SMARTPTR(IPin);
    //AK_WIN32_COM_SMARTPTR(IEnumPins);
    //AK_WIN32_COM_SMARTPTR(IMediaControl);
    //AK_WIN32_COM_SMARTPTR(IMediaEvent);
    //AK_WIN32_COM_SMARTPTR(IAMStreamConfig);
}

AK_WIN32_COM_SMARTPTR(IUnknown); // now available smart ptr IUnknownPtr

namespace ak
{
    namespace win32
    {
        class HRESULT_throwable
        {
        public:
            HRESULT hr;
            HRESULT_throwable() { hr = S_OK; }
            void operator = (HRESULT hr_) { hr = hr_; if (FAILED(hr)) throw _com_error(hr); }
            void operator += (HRESULT hr_) { hr = hr_; }
            bool operator () () { return SUCCEEDED(hr); }
            operator bool () { return SUCCEEDED(hr); }
            bool operator ! () { return FAILED(hr); }
        };

        class COM_initializer
        {
        public:
            COM_initializer()
            {
                HRESULT_throwable hr;
                hr = ::CoInitializeEx(0, COINIT_APARTMENTTHREADED);
                //hr = ::CoInitializeEx(0, COINIT_MULTITHREADED);
            }
            ~COM_initializer()
            {
                CoUninitialize();
            }
        };

        class com
        {
        public:
            // ak::win32::com::create_instance(L"{A8A91A66-3A7D-4424-8D24-04E180695C7A}");
            inline static IUnknownPtr create_instance(const std::string & cls_guid)
            {
                return create_instance(ak::strings::utf8_to_unicode(cls_guid));
            }
            inline static IUnknownPtr create_instance(const std::wstring & cls_guid)
            {
                HRESULT_throwable hr;

                CLSID clsid;
                hr = ::CLSIDFromString(cls_guid.c_str(), &clsid);

                IUnknownPtr unknown;
                hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (void**)&unknown);
                
                return unknown;
            }

            //template<class T>
            //inline static _com_ptr_t<T> create_instance(const std::wstring & cls_guid)
            //{
            //    return create_instance(cls_guid);
            //}
        };
    }
}