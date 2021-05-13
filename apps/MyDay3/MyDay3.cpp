#include "stdafx.h"

#include <thread>

int ak_main(const std::vector<std::string> & args)
{
	
	// for (int i = 0; i < args.size(); ++i) {
	// 	std::stringstream ss;
	// 	ss << i << ". " << args[i] << std::endl;
	// 	ak::ui::messagebox::show(ss.str());
	// }

	while (true)
	{
		// ak::ui::messagebox::show(".");

		std::vector<std::string> files;
		ak::filesystem::files(".\\", "*", files);
		std::cout << "files.size(): " << files.size() << std::endl;

		for (int i = 0; i < files.size(); ++i)
		{
			// std::stringstream ss;
			auto t = ak::filesystem::file_m_time(files[i]);
			std::cout << files[i] << " " << t << std::endl;
			//ak::ui::messagebox::show(ss.str());	
		}

		std::this_thread::sleep_for(std::chrono::minutes(2));
	}

	return 0;
}