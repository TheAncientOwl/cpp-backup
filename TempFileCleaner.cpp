#include <filesystem>
#include <iostream>
#include <fstream>

namespace TempFileCleaner
{
	void clean(const std::filesystem::path& path, bool printMessage = false)
	{
		if (printMessage)
			std::cout << "_______________________________________________________________\n"
					     "[INFO] Cleaning " << path << " . . .\n\n";
			

		std::filesystem::current_path("C:\\");
		for (auto& child : std::filesystem::directory_iterator(path))
		{
			try
			{
				std::filesystem::remove_all(child);
			}
			catch (const std::filesystem::filesystem_error& e)
			{
				if (printMessage)
					std::cout << ">> " << e.what() << '\n';
			}
		}

		if (printMessage)
			std::cout << '\n';
	}
}

int main()
{
	std::filesystem::path winTempPath = "Windows\\Temp\\";
	std::filesystem::path myTempPath = "Users\\THEANC~1\\AppData\\Local\\Temp\\";

	int printMsg = 0;
	int pause = 0;
	{
		std::ifstream config("TempFileCleaner.cfg");
		std::string aux;

		config >> aux >> printMsg;
		config >> aux >> pause;

		config.close();
	}

	TempFileCleaner::clean(winTempPath, printMsg);
	TempFileCleaner::clean(myTempPath, printMsg);

	if (pause)
	{
		std::cout << '\n';
		system("pause");
	}

	return 0;
}