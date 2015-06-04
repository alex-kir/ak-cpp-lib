
//#include "stdafx.h"
#include <ak/ak.h>
#include <iomanip>
#include <fstream>


void main()
{
	using namespace ak::ui;

	while (true)
	{
		ak::system::thread::sleep(0.1f);
		auto skype = topwindow::foreground();
		if (skype.wnd_class_name() == "tSkMainForm" && ak::string::start_with(skype.get_text(), "Skype"))
		{
			auto cc = skype.children();
			for each (auto w in cc)
			{
				auto cn = w.wnd_class_name();
				//ak::console() << cn << "\n";

				if (cn == "TConversationForm")
				{
					auto rt = w.rectangle(false);
					w.rectangle(rt.left(), 0, rt.width(), rt.height() + rt.top());
					//ak::console() << rt.left() << ", " << rt.top() << ", " << rt.right() << ", " << rt.bottom() << "\n";
				}
			}
		}
	}

}