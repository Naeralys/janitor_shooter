//
//  TextureManager.hpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Game.hpp"

class TextureManager {
public:
    static SDL_Texture* LoadTexture( const char* fileName );
    static void Draw( SDL_Texture* tex, SDL_Rect src, SDL_Rect dest );
};

#endif /* TextureManager_hpp */
