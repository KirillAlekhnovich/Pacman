#include "CObject.h"

using namespace std;

const CTilePos &CObject::getPosition() const {
    return position;
}

void CObject::setPosition(const CTilePos &pos, int tileSize) {
    position = pos;
    obj.x = pos.x;
    obj.y = pos.y;
    obj.w = tileSize;
    obj.h = tileSize;
}

void CObject::setSource(int x, int y, int w, int h) {
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;
}

void CObject::setImage(const string& filename, SDL_Renderer *ren) {
    SDL_Surface *surface;
    surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
        cout << "IMG_Load failure: " << IMG_GetError() << endl;

    texture = SDL_CreateTextureFromSurface(ren, surface);
    if (texture == nullptr)
        cout << "SDL_CreateTextureFromSurface failure : " << SDL_GetError() << endl;
    SDL_FreeSurface(surface);
}

void CObject::draw(SDL_Renderer *renderer) const{
    SDL_RenderCopy(renderer, texture, &src, &obj);
}

void CObject::quit() const{
    SDL_DestroyTexture(texture);
}

int CObject::eat() const {
    return 0;
}