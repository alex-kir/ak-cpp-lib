#pragma once

namespace ak
{
    namespace ui
    {
        class topwindow : public window
        {
        public:
            topwindow() { }
            topwindow(const window & wnd) { object(wnd.object()); }
        public:
            static topwindow foreground();
			static std::vector<topwindow> all();
        public:
            void maximize();
            void minimize();
            void restore();
            void close();
        };
    }
}