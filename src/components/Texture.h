#pragma once
class Texture
{
  public:
    Texture(SDL_Renderer *renderer);
    ~Texture();
    bool loadFromFile(std::string path);
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *gFont);
    bool loadFromRenderedTextShaded(std::string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Color bgColor);
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth();
    int getHeight();

  private:
    SDL_Renderer *gRenderer;
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
};