#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
  public:
    Texture();

    ~Texture();

    //load images
    bool loadFromFile( std::string path, SDL_Renderer* renderer);

    //deallocate textures
    void free();

    //Render texture at givven pointer
    void render(int x, int y, SDL_Renderer* renderer);

    //get image demensions
    int getWidth(){return this->mWidth;};
    int getHeight(){return this->mHeight;};

  private:
    SDL_Texture* mTexture;

    //image dimensions
    int mWidth;
    int mHeight;
};

#endif //TEXTURE_H
