///Users/adam/Development/Shooter/Shooter/GameObject.hpp
//  GameObject.hpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Game.hpp"

class GameObject {
private:
    SDL_Texture *texture;
    SDL_Rect dest, src;
    SDL_Renderer* renderer;
public:
    float w, h, x, y, velX, velY;
    GameObject( const char* fileName, SDL_Renderer* renderer, int xPos, int yPos, int width, int height );
    void Update();
    void Render();
};

#endif /* GameObject_hpp */
