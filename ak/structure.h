#pragma once

namespace ak
{
    //template<class T1, class T2>
    //struct structure
    //{
    //    structure(const T1 & t1, const T2 & t2) : first(t1), second(t2) { }
    //    T1 first;
	   // T2 second;
    //};

    template<class T1, class T2, class T3 = int>
    class structure
    {
    public:
        structure() { }
        structure(const T1 & t1, const T2 & t2, const T3 & t3) : first(t1), second(t2), third(t3) { }
        T1 first;
	    T2 second;
        T3 third;
    };
}