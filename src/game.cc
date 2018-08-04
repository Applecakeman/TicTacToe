#include "game.h"
#include "utilities.h"
#include "block.h"


Game::Game()
{
    try{
        //try to inizialise
        _init("Test");
        //blit it to the surface
        mX = f_loadTexture("res/X.png", mRenderer);
        mO = f_loadTexture("res/O.png", mRenderer);
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderClear(mRenderer);
        int count = 0;
        for (size_t j = 0; j < ROWS; j++) {
            for (size_t i = 0; i < COLLUMS; i++) {
                mBlock.push_back(Block(static_cast<int>((Block::WIDTH + OFFSET)
                                        * i + SCREEN_WIDTH/2-((Block::WIDTH + OFFSET) * COLLUMS/2)),
                                      static_cast<int>((Block::HEIGHT + OFFSET)
                                        * j + SCREEN_HEIGHT/2-((Block::HEIGHT + OFFSET) * ROWS/2)),
                                      mRenderer));
                ++count;
            }
        }
        SDL_RenderPresent(mRenderer);
    }
    catch(const char *e){
        std::cout << "ERROR:" << " " << e << '\n';
    }

}

Game::~Game()
{
    //deallocate loaded renderer
    mBlock.clear();
    if (mRenderer != NULL)
        SDL_DestroyRenderer(mRenderer);

    //destroy window
    if (mWindow != NULL) {
        SDL_DestroyWindow(mWindow);
        mWindow = NULL;
    }
    //quit SDL
    SDL_Quit();
}

//public methodes
void Game::run()
{
    bool running = true;
    while (running) {
        if (_input(running))
          _render();
    }
    return;
}

bool Game::_input(bool &running){
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        //end prog
        if (event.type == SDL_QUIT) {
            running = false;
            return true;
        }
        else if (event.type == SDL_KEYDOWN) {
          switch (event.key.keysym.sym) {
              //end prog
              case SDLK_ESCAPE:
                    running = false;
                    return true;
                    break;
                //do some shit
                case SDLK_SPACE:
                    mBlock[0].mark(X,mRenderer, mX);
                    mBlock[1].mark(O,mRenderer, mO);
                    return true;
                    break;
            }
        }
    }
    return false;
}

void Game::_render(){

    SDL_RenderPresent(mRenderer);
    return;
}

//private methods
void Game::_init(std::string name){

        //set pointer null
        mWindow = NULL;
        mSurface = NULL;

        //inizialise SDL with everything
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
            throw("SDL not inizialized!");

            mWindow = SDL_CreateWindow(name.c_str(),
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH,
                                        SCREEN_HEIGHT,
                                        SDL_WINDOW_SHOWN);
            if (mWindow == NULL)
                throw("Create window failed!");

        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            throw(SDL_GetError());
        }

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
        if (mRenderer == NULL)
            throw("Create renderer failed");

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);

        return;
}
