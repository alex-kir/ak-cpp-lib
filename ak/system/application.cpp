#include <ak/system/application.h>
#include <ak/system/process.h>

namespace ak
{
    namespace system
    {
        std::string application::exepath()
        {
			process p;
			p.open();
			std::string retval = p.exepath();
			p.close();
            return retval;
        }

        //module module::get_or_load(const std::string & name)
        //{
        //    module m;
        //    m.object<HMODULE>(::GetModuleHandleA(name.c_str()));
        //    if (m.empty())
        //        m.object<HMODULE>(::LoadLibraryA(name.c_str()));
        //    return m;
        //}

        //void * module::getproc(const std::string & name)
        //{
        //    return ::GetProcAddress(object<HMODULE>(), name.c_str());
        //}

        //static void inject(int pid, const std::string & path)
        //{
        //    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
        //    std::cout << "OpenProcess() return 0x" << std::hex << process << std::endl;
        //    if (process)
        //    {
        //        int n = path.size() + 1;
        //        LPVOID ptr = VirtualAllocEx(process, NULL, n, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

        //        if (ptr)
        //        {
        //            DWORD m = 0;
        //            WriteProcessMemory(process, ptr, path.c_str(), n, &m);
        //            if (m == n)
        //            {
        //                LPTHREAD_START_ROUTINE loadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
        //                if (loadLibrary)
        //                {
        //                    DWORD tid = 0;
        //                    HANDLE thread = CreateRemoteThread(process, NULL, 0, loadLibrary, ptr, 0, &tid);
        //                    if (thread != NULL)
        //                    {
        //                        ::WaitForSingleObject(thread, INFINITE);
        //                        DWORD exitCode = 0;
        //                        ::GetExitCodeThread(thread, &exitCode);
        //                    }
        //                }
        //            }
        //        }
        //    }
        //}
    }
}