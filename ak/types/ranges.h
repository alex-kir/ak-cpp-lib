#pragma once

namespace ak
{
    namespace types
    {
        template<typename T>
        class ranges : public std::vector<range<T> >
        {
        public:

            void pack(const T & delta)
            {
                std::sort(
                    begin(),
                    end()/*,
                    ak::predicate_for_getter(
                    ranges,
                    &ak::types::range<time_t>::get_min_value
                    )*/
                    );

                for (int i = 0, n = size(); i < n; i++)
                {
                    if (at(i).is_empty())
                        continue;
                    for (int j = i + 1; j < n; j++)
                    {
                        if (at(j).is_empty())
                            continue;
                        if (at(i).intersect(at(j), delta))
                        {
                            at(i).extend_by(at(j));
                            at(j).make_empty();
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                erase(
                    std::remove_if(
                    begin(),
                    end(),
                    ak::predicate_unary<ak::types::range<T> >(
                    &ak::types::range<T>::is_empty,
                    true,
                    std::logical_and<bool>()
                    )
                    ),
                    end()
                    );
            }

        };
    }
}