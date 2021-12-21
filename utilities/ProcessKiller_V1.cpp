#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
	system("color 2");
	system("cls");

	std::filesystem::path folderPath = std::filesystem::current_path() / "WinHelper";
	std::filesystem::create_directories(folderPath);

	std::filesystem::path configPath = folderPath / "ProcessKiller.cfg";
	if (!std::filesystem::exists(configPath))
	{
		std::ofstream cfg(configPath);
		cfg.close();

		system("color 4");
		system("cls");
		std::cout << ">> Config file created \"WinHelper\\ProcessKiller.cfg\", add processes to kill (1/line).\n\n";
		system("pause");
	}
	else
	{
		std::ifstream cfg(configPath);
		std::string processName;

		while (std::getline(cfg, processName))
		{
			std::string command = "taskkill /f /im ";
			command.append(processName);
			system(command.c_str());
		}

		system("pause");
		cfg.close();
	}

	return 0;
}