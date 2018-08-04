#include "texture.h"

Texture::Texture(){
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Texture::~Texture(){
  free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* renderer){
  free();
  SDL_Texture* newTexture = NULL;
  SDL_Surface* surface = IMG_Load( path.c_str() );
  if (surface == NULL)
      throw(SDL_GetError());

  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

  newTexture = SDL_CreateTextureFromSurface(renderer, surface);
  if (newTexture == NULL)
      throw(SDL_GetError());

  mWidth = surface->w;
  mHeight = surface->h;

  SDL_FreeSurface(surface);

  mTexture = newTexture;

  return mTexture != NULL;
}


void Texture::free(){
  if(mTexture != NULL)
  {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}


void Texture::render(int x, int y, SDL_Renderer* renderer){
  SDL_Rect renderQuad = { x, y, mWidth, mHeight};
  SDL_RenderCopy(renderer, mTexture, nullptr, &renderQuad);
}
