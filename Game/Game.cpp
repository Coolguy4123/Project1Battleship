#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <string>
#include <set>
#include <ctime>
#include <queue>
#include "Game.h"
#include "Functions.h"

using namespace std;

/*Constructor for class Game
  Setting the labels and the contents of the grid*/

  Game::Game(){
      const int ROWS=10,COLS=10;
      arr=new char*[ROWS];
      for(int i=0;i<ROWS;i++){
          arr[i]=new char[COLS];
      }
      for(int i=0;i<10;i++){
          for(int j=0;j<10;j++){
              arr[i][j]='.';
          }
      }
      //Pushing numbers 1-10 into a list and sort it using the stl function
      //The numbers are the names of the columns
      horzRow.push_back(2);
      horzRow.push_back(1);
      horzRow.push_back(7);
      horzRow.push_back(5);
      horzRow.push_back(3);
      horzRow.push_back(9);
      horzRow.push_back(10);
      horzRow.push_back(4);
      horzRow.push_back(6);
      horzRow.push_back(8);
      horzRow.sort();
  }

  //Whenever a new game has started, it will print out the rules of the game
  //Will also ask the player to type in any letter to continue the game
  void Game::mainMenu(){
      char c;
      bool valid;
      cout << setw(45)<<"**********Welcome to Battle Ship**********" << endl;
      cout << "--Rules:" << endl<<endl;
      cout << "(1) You are given 4 ships with individual points"<< endl;
      cout << "\t--Carrier(C): 5 points" << endl;
      cout << "\t--Battleship(B): 4 points" << endl;
      cout << "\t--Submarine(S): 3 points" << endl;
      cout << "\t--Destroyer(D): 2 points" << endl<<endl;
     cout << "(2) Your goal is to guess a point that the enemy's ship hides ie: H 1" <<endl<<endl;
      cout << "(3) If the point contains an enemy ship, the enemy loses a point on their ship. Otherwise, nothing happens"<<endl<<endl;
      cout << "(4) The player and enemy(computer) will take turn guessing points"<<endl<<endl;
      cout << "(5) The player wins if the enemy ships are all destroyed. Or else, the enemy wins" <<endl<<endl<<endl<<endl;
      cout << "* Player's ships are all uppercases"<<endl<<endl;
      cout << "* Recommend to enlarge output screen as big as possible, results will show up on top and the updated grid below that"<<endl;
      cout << "* To input a point, type in the column and the row with a space between, ie: A 5" << endl<<endl;

    //Prompts the user to type in any letters to continue the game
      cout << "Type in any letters to continue: ";
    cin>>c;
    valid=isalpha(c);
    while(!valid){
      cout<<"Please enter any letter to continue the game: ";
      cin>>c;
      valid=isalpha(c);
    }
    cout<<endl<<endl<<endl;
  }

//A member function of class Game
//Purpose is to print the logs of the game(every moves performed by both the player and the enemy) when one party wins
void Game::printLogs(){
    char c;
    int indx;
    queue<string> copyque=log;
    cout<<"There are a total of "<<numMoves.size()<<" moves in this game"<<endl;
    cout<<"Here are the logs of the game: "<<endl<<endl<<endl;
    int i=1;
    while(!log.empty()){
      cout<<'['<<i<<"]: "<<log.front()<<endl;
      log.pop();
      i++;
    }
  cout<<endl<<endl;
  cout<<"Do you want to look at a specific move?(Y/N): ";
  cin>>c;
  while(cin.fail()||c!='Y'&&c!='N'){
    cout<<"Please enter the correct choice: ";
    cin>>c;
    cout<<endl;
  }
  cout<<endl<<endl;
  if(c=='Y'||c=='y'){
    cout<<"Enter the index of the move you want to see: ";
    cin>>indx;
    while(indx>copyque.size()||cin.fail()){
      cout<<"The provided indx does not exist or invalid, please re-enter: ";
      cin>>indx;
    }
    for(int j=0;j<indx-1;j++){
      copyque.pop();
    }
    cout<<endl<<"The move at index "<<indx<<" is: "<<copyque.front()<<endl;
  }
}

//A member function of class Game
/*Purpose is to print the grid of the game
 Prints all characters of the grid except the enemy ships*/
