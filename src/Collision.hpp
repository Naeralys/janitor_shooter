//
//  Collision.hpp
//  Shooter
//
//  Created by Adam Lind on 9/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#ifndef Collision_hpp
#define Collision_hpp

#include "Game.hpp"
#include "GameObject.hpp"
#include "Character.hpp"

class Collision {
    public:
        void Bullet( Character *player, GameObject *bullet );
        void Map( Character *player, GameObject *tile[] );
        bool Object( Character *player, GameObject *rect );
};

#endif /* Collision_hpp */
