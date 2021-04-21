#include <iostream>
#include <stdio.h>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

/* PARAMETERS */
int const OFFSET = 2;
int const SPACE = 2;
int const SIZE = 40;
//FPS
int const FPS = 60;
int const FRAMES_DELAY = 1000 / 60;

/* buffred objects */
// window
SDL_Window *window;
SDL_Renderer *renderer;
// rectangles
SDL_Texture *red;
SDL_Texture *green;
SDL_Texture *yellow;
SDL_Texture *blue;
SDL_Texture *white;
// circles
SDL_Texture *redCircle;
SDL_Texture *greenCircle;
SDL_Texture *yellowCircle;
SDL_Texture *blueCircle;
// dices
SDL_Texture *diceImages[6];
// images
SDL_Texture *center;

/* State variables */
bool isRunning;
bool isDiceRunning;

/* environment objects */
//structure
struct cell
{
  SDL_Rect rect;
  char color;
};
struct Player
{
  cell base;
  cell ball[4];
  char color;
};
struct Dice
{
  cell dice;
  int current;
};
// variables
cell Map[15][15];
Player player[5];
cell base;
Dice dice;

string greeting = "Hello";

/************************/
/****** Functions *******/
/************************/

/* init */
// initialize SDL window
// Load images
// initialize state
void init(char title[], int xPos, int yPos, int width, int height, bool fullScreen);

/* set Images */
// Load images from files
void setImage(char name[], SDL_Texture **var);

/* init Map */
// init grid
// init players
// init base
void initMap();

/* Create player */
// create new player
// fill player
// fill player balls
// return player
Player newPlayer(int x, int y, char color);

/* Create cell */
// declare new cell
// fill cell
// return cell
cell newCell(int x, int y, int s, char color);

/* Create dice */
// set current player
// set draw position
void setupDice(int plyer, int face);

/* Handle user input */
// not ready yet ....
void handleEvent();

/* update environment objects and state */
// not ready yet
void update();
/* render environment objects on screen */
// to be filled ......
void render();
/* clear app */
// to be filled ......
void clean();

/* Start function */
int main(int argv, char **args)
{

  init("chichbich", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 632, 632, false);

  Uint32 StartTime;
  Uint32 ProccessTime;

  isRunning = true;

  /* Game loop */
  while (isRunning)
  {
    //get start time in ms
    StartTime = SDL_GetTicks();

    /* Handle user input */
    handleEvent();
    /* update all changed objects eg positions etc.. */
    update();
    /* render changes to display */
    render();

    ProccessTime = SDL_GetTicks() - StartTime;

    if (FRAMES_DELAY > ProccessTime)
    {
      SDL_Delay(FRAMES_DELAY - ProccessTime);
    }
  }

  clean();

  system("pause");
  return 0;
}

void init(char title[], int xPos, int yPos, int width, int height, bool fullScreen)
{
  
}

void handleEvent()
{
  
}

int count = 100;
void update()
{
  
}

void render()
{

}

void clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game cleaned ! bye bye :p" << std::endl;
}