#pragma once

namespace ak
{
	class console
	{
	public:
		void static write(const char * sz);

		template<class T>
		const console & operator << (const T & t) const
		{
			std::ostringstream ss;
			ss << t;
			write(ss.str().c_str());
			return *this;
		}
	};
}