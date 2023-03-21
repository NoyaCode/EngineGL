#include "Debug.h"
#include <cstdarg>
#include <string> 

using namespace Core::Debug;

void Log::OpenFile(std::filesystem::path const& filename)
{
	if (logFile)
		logFile.close();

	logFile.open(filename);
	
}

Log::~Log()
{
	logFile.close();
}

std::string Log::Print(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	std::string res;

	for (int i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{

			case 'd':
			{
				int d = va_arg(args, int);
				res += std::to_string(d);
				i++;
				break;
			}

			case 'i':
			{
				int d = va_arg(args, int);
				res += std::to_string(d);
				i++;
				break;
			}

			case 'c':
			{
				char c = va_arg(args, char);
				res += std::to_string(c);
				i++;
				break;
			}

			case 'f':
			{
				double f = va_arg(args, double);
				res += std::to_string(f);
				i++;
				break;
			}

			case 's':
			{
				const char* s = va_arg(args, const char*);
				res += s;
				i++;
				break;
			}

			case 'u':
			{
				unsigned int u = va_arg(args, unsigned int);
				res += std::to_string(u);
				i++;
				break;
			}

			default:
			{
				res.push_back('%');
				break;
			}
			}
		}
		else
		{
			res.push_back(format[i]);
		}
	}

	if (logFile)
		logFile << res << "\n";

	std::cout << res << "\n";

	return res;
}

