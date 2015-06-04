#pragma once

#include <ak/size.h>
#include <ak/types/types.h>
#include <ak/rectangle.h>
#include <ak/exception.h>
#include <ak/sysobj.h>

#include <string>
#include <map>
#include <vector>

namespace ak
{
	namespace ui
	{
        class dc;

        class control : public sysobj
		{
            friend class window_utils;
        public:
            control();
            template<typename T>
            control(const T h) : sysobj(h) { };
            ~control();
		public:

		public:
            void show();
            void show_no_activate();
            void hide();
            bool is_show();
            //------------------//
            // control hierarhy //
            //------------------//
            control parent();
            std::vector<control> children();
            static control under_point(const point<int> & pt);
            pointi pointtoclient(const pointi & pt);
		public:
            std::string text();
            void text(const std::string & text);
            std::string control::classname();
            long stylemask();
            long stylemaskex();
        public:
            int post_message(int m, int wparam, int lparam);
            void invalidate();
            void update_layered(dc & dc);
		public:
            //----------------//
            // size, position //
            //----------------//
            ak::rectangle<int> rectangle(bool onscreen);
            void rectangle(int x, int y, int width, int height);
            ak::rectangle<int> clientrectangle();
            
            ak::point<int> position(bool onscreen)
            {
                return rectangle(onscreen).position();
            }
            template<typename T>
            void position(const ak::point<T> & pt)
            {
                position(pt.x, pt.y);
            }
            void position(int x, int y);

            ak::sizei size(bool onscreen)
            {
                return rectangle(onscreen).size();
            }
            void size(int width, int height);
            
            void clientsize(int width, int height);
            void adjust_size(int cx, int cy);
            void adjust_height(int cy);
		public:
		};
    }
}