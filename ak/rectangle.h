#pragma once
#include <ak/types/types.h>
#include <ak/size.h>

namespace ak
{
    using ak::types::point;

    template<typename T1>
    class rectangle
    {
    private:
        T1 _x1, _y1, _x2, _y2;
		void _sort() { _sortx(); _sorty();	};
        void _sortx() { if (_x1 > _x2) std::swap(_x1, _x2); };
        void _sorty() { if (_y1 > _y2) std::swap(_y1, _y2); };
    public:
        rectangle() : _x1(0), _y1(0), _x2(0), _y2(0) { }
        rectangle(int width, int height) : _x1(0), _y1(0), _x2(width), _y2(height) { _sort(); }
        rectangle(const size<T1> & sz) : _x1(0), _y1(0), _x2(sz.width), _y2(sz.height) { _sort(); }
        rectangle(T1 x1, T1 y1, T1 x2, T1 y2) : _x1(x1), _y1(y1), _x2(x2), _y2(y2) { _sort(); }
        rectangle(const point<T1> & pt, const size<T1> & sz) : _x1(pt.x), _y1(pt.y), _x2(pt.x + sz.width), _y2(pt.y + sz.height) { _sort(); }
        rectangle(const point<T1> & pt1, const point<T1> & pt2) : _x1(pt1.x), _y1(pt1.y), _x2(pt2.x), _y2(pt2.y) { _sort(); }
    public:
        T1 left() const { return _x1; }
        T1 top() const { return _y1; }
        T1 right() const { return _x2; }
        T1 bottom() const { return _y2; }
    public:
        rectangle & left(T1 left1, bool fixsize)
        {
            if (fixsize)
            {
                T1 width1 = width();
                _x2 = left1 + width1;
            }
            _x1 = left1;
            _sortx();
            return *this;
        }
        rectangle & top(T1 top1, bool fixsize)
        {
            if (fixsize)
            {
                T1 height1 = height();
                _y2 = top1 + height1;
            }
            _y1 = top1;
            _sorty();
            return *this;
        }
        rectangle & right(T1 right1, bool fixsize)
        {
            if (fixsize)
            {
                T1 width1 = width();
                _x1 = right1 - width1;
            }
            _x2 = right1;
            _sortx();
            return *this;
        }
        rectangle & bottom(T1 bottom1, bool fixsize)
        {
            if (fixsize)
            {
                T1 height1 = height();
                _y1 = bottom1 - height1;
            }
            _y2 = bottom1;
            _sorty();
            return *this;
        }
    public:
        T1 x() const { return left(); }
        T1 y() const { return top(); }
        T1 width() const { return std::abs(_x1 - _x2); }
        T1 height() const { return std::abs(_y1 - _y2); }
    public:
        rectangle & width(T1 width1) { _x2 = _x1 + width1; _sortx(); return *this; }
        rectangle & height(T1 height1) { _y2 = _y1 + height1; _sorty(); return *this; }
    public:
        point<T1> location() const { return point<T1>(x(), y()); }
        point<T1> position() const { return location(); }
        size<T1> size() const { return ak::size<T1>(width(), height()); }
    public:
        rectangle & location(T1 x, T1 y) { return left(x, true).top(y, true); }
        rectangle & location(const point<T1> & pt) { return location(pt.x, pt.y); }
        rectangle & size(T1 width1, T1 height1) { return width(width1).height(height1); }
        rectangle & size(const ak::size<T1> & sz) { return size(sz.width, sz.height); }
    public:
        void inflate(T1 t) { _sort(); _x1 -= t; _x2 += t; _y1 -= t; _y2 += t; }
        void inflate(const ak::size<T1> & sz) { _sort(); _x1 -= sz.width; _x2 += sz.width; _y1 -= sz.height; _y2 += sz.height; }
        //void inflate(const point<T1> & pt) { _sort(); _x1 -= pt.x; _x2 += pt.x; _y1 -= pt.y; _y2 += pt.y; }
    public:
        bool contains(const point<T1> & pt) {return pt.x > left() && pt.x < right() && pt.y > top() && pt.y < bottom(); }
        //size<T1> get_size() const { return size<T1>(width(), height()); }

    };

    typedef rectangle<int> rectanglei;
    typedef rectangle<float> rectanglef;
    typedef rectangle<double> rectangled;
}