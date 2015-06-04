#pragma once

namespace ak
{
    namespace ui
    {
        class textbox : public window
        {
        public:
            textbox & create(const window & parent, const std::string & text, int x, int y, int width, int height);
            template<typename T>
            textbox & create(const window & parent, const std::string & text, const ak::rectangle<T> & rt)
            {
                return create(parent, text, rt.x(), rt.y(), rt.width(), rt.height());
            }
        };
    }
}

