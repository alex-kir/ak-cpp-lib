#pragma once
#include <ak/cast.h>
#include <ak/types/types.h>
#include <vector>
#include <algorithm>
#include <map>

namespace ak
{

    class notification_args : public std::map<std::string, ak::types::any>
    {
    public:
        template<typename T>
        notification_args & add(const std::string & key, const T & value)
        {
            ak::types::any a;
            a = value;
            this->operator[](key) = a;

            return *this;
        }

        const ak::types::any & operator [] (const std::string & key) const
        {
            const_iterator it = find(key);
            //if (it == end())
            //    return ;
            return it->second;
        }
        ak::types::any & operator [] (const std::string & key)
        {
            return (*((std::map<std::string, ak::types::any>*)this))[key];
        }
    };

    class basic_notification
    {
    protected:
        basic_notification() { }
    public:
        virtual ~basic_notification() { }
        virtual void notify(const notification_args & args) = 0;
        virtual basic_notification * clone() = 0;
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////
    
    template<typename _Class, typename _Method>
    class notification_impl : public basic_notification
    {
    private:
        _Class * object;
        _Method method;
    public:
        notification_impl(_Class * o, _Method m) : object(o), method(m)
        { }
        void notify(const notification_args & args)
        {
            (*object.*method)(args);
        }
        basic_notification * clone()
        {
            return new notification_impl(object, method);
        }
    };


    ///////////////////////////////////////////////////////////////////////////////////////////////

    class notification
    {
        basic_notification * pn;
    public:
        notification()
        {
            pn = 0;
        }
        notification(const notification & other)
        {
            pn = other.pn ? other.pn->clone() : 0;
        }
        void operator = (const notification & other)
        {
            delete pn, pn = 0;
            pn = other.pn ? other.pn->clone() : 0;
        }
        ~notification()
        {
            delete pn, pn = 0;
        }

        template<typename _Class, typename _Method>
        void set(_Class * object, _Method method)
        {
            delete pn, pn = 0;
            pn = new notification_impl<_Class, _Method>(object, method);
        }

        void notify(const notification_args & args)
        {
            if (pn)
                pn->notify(args);
        }
    };   

    class notifications : protected std::vector<notification>
    {
    public:
        template<typename _Class, typename _Method>
        void add(_Class * object, _Method method)
        {
            notification n;
            n.set(object, method);
            push_back(n);
        }

        void notify(const notification_args & args)
        {
            for (int i = 0; i < (int)size(); i++)
            {
                at(i).notify(args);
            }
        }
    };



    ///////////////////////////////////////////////////////////////////////////////////////////////



}
//
//namespace ak
//{
//    
//    template<typename T>
//    class basic_event_arg_impl
//    {
//    protected:
//        virtual void push(const T & arg)
//        {
//            throw ak::exception() << "basic_event_arg_impl::push_impl(T)";
//        }
//        virtual void pop(T & arg)
//        {
//            throw ak::exception() << "basic_event_arg_impl::push_impl(T)";
//        }
//    };
//
//    class basic_event_arg
//        : public basic_event_arg_impl<int>
//        , public basic_event_arg_impl<double>
//        , public basic_event_arg_impl<std::string>
//    {
//    };
//
//    template<typename TBase>
//    class event_arg_end
//    {
//    public:
//        typedef TBase BaseType;
//    };
//
//    template<typename TBase>
//    class eae : public event_arg_end<TBase>
//    {
//    };
//
//    template<typename T, typename TNext, typename TBase = TNext::BaseType>
//    class event_arg_list
//    {
//    public:
//        typedef TBase BaseType;
//    private:
//        T argument;
//        TNext next;
//    public:
//        virtual TNext & push(const T & arg)
//        {
//            argument = arg;
//            return next;
//        }
//        virtual TNext & pop(T & arg)
//        {
//            arg = argument;
//            return next;
//        }
//    };
//    
//    template<typename T, typename TNext, typename TBase = TNext::BaseType>
//    class eal : public event_arg_list<T, TNext, TBase>
//    { };
//
//    class basic_event
//    {
//        
//    };
//
//    template<typename TArg>
//    class event
//    {
//    };
//
//    class events
//    {
//
//    };
//
//}
//
//namespace ak_tests
//{
//    void test1();
//}
