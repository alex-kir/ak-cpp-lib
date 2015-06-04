#pragma once
#include <vector>
#include <utility>
namespace ak
{
    template<typename _Type, typename _Read, typename _Write>
    class binstream_wrapper
    {
        _Type * _object;
        _Read _read;
        _Write _write;
    public:
        binstream_wrapper(_Type & object, _Read read, _Write write) : _object(&object), _read(read), _write(write)
        {
        }

        inline binstream_wrapper & operator <<(unsigned char data)
        {
            (*_object.*_write)(&data, sizeof(unsigned char));
            return *this;
        }

        inline binstream_wrapper & operator >>(unsigned char & data)
        {
            (*_object.*_read)(&data, sizeof(unsigned char));
            return *this;
        }

        inline binstream_wrapper & operator <<(unsigned int data)
        {
            (*_object.*_write)(&data, sizeof(unsigned int));
            return *this;
        }

        inline binstream_wrapper & operator >>(unsigned int & data)
        {
            (*_object.*_read)(&data, sizeof(unsigned int));
            return *this;
        }

        inline binstream_wrapper & operator <<(int data)
        {
            (*_object.*_write)(&data, sizeof(int));
            return *this;
        }

        inline binstream_wrapper & operator >>(int & data)
        {
            (*_object.*_read)(&data, sizeof(int));
            return *this;
        }

        template<typename T1, typename T2>
        inline binstream_wrapper & operator << (std::pair<T1, T2> & p)
        {
            *this << p.first << p.second;
            return *this;
        }

        template<typename T1, typename T2>
        inline binstream_wrapper & operator >> (std::pair<T1, T2> & p)
        {
            *this >> p.first >> p.second;
            return *this;
        }

        template<typename T>
        inline binstream_wrapper & operator << (std::vector<T> & v)
        {
            *this << (int)v.size();
            for (std::vector<T>::iterator it = v.begin(); it != v.end(); it++)
                *this << *it;
            return *this;
        }

        template<typename T>
        inline binstream_wrapper & operator >> (std::vector<T> & v)
        {
            int n = 0;
            *this >> n;
            v.resize(n);
            for (std::vector<T>::iterator it = v.begin(); it != v.end(); it++)
                *this >> *it;
            return *this;
        }

        inline binstream_wrapper & operator << (std::vector<bool> & v)
        {
            *this << (int)v.size();
            for (int i = 0; i < (int)v.size(); i++)
            {
                unsigned char ch = 0;
                for (int j = 0; j < 8 && i + j < (int)v.size(); j++)
                {
                    if (v[i + j])
                    {
                        ch = ch | (1 << j);
                    }
                }
                *this << ch;
            }
            return *this;
        }

        inline binstream_wrapper & operator >> (std::vector<bool> & v)
        {
            int n = 0;
            *this >> n;
            v.resize(n);
            for (int i = 0; i < (int)v.size(); i++)
            {
                unsigned char ch = 0;
                *this >> ch;
                for (int j = 0; j < 8 && i + j < (int)v.size(); j++)
                {
                    v[i + j] = (ch & (1 << j)) ? true : false;
                }
            }
            return *this;
        }

    };
    
    template<typename _Type, typename _Read, typename _Write>
    binstream_wrapper<_Type, _Read, _Write> binstreamer(_Type & object, _Read read, _Write write)
    {
        return binstream_wrapper<_Type, _Read, _Write>(object, read, write);
    }

}