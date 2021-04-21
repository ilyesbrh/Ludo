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

cell getinsideCell(cell c);
/* clear app */
// to be filled ......
void clean();

/* Start function */
int main(int argv, char **args)
{

  init("chichbich", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 632, 632, false);

  Uint32 StartTime;
  Uint32 ProccessTime;

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
  int flags = 0;
  if (fullScreen)
  {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    std::cout << "SDL initialized successfully" << std::endl;

    window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
    if (window)
      std::cout << "Window created!" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer)
    {
      std::cout << "Renderer created!" << std::endl;
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    isRunning = true;
  }
  else
  {
    isRunning = false;
    std::cout << "Problem happen in INIT!" << std::endl;
  }

  /* Load images */
  /* rectangle images */
  setImage("assets/g.png", &green);
  setImage("assets/b.png", &blue);
  setImage("assets/y.png", &yellow);
  setImage("assets/r.png", &red);
  setImage("assets/w.png", &white);

  /* circle images */
  setImage("assets/g-c.png", &greenCircle);
  setImage("assets/b-c.png", &blueCircle);
  setImage("assets/y-c.png", &yellowCircle);
  setImage("assets/r-c.png", &redCircle);

  /* Dice images */
  setImage("assets/1.png", &diceImages[0]);
  setImage("assets/2.png", &diceImages[1]);
  setImage("assets/3.png", &diceImages[2]);
  setImage("assets/4.png", &diceImages[3]);
  setImage("assets/5.png", &diceImages[4]);
  setImage("assets/6.png", &diceImages[5]);

  /* other images */
  setImage("assets/c.png", &center);

  /* INIT map values */
  initMap();
}

void setImage(char name[], SDL_Texture **var)
{
  SDL_Surface *img_temp;
  img_temp = IMG_Load(name);
  SDL_SetColorKey(img_temp, SDL_TRUE, SDL_MapRGB(img_temp->format, 122, 122, 122));
  *var = SDL_CreateTextureFromSurface(renderer, img_temp);
  SDL_FreeSurface(img_temp);
}

void initMap()
{
  /* init Grid */
  for (int x = 0; x < 15; x++)
  {
    for (int y = 0; y < 15; y++)
    {

      Map[x][y] = newCell(x, y, SIZE, 'w');

      if (x == 7 && y > 0 && y < 14)
      {
        if (y > 7)
        {
          Map[x][y].color = 'b';
        }
        else
        {
          Map[x][y].color = 'g';
        }
      }
      if (y == 7 && x > 0 && x < 14)
      {
        if (x > 7)
        {
          Map[x][y].color = 'y';
        }
        else
        {
          Map[x][y].color = 'r';
        }
      }
      if (x == 8 && y == 1)
      {
        Map[x][y].color = 'g';
      }
      if (x == 6 && y == 13)
      {
        Map[x][y].color = 'b';
      }
      if (x == 1 && y == 6)
      {
        Map[x][y].color = 'r';
      }
      if (x == 13 && y == 8)
      {
        Map[x][y].color = 'y';
      }
    }
  }

  /* init Players */
  player[0] = newPlayer(0, 0, 'r');
  player[1] = newPlayer(9, 0, 'g');
  player[2] = newPlayer(9, 9, 'y');
  player[3] = newPlayer(0, 9, 'b');
  /* init base */
  base = newCell(6, 6, 3 * (SIZE + SPACE) - SPACE, 'c');
  /* init dice */
  setupDice(0, 6);
}

void setupDice(int plyer, int face)
{
  dice.current = plyer;
  dice.dice.color = face;
  dice.dice.rect.h = SIZE - SPACE;
  dice.dice.rect.w = SIZE - SPACE;
  dice.dice.rect.x = 3 * (SIZE + SPACE) - (SIZE / 2) + player[dice.current].base.rect.x;
  dice.dice.rect.y = 3 * (SIZE + SPACE) - (SIZE / 2) + player[dice.current].base.rect.y;
  isDiceRunning = false;
}

