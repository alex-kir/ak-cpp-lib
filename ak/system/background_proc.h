#pragma once
#include <ak/notification.h>
#include <ak/shared_ptr.h>
#include <ak/system/thread.h>

namespace ak
{
    namespace system
    {
        template<typename _Notification>
        class _background_proc_wrap : public thread
        {
            _Notification _proc;
        public:
            _background_proc_wrap(const _Notification & proc) : _proc(proc)
            {
            }
            virtual void procedure()
            {
                _proc.notify();
            }
        };

        template<typename _Class, typename _Method>
        thread * background_proc(_Class * object, _Method method)
        {
            _background_proc_wrap<ak::notification_0<_Class, _Method> > * bgproc = 0;
            bgproc = new _background_proc_wrap<ak::notification_0<_Class, _Method> >(create_notification_0(object, method));
            bgproc->run();
            return bgproc;
        }
    }
}