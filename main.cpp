#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "curler/include/curl/multi.h"
#include "curler/include/curl/curl.h"
#include "WebScraper.h"
#include <set>
#include "MainMenu.h"
using namespace std;
#include "imageBoard.h"
 

int main()
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);


    vector<string> picNames;
        std::string hi;


    string url = "http://disney.wikia.com/wiki/The_Disney_Wiki";
    //cout << "please enter Website url\n";
    int depth =3;
    //cin >> url;
    //cout << "\nPlease enter depth:\n";
   // cin >> depth;
    std::set<std::string> v;
    WebScraper Crawler(url, depth, v, picNames);
    //Crawler.imageScraper("http://vignette1.wikia.nocookie.net/disney/images/b/bc/Wiki.png/revision/latest?cb=20150817203131");
    cout << "\n\n Disp \n\n";
    for (std::set<std::string>::iterator i = v.begin(); i != v.end(); i++) 
    	std::cout << *i << "\n";
	
    //for(int x = 0; x < v.size();x++)
       //cout << x << ": " << v[x] << endl;

        imageBoard board;
    board.menufunc(hi, picNames);


    MainMenu menu;

    menu.menufunc(hi);
       
}
