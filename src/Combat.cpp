//
//  Combat.cpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#include "Combat.hpp"

void Combat::Shoot( GameObject* bullet, int direction ) {
    if( direction == 1 ) {
        bullet->velX = 15;
    }
    if( direction == 2 ) {
        bullet->velX = -15;
    }
}

void Combat::Melee( Character* playerOne, Character* playerTwo, int direction ) {
    if( playerTwo->Vulnerable() ) {
        if( direction == 1 ) {
            if( ( playerTwo->x <= playerOne->x ) && ( playerTwo->x >= playerOne->x - 128 ) && ( playerTwo->y >= playerOne->y - 36 ) && ( playerTwo->y <= playerOne->y + 100 ) ) {
                if( playerTwo->Block() ) {
                    playerOne->velX = 10 * playerOne->Knockback();
                    playerOne->KeyLock( 40 );
                }
                else {
                    playerTwo->velX = -10 * playerTwo->Knockback();
                    playerTwo->KeyLock( 40 );
                }
            }
        }
        if( direction == 2 ) {
            if( ( playerTwo->x >= playerOne->x ) && ( playerTwo->x <= playerOne->x + 128 ) && ( playerTwo->y >= playerOne->y - 36 ) && ( playerTwo->y <= playerOne->y + 100 ) ) {
                if( playerTwo->Block() ) {
                    playerOne->velX = -10 * playerOne->Knockback();
                    playerOne->KeyLock( 40 );
                }
                else {
                    playerTwo->velX = 10 * playerTwo->Knockback();
                    playerTwo->KeyLock( 40 );
                }
            }
        }
    }
}
