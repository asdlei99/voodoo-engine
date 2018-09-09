#include "../stdafx.h"

#include "log.h"


namespace Nixie
{
	Log::Log()
	{
		fs_.open("log.txt");

#ifdef NIXIE_LOG_CONSOLE_ENABLED
		if (AllocConsole())
		{
			freopen("CONOUT$", "w", stdout);
			SetConsoleTitle("Nixie | Debug Console");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		}

		cout_buffer_ = std::cout.rdbuf(&console_buffer_);
		cerr_buffer_ = std::cerr.rdbuf(&console_buffer_);
#endif
	}

	
	Log::~Log()
	{
		fs_.close();

#ifdef NIXIE_LOG_CONSOLE_ENABLED
		std::cout.rdbuf(cout_buffer_);
		std::cout.rdbuf(cerr_buffer_);
#endif
	}


	Log& Log::Get()
	{
		static Log instance;
		return instance;
	}


	void Log::Write(std::string s)
	{
		Get().fs_ << s << std::endl;

#ifdef NIXIE_LOG_CONSOLE_ENABLED
		WriteToConsole(s);
#endif
	}


#ifdef NIXIE_LOG_CONSOLE_ENABLED
	void Log::WriteToConsole(std::string s)
	{
		std::cout << s << std::endl;
	}
#endif
}