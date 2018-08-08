#include "texture.h"

/*************/
/*constructor*/
/*************/

Texture::Texture()
{
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

/***************/
/*deconstructor*/
/***************/

Texture::~Texture()
{
  _free();
}

/****************/
/*public methods*/
/****************/

void Texture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
  _free();
  SDL_Texture* newTexture = NULL;

  //load surface
  SDL_Surface* surface = IMG_Load( path.c_str() );
  if (surface == NULL)
    throw(SDL_GetError());

  //color key loaded surface
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

  //create texture from colorkeyed surface
  newTexture = SDL_CreateTextureFromSurface(renderer, surface);
  if (newTexture == NULL)
    throw(SDL_GetError());

  mWidth = surface->w;
  mHeight = surface->h;

  SDL_FreeSurface(surface);

  mTexture = newTexture;
}

void Texture::render(int x, int y, SDL_Renderer* renderer)
{
  SDL_Rect rect = { x, y, mWidth, mHeight};
  SDL_RenderCopy(renderer, mTexture, nullptr, &rect);
}

void Texture::render(int x, int y, int w, int h, SDL_Renderer* renderer)
{
  SDL_Rect rect = { x, y, w, h};
  SDL_RenderCopy(renderer, mTexture, nullptr, &rect);
  mWidth = rect.w;
  mHeight = rect.h;
}

void Texture::render(SDL_Rect rect, SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, mTexture, nullptr, &rect);
  mWidth = rect.w;
  mHeight = rect.h;
}

/****************/
/*private methods*/
/****************/

void Texture::_free()
{
  if(mTexture != NULL)
  {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}
