#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "curler/include/curl/multi.h"
#include "curler/include/curl/curl.h"
#include "WebScraper.h"

using namespace std;


 

int main()
{
    string url = "www.wilsondm.com";
    cout << "please enter Website url\n";
    cin >> url;
std::vector<std::string> v;
    WebScraper Crawler(url, 1, v);
    std::vector<std::string> list = Crawler.getUrls();
    
    for(int x = 0; x < list.size();x++)
      cout << list[x] << endl;




 
 

}
