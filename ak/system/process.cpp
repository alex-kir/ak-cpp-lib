#include <ak/system/process.h>
#include <ak/exception.h>

namespace ak
{
    namespace system
    {
        process::process()
        {
			_pid = ::GetCurrentProcessId();
			_process = 0;
        }

		bool process::open()
		{
			_process = ::OpenProcess(PROCESS_ALL_ACCESS, TRUE, _pid);
			return !_process.empty();
		}

		void process::close()
		{
			::CloseHandle(_process);
			_process = 0;
		}

        process process::create(const std::string & exepath, const std::string & args, const sysobj & _stdin, const sysobj & _stdout, const sysobj & _stderr)
        {
	        std::string _currentDir;
			::STARTUPINFOA si;
            memset(&si, 0, sizeof(si));
            si.cb = sizeof(si);
            if (!_stdin.empty() || !_stdout.empty() || !_stderr.empty())
            {
                si.hStdInput = _stdin;
                si.hStdOutput = _stdout;
                si.hStdError = _stderr;
                si.dwFlags |= STARTF_USESTDHANDLES;
            }
			::PROCESS_INFORMATION pi;
			::SECURITY_ATTRIBUTES p_sa, t_sa;
            memset(&p_sa, 0, sizeof(SECURITY_ATTRIBUTES));
            p_sa.nLength = sizeof(SECURITY_ATTRIBUTES);
            memset(&t_sa, 0, sizeof(SECURITY_ATTRIBUTES));
            t_sa.nLength = sizeof(SECURITY_ATTRIBUTES);

            if (::CreateProcessA(
                exepath.empty() ? 0 : exepath.c_str(), // No module name (use command line)
                (char*)args.c_str(), // Command line
                &p_sa, // Process handle not inheritable
                &t_sa, // Thread handle not inheritable
                true, // bInheritHandles
                CREATE_NEW_CONSOLE, // dwCreationFlags
                0, // lpEnvironment
                _currentDir.empty() ? 0 :_currentDir.c_str(), // lpCurrentDirectory
                &si, // lpStartupInfo
                &pi // lpProcessInformation
                ))
            {
                ::CloseHandle(pi.hThread);
				return process(pi.dwProcessId, pi.hProcess);
            }
            else
                throw ak::exception() << "process::create(), error = " << GetLastError();
        }

        void process::terminate()
        {
			::TerminateProcess(_process, 0);
			_process = 0;
			_pid = 0;
        }

		std::string process::exepath()
		{
			char buffer[300];
			DWORD dw = 299;
#if 0
			if (::QueryFullProcessImageNameA(_process, 0/*PROCESS_NAME_NATIVE*/, buffer, &dw))
				return std::string(buffer, dw);
#else
            dw = ::GetModuleFileNameA(0, buffer, dw);
			if (dw > 0)
				return std::string(buffer, dw);
#endif
			return "";
		}

        process process::current()
        {
            return process();
        }

		std::vector<process> process::all()
		{
			std::vector<process> retval;

			for (int i = 0; i < 0xffff; i += 4)
			{
				process pr(i);
				if (pr.open())
				{
					pr.close();
					retval.push_back(pr);
				}
			}

			return retval;
		}
    }
}
