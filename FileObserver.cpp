#include "stdafx.h"
#include "FileObserver.h"
#include <iostream>
#include <ctime>


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
using boost::property_tree::ptree;
struct stat fileInfo;

FileObserver::FileObserver(std::string m_fname)
{
	this->m_fname = m_fname;
}

FileObserver::~FileObserver()
{
}


void FileObserver::readFromFile() {

	ptree pt;
	read_ini(m_fname, pt);
	for (auto& section : pt)
	{
		std::cout << '[' << section.first << "]\n";
		for (auto& key : section.second)
			std::cout << key.first << "=" << key.second.get_value<std::string>() << "\n";
	}
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
			std::cout << "File's last modified time is " << ctime(&old_modified) << std::endl;
			std::cout << "File's new modified time is  " << ctime(&new_modified) << std::endl;
			old_modified = new_modified;
			readFromFile();
		}
	}
}


