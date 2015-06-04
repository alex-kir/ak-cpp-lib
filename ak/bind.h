#pragma once

namespace ak
{
    template<class SENDER, class ARGS>
    class bind
    {
        typedef void (*event_handler)(SENDER * sender, ARGS e);
        event_handler _eh;
    public:
        bind()
        {
            _eh = 0;
        }
        bind(const bind & b);
        bind(const event_handler eh)
        {
            _eh = eh;
        }

        void operator () (SENDER * sender, ARGS e)
        {
            if (_eh)
                _eh(sender, e);
        }
    };
}