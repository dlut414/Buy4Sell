///class header file for base class Log: handle Log for each class
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <iostream>
#define PRINT(x) (std::cout << "In file: " << __FILE__ << " @line: " << __LINE__ << #(x) << "=" << x << std::endl;)

class Log(){
public:
	explicit Log(){}
	~Log(){}
};