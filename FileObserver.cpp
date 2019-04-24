/**
FileObserver.cpp
Purpose: Continuously checking .ini file and if it modified then writes the content to console.
@author Zoltan Herczeg
@date 19/04/19
*/

#include "stdafx.h"
#include "FileObserver.h"
#include <iostream>
#include <string>
#include <ctime>
#include "sys/stat.h"
#include "time.h"
#include <windows.h>
struct stat fileInfo;
#include <sys/types.h>
#include "simpleini-master\SimpleIni.h"    



FileObserver::FileObserver(std::string m_fname)
{
	this->m_fname = m_fname;
}

FileObserver::~FileObserver()
{
}

void FileObserver::readFromFile() {

	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(m_fname.c_str());
	CSimpleIniA::TNamesDepend sections;
	ini.GetAllSections(sections);
    CSimpleIniA::TNamesDepend keys;

	for (CSimpleIniA::Entry n : sections) {
		std::cout <<"[" <<n.pItem << "]"<< '\n';
		ini.GetAllKeys(n.pItem, keys);
		for (CSimpleIniA::Entry m : keys) {
			const char* pVal = ini.GetValue(n.pItem,m.pItem, "");
			std::cout << m.pItem << " = "  << pVal<< '\n';

		}

	}

	std::cout << "-----------------------------------------------------" << std::endl;
}

int FileObserver::hasFileChanged(time_t time1, time_t time2) {
	return difftime(time1, time2) > 0.0 ? 1 : -1;
}

void FileObserver::readFileInfo() {
	stat(m_fname.c_str(), &fileInfo);
}

void FileObserver::runIsFileModified() {
	readFileInfo();
	time_t new_modified = 0;
	time_t old_modified = 0;
	old_modified = fileInfo.st_mtime;
	while (true) {
		readFileInfo();


		new_modified = fileInfo.st_mtime;

		if (hasFileChanged(new_modified, old_modified) == 1)
		{
			std::cout << "File's last modified time is " << ctime(&old_modified);
			std::cout << "File's new modified time is  " << ctime(&new_modified) << std::endl;
			old_modified = new_modified;
			readFromFile();
		}
	}
}
