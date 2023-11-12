#include <iostream>
#include <iomanip>
#include <cctype>
#include "Game.h"
#include "Functions.h"
#include <set>

using namespace std;

//Function that assigns the ship at a random position 
void assign(Game&game, int shipSize,char shipChar){
  int rnum=rand()%2;
  if(rnum==1){//vertical, column can be 0-9, row can be 0-(10-shipSize)
    int rRow=rand()%(10-shipSize);
    int rCol=rand()%10;
    bool collisionVert=collidesVert(game,rRow,rCol,shipSize);
    //Will regenerate a new Row and Column if there is collision in vertical direction
    while(collisionVert){
      rRow=rand()%(10-shipSize);
      rCol=rand()%10;
      collisionVert=collidesVert(game,rRow,rCol,shipSize);
    }
    //Will assign ship on grid based on its size
    for(int i=rRow;i<rRow+shipSize;i++){
      game.setPos(i,rCol,shipChar);
    }
  }
  else {//Horizontal, row can be 0-9, column can be 0-(10-shipSize)
    int rCol=rand()%(10-shipSize);
    int rRow=rand()%10;
    bool collisionHorz=collidesHorz(game,rCol,rRow,shipSize);
    //Will regenerate a new Row and Column if there is a collision in the horizontal direction
    while(collisionHorz){
      rCol=rand()%(10-shipSize);
      rRow=rand()%10;
      collisionHorz=collidesHorz(game,rCol,rRow,shipSize);
    }
    //Will assign ship on the grid based on its size
    for(int i=rCol;i<rCol+shipSize;i++){
      game.setPos(rRow,i,shipChar);
    }
  }
}

//return the letter using the Game's class getLetter function
char getletter(char* letterAry,int indx){
  return letterAry[indx];
}

//Function that determines if there is a collision in the vertical direction
//Col is fixed
bool collidesVert(Game&game,int rRow,int rCol,int shipSize){
  bool vert=false;
  for(int i=rRow;i<rRow+shipSize;i++){
    if(game.getPos(i,rCol)!='.'){
      vert=true;
      break;
    }
  }
    return vert;
}

//Function to determine if the player hits a point of an enemy ship
//Enemy's ships are in lower cases
bool pdetermineHit(Game&game,int ver,int horz){
if(game.getPos(ver,horz)=='c'||game.getPos(ver,horz)=='b'||game.getPos(ver,horz)=='s'||game.getPos(ver,horz)=='d'){
    return true;
  }
  return false;
}

//Function to determine if the enemy hits a point of a player's ship
//Players ship are in upper cases
bool edetermineHit(Game&game,int ver, int horz){
    if(game.getPos(ver,horz)=='C'||game.getPos(ver,horz)=='B'||game.getPos(ver,horz)=='S'||game.getPos(ver,horz)=='D'){
    return true;
  }
  return false;
}

//Function for determining weather the player's given position is a valid position
//Returns false if the position is '.'
bool pdetermineError(Game& game,int ver,int horz,set<char> const &s){
  char c=game.getPos(ver,horz);
  if(s.find(c)!=s.end()){
    return true;
  }
  return false;
}

//Function for determining weather the enemy's given position is a valid position
//Returns false if the position is '.'
bool edetermineError(Game& game,int ver,int horz,set<char> const &s){
  char c=game.getPos(ver,horz);
  if(s.find(c)!=s.end()){
    return true;
  }
  return false;
}

//Function to see if any given positions are out of bounds
//Will check if the vertical axis(letter) and horizontal axis(number) are valid positions
bool pOOB(int ver,int horz){
  if(ver==-1||horz>10||horz<1){
    return true;
  }
  return false;
}

//Function to see if there are any collisions in the horizontal direction
//row is a fixed quantity
bool collidesHorz(Game&game,int rCol,int rRow,int shipSize){
  bool horz=false;
  for(int i=rCol;i<rCol+shipSize;i++){
    if(game.getPos(rRow,i)!='.'){
      horz=true;
      break;
    }
  }
    return horz;
}

//Function for returning a value based on the vertical axis(a letter)
//Will return -1 if the character is not found in the cases
int chartoInt(char c){
  switch(c){
    case 'A':
    return 0;
    break;
    case 'B':
    return 1;
    break;
    case 'C':
    return 2;
    break;
    case 'D':
    return 3;
    break;
    case 'E':
    return 4;
    break;
    case 'F':
    return 5;
    break;
    case 'G':
    return 6;
    break;
    case 'H':
    return 7;
    break;
    case 'I':
    return 8;
    break;
    case 'J':
    return 9;
    break;

    default:
    return -1;
    break;
  }
}