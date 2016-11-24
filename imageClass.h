#pragma once

#include <string>
#include <vector>
#include "curler/include/curl/multi.h"
#include "curler/include/curl/curl.h"
#include <iostream>
#include <set>
#include <fstream>
#include <cstring>
#include <unordered_map>

typedef std::unordered_map<std::string,std::string> map;

class imageClass
{
public:
   imageClass();
   void addHashElement(long value);
   
private:
};
