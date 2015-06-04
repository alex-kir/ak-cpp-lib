#pragma once

namespace ak
{
	namespace ui
	{
        class dialog_result
        {
            int _operation;
            int _sender;
        public:
            dialog_result() : _sender(0), _operation(0)
            { }
            dialog_result(int sender, int operation) : _sender(sender), _operation(operation)
            { }
            bool operator == (const dialog_result & r) const
            {
                return _sender == r._sender && _operation == r._operation;
            }
            bool operator != (const dialog_result & r) const
            {
                return !(*this == r);
            }
        public:
            static const dialog_result unknown()                        { return dialog_result(0xffffffff,  0xffff); }
            static const dialog_result button_clicked(int id)           { return dialog_result(id,          0x0001); }
            static const dialog_result close()                          { return dialog_result(0,           0x0002); }
            static const dialog_result queryendsession()                { return dialog_result(0,           0x0003); }
            static const dialog_result endsession()                     { return dialog_result(0,           0x0004); }
            static const dialog_result mouse_move()                     { return dialog_result(0,           0x0005); }
            static const dialog_result timer(int id)                    { return dialog_result(id,          0x0006); }
            static const dialog_result mouse_leave()                    { return dialog_result(0,           0x0007); }
        };
    }
}