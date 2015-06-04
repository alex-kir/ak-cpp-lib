#pragma once

namespace ak
{
    namespace math
    {
        template<typename T>
        class linear_extrapolation
        {
            T delta;
            std::vector<std::pair<T, T> > pp;
        public:
            linear_extrapolation(T d = 0)
            {
                delta = d;
            }
            linear_extrapolation & set(T x, T y)
            {
                struct
                {
                    T & delta;
                    T & x;
                    bool operator () (const std::pair<T, T> & left)
                    {
                        T diff = left.first - x;
                        return -delta < diff && diff < delta;
                    }
                } equal = { delta, x };
                pp.erase(std::remove_if(pp.begin(), pp.end(), equal), pp.end());

                pp.push_back(std::pair<T, T>(x, y));
                struct
                {
                    bool operator () (const std::pair<T, T> & left, const std::pair<T, T> & rigth)
                    {
                        return left.first < rigth.first;
                    }
                } sorter;
                std::sort(pp.begin(), pp.end(), sorter);
                return *this;
            }
            T get(T x)
            {
                if (pp.size() < 2)
                    throw ak::exception() << "linear_extrapolation.get() : pp.size() < 2";
                int i = 0;
                int j = 1;
                for (int n = pp.size() - 1; j < n; i++, j++)
                {
                    if (x < pp[j].first)
                    {
                        break;
                    }
                }
                return pp[i].second + (x - pp[i].first) /
                    (pp[j].first - pp[i].first) *
                    (pp[j].second - pp[i].second);
            }
        };
    }
}