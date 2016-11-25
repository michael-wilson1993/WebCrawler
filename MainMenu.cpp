#include <iostream>
#include <iomanip>
#include "MainMenu.h"


bool MainMenu::menufunc(string &opt)
{
	Cprint("green", "bold");
	unsigned int curs=0, Ssize =0;
	char choice;
	const unsigned int OPT = 4;
	string option[OPT]= {"list Images", "display Image", "crawl link", "check Image"};

//save exit resume
	while(true)
	{
		system("clear");
		Cprint("green", "bold"); 
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
			case 'm':
			{
				switch(curs)
				{

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
	Cprint("green");
	
	vector<string> names;
	
	if(names.size() == 0)
		return "";


	unsigned int curs = 0, loopProtect = 0;
	unsigned int SIZE_LEADER = names.size();

	char choice;	
	if (names.size() > 9)
		SIZE_LEADER = 9;

	while (true)
	{ 	// title
		system("clear");
		printf("\033[09;32m");
		cout << "|    |                                             |" << endl;
		Cprint("green");
		cout << "| #  |          LoadFile Name                      |" << endl;
		Cprint("green", "slash");
		cout << "|    |                                             |" << endl;
		printf("\033[00;32m");

			if (curs > 3 && curs < names.size() -4)
			{
				loopProtect = curs - 4;
				SIZE_LEADER = curs + 5;
			}

		for (unsigned int x = loopProtect; x < SIZE_LEADER;x++)
		{

				cout << "|" << std::setw(4) << left << x << "|"; 



		if (curs == x)
		{
			printf("\033[01;33m");
			cout << " " << std::setw(44) << left  << names[x];
			printf("\033[00;32m");
	
		}
		else
		{

			printf("\033[01;31m");
			cout << " " << std::setw(44) << left  << names[x];
			printf("\033[00;32m");
			
		}

			cout << '|' << endl;
			printf("\033[09;32m");
			cout << "|                                                 |" << endl;
			printf("\033[00;32m");
		}
				cout << "press esc to go back!" << endl;
		
		cin >> choice;
		if (choice == 27)
			return "";
		if(choice == 'm')
		{
			return names[curs];
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

