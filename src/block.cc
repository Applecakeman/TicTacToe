#include "block.h"

/*************/
/*constructor*/
/*************/

Block::Block(int posX, int posY, SDL_Renderer* renderer)
{
  //set demensions
  mRect = {posX, posY, WIDTH, HEIGHT};
  mPosition.x = posX;
  mPosition.y = posY;
  //render block in color blue
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF); //todo add member variable for color
  SDL_RenderFillRect(renderer, &mRect);
  //load mark textures
  mO.loadFromFile("res/O.png", renderer);
  mX.loadFromFile("res/X.png", renderer);
  //set default value flags
  mMark = NONE;
  mClicked = false;
}

/****************/
/*public methods*/
/****************/

void Block::render(SDL_Renderer *renderer)
{
  //render block in color blue
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF); //todo add member variable for color
  SDL_RenderFillRect(renderer, &mRect);
  //render setted mark
  if (getMark() == X)
    mX.render(mRect, renderer);
  else if (getMark() == O)
    mO.render(mRect, renderer);
}

void Block::mark(int mark,SDL_Renderer* renderer)
{
  if (getClicked() && getMark() == NONE)
  {
    if (mark == X)
    {
      mX.render(mRect, renderer);
      mMark = X;
    }
    else if (mark == O)
    {
      mO.render(mRect, renderer);
      mMark = O;
    }
  }
}

void Block::input(SDL_Event *e)
{
  if (e->type == SDL_MOUSEMOTION ||
      e->type == SDL_MOUSEBUTTONDOWN ||
      e->type == SDL_MOUSEBUTTONUP)
  {
    int x,y;
    SDL_GetMouseState(&x, &y);

    bool inside = true;

    if (x < mPosition.x)
      inside = false;
    else if (x > mPosition.x + WIDTH)
      inside = false;
    else if (y < mPosition.y)
      inside = false;
    else if (y > mPosition.y +HEIGHT)
      inside = false;

    if (inside)
    {
      switch (e->type)
      {
        case SDL_MOUSEBUTTONDOWN:
          if (getMark() == NONE)
            mClicked = true;
          break;

        case SDL_MOUSEMOTION:
          break;
      }
    }
  }
}
