/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this
 * template
 */

/*
 * File:   Game.h
 * Author: Freeman Yiu
 *
 * Created on 19 October 2023, 3:08 pm
 */
// Header files
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <string>
#ifndef GAME_H
#define GAME_H
using namespace std;

// Declare class PC and Player Here
// Since some Game member function require both classes, declare here to solve
// the problem
class PC;
class Player;

// Class Game with its members and members function
class Game {
protected:
  char **arr;
  list<int> horzRow;
  queue<string> log;
  stack<int> numMoves;

public:
  Game();
  void mainMenu();
  void prompt();
  void drawGrid();
  void setGrid();
  void setPos(int, int, char);
  void insertLog(string);
  void printLogs();
  void pushStack();
  void promptafterLosing(Game &, Player, PC);
  char getPos(int, int);
  char getLetter(int);
  friend class Player;
  friend class PC;
};

// Second class named Player
// This class is based on the user
class Player {
private:
  map<char, int> ships;
  //set<char> forbiddenChars;

public:
  Player();
  bool lose();
  bool determineHit(Game &, int, int);
  void placement(Game &);
  void updateGrid(Game &, PC &);
  void deductHealth(char);
  void printDestroyedShip();
  bool collides(Game &, int, int, int);
  friend class Game;
  friend class PC;
};

// Third class named PC
// This class refers to the enemy
// It will choose points randomly without colliding
class PC {
private:
  map<char, int> eships;
public:
  PC();
  bool lose();
  void randomPlacement(Game &);
  void updateGridE(Game &, Player &);
  void edeductHealth(char);
  void eprintDestroyedShip();
  bool hitTarget(Game &);
  friend class Game;
  friend class Player;
};

#endif /* GAME_H */
