#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Block
{
    public:
        //constructor and deconstructor
        Block(int posX, int posY, SDL_Renderer* renderer);

        //constants
        static const int WIDTH = 80;
        static const int HEIGHT = 80;

        //methods
        bool isClicked();
        bool getIsEmpty(){return this->_isEmpty;};
        SDL_Rect getRect(){return this->mRect;};
        void mark(int shape, SDL_Renderer* renderer, SDL_Texture* texture);

    private:
        //enum
        enum eShape { O, X };

        //objects
        SDL_Rect mRect;

        //flags
        bool _isEmpty;
        //methods

};

#endif //BLOCK_H
