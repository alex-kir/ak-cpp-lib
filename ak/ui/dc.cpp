#include <ak/ui/dc.h>

#pragma comment (lib, "Msimg32.lib")

namespace ak
{
	namespace ui
	{
		dc::dc()
		{
			_width = 0;
			_height = 0;
			_buffer = 0;
			_dc = 0;
			_bitmap = 0;
		}

		dc::~dc()
		{
		}

		void dc::create(unsigned int width, unsigned int height)
		{
			_width = width;
			_height = height;
			SIZE sz = {_width, _height};
			BITMAPINFO bmi;
			ZeroMemory(&bmi, sizeof(BITMAPINFO));
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = sz.cx;
			bmi.bmiHeader.biHeight = sz.cy;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;
			bmi.bmiHeader.biSizeImage = sz.cx * sz.cy * 4;
            _dc = ::CreateCompatibleDC(NULL);
            _bitmap = ::CreateDIBSection(_dc.object<HDC>(), &bmi, DIB_RGB_COLORS, (void**)&_buffer, NULL, 0x0);
            ::SelectObject(_dc.object<HDC>(), _bitmap.object<HBITMAP>());
            ::SelectObject(_dc.object<HDC>(), GetStockObject(DC_PEN));
		}

		void dc::from_window(ak::ui::window & w)
		{
            HWND h = (HWND)w.get_internal_handle();
            _dc = ::GetDC(h);
            RECT rt;
            ::GetClientRect(h, &rt);
            _width = rt.right;
            _height = rt.bottom;
		}

