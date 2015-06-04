#pragma once

#pragma warning (disable: 4355)

namespace alexk
{
    namespace gc
    {

        class gc_object;

        class gc_reference_basic;
        class gc_field_basic;

        template<typename T>
        class gc_ref;
        
        template<typename T>
        class gc_field;


        //-----------------------------//
        //-----OBJECT------------------//
        //-----------------------------//

        class gc_object
        {
        public:
            gc_object();
        protected:
            virtual ~gc_object();
            friend class gc_collector;
        };

        //-----------------------------//
        //-----REFERENCE---------------//
        //-----------------------------//

        class gc_reference_basic
        {
        public:
            gc_reference_basic();
            virtual ~gc_reference_basic();
            virtual gc_object * getobject() = 0;
        };

        template<typename T>
        class gc_ref : public gc_reference_basic
        {
            T * _object;
        public:
            gc_ref(T * o)
            {
                _object = o;
            }
            gc_object * getobject()
            {
                return _object;
            }
            T * operator -> ()
            {
                return _object;
            }
            operator T * ()
            {
                return _object;
            }
        };

        //-----------------------------//
        //-----FIELD-------------------//
        //-----------------------------//

        class gc_field_basic
        {
        protected:
            gc_object * _holder;
            gc_object * _object;
        public:
            gc_field_basic(gc_object * p, gc_object * o);
            virtual ~gc_field_basic();
            gc_object * getobject();
            gc_object * getholder();
            void change();
        };

        template<typename T>
        class gc_field : public gc_field_basic
        {
        public:
            gc_field(gc_object * p, T * o = 0)
                : gc_field_basic(p, o)
            {
            }
            T * operator -> ()
            {
                return _object;
            }
            void operator = (T * o)
            {
                _object = o;
                change();
            }
        };
    }
}