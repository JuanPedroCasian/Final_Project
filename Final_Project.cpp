/*
Final_Project.cpp
Nov 3, 2017
Juan Casian
*/
#include <cstdlib>
#include <ncurses.h>

bool GameOver;
const int width = 20, height = 20;
int x, y, FruitX, FruitY, Score;

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};                                                      /* enum is a way to enumerate certain variables
                                                        within another variable, like in a struct.
                                                        Ex: enum Seasons = {Spring, Summer, Autumn, Winter};
                                                        Inside Seasons the values are Spring = 0 , Summer = 1
                                                        and so on.
                                                        Later you use it like a new type of variable.
                                                        Season CurrentSeason;
                                                        CurrentSeason = Summer;
                                                        cout << CurrentSeason ;

                                                        Result: 1

                                                        */

eDirection dir; //You ar creating the direction variable;

int TailX[100], TailY[100];
int nTail = 0;

void Setup (){

  initscr();  //Used to initialize the ncurses data structure, in other words the window
  clear();  //Clears everything in the screen
  noecho();
  cbreak();
  curs_set(0);

  GameOver = false; //Initiating all variables for the game
  dir = STOP;       //For it not to move
  x = width/2;      //for the snake to appear at the middle
  y = height/2;
  FruitX = (rand() % width) +1;       //For the fruit location
  FruitY = (rand() % height) +1;
  Score = 0;
}

void Draw(){

  clear();

  for (int i = 0; i < width+2; i++){
    mvprintw(0,i,"+");
  }

  for (int i = 0; i < height+2; i++){

      for (int j = 0; j < width+2; j++){

        if (i == 0 || i == 21){
          mvprintw(i,j,"*");
        } else if (j == 0 || j == 21){
          mvprintw (i,j,"*");
        } else if (i == y && j == x){
          mvprintw(i,j,"O");
        } else if (i == FruitY && j == FruitX){
          mvprintw(i,j,"Q");
        } else {
          for (int k = 0; k < nTail; k++){
            if (TailX[k] == j && TailY[k] == i){
               mvprintw(i,j,"o");
            }
          }
        }
      }
  }

  mvprintw(23,0,"Score %d", Score);

  refresh();

}

void Input (){

  keypad(stdscr, TRUE);
  halfdelay(1);

  int c = getch();

  switch (c){
    case KEY_LEFT:
      dir = LEFT;
      break;
    case KEY_RIGHT:
      dir = RIGHT;
      break;
    case KEY_UP:
      dir = UP;
      break;
    case KEY_DOWN:
      dir = DOWN;
      break;

    case 113: //q of quit is case #113
      GameOver = true;
      break;
  }

}

void Logic(){

  int prevX = TailX[0];
  int prevY = TailY[0];
  int prev2X, prev2Y;

  TailX[0] = x;
  TailY[0] = y;

  for(int i = 0; i <= nTail; i++){
     prev2X = TailX[i];
     prev2Y = TailY[i];

     TailX[i] = prevX;
     TailY[i] = prevY;

     prevX = prev2X;
     prevY = prev2Y;
  }

  switch(dir){
    case LEFT:
      x--;
      break;
    case RIGHT:
      x++;
      break;
    case UP:
      y--;
      break;
    case DOWN:
      y++ ;
      break;
  }

    if (x > width || x < 1 || y < 1 || y > height) {
      GameOver = true;
    }

    if (x == FruitX && y == FruitY){
      Score++;
      FruitX = (rand() % width) +1;       //For the fruit location
      FruitY = (rand() % height) +1;
      nTail++;
    }

    for (int i = 0; i < nTail; i++){
      if (TailX[i] == x && TailY[i] == y){
        GameOver = true;

      }
    }

}

int main (){

  Setup();

  while (!GameOver) {

    Draw();
    Input();
    Logic();

  }

  getch();
  endwin();


  return 0;
}
