#pragma once

#include <ak/misc/nocopy.h>
#include <ak/bind.h>
#include <ak/event_handler.h>
#include <ak/size.h>
#include <ak/types/types.h>
#include <ak/rectangle.h>
#include <ak/structure.h>
#include <ak/exception.h>
#include <ak/sysobj.h>

#include <string>
#include <map>
#include <vector>

namespace ak
{
	namespace ui
	{
        using namespace ak::types;
        class dc;

        class window : public sysobj
		{
            friend class window_utils;
        public:
            window();
            template<typename T>
            window(const T h) : sysobj(h) { };
            ~window();
		public:
            void create(const std::string & cls, int class_style, const std::string & title, int window_style, int window_style_ex, int x, int y, int width, int height, const window & parent);
            void create(const std::wstring & cls, int class_style, const std::wstring & title, int window_style, int window_style_ex, int x, int y, int width, int height, const window & parent);
            void destroy();
		public:
            template<typename _Char, typename _Int>
            void create(const std::basic_string<_Char> & cls, const std::basic_string<_Char> & title, int ws, int wsex, int x, int y, int width, int height, const window & parent = window())
            {
                create(cls, 0, title, ws, wsex, x, y, width, height, parent);
            }

            template<typename _Char, typename _Int>
            void create(const std::basic_string<_Char> & cls, const std::basic_string<_Char> & title, int ws, int wsex, const ak::rectangle<_Int> & rt, const window & parent = window())
            {
                create(cls, 0, title, ws, wsex, rt.x(), rt.y(), rt.width(), rt.height(), parent);
            }

            template<typename _Char, typename _Int>
            void create(const std::basic_string<_Char> & cls, const std::basic_string<_Char> & title, int ws, int wsex, const ak::size<_Int> & sz, const window & parent = window())
            {
                create(cls, 0, title, ws, wsex, 0x80000000, 0x80000000, sz.width, sz.height, parent);
            }

            template<typename _Char, typename _Int>
            void create(const std::basic_string<_Char> & cls, const std::basic_string<_Char> & title, int ws, int wsex, const ak::point<_Int> & pt, const ak::size<_Int> & sz, const window & parent = window())
            {
                create(cls, 0, title, ws, wsex, pt.x, pt.y, sz.width, sz.height, parent);
            }

		public:
            window parent();
		public:
            void set_capture();
            void release_capture();
            void show();
            void show_no_activate();
            void hide();
            bool is_show();
		public:
            int get_id();
            void set_id(int id);
		public:
            std::string get_text();
            void set_text(const std::string & text);
			std::string wnd_class_name();
        private:
            
		public:
            bool is_valid_handle() const { return !empty(); }
            void * get_internal_handle() const { return object<void*>(); }
        public:
            int post_message(int m, int wparam, int lparam);
            static void quit();
            void invalidate();
            void update_layered(dc & dc);
		public:
            ak::rectangle<int> rectangle(bool onscreen);
            void rectangle(int x, int y, int width, int height);
            ak::rectangle<int> clientrectangle();
            
            point<int> position(bool onscreen) { return rectangle(onscreen).position(); }
            template<typename T>
            void position(const ak::point<T> & pt)
            {
                position(pt.x, pt.y);
            }
            void position(int x, int y);

            ak::sizei size(bool onscreen) { return rectangle(onscreen).size(); }
            void size(int width, int height);
            
            
            void clientsize(int width, int height);
            void adjust_size(int cx, int cy);
            void adjust_height(int cy);
		public:
            void set_timer(int id, int elapse);
            void kill_timer(int id);
		public:
            window & set_font();
			std::vector<window> children();
		};
    }
}