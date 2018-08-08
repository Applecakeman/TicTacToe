#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "texture.h"

class Block
{
    public:
      //constructor and deconstructor
      Block(int posX, int posY, SDL_Renderer* renderer);
      ~Block(){}; //empty at the moment

      //enum
      enum eMark { NONE, O, X };

      //constants
      static const int WIDTH = 80;
      static const int HEIGHT = 80;

      //methods
      void input(SDL_Event* e);
      void render(SDL_Renderer* renderer);
      void mark(int mark, SDL_Renderer* renderer);

      //properties
      bool getClicked(){return mClicked;};
      void setClicked(bool clicked){mClicked = clicked;};
      eMark getMark(){return mMark;};

    private:
      //objects
      SDL_Rect mRect;
      Texture mX;
      Texture mO;

      //flags
      bool mClicked;
      eMark mMark;

      struct stPosition {
        int x;
        int y;
      } mPosition;

      //methods

};
#endif //BLOCK_H
