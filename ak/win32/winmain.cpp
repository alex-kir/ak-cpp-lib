
#include <ak/strings/strings.h>

int ak_main(const std::vector<std::string> & args);

#ifdef _CONSOLE

int main(int argc, char **argv)
{
	try
	{
		std::vector<std::string> args;
		for (int i = 0; i < argc; ++i)
			args.push_back(std::string(argv[i]));

		return ak_main(args);
	}
	catch(const std::exception & ex)
	{
		return -1;
	}
}

#else

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		int argc;
		wchar_t ** argv = ::CommandLineToArgvW(::GetCommandLineW(), &argc);

		std::vector<std::string> args;
		for (int i = 0; i < argc; ++i)
		{
			auto ustr = std::wstring(argv[i]);
			args.push_back(ak::strings::unicode_to_utf8(ustr));
		}

		return ak_main(args);
	}
	catch(const std::exception & ex)
	{
		return -1;
	}
}


#endif
