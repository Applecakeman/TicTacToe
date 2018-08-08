#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class Texture
{
  public:
    //construct & deconstructor
    Texture();
    ~Texture();

    //methodes
    //load images
    void loadFromFile( std::string path, SDL_Renderer* renderer);

    //Render texture at given position
    void render(int x, int y, SDL_Renderer* renderer);
    //Render texture at given position and with given dimensions
    void render(int x, int y, int w, int h, SDL_Renderer* renderer);
    //Render texture in given rectangle
    void render(SDL_Rect rect, SDL_Renderer* renderer);

    //properties
    //get image demensions
    int getWidth(){return this->mWidth;};
    int getHeight(){return this->mHeight;};
    SDL_Texture* getTexture(){return this->mTexture;};

  private:
    //methodes
    //deallocate textures
    void _free();

    //objects
    SDL_Texture* mTexture;

    //image dimensions
    int mWidth;
    int mHeight;
};

#endif //TEXTURE_H