void Game::drawGrid(){
    char verticalChar[10]={'B','C','J','I','H','A','D','F','E','G'};
    sort(verticalChar,verticalChar+10);
    cout << "    ";
    for(auto i:horzRow){
      cout << i << "  ";
    }
    cout << endl;
      for(int i=0;i<10;i++){
          //cout << static_cast<char>('A'+i) << " ";
          cout<<verticalChar[i]<<" ";
          for(int j=0;j<10;j++){
            /*Will display characters of enemy's ships as '.'
              Original contents stay the same*/
              if(arr[i][j]=='c'||arr[i][j]=='b'||arr[i][j]=='s'||arr[i][j]=='d'){
                cout << "  " << '.';
              }
            else {
              cout << "  " << arr[i][j];
            }
          }
          cout << endl;
      }
  }

/*A member function of class Game
Displays the winner of the game and prompts the user whether they want to print out the logs of the game or not*/
  void Game::promptafterLosing(Game& game,Player p1,PC p2){
    char c;
    if(p2.lose()){
      cout<<"You have won the game by sinking all the enemy ships!"<<endl<<endl<<endl;
      game.insertLog("Player wins");
      game.pushStack();
    }
    else {
      cout<< "You lost the game"<<endl;
      game.insertLog("Player loses");
      game.pushStack();
    }

    cout<<"Do you want to look at the logs of the game(every moves in the game)(Y/N)? ";
    cin>>c;
    cout<<endl<<endl;
    while(cin.fail()||c!='Y'&&c!='N'){
    cout<<"Please enter the correct choice: ";
    cin>>c;
    cout<<endl;
    }
    if(c=='Y'||c=='y'){
      game.printLogs();
    }
    cout<<endl<<endl;
    cout<<"Thanks for playing"<<endl;
  }

  //Constructor of class Player
  //Initialize the health all player's ships whenever a new game starts
  Player::Player(){
      ships['C'] = 5;
      ships['B'] = 4;
      ships['S'] = 3;
      ships['D'] = 2;
  }

  //Constructor of class PC
  //Initialize the health for all enemy ships whenever a new game starts
  PC::PC(){
    eships['c'] = 5;
    eships['b'] = 4;
    eships['s'] = 3;
    eships['d'] = 2;
    
  }

  //Enemy side will print a statement if a player's ship is fully destroyed
  void Player::printDestroyedShip(){
    cout<<endl<<endl;
    if(ships['C']==0){
      cout<<setw(20)<<"######ALERT######"<<endl<<endl;
      cout<<"***The player's Carrier has been destroyed completely***";
    }
    else if(ships['B']==0){
      cout<<setw(20)<<"######ALERT######"<<endl<<endl;
      cout<<"***The player's Battleship has been destroyed completely***";
    }
    else if(ships['S']==0){
      cout<<setw(20)<<"######ALERT######"<<endl<<endl;
      cout<<"***The player's Submarine has been destroyed completely***";
    }
    else if(ships['D']==0){
      cout<<setw(20)<<"######ALERT######"<<endl<<endl;
      cout<<"***The player's Destroyer has been destroyed completely***";
    }
}

//Players side will print a statement if an enemy ship is fully destroyed
void PC::eprintDestroyedShip(){
  if(eships['c']==0){
    cout<<setw(35)<<"######ALERT######"<<endl;
    cout<<"***The enemy's Carrier has been destroyed completely***";
  }
  else if(eships['b']==0){
    cout<<setw(35)<<"######ALERT######"<<endl;
    cout<<"***The enemy's Battleship has been destroyed completely***";
  }
  else if(eships['s']==0){
    cout<<setw(35)<<"######ALERT######"<<endl;
    cout<<"***The enemy's Submarine has been destroyed completely***";
  }
  else if(eships['d']==0){
    cout<<setw(35)<<"######ALERT######"<<endl;
    cout<<"***The enemy's Destroyer has been destroyed completely***";
  }
}

