#pragma once

namespace ak
{
    template<typename T, typename R, int S>
    class array
    {
        T * buffer;
        int width;
        int height;
    public:
        array(T * b)
        {
            buffer = b;
            width = w;
            height = h;
        }

        R & operator [](int index)
        {
            return R(buffer + S * index);
        }
    };

}