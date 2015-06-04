#pragma once

#include <ak/sysobj.h>
#include <ak/system/handle.h>

#include <vector>
#include <string>

namespace ak
{
	namespace system
	{
		class process
		{
			sysobj _process;
			unsigned int _pid;

		public:
			process();
			process(int pid) { _pid = pid; }
			process(int pid, const sysobj & h) { _pid = pid; _process = h; }
			bool open();
			void close();
			void terminate();
		public:
			static process create(const std::string & exepath, const std::string & args, const sysobj & _stdin, const sysobj & _stdout, const sysobj & _stderr);
			static process create(const std::string & exepath, const std::string & args)
			{
				return create(exepath, args, 0, 0, 0);
			}
		public:
			int id() { return _pid; }
			std::string exepath();
		public:
			static process current();
			static std::vector<process> all();
		};
	}
}