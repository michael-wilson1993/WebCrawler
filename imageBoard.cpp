
#include "imageBoard.h"
#include "MainMenu.h"
#include "imgLoader.h"
#include "WebScraper.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <iomanip>
#include <fstream>

void logTimes(int time1, int time2)
{
	std::ofstream fout;
  fout.open("logFiles/timeLog.txt", std::ofstream::out | std::ofstream::app);
  fout << "<SearchFromFile: " << setw(4) << left << time1 << "> <searchFromUrl: " << setw(4) << left << time2 << ">" <<  std::endl;
  fout.close();
}

string findLinkFromkey(std::string key )
{
	std::string line, ret;
	bool flag = false;
    std::ifstream fin("logFiles/lookUpTable.txt");
    if(fin.is_open())
    while(!fin.eof())
    {
        getline(fin, line);
        if(line.find(key)!= std::string::npos)
        {
        	for(int x = 0 ;x < line.size(); x++)
        	{
        		if(line[x] == '|')
        			flag = true;
        		else if(flag) // key was found
        		{
        			ret += line[x];
        		}
        	}
        	if(flag)
        		return ret;
        }
        
    }
    return "";
}

  std::string imageBoard::menufunc(string &opt, std::vector<std::string> names)
{
	
	

	unsigned int curs = 0, loopProtect = 0;
	unsigned int size = names.size();



		char choice;	
	if (names.size() > 9)
		size = 9;

	while (true)
	{
		system("clear");
		printf("\033[09;32m");
		cout << "|    |                                                                                                                    |";
		printf("\033[00;32m");
		cout << endl << "| #  |                            ";
		printf("\033[01;31m");
		cout <<"Name ";
		printf("\033[00;32m");
		cout << "                                                           " ;
		printf("\033[0;35m");
		cout << "    " ;
		printf("\033[00;32m");
		cout <<"    " ;
		printf("\033[1;36m");
		cout <<  "     ";
		printf("\033[00;32m");
		cout << "    ";
		printf("\033[0;34m");
		cout << "   ";
		printf("\033[00;32m");
		cout << "    |" << endl;
		printf("\033[09;32m");
		cout << "|    |                                                                                                                    |" << endl;
		printf("\033[00;32m");



		if (curs > 3 && curs < names.size() -4)
		{
			loopProtect = curs - 4;
			size = curs + 5;
		}

		for (unsigned int x = loopProtect; x < size;x++)
		{

			cout << "|" << std::setw(4) << left <<  x  << "|"; 

			

			if (curs == x)
			{
				
				printf("\033[01;33m");
				cout << " " << std::setw(114) << left  << names[x];
				printf("\033[00;32m");

			}
			else
			{

				printf("\033[01;31m");
				cout << " " << std::setw(114) << left  << names[x];
				printf("\033[00;32m");

			}

			cout << '|' << endl;
			printf("\033[09;32m");
			cout << "|    |                                                                                                                    |" << endl;
			printf("\033[00;32m");
		}
		cout << "press esc to go back!" << endl;
		
		cin >> choice;
		if(choice == 27)
		{
			return "";
		}
		if (choice == 'm')
		{
			if(size > 0)
			{
				long mtime1, mtime2;
				{
				imgLoader img;
				struct timeval start, end;
				long  seconds, useconds; 
				gettimeofday(&start, NULL);
				img.displayImage(names[curs]);
				gettimeofday(&end, NULL);
				seconds  = end.tv_sec  - start.tv_sec;
    			useconds = end.tv_usec - start.tv_usec;
    			mtime1 = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    			
				}

				{
								imgLoader img;
				struct timeval start, end;
				long  seconds, useconds; 
				gettimeofday(&start, NULL);
    			std::string link = findLinkFromkey(names[curs]);
    			WebScraper web;
    			web.downloadToTemp(link);
    						gettimeofday(&end, NULL);
				seconds  = end.tv_sec  - start.tv_sec;
    			useconds = end.tv_usec - start.tv_usec;
    			mtime2 = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    			
    			}	
    			logTimes(mtime1, mtime2);


			}
		}

		else if(choice == 's' && curs != names.size() - 1)
		{
			curs++;
		}
		else if(choice == 'w' && curs != 0 )
		{
			curs--;
		}

	}

}

void imageBoard::Cprint(string color, string type)
{
  printf("\033[0m");
  if (color == "default") // clear
    printf("\033[0m");

  if (color == "red") // red 31
    printf("\033[00;31m");

  if (color == "green") // green 32
    printf("\033[00;32m");

  if (color == "blue") // blue 34
    printf("\033[00;34m");

  if (color == "magenta") // magenta 35
    printf("\033[00;35m");

  if (color == "cyan") // cyan 36
    printf("\033[00;36m");

  if (color == "grey") // grey 37
    printf("\033[00;37m");

  if (type == "bold") // bold 1
    printf("\033[1m");

  if (type == "slash") // slash 9
    printf("\033[9m");
}

