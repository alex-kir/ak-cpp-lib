

#include "stdafx.h"
#include <ak/ak.h>
#include <time.h>
#include <iomanip>
#include <fstream>

class indexes
{
public:
    std::vector<int> inds;
    indexes()
    {
    }
    //indexes(int i)
    //{
    //    inds.push_back(i);
    //}
    indexes & add(int i)
    {
        inds.push_back(i);
        return *this;
    }

    bool operator < (const indexes & other) const
    {
        size_t n = other.inds.size();
        if (inds.size() < n)
            return true;
        for (size_t i = 0; i < n; i++)
            if (inds[i] < other.inds[i])
                return true;
        return false;
    }
};

indexes & operator , (indexes & c, const int i2)
{
    return c.add(i2);
}

//template<typename T>
//comma & operator , (comma & c, const T & t2)
//{
//    return c;
//}

namespace ak
{
    namespace html
    {
        namespace ui
        {
            class controls
            {
            };

            class button
            {
            public:
                template<typename R>
                void render(R & r)
                {
                    r.render(*this);
                }
            };

            class table
            {
            public:
                class cell
                {
                public:
                    std::string txt;
                    cell()
                    {
                    }
                    cell(const std::string & t)
                    {
                        txt = t;
                    }
                    cell & set_text(const std::string & t)
                    {
                        txt = t;
                        return *this;
                    }
                    cell & text(const std::string & t)
                    {
                        txt = t;
                        return *this;
                    }
                };

            public:
                std::map<std::string, int> order;
                std::map<std::string, std::string> header;
                std::map<int, std::map<std::string, cell> > body;
            public:
                template<typename R>
                void render(R & r)
                {
                    r.render(*this);
                }

                cell & cell(const std::string & col, int row)
                {
                    return body[row][col];
                }
                //std::string & operator[](const int ii, const std::string & s)
                //{
                //    return data[ii];
                //}

                //std::string & operator[](const indexes & ii)
                //{
                //    return data[ii];
                //}


            };
        }

        class basic_renderer
        {
        public:
            std::stringstream html;
            void render(const ui::button & b)
            {

            }

            void render(const ui::table & b)
            {

            }

            std::string str()
            {
                return html.str();
            }
        };

        class green_table_renderer : public virtual basic_renderer
        {
        public:
            bool first;
            green_table_renderer()
            {
                first = true;
            }

            void render(const ui::table & b)
            {
                if (first)
                {
                    first = false;
                    html << "<style>";
                    html << "body { background-color:#afa; }";
                    html << "table { border:solid #000 1px; }";
                    html << "tr { border:solid #000 0px;}";
                    html << "th { padding:5px; text-transform:capitalize; font-weight:bold; font-variant:small-caps; background-color:#7a7; }";
                    html << "td { padding:5px; border:solid #000 0px; background-color:#bfb; }";
                    html << ".odd td{ background-color:#8e8; }";
                    html << "</style>";
                }
            }

        };

    }
}


//<div style="border:1px solid #000;margin:-1px; position:absolute;left:20%; top:10%; right:20%; bottom:80%">
//<div style="border:1px solid #000;margin:-1px; position:absolute; left:10px; top:10px; right:10px; bottom:-35px;">
//<span style="border:1px solid #000;margin:-1px;">This is a heading with an absolute position</span>
//</div></div>

class App
{
private:
    ak::settings settings;
    ak::types::ranges<time_t> ranges;
    ak::net::http_server server;

    ak::system::bg_method processingThread;
    bool stopped;

    time_t busy_secs;

public:
    ak::ui::icon ico1;
    ak::ui::icon ico2;
    bool animation;
public:
    App()
    {
        ico1.load_from_resource(101);
        ico2.load_from_resource(102);
        animation = false;

        busy_secs = 0;

        settings.setdefault("gluetime", 600);
        settings.setdefault("endtime", 28800);
        settings.setdefault("breaktime", 60*60);
        settings.save();
    }
    ~App()
    {
        processingThread.wait();
    }

    ak::win32::message_loop mloop;
    std::string path;

    void run()
    {
        stopped = false;
        path = ak::path::get_folder(ak::system::process().exepath());

        load(path + "data1.txt");
        load(path + "data2.txt");

        processingThread.create(&app, &App::onProcessingThread, true);


        server.responder("/").set(&app, &App::on_show_page2);
        server.responder("/settings").set(&app, &App::page_settings);
        server.responder("/reload").set(&app, &App::on_reload);
        server.responder("/quit").set(&app, &App::on_quit_confirm);
        server.responder("/quit/yes").set(&app, &App::on_quit);
        server.create("localhost", 10111, 10121);
        server.runasync();

        ni.set_tip(title()).set_icon(ico1);
        ni.on_mouse_left_dblclk.add(&app, &App::on_nicon_double_click);
        ni.on_mouse_right_up.add(&app, &App::on_nicon_mouse_right_up);

        ni.show();
        app.mloop.start();
        ni.hide();

    }

