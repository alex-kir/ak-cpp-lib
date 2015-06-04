#pragma once
#include <ak/system/handle.h>

namespace ak
{
	namespace system
	{
        class handle;

		class pipe : public handle
		{
		public:
			static void create(handle & rd, handle & wr, int sz = 1024);
		public:
			void create(const std::string & name, const int buffSize = 10240);
			void connect(const std::string & name);
			void read(std::string & name, int const buffSize = 1024);
			void write(const std::string & name);
		};
	}
}