#include <iostream>
#include <iomanip>
#include "MainMenu.h"


std::string MainMenu::menufunc(string &opt)
{
	Cprint("green", "bold");
	unsigned int curs=0, Ssize =0;
	char choice;
	const unsigned int OPT = 4;
	string option[OPT]= {"list Images", "crawl link", "check Image", "exit"};

//save exit resume
	while(true)
	{
		system("clear");
		Cprint("green", "bold");
		cout << endl;
		cout << "|----------------|" << endl;
		cout << "|  Main Menu     |" << endl;
		cout << "|----------------|" << endl;
		for(unsigned int x = 0; x < OPT;x++)
		{
			if (curs == x)
			{
				cout << '|';
				Cprint("red", "bold");
				cout << "{";

				Cprint("blue", "bold");

				cout <<  option[x];
				Ssize = 15 -option[x].size();

				Cprint("red", "bold");

				cout << "}";
				Cprint("green", "bold");
				cout << std::setw(Ssize) << right << '|' << endl;


			}
			else
			{
				Cprint("green", "bold");
				cout << "| ";
				cout << option[x];
				Ssize = 16 -option[x].size();
				cout << std::setw(Ssize) << right << '|' << endl;
			}

		}
		cout << "|----------------|";
		cin>>choice;
		switch(choice)
		{
			case 's':
			{
				if(curs == OPT - 1)
				{
					curs=0;
					break;
				}
				else
				{
					curs++;
					break;
				}
			}
			case 'w':
			{
				if(curs == 0)
				{
					curs=OPT - 1;
					break;
				}
				else
				{
					curs--;
					break;
				}
			}
			case 'd':
			{
				switch(curs)
				{
					case 0:
						return "listImages";
						break;
					case 1:
						return EnterName();
						break;
					case 2:
						return EnterName() + "=";
						break;
					case 3:
						return "exit";
						break;
	   			}
			}
		}
	}
}

void MainMenu::Cprint(string color, string type)
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

string MainMenu::EnterName()
{
	string name;
	while(true)
	{

		system("clear");
	

	    char choice;
		cout << "|------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "|                                                                  Enter URL here                                                          |" << endl;
		cout << "|---------|--------------------------------------------------------------------------------------------------------------------------------|" << endl;
		cout << "|  URL  " ": |";
		Cprint("red", "bold");
		cout << setw(128) << left << name;
		Cprint("green", "bold");
		cout << '|' << endl;
		cout << "|---------|--------------------------------------------------------------------------------------------------------------------------------|" << endl;

		cin >> noskipws >> choice;


		if ((choice > 32 && choice < 126))
		{	
		      name += choice;
		}
	
		else if (choice == '' && name.size() != 0)
		{	   
		   name.erase(name.end() -1);
		}
	
		if(choice == '\n')//check if players presses enter
		{

		  return name;

		}
	}

}