    void on_reload(const ak::notification_args & args)
    {
        std::stringstream * ss = args["stream"];

        settings.load();

        (*ss) << "<h3>Settings was reloaded.</h3>";

        (*ss) << "<p>gluetime = " << settings.get<int>("gluetime") << "</p>";
        (*ss) << "<p>endtime = " << settings.get<int>("endtime") << "</p>";
        (*ss) << "<p>breaktime = " << settings.get<int>("breaktime") << "</p>";

        (*ss) << "<a href='/'>Back</a>";
    }

    void on_quit_confirm(const ak::notification_args & args)
    {
        ak::types::any a = args["stream"];
        std::stringstream * ss;
        ss = a;
        (*ss) << "<h3>Do you realy want to quit?</h3>";
        (*ss) << "<a href='/quit/yes'>Yes</a> ";
        (*ss) << "<a href='/'>No</a>";

    }

    void on_quit(const ak::notification_args & args)
    {
        ak::types::any a = args["stream"];
        std::stringstream * ss;
        ss = a;
        (*ss) << "<h3>Bye!</h3>";

        server.stop();
        stopped = true;
        mloop.stop();
    }

    void on_nicon_double_click(const ak::notification_args & args)
    {
        ak::win32::open_url(ak::string::format("http://%%:%%/") % server.get_host() % server.get_port());
    }

    void on_nicon_mouse_right_up(const ak::notification_args & args)
    {
        busy_secs = 0;
        animation = false;
    }

    void page_settings(const ak::notification_args & args)
    {
        std::stringstream & ss = *(std::stringstream*)args["stream"];

        render_header(ss);

        ss << "<center>";
        ss << "<form>";
        ss << "<table>";
        std::vector<std::string> keys = settings.keys();
        for (int i = 0, n = keys.size(); i < n; i++)
        {
            ss << "<tr>"
                << "<td>" << keys[i] << "</td>"
                << "<td><input name=\"" << keys[i] << "\" type=text value=\"" << settings.get<std::string>(keys[i]) << "\"/></td>"\
                << "</tr>";
        }
        ss << "</table>";
        ss << "</form>";
        ss << "<input type=submit value=\"Save\"/>";
        ss << "</center>";
    }

    void on_show_page2(const ak::notification_args & args)
    {
        ak::types::any a = args["stream"];
        std::stringstream * ss;
        ss = a;
        on_show_page(*ss);
    }


    void render_header(std::stringstream & ss)
    {
        ss << "<style>";
        ss << "body { background-color:#afa; }";
        ss << "table { border:solid #000 1px; }";
        ss << "tr { border:solid #000 0px;}";
        ss << "th { padding:5px; text-transform:capitalize; font-weight:bold; font-variant:small-caps; background-color:#7a7; }";
        ss << "td { padding:5px; border:solid #000 0px; background-color:#bfb; }";
        ss << ".odd td{ background-color:#8e8; }";
        ss << ".weekssum td{ background-color:yellow; }";
        ss << "</style>";

        ss << "<body>";
        ss << "<div style=\"text-align:right;\">";
        ss << "<a href=\"/\"><b>Times</b></a> | ";
        ss << "<a href=\"/settings\">Settings</a> | ";
        ss << "<a href=\"/reload\">Reload settings</a> | ";
        ss << "<a href=\"/quit\">Quit</a>";
        ss << "</div>";
        ss << "<hr/>";

        ss << "<center>";
        ss << "<h1>My Day 2</h1>";
        ss << "<hr/>";
        ss << "</center>";
    }