//Member function of class Player
//Function for player to choose a point and determine if it will hit or miss
//****A VERY CRUCIAL FUNCTION FOR THE PLAYER
void Player::updateGrid(Game&game,PC &enemy){
  //Initialize a set of forbidden characters for the player
  set<char>forbiddenChars;
  forbiddenChars.insert('C');
  forbiddenChars.insert('B');
  forbiddenChars.insert('D');
  forbiddenChars.insert('S');
  forbiddenChars.insert('X');
  forbiddenChars.insert('x');
  forbiddenChars.insert('!');
  forbiddenChars.insert('%');
  //Prompts user to enter a position and turns the vertical position(letter) into a number
  cout<<endl;
  cout << "Please enter a position: ";
  char vert,shipletter;
  int horz, ver;
  bool error, oob;
  string logs;
  char spacing[27];
  fill(spacing,spacing+27,'-'); //Using fill STL to fill '-' 27 times
  cin>>vert>>horz;
  cout<<endl<<endl<<endl<<endl;
  //Error handling
  while(cin.fail()){
    cout<<"Enter a correct format (i.e. A 5): ";
    cin.clear();
    cin>>vert>>horz;
    cout<<endl;
  }
  vert = toupper(vert);
  ver = chartoInt(vert);

  //Process to check if user's input is out of bounds
  oob=pOOB(ver,horz);
  while(oob){
    if(ver==-1&& horz>0 && horz<11){
        cout<< "Please enter a letter between A and J inclusive: ";
    }
    else if(ver!=-1&&(horz < 1 || horz > 10)){
      cout<< "Please enter a number between 1 and 10 inclusive: ";
    }
    else if(ver==-1&&(horz < 1 || horz > 10)){
      cout<< "Position provided is invalid, please type another position: ";
    }
    cin>>vert>>horz;
    //Error handling
    while(cin.fail()){
      cout<<"Enter a correct format (i.e. A 5): ";
      cin.clear();
      cin>>vert>>horz;
      cout<<endl;
    }
    vert=toupper(vert);
    ver=chartoInt(vert);
    oob=pOOB(ver,horz);
    cout<<endl<<endl;;
  }

  //Check if user's inputted position is taken or it's own ship
  error = pdetermineError(game,ver,horz-1,forbiddenChars);
  while(error){
    cout << "Position provided is taken or invalid, please type another position: ";
    cin>>vert>>horz;
    //Error handling
    while(cin.fail()){
      cout<<"Enter a correct format (i.e. A 5): ";
      cin.clear();
      cin>>vert>>horz;
      cout<<endl;
    }
    vert=toupper(vert);
    ver=chartoInt(vert);
    oob=pOOB(ver,horz);

    //Checking user's position to see if it is out of bounds
    while(oob){
      if(ver==-1&& horz>0 && horz<11){
          cout<< "Please enter a letter between A and J inclusive: ";
      }
      else if(ver!=-1&&(horz < 1 || horz > 10)){
        cout<< "Please enter a number between 1 and 10 inclusive: ";
      }
      else if(ver==-1&&(horz < 1 || horz > 10)){
        cout<< "Position provided is invalid, please type another position: ";
      }
      //Error handling  
      while(cin.fail()){
        cout<<"Enter a correct format (i.e. A 5): ";
        cin.clear();
        cin>>vert>>horz;
        cout<<endl;
      }
      vert=toupper(vert);
      ver=chartoInt(vert);
      oob=pOOB(ver,horz);
      cout<<endl<<endl;
    }
    vert = toupper(vert);
    ver = chartoInt(vert);
    error=pdetermineError(game,ver,horz-1,forbiddenChars);
    cout<<endl<<endl;
  }

  //If the user hits a ship, it will set that position to '!'
  //Also, it will deduct health points from the enemy side and add a message to the game logs
  cout<<setw(22)<<"*****Results*****"<<endl;
  if(pdetermineHit(game,ver,horz-1)){
    for(auto i=spacing;i!=spacing+27;i++){
      cout<<*i;
    }
    cout<<endl<<endl<<"--Player's side: "<<endl<<endl;
    logs="";
    logs+="Player hits an enemy ship at point ";
    logs+=vert;
    logs+=to_string(horz);
    shipletter=game.getPos(ver,horz-1);
    game.setPos(ver,horz-1,'!');
    enemy.edeductHealth(shipletter);
    game.insertLog(logs);
    game.pushStack();

    cout<<"You hit a point of an enemy ship!"<<endl<<endl;
    enemy.eprintDestroyedShip();
  }

    //Displays an 'X' if misses a point and adds a "miss" sentence to the game logs
  else{
    for_each(spacing,spacing+27,printBarrier); //Using for_each STL
    cout<<endl<<endl<<"--Player's side: "<<endl<<endl;
    logs="";
    logs+="Player misses at point ";
    logs+=vert;
    logs+=to_string(horz);
    game.setPos(ver,horz-1,'X');
    game.insertLog(logs);
    game.pushStack();
    cout<<"You missed!"<<endl;
  }
  cout<<endl<<endl;
}

//Set the specific location with character c based on the vertical position and horizontal position
void Game::setPos(int x,int y,char c){
  arr[x][y]=c;
}

//Insert a string to the game logs
void Game::insertLog(string s){
  log.push(s);
}

