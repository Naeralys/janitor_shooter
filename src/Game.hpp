//
//  Game.hpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Game {
private:
    SDL_Window *window;
    int isRunning;
public:
    void Init( const char *title, int xPos, int yPos, int width, int height, bool fullscreen );
    void HandleEvents();
    void Start();
    void Update();
    void Render();
    void Clean();
    void Reset();
    bool Running() { return isRunning; };
    
    static SDL_Renderer *renderer;
};

#endif /* Game_hpp */
