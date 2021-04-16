#pragma once
#include <map>
#include <string>

struct ConStruct {
	std::string value;
	std::string syumbol;
};

typedef std::map<std::string, ConStruct> Maptype;