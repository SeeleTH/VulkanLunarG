#pragma once
#include "wfmacro.h"

#include <string>
#include <iostream>
#include <fstream>

#if defined(OS_WIN32)
#include <Windows.h>
#endif


namespace wfOS
{
#if defined(OS_WIN32)
	typedef HMODULE LibraryHandle;
#endif


	struct WindowContext
	{
#if defined(OS_WIN32)
		HINSTANCE Instance;
		HWND Handle;
		WindowContext()
			: Instance()
			, Handle()
		{}
#endif
	};

	typedef std::ofstream ofstr;
	typedef std::ifstream ifstr;

	std::string BrowseOpenFile(const char* filter = "");
	std::string BrowseSaveFile(const char* filter = "", const char* ext = "");

	enum MSGBOX_TYPE
	{
		MSGBOX_OK = 0x00000000L,
		MSGBOX_OKCANCEL = 0x00000001L,
		MSGBOX_ABORTRETRYIGNORE = 0x00000002L,
		MSGBOX_YESNOCANCEL = 0x00000003L,
		MSGBOX_YESNO = 0x00000004L,
		MSGBOX_RETRYCANCEL = 0x00000005L
	};

	//NPOSHelper::CreateMessageBox(BrowseOpenFile("All\0*.*\0Text\0*.TXT\0").c_str(), "", MSGBOX_OK);
	int CreateMessageBox(const char* text, const char* title, const unsigned int type);

	std::string GetRelPathFromFull(const std::string& mainPath, const std::string& convPath);
	std::string GetOSCurrentDirectory();
	void SetOSCurrentDirectory(std::string &dir);

	float GetOSTimeInSec();
	long GetOSTimeInMSec();
}