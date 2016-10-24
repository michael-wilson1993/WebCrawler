#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "curler/include/curl/multi.h"
#include "curler/include/curl/curl.h"
#include "WebScraper.h"
#include <set>
#include "imageScraper.h"
using namespace std;

 

int main()
{
        imageScraper img("http://vignette4.wikia.nocookie.net/disney/images/e/ea/Moana_Disney_wiki_slider.jpg/revision/latest/scale-to-width-down/670?cb=20161008043003");

/*
    string url = "www.wilsondm.com";
    cout << "please enter Website url\n";
    int depth = 1;
    cin >> url;
    cout << "\nPlease enter depth:\n";
    cin >> depth;
    std::set<std::string> v;
    WebScraper Crawler(url, depth, v);

    cout << "\n\n Disp \n\n";
    for (std::set<std::string>::iterator i = v.begin(); i != v.end(); i++) 
    	std::cout << *i << "\n";
	
    //for(int x = 0; x < v.size();x++)
       //cout << x << ": " << v[x] << endl;
       */
}
