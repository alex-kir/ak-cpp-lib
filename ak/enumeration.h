#pragma once

#include <ak/misc/nocopy.h>

namespace ak
{
    class enumeration
    {
    private:
        const int _value;
    protected:
        enumeration(const int val) : _value(val) { };
    public:
        operator int() const { return _value; }
    };

}