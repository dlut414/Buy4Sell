///class header file for base class Log: handle Log for each class
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <iostream>
#include <string.h>
#define __FILENAME__ (strrchr(__FILE__) ? (strrchr(__FILE__) + 1) : (__FILE__))
#define PRINT(x) std::cout << "In file: " << __FILENAME__ << " @line: " << __LINE__ << #x << "=" << x << std::endl;

class Log{
public:
	explicit Log(){}
	~Log(){}
};