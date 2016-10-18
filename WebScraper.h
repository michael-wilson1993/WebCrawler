#pragma once
#include <string>
#include <vector>
#include "curler/include/curl/multi.h"
#include "curler/include/curl/curl.h"
#include <iostream>

class WebScraper
{
public:
	WebScraper(std::string link, int level, std::vector<std::string> &links);
	//size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s);
	bool init(std::string link, int level);
	std::vector<std::string> scrape(std::string s);
	std::vector<std::string> getUrls() {return linkOfLists;};




private:
	CURL *curl;
    CURLcode res;
    std::vector<std::string> linkOfLists;
    std::string s;
};
