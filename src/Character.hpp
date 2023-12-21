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
#include "GameObject.hpp"

class Character : public GameObject
{
private:
    float knockback;
    bool keylock, vulnerable, block, runningLeft, runningRight;
    int locktimer, locktime, vulnerableTimer, blockTimer, blockCooldown;
    int animationTimer, animationChoice;

public:
    float velX, velY, cooldown;
    Character(const char *fileName, SDL_Renderer *renderer, int x, int y);
    void Update();
    void Animation(int animationLenght);
    void RunAnimation(int direction);
    float Knockback();
    void ResetKnockback();
    void KeyLock(int locktime);

    // Resets character object based on provided x coordinate
    void Reset(int x);

    bool CheckKeyLock();
    bool Vulnerable();
    bool Block();
    void Block(bool blockTrigger);
    void Invulnerable();
    int Running();
    void Running(int direction);
};

#endif /* Character_hpp */
