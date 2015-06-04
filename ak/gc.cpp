#include "gc.h"

#include <set>
#include <iostream>

namespace alexk
{
    namespace gc
    {
        //-----------------------------//
        //-----COLLECTOR---------------//
        //-----------------------------//

        class gc_collector
        {
        private:
            struct context_s;
            static context_s * _context;
            context_s * context();
            
        public:
            void add(gc_object * r);
            void add(gc_reference_basic * r);
            void add(gc_field_basic * r);
            void change(gc_field_basic * r);
            void remove(gc_reference_basic * r);
            void remove(gc_field_basic * r);

            void collect();
            void print();
        };

        //-----------------------------//

        struct gc_collector::context_s
        {
            std::set<gc_object*> objects;
            std::set<gc_reference_basic*> references;
            std::set<gc_field_basic*> fields;
            int rcount;
            int fcount;
            bool collecting;
        };

        gc_collector::context_s * gc_collector::_context = 0;

        gc_collector::context_s * gc_collector::context()
        {
            if (!_context)
            {
                _context = new context_s();
                _context->rcount = 0;
                _context->fcount = 0;
                _context->collecting = false;
            }
            return _context;
        }

        void gc_collector::add(gc_object * r)
        {
            context()->objects.insert(r);
        }
        
        void gc_collector::add(gc_reference_basic * r)
        {
            context()->references.insert(r);
        }

        void gc_collector::add(gc_field_basic * r)
        {
            context()->fields.insert(r);
        }

        void gc_collector::remove(gc_reference_basic * r)
        {
            context()->references.erase(r);
            context()->rcount++;
            if (context()->rcount > 8 || context()->references.size() == 0)
            {
                gc_collector().collect();
            }
        }

        void gc_collector::remove(gc_field_basic * r)
        {
            context()->fields.erase(r);
            context()->fcount++;
            if (context()->fcount > 16)
            {
                gc_collector().collect();
            }
        }

        void gc_collector::change(gc_field_basic * r)
        {
            context()->fcount++;
            if (context()->fcount > 16)
            {
                gc_collector().collect();
            }
        }

        void gc_collector::collect()
        {
            if (context()->collecting)
                return;

            context()->collecting = true;

            print();

            typedef std::set<gc_object*>::iterator object_it;
            typedef std::set<gc_reference_basic*>::iterator ref_it;
            typedef std::set<gc_field_basic*>::iterator field_it;

            std::set<gc_object*> & objects = context()->objects;
            std::set<gc_reference_basic*> & refs = context()->references;
            std::set<gc_field_basic*> & fields = context()->fields;

            std::set<gc_object*> marked;

            // ----

            for (ref_it it = refs.begin(); it != refs.end(); it++)
            {
                marked.insert((*it)->getobject());
            }

            // ----

            bool done = false;
            while (!done)
            {
                done = true;
                for (field_it it = fields.begin(); it != fields.end(); it++)
                {
                    if (marked.find((*it)->getholder()) == marked.end())
                        continue;

                    gc_object * obj = (*it)->getobject();
                    if (obj && marked.find(obj) == marked.end())
                    {
                        marked.insert(obj);
                        done = false;
                    }
                }
            }

            // ----

            for (object_it it = objects.begin(); it != objects.end(); it++)
            {
                if (marked.find(*it) == marked.end())
                {
                    delete *it;
                }
            }

            // ----

            objects = marked;
            context()->rcount = 0;
            context()->fcount = 0;

            context()->collecting = false;

            print();
        }

        void gc_collector::print()
        {
            //std::ofstream file("GCLog.txt");
            std::ostream & file = std::cout;
            file << "=======================================================" << std::endl;
            file << "gc_collector::print()" << std::endl;
            file << "    objects    : " << context()->objects.size() << std::endl;
            file << "    references : " << context()->references.size() << std::endl;
            file << "    fields     : " << context()->fields.size() << std::endl;
            file << "-------------------------------------------------------" << std::endl;
            file << std::endl;
        }

        //-----------------------------//
        //-----OBJECT------------------//
        //-----------------------------//
        gc_object::gc_object()
        {
            gc_collector().add(this);
        }

        gc_object::~gc_object()
        {
        }

        //-----------------------------//
        //-----REFERENCE---------------//
        //-----------------------------//
        gc_reference_basic::gc_reference_basic()
        {
            gc_collector().add(this);
        }
        gc_reference_basic::~gc_reference_basic()
        {
            gc_collector().remove(this);
        }

        //-----------------------------//
        //-----FIELD-------------------//
        //-----------------------------//

        gc_field_basic::gc_field_basic(gc_object * p, gc_object * o)
        {
            _holder = p;
            _object = o;
            gc_collector().add(this);
        }
        gc_field_basic::~gc_field_basic()
        {
            gc_collector().remove(this);
        }
        gc_object * gc_field_basic::getobject()
        {
            return _object;
        }
        gc_object * gc_field_basic::getholder()
        {
            return _holder;
        }
        void gc_field_basic::change()
        {
            gc_collector().change(this);
        }

    }
}