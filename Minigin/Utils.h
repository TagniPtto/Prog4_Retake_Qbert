#include <iostream>


#define LOG(msg)	std::cout <<"[" << __FUNCTION__ << ":" << __LINE__ << "] " << msg
#define LOGLN(msg)	LOG(msg) << std::endl