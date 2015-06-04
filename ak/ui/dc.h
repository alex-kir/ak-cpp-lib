#pragma once

#include <ak/misc/nocopy.h>
#include <ak/ui/window.h>
#include <ak/ui/icon.h>
#include <ak/rectangle.h>
#include <ak/sysobj.h>

namespace ak
{
    namespace ui
    {
        class dc
        {
            unsigned int * _buffer;
            unsigned int _width;
            unsigned int _height;
            sysobj _dc;
            sysobj _bitmap;
        public:
            dc();
            virtual ~dc();
        public:
            void create(unsigned int w, unsigned int h);
            template<typename T1>
            void create(const size<T1> & sz)
            {
                create(sz.width, sz.height);
            }
            void from_window(ak::ui::window & w);
            void from_file(const std::string & filename);
            void destroy();

        public:
            sysobj & object() { return _dc; }
            unsigned int width() const { return _width; };
            unsigned int height() const { return _height; };
            //ak::sizei size() { return ak::sizei(_width, _height); }
            unsigned int  * buffer() { return _buffer; };

            unsigned int * operator [] (int y) { return _buffer + (_height - y - 1) * _width; }
        public:
            void copy(dc & dc_);
            void copy_alpha(dc & other, const point<int> & pt);
            //void copy_transparent(dc & dc_);

            void fill(unsigned int color);
            void fill_and(unsigned int color);
            void fill_or(unsigned int color);

            void fill(unsigned int color, int x1, int y1, int x2, int y2);
            void fill(unsigned int color, const point<int> & pt, const ak::size<int> & sz);
            void fill(unsigned int color, const rectangle<int> & rt);
            void fill_or(unsigned int color, const rectangle<int> & rt);

        public:
            void draw_line(int x1, int y1, int x2, int y2);
            void draw_rect(const ak::rectangle<int> & rect);
        public:
            ak::size<int> measure_text(const std::string & text, int width = 0xffff);
            ak::size<int> measure_text(const std::wstring & text, int width = 0xffff);
        public:
            void draw_text(const std::string & text, int x, int y);
            template<typename T>
            void draw_text(const std::string & text, const ak::point<T> & pt)
            {
                draw_text(text, pt.x, pt.y);
            }
            void draw_text(const std::wstring & text, const ak::point<int> & pt);

            void draw_text(const std::string & text, const ak::rectangle<int> & rect);
            void draw_text(const std::wstring & text, const ak::rectangle<int> & rect);
        public:
            template<typename T>
            void draw_icon(const icon & icon1, const ak::point<T> & pt) { draw_icon(icon1, pt.x, pt.y); }
            void draw_icon(const icon & icon1, int x, int y);

        public:
            void color(int rgb);
            void color(int r, int g, int b);
            void text_color(int rgb);
            void bk_color(int rgb);
            void bk_transparent();
        public:
            void font();
        };
    }
}