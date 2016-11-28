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
#include "imageBoard.h"
#include "imgLoader.h"
#include <exception>


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

    // url name, initialized just in case
    string url = "http://disney.wikia.com/wiki/The_Disney_Wiki";
    
    // depth that the search will go
    int depth = 5;
    
    std::set<std::string> v;
    loadvisitedLinks(v);
    loadImageVector(picNames);

    // creates a menu that asks for user input
    imageBoard board;
    MainMenu menu;

    // runs while the exit button isn't clicked
    while(true)
    {
        opt = menu.menufunc(opt);
        if(opt == "exit" || opt == "")
            return 0;
        else if(opt == "listImages")
        {
            board.menufunc(opt, picNames);
        }
        else if(opt[opt.size()-1] == '=')
        {
            opt.pop_back();
            WebScraper Crawler;
            Crawler.imageScraper(opt, picNames);
        }
        else
        {
            WebScraper Crawler(opt, depth, v, picNames);
        }
    }
}

void loadImageVector(vector<string> &names)
{
   // reads in images until the end of file
    string line;
    ifstream fin("logFiles/savedImages");
    if(fin.is_open())
    while(!fin.eof())
    {
        getline(fin, line);
        names.push_back(line);
    }
}
void loadvisitedLinks(std::set<std::string> &link)
{
   // reads visited links
    string line;
    ifstream fin("logFiles/VisitedLinks");
    if(fin.is_open())
    while(!fin.eof())
    {
        getline(fin, line);
        link.insert(line);
    }
}