    void on_show_page(std::stringstream & ss)
    {
        render_header(ss);

        ss << "<center>";
        ss << "<table>";
        ss << "<tr><th>Start time</th><th>End time</th><th>Difference</th></tr>";

        bool odd = true;
        std::string day1;
        std::string day2;
        int summary = 0;
        int week_summary = 0;
        int prevWeek = 0;
        for (int i = ranges.size() - 1; i >= 0; i--)
        {
            char buffmax[100];
            char buffmin[100];
            char format[] = "%d %b %Y <b>%H:%M</b>";
            time_t mintime = ranges[i].get_min_value();
            time_t maxtime = ranges[i].get_max_value();

            _strftime_l(buffmin, 99, format, localtime(&mintime), _locale_t());
            _strftime_l(buffmax, 99, format, localtime(&maxtime), _locale_t());
            time_t minutes = (maxtime - mintime) / 60;

            day1.assign(buffmin, 2);
            if (day2 != day1)
            {
                if (summary != 0)
                {
                    ss << "<tr class=" << (odd ? "odd" : "") << ">";
                    ss << "<td colspan=2 align=right><u><b>Summary:</b></u></td>";
                    ss << "<td><u><b>" << std::setw(2) << std::setfill('0') << summary / 60 << ":" << std::setw(2) << summary % 60 << "</b></u></td>";
                    ss << "</tr>";
                }

                summary = 0;
                day2 = day1;
                odd = !odd;
            }

            int week = ((int)mintime - 4 * 24 * 60 * 60) / (1 * 60 * 60 * 24 * 7);
            if (week != prevWeek && prevWeek > 0)
            {
                ss << "<tr class=weekssum >";
                ss << "<td colspan=2 align=right><u><b>Week's Summary:</b></u></td>";
                ss << "<td><u><b>" << std::setw(2) << std::setfill('0') << week_summary / 60 << ":" << std::setw(2) << week_summary % 60 << "</b></u></td>";
                ss << "</tr>";
                week_summary = 0;
            }
            prevWeek = week;
            week_summary += (int)minutes;

            summary += (int)minutes;
            ss << "<tr class=" << (odd ? "odd" : "") << ">";
            ss << "<td>" << buffmin << "</td>";
            ss << "<td>" << buffmax << "</td>";
            ss << "<td>" << std::setw(2) << std::setfill('0') << minutes / 60 << ":" << std::setw(2) << minutes % 60 << "</td>";
            
            ss << "</tr>";

        }
        ss << "</table>";
        ss << "</center>";
        ss << "</body>";
    }

    void onProcessingThread(const ak::notification_args & args)
    {
        using namespace ak::system;
        
        ak::types::point<int> pt1;
        while (!stopped)
        {
            ak::types::point<int> pt2 = ak::system::user_io::cursor_position();
            if (pt1 != pt2)
            {
                pt1 = pt2;

                time_t t = time(0);

                if (!ranges.empty())
                {
                    time_t delta = t - ranges[ranges.size() - 1].get_max_value();
                    if (delta >= settings.get<int>("gluetime"))
                    {
                        busy_secs = 0;
                    }
                    else
                    {
                        busy_secs += delta;
                    }
                }

                ranges.push_back(ak::types::range<time_t>(t, t));
                ranges.pack(settings.get<int>("gluetime"));
                save(path + "data1.txt");
                save(path + "data2.txt");

                range<time_t> tt(t / 86400 * 86400, t);
                time_t diff = 0;
                for (int i = 0, n = ranges.size(); i < n; i++ )
                {
                    range<time_t> ttt = ranges[i].common_with(tt);
                    if (!ttt.is_empty())
                    {
                        diff += ttt.get_max_value() - ttt.get_min_value();
                    }
                }
                
                animation = diff > settings.get<int>("endtime") || busy_secs > settings.get<int>("breaktime");
            }
            
            

            for (int sec = 0; !stopped && sec < 20; sec++)
            {
                thread::sleep(0.5f);
                if (animation)
                {
                    animate_icon();
                }
            }
        }
    }

    void animate_icon()
    {
        ni.set_icon(ico2);
        ni.refresh();
        ak::system::thread::sleep(0.5f);
        ni.set_icon(ico1);
        ni.refresh();
    }

    void load(const std::string & filename)
    {
        std::ifstream file(filename.c_str());
        if (!file)
            return;
        while(true)
        {
            if (file.eof())
                break;
            std::string line;
            std::getline(file, line);

            std::stringstream ss;
            ss.str(line);
            time_t t1 = 0;
            time_t t2 = 0;
            ss >> t1 >> t2;

            if (t1 != 0 && t2 != 0)
                ranges.push_back(ak::types::range<time_t>(t1, t2));
        }
    }

    void save(const std::string & filename)
    {
        std::ofstream file(filename.c_str());
        for (int i = 0, n = ranges.size(); i < n; i++)
        {
            file << ranges[i].get_min_value() << " " << ranges[i].get_max_value() << std::endl;
        }
    }

    std::string title()
    {
        return ak::string::format("My Day 2 | %%:%%") % server.get_host() % server.get_port();
    }

    ak::ui::notify_icon ni;

} app;

void main()
{
    //ak_tests::test1();
    //std::string st;
    //comma(), "1", "2", "3";

    using namespace ak;
    using namespace ak::ui;
    using namespace ak::system;

    app.run();


}


