#pragma once

namespace ak
{
    namespace types
    {
        template<typename T>
        class range
        {
        private:
            bool empty;
            T min_value, max_value;
        public:
            range()
            {
                make_empty();
            }

            range(const T & min, const T & max)
            {
                set_bounds(min, max);
            }

            bool is_empty() const
            {
                return empty;
            }

            const T & get_min_value() const
            {
                return min_value;
            }

            const T & get_max_value() const
            {
                return max_value;
            }

            void make_empty()
            {
                empty = true;
            }

            bool intersect(const range & other) const
            {
                if (is_empty()) return false;
                if (other.is_empty()) return false;
                if (other.max_value < min_value) return false;
                if (max_value < other.min_value) return false;
                return true;
            }

            bool intersect(const range & other, const T & delta) const
            {
                if (is_empty()) return false;
                if (other.is_empty()) return false;
                if (other.max_value + delta < min_value) return false;
                if (max_value + delta < other.min_value) return false;
                return true;
            }

            range common_with(const range & r) const
            {
                range retval;
                if (intersect(r))
                    retval.set_bounds(std::max<T>(min_value, r.min_value), std::min<T>(max_value, r.max_value));
                return retval;
            }

            void extend_by(const range & r)
            {
                if (!r.is_empty())
                    extend_by(r.min_value, r.max_value);
            }

            void extend_by(T value)
            {
                extend_by(value, value);
            }

            void extend_by(T min, T max)
            {
                if (is_empty())
                {
                    set_bounds(min, max);
                }
                else
                {
                    set_bounds(std::min<T>(min_value, min), std::max<T>(max_value, max));
                }
            }

            void set_bounds(T min, T max)
            {
                empty = false;
                if (min < max)
                {
                    min_value = min;
                    max_value = max;
                }
                else
                {
                    min_value = max;
                    max_value = min;
                }
            }
        };

        template<typename T>
        bool operator < (const range<T> & l, const range<T> & r)
        {
            return l.get_min_value() < r.get_min_value();
        }

        typedef range<int> rangei;
        typedef range<double> ranged;
        typedef range<float> rangef;
    }
}
