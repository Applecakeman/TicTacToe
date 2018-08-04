#include "block.h"
#include "utilities.h"

Block::Block(int posX, int posY, SDL_Renderer* renderer){
    mRect = {posX, posY, WIDTH, HEIGHT};

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &mRect);

    _isEmpty = true;
}

void Block::mark(int shape,SDL_Renderer* renderer,SDL_Texture* texture){
    if (getIsEmpty()){
      if (shape == X) {
        SDL_RenderCopy(renderer, texture, nullptr, &mRect);
        _isEmpty = false;
      }
      else if (shape == O) {
        SDL_RenderCopy(renderer, texture, nullptr, &mRect);
        _isEmpty = false;
      }
    }
    return;
}