//Push a value to stack every time the player/enemy makes a move
void Game::pushStack(){
  numMoves.push(1);
}

//Return the character of a given position
char Game::getPos(int x,int y){
  return arr[x][y];
}



//Placing every ships onto the grid randomly using the "assign" function(Player's side)
//Players ships are are upper-case letters
void Player::placement(Game& game){
  //Using iterator
  for(auto i=ships.begin();i!=ships.end();i++){
    int shipSize=i->second;
    char shipChar=i->first;
    assign(game,shipSize,shipChar);
  }
}

//If the enemy hits a point, a health is subtracted from the corresponding player's ship
void Player::deductHealth(char c){
  ships[c]--;
}

//If the players hits a point, a health is subtracted from the corresponding enemy's ship
void PC::edeductHealth(char c){
  eships[c]--;
}

//Placing every ships onto the grid randomly using the "assign" function(Enemy's side)
//Players ships are are lower-case letters
void PC::randomPlacement(Game& game){
  for(auto i:eships){
    int shipSize=i.second;
    char shipChar=i.first;
    assign(game,shipSize,shipChar);
  }
}

//Member function of class Player
//Will return true if all player's ships are destroyed
//Loops through the map of ships to see if every ship's value is 0
bool Player::lose(){
  for(auto i:ships){
    if(i.second!=0){
      return false;
    }
  }
  return true;
}

//Function to determine if the enemy(PC) loses
//It will iterate through the enemy's ship map to see if all the values are 0 and returns true if all of them are destroyed
bool PC::lose(){
  for(auto i:eships){
    if(i.second!=0){
      return false;
    }
  }
  return true;
}

//Member function of class PC
//Main function that
//****A VERY CRUCIAL FUNCTION FOR THE ENEMY
void PC::updateGridE(Game&game,Player& p){
  //Initialize an array of letters to compare the enemy's position
  char* letterchoices=new char[10];
  char* copyletters=new char[10];
  for(int i=0;i<10;i++){
    letterchoices[i]=static_cast<char>(i+'A');
  }
  //Initialize forbidden characters for the enemy
  set<char> eforbiddenChars;
  eforbiddenChars.insert('c');
  eforbiddenChars.insert('b');
  eforbiddenChars.insert('d');
  eforbiddenChars.insert('s');
  eforbiddenChars.insert('X');
  eforbiddenChars.insert('x');
  eforbiddenChars.insert('!');
  eforbiddenChars.insert('%');

  copy(letterchoices,letterchoices+10,copyletters);//Copy the original letter array to a new one(STL)
  random_shuffle(copyletters,copyletters+10);//Randomly switch places in the array
  int randomLetIndx=rand()%10;
  char vert=getletter(copyletters,randomLetIndx);
  int ver=chartoInt(vert);
  int horz=rand()%10;
  string logs="";
  char shipletter;
  bool error;

  //Will regenerate a new position if the original position is already occupied or not valid
  error=edetermineError(game,ver,horz,eforbiddenChars);
  while(error){
    random_shuffle(copyletters,copyletters+10);
    randomLetIndx=rand()%10;
    vert=getletter(copyletters,randomLetIndx);
    ver=chartoInt(vert);
    horz=rand()%10;
    error=edetermineError(game,ver,horz,eforbiddenChars);
  }
  cout<<"--Enemy's side:"<<endl<<endl;
  cout<<"The enemy chooses point "<<vert<<horz+1<<endl;

  //If the enemy hits a player's point, it will set the position with %
  //It will add a sentence to the game logs and print out a statement alerting the player
  if(edetermineHit(game,ver,horz)){
       logs="";
       logs+="Enemy hits a point of player's ship at point ";
       logs+=vert;
       logs+=to_string(horz);
       shipletter=game.getPos(ver,horz);
       game.setPos(ver,horz,'%');
       p.deductHealth(shipletter);
       cout<<"The enemy has hit a point of your ship!"<<endl;
       p.printDestroyedShip();
       game.insertLog(logs);
       game.pushStack();
    }

    //If the enemy misses a point, it will set the position with 'x'
    //Will add a statement to the game logs related to the enemy missing a point
  else{
      logs="";
      logs+="The enemy misses at point ";
      logs+=vert;
      logs+=to_string(horz);
      game.setPos(ver,horz,'x');
      game.insertLog(logs);
      cout<<"The enemy misses"<<endl;
      game.pushStack();
    }
  cout<<endl<<endl;
}
