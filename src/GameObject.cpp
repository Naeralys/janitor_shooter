//
//  GameObject.cpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject( const char* fileName, SDL_Renderer* renderer, int xPos, int yPos, int width, int height ) {
    this->renderer = renderer;
    texture = TextureManager::LoadTexture( fileName );
    this->x = xPos;
    this->y = yPos;
    this->w = width;
    this->h = height;
    src.x = 0;
    src.y = 0;
    src.h = height;
    src.w = width;
    dest.h = src.h;
    dest.w = src.w;
    dest.x = xPos;
    dest.y = yPos;
}

void GameObject::Update() {
    dest.x = x;
    dest.y = y;
    x += velX;
    y += velY;
}
void GameObject::Render() {
    SDL_RenderCopy( Game::renderer, texture, &src, &dest );
}
