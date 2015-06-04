#include <ak/system/pipe.h>
#include <ak/exception.h>

namespace ak
{
	namespace system
	{
		void pipe::create(handle & rd, handle & wr, int sz)
		{
			void * hr, * hw;

			SECURITY_ATTRIBUTES attr; 
			attr.nLength = sizeof(SECURITY_ATTRIBUTES); 
			attr.bInheritHandle = TRUE;
			attr.lpSecurityDescriptor = NULL; 

			if (!CreatePipe(&hr, &hw, &attr, sz))
				throw ak::exception() << "pipe is not created";

            rd.internal_handle(hr);
			wr.internal_handle(hw);
		}


		void pipe::create(const std::string & name, const int buffSize)
		{
		    std::string pipename = std::string("\\\\.\\pipe\\") + name;

		    void * h = CreateNamedPipeA(pipename.c_str(),
		        PIPE_ACCESS_DUPLEX,
		        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		        PIPE_UNLIMITED_INSTANCES,
		        buffSize, buffSize,
		        NMPWAIT_USE_DEFAULT_WAIT, NULL);
		    internal_handle(h);
		    if (!is_valid_handle())//(h == INVALID_HANDLE_VALUE) 
		    {
		        return;
		    }

		    BOOL connected = ConnectNamedPipe(internal_handle(), NULL);
		    if (!connected)
		    {
                close();
		        return;
		    }
		}

		void pipe::connect(const std::string & name)
		{
            std::string pipename = std::string("\\\\.\\pipe\\") + name;
		    void * h = CreateFileA(pipename.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);          // no template file 
            internal_handle(h);
		    if (!is_valid_handle())//(h == INVALID_HANDLE_VALUE) 
		    {
		        return;
		    }
		    //BOOL wait = WaitNamedPipeA(pipename.c_str(), 10000);
		    //LOG << "pipe::connect::WaitNamedPipeA() = " << dec << wait << ENDLOG;
		}

		void pipe::read(std::string & message, const int buffSize)
		{
		    DWORD cbBytesRead = 0;
		    message.resize(buffSize);
		    BOOL fSuccess = ReadFile(internal_handle(), (LPVOID)message.c_str(), (DWORD)message.size(), &cbBytesRead, NULL);
		    message.resize(cbBytesRead);
		    if (!fSuccess) 
		    {
                close();
		        return; 
		    }

		}

		void pipe::write(const std::string & message)
		{
		    DWORD cbWritten = 0;
		    BOOL fSuccess = WriteFile(internal_handle(), (LPVOID)message.c_str(), (DWORD)message.size(), &cbWritten, NULL);
		    if (!fSuccess)
		    {
                close();
		        return;
		    }
		}
	}
}