Player newPlayer(int x, int y, char color)
{
  Player player;
  player.base = newCell(x, y, 6 * (SIZE + SPACE) - SPACE, color);
  player.color = color;
  for (int i = 0; i < 4; i++)
  {
    player.ball[i].color = color - 32;
    player.ball[i].rect.w = SIZE - 2 * SPACE;
    player.ball[i].rect.h = SIZE - 2 * SPACE;
  }
  player.ball[0].rect.x = player.base.rect.x + SIZE + SPACE + (SIZE / 2) + (SIZE + SPACE) * 0;
  player.ball[0].rect.y = player.base.rect.y + SIZE + SPACE + (SIZE / 2) + (SIZE + SPACE) * 0;

  player.ball[1].rect.x = player.base.rect.x + SIZE + SPACE + (SIZE / 2) + (SIZE + SPACE) * 2;
  player.ball[1].rect.y = player.base.rect.y + SIZE + SPACE + (SIZE / 2) + (SIZE + SPACE) * 0;

  player.ball[2].rect.x = player.base.rect.x + SIZE + SPACE + (SIZE / 2) + (SIZE + SPACE) * 0;
  player.ball[2].rect.y = player.base.rect.y + SIZE + SPACE + (SIZE / 2) + (SIZE + SPACE) * 2;

  player.ball[3].rect.x = player.base.rect.x + SIZE + SPACE + (SIZE / 2) + (SIZE + SPACE) * 2;
  player.ball[3].rect.y = player.base.rect.y + SIZE + SPACE + (SIZE / 2) + (SIZE + SPACE) * 2;

  return player;
}
cell newCell(int x, int y, int s, char color)
{
  cell temp;
  SDL_Rect dstrect;
  dstrect.x = x * (SIZE + SPACE) + OFFSET;
  dstrect.y = y * (SIZE + SPACE) + OFFSET;
  dstrect.h = s;
  dstrect.w = s;

  temp.color = color;
  temp.rect = dstrect;

  return temp;
}

void handleEvent()
{
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type)
  {
  case SDL_QUIT:
    isRunning = false;
    break;

  default:
    break;
  }
}

int count = 100;
void update()
{
  count--;
  if (count == 0)
  {
    count = 100;
    setupDice((dice.current + 1) % 4, ((dice.dice.color + 1) % 7));

    std::cout << "updated" << std::endl;
  }
}

void DrawShape(cell c)
{
  switch (c.color)
  {
  case 'r':
    SDL_RenderCopy(renderer, red, NULL, &c.rect);
    break;
  case 'b':
    SDL_RenderCopy(renderer, blue, NULL, &c.rect);
    /* code */
    break;
  case 'g':
    SDL_RenderCopy(renderer, green, NULL, &c.rect);
    /* code */
    break;
  case 'y':
    SDL_RenderCopy(renderer, yellow, NULL, &c.rect);
    /* code */
    break;
  case 'R':
    SDL_RenderCopy(renderer, redCircle, NULL, &c.rect);
    break;
  case 'B':
    SDL_RenderCopy(renderer, blueCircle, NULL, &c.rect);
    /* code */
    break;
  case 'G':
    SDL_RenderCopy(renderer, greenCircle, NULL, &c.rect);
    /* code */
    break;
  case 'Y':
    SDL_RenderCopy(renderer, yellowCircle, NULL, &c.rect);
    /* code */
    break;
  case 'c':
    SDL_RenderCopy(renderer, center, NULL, &c.rect);
    /* code */
    break;
  case 1:
    SDL_RenderCopy(renderer, diceImages[0], NULL, &c.rect);
    /* code */
    break;
  case 2:
    SDL_RenderCopy(renderer, diceImages[1], NULL, &c.rect);
    /* code */
    break;
  case 3:
    SDL_RenderCopy(renderer, diceImages[2], NULL, &c.rect);
    /* code */
    break;
  case 4:
    SDL_RenderCopy(renderer, diceImages[3], NULL, &c.rect);
    /* code */
    break;
  case 5:
    SDL_RenderCopy(renderer, diceImages[4], NULL, &c.rect);
    /* code */
    break;
  case 6:
    SDL_RenderCopy(renderer, diceImages[5], NULL, &c.rect);
    /* code */
    break;

  default:
    SDL_RenderCopy(renderer, white, NULL, &c.rect);

    break;
  }
}
cell getinsideCell(cell c)
{
  cell tc;

  tc.rect.x = c.rect.x + SIZE + SPACE;
  tc.rect.y = c.rect.y + SIZE + SPACE;
  tc.rect.w = c.rect.w - 2 * (SIZE + SPACE);
  tc.rect.h = c.rect.h - 2 * (SIZE + SPACE);

  tc.color = 'w';
  return tc;
}
void render()
{

  // clear renderer
  SDL_RenderClear(renderer);

  // Draw cells
  for (int x = 0; x < 15; x++)
  {
    for (int y = 0; y < 15; y++)
    {
      DrawShape(Map[x][y]);
    }
  }

  // Draw bases
  for (int i = 0; i < 5; i++)
  {
    // Draw outside
    DrawShape(player[i].base);

    // Draw inside
    cell temp_cell = getinsideCell(player[i].base);
    DrawShape(temp_cell);

    // Draw balls
    for (int j = 0; j < 4; j++)
    {
      DrawShape(player[i].ball[j]);
    }
  }

  // Draw dice
  DrawShape(dice.dice);

  // Draw Center base
  DrawShape(base);

  // present renderer
  SDL_RenderPresent(renderer);
}

void clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game cleaned ! bye bye :p" << std::endl;
}