#pragma once

namespace ak
{
	namespace path
	{
		template<typename T>
		std::basic_string<T> change_ext(const std::basic_string<T> & path, const std::basic_string<T> & ext)
		{
			//std::tr1::regex rx;

			return "";
		}

		template<typename T>
		std::basic_string<T> get_folder(const std::basic_string<T> & path)
		{
			size_t n1 = path.find_last_of("\\");
			size_t n2 = path.find_last_of("/");

			if (n1 == std::basic_string<T>::npos && n2 == std::basic_string<T>::npos)
				return std::basic_string<T>();

			if (n1 != std::basic_string<T>::npos && n2 == std::basic_string<T>::npos)
				return path.substr(0, n1 + 1);

			if (n1 == std::basic_string<T>::npos && n2 != std::basic_string<T>::npos)
				return path.substr(0, n2 + 1);

			return path.substr(0, std::max(n1, n2) + 1);
		}

		template<typename T>
		std::basic_string<T> filename_ext(const std::basic_string<T> & path)
		{
			size_t n1 = path.find_last_of("\\");
			size_t n2 = path.find_last_of("/");

			if (n1 == std::basic_string<T>::npos && n2 == std::basic_string<T>::npos)
				return path;

			if (n1 != std::basic_string<T>::npos && n2 == std::basic_string<T>::npos)
				return path.substr(n1 + 1);

			if (n1 == std::basic_string<T>::npos && n2 != std::basic_string<T>::npos)
				return path.substr(n2 + 1);

			return path.substr(0, std::max(n1, n2) + 1);
		}
	}
}