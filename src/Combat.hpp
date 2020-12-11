//
//  Combat.hpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#ifndef Combat_hpp
#define Combat_hpp

#include "Game.hpp"
#include "GameObject.hpp"
#include "Collision.hpp"

class Combat {
public:
    void Shoot( GameObject* bullet, int direction );
    void Melee( Character* playerOne, Character* playerTwo, int direction );

};

#endif /* Combat_hpp */
