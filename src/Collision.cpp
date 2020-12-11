//
//  Collision.cpp
//  Shooter
//
//  Created by Adam Lind on 9/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#include "Collision.hpp"

void Collision::Bullet( Character *player, GameObject *bullet ) {
    if( player->Vulnerable() ) {
        if( ( bullet->x >= player->x ) && ( bullet->x <= player->x + 32 ) && ( bullet->y >= player->y ) && ( bullet->y <= player->y + 32 ) ) {
            if( bullet->velX > 0 ) {
                player->velX = 5 * player->Knockback();
                player->KeyLock( 20 );
            }
            if( bullet->velX < 0 ) {
                player->velX = -5 * player->Knockback();
                player->KeyLock( 20);
            }
        }
    }
}

void Collision::Map( Character *player, GameObject *tile[] ) {
    if( !Object( player, tile[0] ) && !Object( player, tile[1] ) && !Object( player, tile[2] ) ) {
        if( player->y > SCREEN_HEIGHT - 100 ) {
            player->y = SCREEN_HEIGHT - 100;
            player->velY = 0;
        }
        if( player->y < SCREEN_HEIGHT - 100 ) {
            if( player->velY < 20 )
                player->velY += 0.8;
        }
    }
}
bool Collision::Object( Character *player, GameObject *rect ) {
    if( ( player->x + 64 >= rect->x ) && ( player->x <= ( rect->x + rect->w - 32 ) ) && ( player->y + 64 >= rect->y ) && ( player->y + 64 <= rect->y + 64 ) && player->velY > 0 ) {
        player->velY = 0;
        player->y = rect->y - 64;
        return true;
    }
    return false;
}
