#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class Block;

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
        enum eShape { O, X };

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
        std::vector<Block> mBlock;
        SDL_Texture* mX;
        SDL_Texture* mO;


        //flags

        //methods
        void _init(std::string name);
        void _render();
        bool _input(bool &running);

};

#endif //GAME_H
