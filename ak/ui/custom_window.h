#pragma once

#include <ak/misc/nocopy.h>
#include <ak/bind.h>
#include <ak/event_handler.h>
#include <ak/size.h>
#include <ak/point.h>
#include <ak/rectangle.h>
#include <ak/structure.h>
#include <ak/exception.h>

#include <string>
#include <map>
#include <vector>

namespace ak
{
	namespace ui
	{
        class dc;

		class window
		{
            friend class window_utils;
        private:
            void * _inernal_handle;
	        
        public:
            window();
            ~window();
            void create(const std::string & cls, const std::string & title, int class_style, int window_style, int window_style_ex, ak::size<unsigned int> window_size, const window & parent = window());
            void create(const std::string & cls, const std::string & title, int class_style, int window_style, int window_style_ex, const ak::rectangle<int> & window_size, const window & parent = window());
            void create(const std::wstring & cls, const std::wstring & title, int class_style, int window_style, int window_style_ex, ak::size<unsigned int> window_size);
            void create(const std::wstring & cls, const std::wstring & text);
            void destroy();

            // callback return true if processed
            virtual bool message(unsigned int m, unsigned int wp, unsigned int lp);
            int show_dialog();
            void show();
            void hide();

		public:
            bool is_valid_handle();
            void * get_inernal_handle() const { return _inernal_handle; }
	
        public:
            static void quit();
            void invalidate();
            void update_layered(dc & dc);

        public:
            event_handler<window, int> wm_paint;
            event_handler<window, point<int> > wm_mousemove;
            event_handler<window, int> wm_mouseleave;
            event_handler<window, structure<point<int>, int> > wm_buttonup;
            event_handler<window, structure<point<int>, int> > wm_buttondown;

            

		//	WNDPROC _fnPrevProc;

		//	static window * get_this(HWND hWnd);
		//	static void set_this(HWND hWnd, x_Window * wnd);

		//	virtual bool _onClose(){return false;};
		//	virtual bool _onTimer(){return false;};
		//	virtual bool _onClick(){return false;};
		//	virtual bool _onTabchange(){return false;};
		//	virtual bool _onDblClick(){return false;};
		//	virtual bool _onSelChange(){return false;};


		public:
            ak::rectangle<int> rectangle();
            void position(const ak::point<int> & pt);
		//	window(const x_Window * prnt, const char * title, const char * clname, int x, int y, int width, int height, int st, int stex);
		//	~window();
		//	void show(bool sh = true);
		//	int gettext(char * buff, int sz = 1023);
		//	bool settext(const char * buff);
		//	int get_id();
		//	void set_id(int id);
		//	void settimer(int id, int elapse);
		//	void killtimer(int id);
		//	void topmost(bool b);

		//private:
		//	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		//	x_Window(const x_Window &);
		//	x_Window & operator = (const x_Window &);
		};
    }
}