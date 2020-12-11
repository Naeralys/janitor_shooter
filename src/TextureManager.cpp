//
//  TextureManager.cpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture( const char *fileName ) {
    SDL_Surface* tempSurface = IMG_Load( fileName );
    SDL_Texture* tex = SDL_CreateTextureFromSurface( Game::renderer , tempSurface );
    SDL_FreeSurface( tempSurface );
    
    return tex;
}
void TextureManager::Draw( SDL_Texture* tex, SDL_Rect src, SDL_Rect dest ) {
    SDL_RenderCopy( Game::renderer, tex, &src, &dest );
}
