#include "utilities.h"


SDL_Surface* f_loadBMP(std::string path){
    SDL_Surface* optSurface = NULL;
    SDL_Surface* surface = IMG_Load( path.c_str() );
    if (surface == NULL)
        throw(SDL_GetError());

    optSurface = SDL_ConvertSurface(surface, surface->format, 0);
    if (optSurface == NULL)
        throw(SDL_GetError());

    SDL_FreeSurface(surface);

    return optSurface;
}

SDL_Texture* f_loadTexture(std::string path, SDL_Renderer*& renderer){
    SDL_Surface* optSurface = NULL;
    SDL_Texture* newTexture = NULL;
    SDL_Surface* surface = IMG_Load( path.c_str() );
    if (surface == NULL)
        throw(SDL_GetError());

    optSurface = SDL_ConvertSurface(surface, surface->format, 0);
    if (optSurface == NULL)
        throw(SDL_GetError());

    newTexture = SDL_CreateTextureFromSurface(renderer, optSurface);
    if (newTexture == NULL)
        throw(SDL_GetError());

    SDL_FreeSurface(surface);

    return newTexture;
}
