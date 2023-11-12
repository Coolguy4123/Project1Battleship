  /*
   * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
   * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
   */

  /* 
   * File:   main.cpp
   * Author: Freeman Yiu
   *
   * Created on 19 October 2023, 3:07 pm
   */

//All header files
  #include <cstdlib>
  #include <iostream>
  #include <iomanip>
  #include <cctype>
  #include <list>
  #include <algorithm>
  #include <string>
  #include <set>
  #include <map>
  #include <ctime>
  #include <queue>
  #include "Game.h"
  #include "Functions.h"

  using namespace std;

  /*
   * 
   */

  int main(int argc, char** argv) {
    srand(time(0));

      Game newGame;
      Player p1;
      PC p2;

      newGame.mainMenu();
      p1.placement(newGame);
      p2.randomPlacement(newGame);

    newGame.drawGrid();
    while(!p1.lose()&&!p2.lose()){
      p1.updateGrid(newGame,p2);
      p2.updateGridE(newGame,p1);
      cout<<endl;
      newGame.drawGrid();
    }

    newGame.promptafterLosing(newGame,p1,p2);
      return 0;
  }

