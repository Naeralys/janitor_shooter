//
//  Collision.cpp
//  Shooter
//
//  Created by Adam Lind on 9/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#include "Collision.hpp"

void Collision::Bullet(Character *player, GameObject *bullet)
{
    if (player->Vulnerable())
    {
        if ((bullet->x >= player->x) && (bullet->x <= player->x + 64) && (bullet->y >= player->y) && (bullet->y <= player->y + 64))
        {
            if (bullet->velX > 0)
            {
                player->velX = 5 * player->Knockback();
                player->KeyLock(20);
            }
            if (bullet->velX < 0)
            {
                player->velX = -5 * player->Knockback();
                player->KeyLock(20);
            }
        }
    }
}

void Collision::Map(Character *player, GameObject *tile[])
{
    if (!Object(player, tile[0]) && !Object(player, tile[1]) && !Object(player, tile[2]))
    {
        if (player->y > SCREEN_HEIGHT - 180)
        {
            player->y = SCREEN_HEIGHT - 180;
            player->velY = 0;
        }
        if (player->y < SCREEN_HEIGHT - 180)
        {
            if (player->velY < 20)
                player->velY += 0.8;
        }
    }
}
bool Collision::Object(Character *player, GameObject *rect)
{
    if (
        ((player->x + 128) >= rect->x) &&
        ((player->x + 90) <= (rect->x + rect->w)) &&
        (player->y + 128 >= rect->y) &&
        (player->y + 128 <= rect->y + 20) &&
        player->velY > 0)
    {
        player->velY = 0;
        player->y = rect->y - 128;
        return true;
    }
    return false;
}
