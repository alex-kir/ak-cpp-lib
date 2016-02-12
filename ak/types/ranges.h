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
                std::sort<range<T>>(
                    this->begin(),
                    this->end()/*,
                    ak::predicate_for_getter(
                    ranges,
                    &ak::types::range<time_t>::get_min_value
                    )*/
                    );

                for (int i = 0, n = this->size(); i < n; i++)
                {
                    if (this->at(i).is_empty())
                        continue;
                    for (int j = i + 1; j < n; j++)
                    {
                        if (this->at(j).is_empty())
                            continue;
                        if (this->at(i).intersect(this->at(j), delta))
                        {
                            this->at(i).extend_by(this->at(j));
                            this->at(j).make_empty();
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                erase(
                    std::remove_if(
                    this->begin(),
                    this->end(),
                    ak::predicate_unary<ak::types::range<T> >(
                    &ak::types::range<T>::is_empty,
                    true,
                    std::logical_and<bool>()
                    )
                    ),
                    this->end()
                    );
            }

        };
    }
}