


#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <string>
using std::string;
#include <iomanip>
#include <iostream>
#include <vector>
#include "MainMenu.h"
using std::vector;

using namespace std;


class imageBoard
{


  public:
  	imageBoard() {}
//******************************************************************************
   /// \brief menufunc is the general handler for implementing the functionality
   /// of this menu class
   /// \param[in] opt a reference for the program to decide where it must go in
   /// the main
   /// param[in] status is a class to enable manipulation of the current game
   /// and players between classes
   //***************************************************************************
  bool menufunc(string &opt, std::vector<std::string> names);
   
  private:

//*****************************************************************************
/// changed the color of the text being outputed
//
/// param[in] color is the color that you want the text to be.
/// param[in] type is the type of text you want (ex. bold, slash)
//*****************************************************************************
void Cprint(string color = "green", string type = "default");



};


#endif