        void dc::from_file(const std::string & filename)
        {
            _dc = ::CreateCompatibleDC(NULL);
            _bitmap = ::LoadImageA(NULL, filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            BITMAP bitmap;
            ::GetObject(_bitmap, sizeof(BITMAP), (LPSTR)&bitmap);
            _width = bitmap.bmWidth;
            _height = bitmap.bmHeight;
            ::SelectObject(_dc, _bitmap);
        }

        void dc::destroy()
		{
            ::DeleteDC((HDC)_dc);
            _dc = 0;
            ::DeleteObject((HBITMAP)_bitmap);
            _bitmap = 0;
		}

        void dc::draw_line(int x1, int y1, int x2, int y2)
        {
            ::MoveToEx((HDC)_dc, x1, y1, 0);
            ::LineTo((HDC)_dc, x2, y2);
        }

        void dc::draw_rect(const ak::rectangle<int> & rect)
        {
            //::Rectangle((HDC)_dc, rect.left(), rect.top(), rect.right(), rect.bottom());
            ::MoveToEx((HDC)_dc, rect.left(), rect.top(), 0);
            ::LineTo((HDC)_dc, rect.right() - 1, rect.top());
            ::LineTo((HDC)_dc, rect.right() - 1, rect.bottom() - 1);
            ::LineTo((HDC)_dc, rect.left(), rect.bottom() - 1);
            ::LineTo((HDC)_dc, rect.left(), rect.top());
        }

        ak::size<int> dc::measure_text(const std::string & text, int width)
        {
            RECT rt;
            SetRect(&rt, 0, 0, width, 0xffff);
            ::DrawTextA((HDC)_dc, text.c_str(), (int)text.size(), &rt, DT_CALCRECT | DT_WORDBREAK);
            return rectangle<int>(rt.left, rt.top, rt.right, rt.bottom).size();
        }

        ak::size<int> dc::measure_text(const std::wstring & text, int width)
        {
            RECT rt;
            SetRect(&rt, 0, 0, width, 0xffff);
            ::DrawTextW((HDC)_dc, text.c_str(), (int)text.size(), &rt, DT_CALCRECT | DT_WORDBREAK);
            return rectangle<int>(rt.left, rt.top, rt.right, rt.bottom).size();
        }

        void dc::draw_text(const std::string & text, int x, int y)
        {
            RECT rt;
            SetRect(&rt, x, y, x, y);
            ::DrawTextA((HDC)_dc, text.c_str(), (int)text.size(), &rt, DT_LEFT | DT_TOP | DT_NOCLIP);
        }

        void dc::draw_text(const std::wstring & text, const ak::point<int> & pt)
        {
            RECT rt;
            SetRect(&rt, pt.x, pt.y, pt.x, pt.y);
            ::DrawTextW((HDC)_dc, text.c_str(), (int)text.size(), &rt, DT_LEFT | DT_TOP | DT_NOCLIP);
        }

        void dc::draw_text(const std::string & text, const ak::rectangle<int> & rect)
        {
            RECT rt;
            SetRect(&rt, rect.left(), rect.top(), rect.right(), rect.bottom());
            ::DrawTextA((HDC)_dc, text.c_str(), (int)text.size(), &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
        }

        //void dc::draw_text_c(const std::string & text, const ak::rectangle<int> & rect)
        //{
        //    RECT rt;
        //    SetRect(&rt, rect.left(), rect.top(), rect.right(), rect.bottom());
        //    ::DrawTextA((HDC)_dc, text.c_str(), text.size(), &rt, DT_CENTER | DT_VCENTER);
        //}

        void dc::draw_text(const std::wstring & text, const ak::rectangle<int> & rect)
        {
            RECT rt;
            SetRect(&rt, 0, 0, rect.right() - rect.left(), rect.bottom() - rect.top());
            ::DrawTextW((HDC)_dc, text.c_str(), (int)text.size(), &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
        }

        void dc::draw_icon(const icon & icon1, int x, int y)
        {
            ::DrawIcon((HDC)_dc, x, y, icon1.object<HICON>());
        }

        void dc::copy(dc & dc_)
        {
            BitBlt((HDC)_dc, 0, 0, _width, _height, (HDC)dc_._dc, 0, 0, SRCCOPY);
        }

        void dc::fill(unsigned int color)
        {
            int n = width() * height();
            for (int i = 0; i < n; i++)
            {
                _buffer[i] = color;
            }
        }

        void dc::fill_and(unsigned int color)
        {
            int n = width() * height();
            for (int i = 0; i < n; i++)
            {
                _buffer[i] &= color;
            }
        }

        void dc::fill_or(unsigned int color)
        {
            int n = width() * height();
            for (int i = 0; i < n; i++)
            {
                _buffer[i] |= color;
            }
        }

        void dc::fill(unsigned int color, int x1, int y1, int x2, int y2)
        {
            for (int y = y1; y < y2; y++)
            {
                for (int x = x1; x < x2; x++)
                {
                    (*this)[y][x] = color;
                }
            }
        }

        void dc::fill(unsigned int color, const point<int> & pt, const size<int> & sz)
        {
            int x2 = pt.x + sz.width;
            int y2 = pt.y + sz.height;
            for (int y = pt.y; y < y2; y++)
            {
                for (int x = pt.x; x < x2; x++)
                {
                    (*this)[y][x] = color;
                }
            }
        }

        void dc::fill(unsigned int color, const rectangle<int> & rt)
        {
            int x2 = rt.right();
            int y2 = rt.bottom();
            for (int y = rt.top(); y < y2; y++)
            {
                for (int x = rt.left(); x < x2; x++)
                {
                    (*this)[y][x] = color;
                }
            }
        }

        void dc::fill_or(unsigned int color, const rectangle<int> & rt)
        {
            int x2 = rt.right();
            int y2 = rt.bottom();
            for (int y = rt.top(); y < y2; y++)
            {
                for (int x = rt.left(); x < x2; x++)
                {
                    (*this)[y][x] |= color;
                }
            }
        }

        void dc::copy_alpha(dc & other, const point<int> & pt)
        {
            BLENDFUNCTION blender = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
            ::AlphaBlend((HDC)_dc, pt.x-5, pt.y-5, other.width(), other.height(), (HDC)other._dc, 0, 0, other.width(), other.height(), blender);
        }

        void dc::color(int rgb)
        {
            ::SetDCPenColor((HDC)_dc, rgb);
        }

        void dc::bk_color(int rgb)
        {
            ::SetBkColor((HDC)_dc, rgb);
        }

        void dc::bk_transparent()
        {
            ::SetBkMode((HDC)_dc, TRANSPARENT);
        }

        void dc::text_color(int rgb)
        {
            ::SetTextColor((HDC)_dc, rgb);
        }

        void dc::color(int r, int g, int b)
        {
            ::SetDCPenColor((HDC)_dc, RGB(r, g, b));
        }

        void dc::font()
        {
            ::SelectObject((HDC)_dc, (HGDIOBJ)::GetStockObject( DEFAULT_GUI_FONT ));
        }

	}
}