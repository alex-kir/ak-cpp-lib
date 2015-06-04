#include <ak/notification.h>
//#include <ak/reflection/reflection.h>
//#include <ak/types/types.h>
//
//
//namespace ak_tests
//{
//    void test1()
//    {
//        using namespace ak;
//
//        std::string s, s1;
//        double d;
//        int i;
//
//        eal<std::string, eal<int, eal<double, eae<void> > > > args;
//        args.push("1.1").push(2).push(1.1);
//
//        args.pop(s).pop(i).pop(d);
//
//
//        //basic_event_arg & be = args;
//
//        //args.pop()
//        //////////////////////////////////
//
//        int * a = &i;
//
//        s = ak::reflection::type_name_of(&s);
//        s = ak::reflection::type_name_of(&a);
//
//
//        ak::types::any<> aa, aa1;
//        aa = 5;
//        i = aa;
//        aa1 = aa;
//        aa.set(s);
//        s = "123";
//        aa.get(s);
//
//        ak::types::any_stream<true> as;
//        as << 34 << 6 << std::string("asdasd") << "123123321" << 1.1;
//
//        as >> i >> i >> s >> s1 >> s1;
//    }
//}