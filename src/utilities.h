#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

SDL_Surface* f_loadBMP(std::string path);

SDL_Texture* f_loadTexture(std::string path, SDL_Renderer*& renderer);
