#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include "block.h"


class Game
{
    public:
      //constructor and deconstructor
      Game();
      ~Game();

      //methods
      void run();
      
    private:
      //enum
      enum ePlayer { NONE, O, X };
      enum eGameState {RUNNING, PAUSED};

      //constants
      static const int SCREEN_WIDTH = 500;
      static const int SCREEN_HEIGHT = 400;
      static const int COLLUMS = 3;
      static const int ROWS = 3;
      static const int OFFSET = 10;

      //objects
      SDL_Window* mWindow;
      SDL_Surface* mSurface;
      SDL_Renderer* mRenderer;
      std::vector<std::vector<Block*>> mBlock;

      //flags
      ePlayer mPlayer;
      eGameState mGameState;

      //methods
      void _init(std::string name);
      void _initBoard();
      void _render();
      void _input(bool &quit, bool &restart);
      void _update();
      void _changePlayer();
      bool _endCondition();
      bool _checkRows();
      bool _checkCollums();
      bool _checkDiagonals();
      void _restart();
};

#endif //GAME_H
