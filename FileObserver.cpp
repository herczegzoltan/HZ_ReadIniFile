#include "stdafx.h"
#include "FileObserver.h"
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
using boost::property_tree::ptree;

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
