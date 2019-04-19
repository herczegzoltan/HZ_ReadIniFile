/**
FileObserver.h
Purpose: Continuously checking .ini file and if it modified then writes the content to console.
@author Zoltan Herczeg
@date 19/04/19
*/
#pragma once
#include <ctime>
#include <string>
#include "stdafx.h"

class FileObserver
{
	private:
		std::string m_fname;
	public:
		FileObserver(std::string m_fname);
		~FileObserver();
		void runIsFileModified();
		void readFromFile();
		void readFileInfo();
		int	 hasFileChanged(time_t time1, time_t time2);
};