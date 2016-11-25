
#include "imageBoard.h"
#include "MainMenu.h"
#include "imgLoader.h"



  std::string imageBoard::menufunc(string &opt, std::vector<std::string> names)
{
	
	

	unsigned int curs = 0, loopProtect = 0;
	unsigned int SIZE_LEADER = names.size();



		char choice;	
	if (names.size() > 9)
		SIZE_LEADER = 9;

	while (true)
	{
		system("clear");
		printf("\033[09;32m");
		cout << "|    |                                             |";
		printf("\033[00;32m");
		cout << endl << "| #  |        ";
		printf("\033[01;31m");
		cout <<"Name";
		printf("\033[00;32m");
		cout << "         " ;
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
		cout << "|    |                                             |" << endl;
		printf("\033[00;32m");



		if (curs > 3 && curs < names.size() -4)
		{
			loopProtect = curs - 4;
			SIZE_LEADER = curs + 5;
		}

		for (unsigned int x = loopProtect; x < SIZE_LEADER;x++)
		{

			cout << "|" << std::setw(4) << left <<  x  << "|"; 

			

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
			cout << "|    |                                             |" << endl;
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
			imgLoader img;
			img.displayImage(names[curs]);
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

