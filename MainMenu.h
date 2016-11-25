#pragma once

#include <iostream>
#include <string>
using namespace std;
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <vector>
#include <unistd.h>

class MainMenu
{
  public:
   
   MainMenu(){};


//******************************************************************************
/// \brief menufunc is the general handler for implementing the functionality
/// of this menu class
/// \param[in] opt a reference for the program to decide where it must go in
/// the main
/// param[in] status is a class to enable manipulation of the current game
/// and players between classes
//***************************************************************************
   std::string menufunc(string &opt);
        

  private:

//*****************************************************************************
/// changed the color of the text being outputed
//
/// param[in] color is the color that you want the text to be.
/// param[in] type is the type of text you want (ex. bold, slash)
//*****************************************************************************
void Cprint(string color = "green", string type = "default");   


//***************************************************************************
/// \brief EnterName is the function that draws the screen for user input
//***************************************************************************
   string EnterName();

};

