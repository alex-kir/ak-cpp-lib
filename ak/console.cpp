
#include <ak\console.h>

namespace ak
{
	void console::write(const char * sz)
	{
		::OutputDebugStringA(sz);
	}
}