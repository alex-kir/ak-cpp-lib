#pragma once
#include <ak/reflection/reflection.h>
namespace ak
{
    namespace types
    {
        class basic_any_holder
        {
        public:
            virtual ~basic_any_holder() { }
            virtual bool get(void * data, const std::string & name) = 0;
            virtual basic_any_holder * clone() = 0;
        };

        template<typename T>
        class any_holder : public basic_any_holder
        {
            T data;
        public:
            any_holder(const T & d)
            {
                data = d;
            }
            virtual bool get(void * d, const std::string & name)
            {
                if (name == ak::reflection::typename_of(data))
                {
                    *((T*)d) = data;
                    return true;
                }
                else
                {
                    return false;
                }
            }
            virtual basic_any_holder * clone()
            {
                return new any_holder(data);
            }
        };

        class any
        {
        private:
            basic_any_holder * holder;
        public:
            any()
            {
                holder = 0;
            }
            any(const any & other)
            {
                holder = other.holder ? other.holder->clone() : 0;
            }
            void operator = (const any & other)
            {
                delete holder, holder = 0;
                holder = other.holder ? other.holder->clone() : 0;
            }
            ~any()
            {
                delete holder, holder = 0;
            }

            template<typename T>
            void set(const T & t)
            {
                delete holder, holder = 0;
                holder = new any_holder<T>(t);
            }

            template<typename T>
            void get(T & t) const
            {
                if (!holder)
                {
                    throw ak::exception() << "any::get() : no stored data";
                }
                if (!holder->get(&t, ak::reflection::typename_of(t)))
                {
                    throw ak::exception() << "any::get() : type incorrect or no stored data";
                }
            }

            template<typename T>
            void operator = (const T & t)
            {
                set(t);
            }

            template<typename T>
            operator T () const
            {
                T t;
                get(t);
                return t;
            }
        };
    }
}
