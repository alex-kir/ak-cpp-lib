
//#include "stdafx.h"
#include <ak/ak.h>
#include <iomanip>
#include <fstream>


void ak_main()
{
	using namespace ak::ui;

	while (true)
	{
		ak::system::thread::sleep(0.1f);

		// auto upgrade = "TUpgradeForm"
		auto all = topwindow::all();
		auto upgrade = std::find_if(all.begin(), all.end(), [](const window & w)->bool { return w.wnd_class_name()=="TUpgradeForm"; } );
		if (upgrade != all.end())
		{
			// (*upgrade).position(10, 10);
			// upgrade->position(10, 10);
			upgrade->close();
		}

		auto skype = topwindow::foreground();
		if (skype.wnd_class_name() == "tSkMainForm" && ak::string::start_with(skype.get_text(), "Skype"))
		{
			auto cc = skype.children();
			auto skypeTopWindowRect = skype.rectangle(false);
			for (auto w: cc)
			{
				auto cn = w.wnd_class_name();
				//ak::console() << cn << "\n";

				if (cn == "TConversationForm")
				{
					auto rt = w.rectangle(false);
					// w.rectangle(rt.left(), 0, rt.width(), rt.height() + rt.top());
					w.rectangle(rt.left(), 0, skypeTopWindowRect.width() - rt.left(), rt.height() + rt.top());
					//ak::console() << rt.left() << ", " << rt.top() << ", " << rt.right() << ", " << rt.bottom() << "\n";
				}
			}
		}

#ifdef dkjfhaskldjhfalskdjfh

		if (skype.wnd_class_name() == "TConversationForm")
		{
			auto children = skype.children();
			std::cout << "conversation form found, size:" << children.size() << std::endl;

			std::sort(children.begin(), children.end(), [](const window & w1, const window & w2) -> bool {
				return w1.rectangle(false).top() < w2.rectangle(false).top();
			});

			auto banner = std::find_if(children.begin(), children.end(), [](const window & child) -> bool { return child.wnd_class_name() == "TChatBanner"; });
			if (banner == children.end())
				continue;
			
			std::cout << "banner found" << std::endl;

			auto chatContent = std::find_if(banner, children.end(), [](const window & child) -> bool { return child.wnd_class_name() == "TChatContentControl"; });
			if (chatContent == children.end())
				continue;

			std::cout << "chat content found" << std::endl;

			auto bannerRect = banner->rectangle(false);
			int bottomLine = 0;
			for (auto it = banner; it != chatContent; it++)
			{
				auto rt = it->rectangle(false);

				std::cout << it->wnd_class_name() << "; left:" << rt.left() << "; top:" << rt.top() << std::endl;

				// it->rectangle(rt.left(), rt.top() - bannerRect.height(), rt.width(), rt.height());
				it->rectangle(rt.left(), bottomLine - rt.height(), rt.width(), rt.height());
				bottomLine += rt.height();
			}

			{
				auto rt = chatContent->rectangle(false);
				chatContent->rectangle(rt.left(), bottomLine, rt.left(), rt.height() + bottomLine - rt.top());
			}			
		}

#endif

	}

}