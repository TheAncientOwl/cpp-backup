#include <filesystem>
#include <iostream>
#include <fstream>
#include <ctime>

class TempFileCleaner
{
private:
	struct Config
	{
		bool printMsg = false;
		bool pause = false;
		bool log = true;

		void load(const std::filesystem::path& exePath)
		{
			std::filesystem::current_path(exePath);
			std::filesystem::path configFile = "TempFileCleaner" + TempFileCleaner::VERSION + ".cfg";

			if (std::filesystem::exists(configFile))
			{
				std::ifstream cfg(configFile);

				std::string aux;
				cfg >> aux >> printMsg;
				cfg >> aux >> pause;
				cfg >> aux >> log;

				cfg.close();
			}
			else
			{
				std::ofstream cfg(configFile);

				cfg << "printMessages 1\n";
				cfg << "pause 1\n";
				cfg << "log 1\n";

				printMsg = true;
				pause = true;
				log = true;

				cfg.close();
			}
		}
	};

private:
	class Logger
	{
	private:
		std::filesystem::path m_ExePath;

		uintmax_t m_MemoryKB = 0;
		uint32_t m_RemovedFiles = 0;

	public:
		void load(const std::filesystem::path& exePath)
		{
			m_ExePath = exePath;

			std::filesystem::current_path(exePath);
			std::filesystem::path logFile = "TempFileCleaner" + TempFileCleaner::VERSION + ".logs";

			if (!std::filesystem::exists(logFile))
			{
				std::ofstream logs(logFile);
				logs.close();
			}
		}

		void add(uint32_t removedFiles, uintmax_t sizeKB)
		{
			m_RemovedFiles += removedFiles;
			m_MemoryKB += sizeKB;
		}

		void log()
		{
			time_t now = time(NULL);

			tm now_tm{};
			char str[26]{};
			localtime_s(&now_tm, &now);
			asctime_s(str, 26, &now_tm);

			std::filesystem::current_path(m_ExePath);
			std::filesystem::path logFilePath = "TempFileCleaner" + TempFileCleaner::VERSION + ".logs";
			std::fstream logFile(logFilePath, std::ios::out | std::ios::app);

			logFile << ">> " << str;
			logFile << "Deleted files: " << m_RemovedFiles << "(" << m_MemoryKB << " KB)\n";
			logFile << "____________________________\n";

			logFile.close();
		}
	};

private:
	static const std::string VERSION;

	Config m_Config;
	Logger m_Logger;

public:
	TempFileCleaner()
	{
		auto path = std::filesystem::current_path();
		m_Config.load(path);
		m_Logger.load(path);
	}

private:
	uintmax_t toKb(uintmax_t size)
	{
		static const uintmax_t TO_KB = 1024;
		return (size / TO_KB + (size % TO_KB != 0));
	}

	/// <returns>pair(cleanedSize, itemsNumber)</returns>
	std::pair<uintmax_t, uint32_t> getSize(std::filesystem::path path)
	{
		uintmax_t size = 0;
		uint32_t itemsNumber = 0;
		if (std::filesystem::exists(path))
		{
			if (std::filesystem::is_directory(path))
			{
				std::filesystem::recursive_directory_iterator end;
				for (std::filesystem::recursive_directory_iterator dirIt(path); dirIt != end; ++dirIt)
				{
					const std::filesystem::path& filePath = dirIt->path();
					if (!std::filesystem::is_directory(filePath))
					{
						size += toKb(std::filesystem::file_size(filePath));
						++itemsNumber;
					}
				}
			}
			else
			{
				size = toKb(std::filesystem::file_size(path));
				itemsNumber = 1;
			}
		}

		return std::make_pair(size, itemsNumber);
	}

	void clean(const std::filesystem::path& path)
	{
		if (m_Config.printMsg)
			std::cout << "_______________________________________________________________\n"
						 "[INFO] Cleaning " << path << " . . .\n\n";

		std::filesystem::current_path("C:\\");
		for (auto& child : std::filesystem::directory_iterator(path))
		{
			try
			{
				auto size = getSize(child);
				std::filesystem::remove_all(child);

				m_Logger.add(size.second, size.first);
			}
			catch (const std::filesystem::filesystem_error& e)
			{
				if (m_Config.printMsg)
					std::cout << ">> " << e.what() << '\n';
			}
		}

		if (m_Config.printMsg)
			std::cout << '\n';
	}

public:
	void exec()
	{
		clean("Windows\\Temp\\");
		clean("Users\\THEANC~1\\AppData\\Local\\Temp\\");

		if (m_Config.log)
			m_Logger.log();

		if (m_Config.pause)
			system("pause");
	}

};
const std::string TempFileCleaner::VERSION = "V2";

int main()
{
	TempFileCleaner cleaner;
	cleaner.exec();

	return 0;
}