#pragma once

namespace ak
{
    namespace ui
    {
        class groupbox : public window
        {
        public:
            groupbox & create(const window & parent, const std::string & text, int x1, int y1, int x2, int y2);
            
            groupbox & create(const window & parent, const std::string & text, int x1, int y1)
            {
                return create(parent, text, x1, y1, x1, y1);
            }

            template<typename T>
            groupbox & create(const window & parent, const std::string & text, const ak::rectangle<T> & rect)
            {
                return create(parent, text, rect.left(), rect.top(), rect.right(), rect.bottom());
            };
        };
    }
}

