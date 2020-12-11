//
//  Character.hpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#ifndef Character_hpp
#define Character_hpp

#include "Game.hpp"

class Character {
private:
    SDL_Texture *texture;
    SDL_Rect src, dest;
    SDL_Renderer *renderer;
    float knockback;
    bool keylock, vulnerable, block, runningLeft, runningRight;
    int locktimer, locktime, vulnerableTimer, blockTimer, blockCooldown;
    int animationTimer, animationChoice;
public:
    float x, y, velX, velY, cooldown;
    Character( const char* fileName, SDL_Renderer *renderer, int x, int y );
    void Update();
    void Render();
    void Animation( int animationLenght );
    void RunAnimation( int direction );
    float Knockback();
    void ResetKnockback();
    void KeyLock( int locktime );
    bool CheckKeyLock();
    bool Vulnerable();
    bool Block();
    void Block( bool blockTrigger );
    void Invulnerable();
    int Running();
    void Running( int direction );
};


#endif /* Character_hpp */
