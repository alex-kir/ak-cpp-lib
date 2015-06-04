#pragma once

namespace ak
{
    namespace ui
    {
        class combobox : public window
        {
        public:
            combobox & create(const window & parent, int id, const ak::point<int> & pt, const ak::size<int> & sz, const std::vector<std::string> & items);
            combobox & create(const window & parent, int id, const ak::rectangle<int> & rect, const std::vector<std::string> & items)
            {
                return create(parent, id, rect.location(), rect.size(), items);
            };

            void add_item(const std::string & item);
            void select(const std::string & item);
        };
    }
}

