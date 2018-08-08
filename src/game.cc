#include "game.h"

/*************/
/*constructor*/
/*************/

Game::Game()
{
    try
    {
      //try to inizialise
      _init("Test");
      mPlayer = O;
      mGameState = RUNNING;
      _initBoard();
    }
    catch(const char *e)
    {
      std::cout << "ERROR:" << " " << e << '\n';
    }

}
/***************/
/*deconstructor*/
/***************/

Game::~Game()
{
  //deallocate blocks
  for (size_t j = 0; j < COLLUMS; j++)
  {
    for (size_t i = 0; i < mBlock.size(); i++)
    {
      delete mBlock[i][j];
      mBlock[i].clear();
    }
  }
  mBlock.clear();

  //deallocate loaded renderer
  if (mRenderer != NULL)
      SDL_DestroyRenderer(mRenderer);

  //destroy window
  if (mWindow != NULL)
  {
      SDL_DestroyWindow(mWindow);
      mWindow = NULL;
  }
  //quit SDL
  SDL_Quit();
}

/******************/
/*public methodes*/
/******************/

void Game::run()
{
  bool quit, restart;

  //game loop
  while (!quit)
  {
    _input(quit, restart);
    //Game running
    if (mGameState == RUNNING)
    {
      _update();
      _render();
      //pause game if game is over
      if (_endCondition())
        mGameState = PAUSED;

      //restart is false in running mode
      restart = false;
    }
    //Game paused
    else if (mGameState == PAUSED && restart)
    {
      _restart();
      restart = false;
    }
  }
}

/******************/
/*private methodes*/
/******************/

void Game::_input(bool &quit, bool &restart)
{
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0)
  {
    //end prog
    if (event.type == SDL_QUIT)
        quit = true;
    else if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
        //end prog
        case SDLK_ESCAPE:
          quit = true;
          break;
        //restart game
        case SDLK_SPACE:
          restart = true;
          break;
      }
    }

    //handle input of blocks
    if (mGameState == RUNNING)
    {
      for (size_t j = 0; j < COLLUMS; j++)
      {
        for (size_t i = 0; i < ROWS; i++)
          mBlock[i][j]->input(&event);
      }
    }
  }
}

void Game::_render()
{
  //set color and clear renderer
  SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(mRenderer);

  for (size_t j = 0; j < COLLUMS; j++)
  {
    for (size_t i = 0; i < ROWS; i++)
    {
      //render all blocks
      mBlock[i][j]->render(mRenderer);
      //mark block if not yet done
      if (mBlock[i][j]->getMark() == Block::NONE)
      {
        if (mPlayer == X)
          mBlock[i][j]->mark(Block::X, mRenderer);
        else if (mPlayer == O)
          mBlock[i][j]->mark(Block::O, mRenderer);
      }
    }
  }
  //update renderer
  SDL_RenderPresent(mRenderer);
}

void Game::_update()
{
  for (size_t j = 0; j < COLLUMS; j++)
  {
    for (size_t i = 0; i < ROWS; i++)
    {
      //change player if block is clicked first time
      if (mBlock[i][j]->getClicked() && mBlock[i][j]->getMark() != Block::NONE)
      {
        _changePlayer();
        mBlock[i][j]->setClicked(false);
      }
    }
  }
}

void Game::_init(std::string name)
{
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

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
      throw(SDL_GetError());

  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
  if (mRenderer == NULL)
      throw("Create renderer failed");

  SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);

  return;
}

void Game::_initBoard()
{
  //blit it to the surface
  SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(mRenderer);
  //add rows
  for (size_t i = 0; i < ROWS; i++)
    mBlock.push_back(std::vector<Block*>());

  //add collums to rows
  for (size_t j = 0; j < COLLUMS; j++)
  {
    for (size_t i = 0; i < mBlock.size(); i++)
    {
      mBlock[i].push_back(new Block(j * (Block::WIDTH + OFFSET)
                                    + SCREEN_WIDTH/2 - ((Block::WIDTH + OFFSET) * COLLUMS)/2,
                                    i * (Block::HEIGHT + OFFSET)
                                    + SCREEN_HEIGHT/2 - ((Block::HEIGHT + OFFSET) * ROWS)/2,
                                    mRenderer));
    }
  }
  SDL_RenderPresent(mRenderer);
}

void Game::_changePlayer()
{
  if (mPlayer == X) {
    mPlayer = O;
  }
  else{
    mPlayer = X;
  }
}

bool Game::_endCondition()
{
  //game ends if 3 of a kind are in a row/collum/diagonal
  if (_checkRows() || _checkCollums() || _checkDiagonals()) {
    return true;
  }
  else {
    //game ends if board is full
    for (size_t j = 0; j < COLLUMS; j++)
    {
      for (size_t i = 0; i < ROWS; i++)
      {
        if(mBlock[i][j]->getMark() == Block::NONE)
          return false;
      }
    }
    return true;
  }

  return false;
}

bool Game::_checkRows()
{
  for (size_t i = 0; i < ROWS; i++)
  {
    if (mBlock[i][0]->getMark() == mBlock[i][1]->getMark() &&
        mBlock[i][1]->getMark() == mBlock[i][2]->getMark() &&
        mBlock[i][0]->getMark() != Block::NONE)
      return true;
  }
  return false;
}

bool Game::_checkCollums()
{
  for (size_t i = 0; i < ROWS; i++)
  {
    if (mBlock[0][i]->getMark() == mBlock[1][i]->getMark() &&
        mBlock[1][i]->getMark() == mBlock[2][i]->getMark() &&
        mBlock[0][i]->getMark() != Block::NONE)
      return true;
  }
  return false;
}

bool Game::_checkDiagonals()
{
  if (mBlock[0][0]->getMark() == mBlock[1][1]->getMark() &&
      mBlock[1][1]->getMark() == mBlock[2][2]->getMark() &&
      mBlock[1][1]->getMark() != Block::NONE)
    return true;
  else if (mBlock[2][0]->getMark() == mBlock[1][1]->getMark() &&
          mBlock[1][1]->getMark() == mBlock[0][2]->getMark() &&
          mBlock[1][1]->getMark() != Block::NONE)
    return true;

  return false;
}

void Game::_restart()
{
  //clear all blocks
  for (size_t j = 0; j < COLLUMS; j++)
  {
    for (size_t i = 0; i < mBlock.size(); i++)
    {
      delete mBlock[i][j];
      mBlock[i].clear();
    }
  }
  mBlock.clear();
  //switch in running mode again
  mGameState = RUNNING;
  mPlayer = O;
  _initBoard();
}
