// HZ_ReadIniFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileObserver.h"
#include <iostream>


int main()
{
	std::cout << "Started" << std::endl;

	FileObserver fo("inputFile.ini");
	fo.runIsFileModified();

    return 0;
}

