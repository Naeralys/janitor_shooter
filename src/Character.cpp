//
//  Character.cpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#include "Character.hpp"
#include "TextureManager.hpp"

#define BlockCooldown 120

Character::Character(const char *fileName, SDL_Renderer *renderer, int x, int y)
    : GameObject(fileName, renderer, x, y, 256, 128, 255)
{
    keylock = false;
    animationTimer = 0;
    animationChoice = 0;
    knockback = 1.0;
    vulnerable = true;
    runningLeft = false;
    runningRight = false;
}

void Character::Update()
{
    x += velX;
    y += velY;

    dest.x = x;
    dest.y = y;

    if (velX > 0.5 && !CheckKeyLock())
        velX = 0;
    if (velX < -0.5 && !CheckKeyLock())
        velX = 0;
    if (velX > -0.6 && velX < 0.6)
        velX = 0;
    if (keylock)
        locktimer++;
    if (locktimer > locktime)
    {
        keylock = false;
        locktimer = 0;
    }
    if (!Vulnerable())
    {
        vulnerableTimer++;
        if (vulnerableTimer > 20)
            vulnerable = true;
    }
    if (Block())
    {
        blockTimer++;
        if (blockTimer > 10)
        {
            block = false;
            blockCooldown = 0;
        }
    }
    if (!Block())
    {
        if (blockCooldown <= 60)
            blockCooldown++;
    }
    if (!Running())
    {
        src.y = 0;
        src.x = 0;
        animationTimer = 0;
    }
    else if (Running() == 1)
        RunAnimation(1);
    else if (Running() == 2)
        RunAnimation(2);
}

void Character::RunAnimation(int direction)
{
    if (direction == 1)
    {
    }
    else if (direction == 2)
    {
        Animation(1536 * 2);
    }
}
void Character::Animation(int animationLenght)
{
    src.y = 128;

    // Move the index
    switch (animationTimer)
    {
    case 0:
        src.x = 0;
        break;
    case 2:
        src.x = 128 * 2;
        break;
    case 4:
        src.x = 256 * 2;
        break;
    case 6:
        src.x = 384 * 2;
        break;
    case 8:
        src.x = 512 * 2;
        break;
    case 10:
        src.x = 640 * 2;
        break;
    case 12:
        src.x = 768 * 2;
        break;
    case 14:
        src.x = 896 * 2;
        break;
    case 16:
        src.x = 1024 * 2;
        break;
    case 18:
        src.x = 1152 * 2;
        break;
    case 20:
        src.x = 1280 * 2;
        break;
    case 22:
        src.x = 1408 * 2;
        break;
    case 23:
        animationTimer = 0;
        break;
    }
    animationTimer++;
}
float Character::Knockback()
{
    knockback = knockback * 1.1;
    return knockback;
}
void Character::ResetKnockback()
{
    knockback = 1.0;
}
void Character::Reset(int x)
{
    this->x = x;
    this->y = SCREEN_HEIGHT - 250;
    this->velX = 0;
    this->velY = 0;
    this->ResetKnockback();
}
void Character::KeyLock(int locktime)
{
    keylock = true;
    this->locktime = locktime;
}
bool Character::CheckKeyLock()
{
    return keylock;
}
bool Character::Vulnerable()
{
    return vulnerable;
}
void Character::Invulnerable()
{
    vulnerable = false;
    vulnerableTimer = 0;
}
bool Character::Block()
{
    return block;
}
void Character::Block(bool blockTrigger)
{
    if (blockTrigger && blockCooldown >= BlockCooldown)
    {
        block = true;
        blockTimer = 0;
    }
}
int Character::Running()
{
    if (runningLeft == true)
        return 1;
    if (runningRight == true)
        return 2;
    return 0;
}
void Character::Running(int direction)
{
    if (direction == 0)
    {
        runningLeft = false;
        runningRight = false;
    }
    if (direction == 1)
    {
        runningLeft = true;
        runningRight = false;
    }
    if (direction == 2)
    {
        runningRight = true;
        runningLeft = false;
    }
}
