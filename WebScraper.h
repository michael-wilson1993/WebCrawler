#pragma once
#include <string>
#include <vector>
#include "curler/include/curl/multi.h"
#include "curler/include/curl/curl.h"
#include <iostream>
#include <set>
#include <fstream>

class WebScraper
{
public:
	//WebScraper(std::string link, int level, std::vector<std::string> &links);
	WebScraper(std::string link, int level, std::set<std::string> &links, std::vector<std::string> &imageNames);
	WebScraper() {};
	//size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s);
	bool init(std::string link, int level);
	bool imageScraper(std::string link, std::vector<std::string> &picName);
	std::vector<std::string> scrape(std::string s, std::vector<std::string> &picName);
	std::vector<std::string> getUrls() {return linkOfLists;};
	void updateLinkFile(std::string link);
	void updateImageFile(std::string link);
	void imageKeyFile(std::string key, std::string link);
	bool downloadToTemp(std::string link);




private:
	CURL *curl;
    CURLcode res;
    std::vector<std::string> linkOfLists;
    std::string s;
};
