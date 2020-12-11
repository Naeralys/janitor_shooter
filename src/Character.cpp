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

Character::Character( const char* fileName, SDL_Renderer* renderer, int x, int y ) {
    this->renderer = renderer;
    texture = TextureManager::LoadTexture( fileName );
    this->x = x;
    this->y = y;
    this->velX = 0;
    this->velY = 0;
    src.x = 0;
    src.y = 0;
    src.h = 64;
    src.w = 128;
    dest.h = src.h;
    dest.w = src.w;
    keylock = false;
    animationTimer = 0;
    animationChoice = 0;
    knockback = 1.0;
    vulnerable = true;
    runningLeft = false;
    runningRight = false;
}

void Character::Update() {
    // Idle animation
    x += velX;
    y += velY;
    
    dest.x = x;
    dest.y = y;
        
    if( velX > 0.5 )
        velX -= 0.5;
    if( velX < -0.5 )
        velX += 0.5;
    if( velX > -0.6 && velX < 0.6)
        velX = 0;
    if( keylock )
        locktimer++;
    if( locktimer > locktime ) {
        keylock = false;
        locktimer = 0;
    }
    if( !Vulnerable() ) {
        vulnerableTimer++;
        if( vulnerableTimer > 20 )
            vulnerable = true;
    }
    if( Block() ) {
        blockTimer++;
        if( blockTimer > 10) {
            block = false;
            blockCooldown = 0;
        }
    }
    if( !Block() ) {
        if( blockCooldown <= 60 )
            blockCooldown++;
    }
    if( !Running() ) {
        src.y = 0;
        src.x = 0;
        animationTimer = 0;
    }
    else if( Running() == 1 )
        RunAnimation( 1 );
    else if( Running() == 2 )
        RunAnimation( 2 );
}

void Character::RunAnimation( int direction ) {
    if( direction == 1 ) {
    }
    else if( direction == 2 ) {
        Animation( 1536 );
        src.y = 64;
    }

}
void Character::Animation( int animationLenght ) {
    // Move the index
    switch( animationTimer ) {
        case 0: src.x = 0;
            break;
        case 2: src.x = 128;
            break;
        case 4: src.x = 256;
            break;
        case 6: src.x = 384;
            break;
        case 8: src.x = 512;
            break;
        case 10: src.x = 640;
            break;
        case 12: src.x = 768;
            break;
        case 14: src.x = 896;
            break;
        case 16: src.x = 1024;
            break;
        case 18: src.x = 1152;
            break;
        case 20: src.x = 1280;
            break;
        case 22: src.x = 1408;
            break;
        case 23: animationTimer = 0;
            break;
    }
    animationTimer ++;
}
void Character::Render() {
    SDL_RenderCopy( Game::renderer, texture, &src, &dest );
}
float Character::Knockback() {
    knockback = knockback * 1.1;
    return knockback;
}
void Character::ResetKnockback() {
    knockback = 1.0;
}
void Character::KeyLock( int locktime ) {
    keylock = true;
    this->locktime = locktime;
}
bool Character::CheckKeyLock() {
    return keylock;
}
bool Character::Vulnerable() {
    return vulnerable;
}
void Character::Invulnerable() {
    vulnerable = false;
    vulnerableTimer = 0;
}
bool Character::Block() {
    return block;
}
void Character::Block( bool blockTrigger ) {
    if( blockTrigger && blockCooldown >= BlockCooldown ) {
        block = true;
        blockTimer = 0;
    }
}
int Character::Running() {
    if( runningLeft == true )
        return 1;
    if( runningRight == true )
        return 2;
    return 0;
}
void Character::Running( int direction ) {
    if( direction == 0 ) {
        runningLeft = false;
        runningRight = false;
    }
    if( direction == 1 ) {
        runningLeft = true;
        runningRight = false;
    }
    if( direction == 2 ) {
        runningRight = true;
        runningLeft = false;
    }
}
