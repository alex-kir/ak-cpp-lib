#pragma once

namespace ak
{
    template<class SENDER, class ARGS>
    class event_handler
    {
    public:
        typedef void (*event_handler_fn)(SENDER * sender, ARGS & e);
        event_handler()
        {
            _eh = 0;
        }
        event_handler(const event_handler & b)
        {
            _eh = b._eh;
        };
        event_handler(const event_handler_fn eh)
        {
            _eh = eh;
        }
        void operator = (event_handler_fn eh)
        {
            _eh = eh;
        }
        void operator () (SENDER * sender, ARGS e)
        {
            if (_eh)
                _eh(sender, e);
        }
    private:
        event_handler_fn _eh;
    };
}