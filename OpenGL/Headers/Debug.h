#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string.h>
#include <windows.h>
#include <debugapi.h>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define DEBUG_LOG(message, ...) OutputDebugStringA(('\n' + std::string(Core::Debug::Log::Print((std::string(__FILENAME__) + " [%i] " + message).c_str(), __LINE__,  __VA_ARGS__)) + "\n\n").c_str());

#ifdef DEBUGMODE
#define Assert(condition) if(condition) __debugbreak();

#else
#define Assert(condition) if(condition){ Core::Debug::logFile.close(); abort(); }

#endif


namespace Core
{
	namespace Debug
	{
		static std::ofstream logFile;
		class Log
		{
		private:
			Log() {};
			

		public:
			~Log();
			static void OpenFile(std::filesystem::path const& filename);
			static std::string Print(const char* format, ...);
		};
	}
}