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
    WebScraper Crawler(url, 3, v);
    
    cout << "\n\n Disp \n\n";
    for(int x = 0; x < v.size();x++)
       cout << x << ": " << v[x] << endl;
}
