/**
HZ_ReadIniFile.cpp
Purpose: Continuously checking .ini file and if it modified then writes the content to console.
@author Zoltan Herczeg
@date 19/04/19
*/

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

