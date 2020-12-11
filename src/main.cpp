//
//  main.cpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//  

#include <iostream>
#include "Game.hpp"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;

Game *game = nullptr;

int main(int argc, const char * argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    
    Uint32 frameStart;
    int frameTime;
    
    game = new Game();
    
    game->Init( "Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false );
    
    game->Start();
    
    while( game->Running() ) {
        frameStart = SDL_GetTicks();
        
        game->HandleEvents();
        game->Update();
        game->Render();
    
        frameTime = SDL_GetTicks() - frameStart;
        
        if( frameDelay > frameTime ) {
            SDL_Delay( frameDelay - frameTime );
        }
    }
    
    game->Clean();
    
    return 0;
}
