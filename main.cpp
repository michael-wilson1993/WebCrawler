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


void loadImageVector(vector<string> &names);
void loadvisitedLinks(std::set<std::string> &link);

int main()
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);


    vector<string> picNames;
    std::string opt;


    string url = "http://disney.wikia.com/wiki/The_Disney_Wiki";
    //cout << "please enter Website url\n";
    int depth =1;
    //cin >> url;
    //cout << "\nPlease enter depth:\n";
   // cin >> depth;
    std::set<std::string> v;
    loadvisitedLinks(v);
    loadImageVector(picNames);
    
    //Crawler.imageScraper("http://vignette1.wikia.nocookie.net/disney/images/b/bc/Wiki.png/revision/latest?cb=20150817203131");
     // cout << "\n\n Disp \n\n";
     // for (std::set<std::string>::iterator i = v.begin(); i != v.end(); i++) 
     // 	std::cout << *i << "\n";

    //for(int x = 0; x < v.size();x++)
       //cout << x << ": " << v[x] << endl;

    imageBoard board;
    //board.menufunc(opt, picNames);
    MainMenu menu;

    while(true)
    {
        opt = menu.menufunc(opt);
        if(opt == "exit" || opt == "")
            return 0;
        else if(opt == "listImages")
            board.menufunc(opt, picNames);
        else
        {
            WebScraper Crawler(opt, depth, v, picNames);
        }

    }



}

void loadImageVector(vector<string> &names)
{
    string line;
    ifstream fin("savedImages");
    if(fin.is_open())
    while(!fin.eof())
    {
        getline(fin, line);
        names.push_back(line);
    }
}
void loadvisitedLinks(std::set<std::string> &link)
{
    string line;
    ifstream fin("VisitedLinks");
    if(fin.is_open())
    while(!fin.eof())
    {
        getline(fin, line);
        link.insert(line);
    }
}