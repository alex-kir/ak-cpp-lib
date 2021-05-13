#pragma once
#include <string>
#include <vector>
#include <algorithm>
namespace ak
{
    namespace string
    {

        template<typename _Char>
        void split(const std::basic_string<_Char> & str, const std::basic_string<_Char> & glue, std::vector<std::basic_string<_Char> > & res, bool with_empty)
        {
            res.clear();
            size_t pos1 = 0;
            while(true)
            {
                size_t pos2 = str.find(glue, pos1);
                if (pos2 == std::basic_string<_Char>::npos)
                    break;
                if (pos2 - pos1 > 0 || with_empty)
                    res.push_back(str.substr(pos1, pos2 - pos1));
                pos1 = pos2 + glue.size();
            }
            if (pos1 < str.size() || (pos1 == str.size() && with_empty))
                res.push_back(str.substr(pos1));
        }

        template<typename _Char>
        void split(const std::basic_string<_Char> & str, const _Char * glue, std::vector<std::basic_string<_Char> > & res, bool with_empty)
        {
            split(str, std::basic_string<_Char>(glue), res, with_empty);
        }

        template<typename _STD_STRING>
        std::vector<_STD_STRING> explode(const _STD_STRING & str, const _STD_STRING & by, bool with_empty = false)
        {
            std::vector<_STD_STRING> retval;
            split(str, by, retval, with_empty);
            return retval;
        }

        template<typename CHAR>
        std::basic_string<CHAR> implode(const std::vector<std::basic_string<CHAR> > & arr, const std::basic_string<CHAR> & glue)
        {
            std::basic_string<CHAR> retval;
            int n = arr.size() - 1;
            for (int i = 0; i < n; i++)
            {
                retval += arr[i] + glue;
            }
            if (n >= 0)
                retval += arr[n];
            return retval;
        }


        template<typename T>
        std::basic_string<T> replace_all(const std::basic_string<T> & str, const T * from, const T * to)
        {
            return replace_all(str, std::basic_string<T>(from), std::basic_string<T>(to));
        }

        template<typename T>
        std::basic_string<T> replace_all(const std::basic_string<T> & str, const std::basic_string<T> & from, const std::basic_string<T> & to)
        {
            std::vector<std::basic_string<T> > arr = explode<std::basic_string<T> >(str, from, true);
            return implode<T>(arr, to);
        }

        inline std::string to_lower(const std::string & s)
        {
            std::string s1(s.size(), '\0');
            std::transform(s.begin(), s.end(), s1.begin(), tolower);
            return s1;
        }


        template<typename T>
        bool start_with(const std::basic_string<T> & str, const std::basic_string<T> & part)
        {
            return str.size() < part.size() ? false : str.substr(0, part.size()) == part;
        }

        template<typename T>
        bool start_with(const std::basic_string<T> & str, const T * part)
        {
            return start_with(str, std::basic_string<T>(part));
        }

        template<typename T>
        bool end_with(const std::basic_string<T> & str, const std::basic_string<T> & part)
        {
            return str.size() < part.size() ? false : str.substr(str.size() - part.size()) == part;
        }

        template<typename T>
        bool end_with(const std::basic_string<T> & str, const T * part)
        {
            return end_with(str, std::basic_string<T>(part));
        }

        inline std::string trim(const std::string & s)
        {
            const std::string white_space = " \t\r\n";
            int start = 0;
            int end = (int)s.size() - 1;

            for (; start < (int)s.size(); start++)
            {
                if (white_space.find(s[start]) == std::string::npos)
                    break;
            }
            
            for (; end >= 0; end--)
            {
                if (white_space.find(s[end]) == std::string::npos)
                    break;
            }

            return s.substr(start, end - start + 1);
        }

        template<typename T>
        T _between_impl(const T & str, const T & start, const T & stop)
        {
            int startpos = str.find(start);
            if (startpos == T::npos)
                return T();
            startpos += start.size();

            int stoppos = str.find(stop, startpos);
            if (stoppos == T::npos)
                return T();

            int sz = stoppos - startpos;
            if (sz < 0)
                return T();
            return str.substr(startpos, sz);
        }

        template<typename T>
        T _before_impl(const T & str, const T & token)
        {
            int pos = str.find(token);
            if (pos == T::npos)
                return T();
            return str.substr(0, pos);
        }

        template<typename T>
        T _after_impl(const T & str, const T & token)
        {
            int pos = str.find(token);
            if (pos == T::npos)
                return T();
            return str.substr(pos + token.size());
        }

        inline std::string between(const std::string & str, const std::string & start, const std::string & stop)
        {
            return _between_impl<std::string>(str, start, stop);
        }

        inline std::string before(const std::string & str, const std::string & token)
        {
            return _before_impl<std::string>(str, token);
        }

    }
    namespace text
    {
        template<typename T>
        class _string
        {
        private:
            const T refstr;
            _string()
            { }
        public:
            _string(const T & str) : refstr(str)
            { }

            _string before(const T & token)
            {
                return ak::string::_before_impl<T>(refstr, token);
            }
            _string after(const T & token)
            {
                return ak::string::_after_impl<T>(refstr, token);
            }
            _string trim()
            {
                return ak::string::trim(refstr);
            }
            operator T ()
            {
                return refstr;
            }
        };

        template<typename T>
        _string<T> string(const T & t)
        {
            return _string<T>(t);
        }
    }
}
