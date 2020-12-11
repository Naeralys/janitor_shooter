//
//  Game.cpp
//  Shooter
//
//  Created by Adam Lind on 5/1/18.
//  Copyright © 2018 Adam Lind. All rights reserved.
//

#include "Game.hpp"
#include "TextureManager.hpp"
#include "Character.hpp"
#include "GameObject.hpp"
#include "Combat.hpp"
#include "Collision.hpp"

Character* playerOne, *playerTwo;
GameObject* bulletOne[10], *bulletTwo[10], *tile[5], *map;
Combat* combat;
Collision* collision;
SDL_GameController* controller[2];

float movementSpeed = 0.0002;
const Uint8 *keyState;
int bulletIndex = 0;

SDL_Renderer* Game::renderer = nullptr;

void Game::Init( const char *title, int xPos, int yPos, int width, int height, bool fullscreen ) {
    // Initialize SDL with everything
    if( SDL_Init( SDL_INIT_EVERYTHING ) == 0 ) {
        // Create a window
        window = SDL_CreateWindow( title, xPos, yPos, width, height, fullscreen );
        if( window ) {
            std::cout << "Window created!" << std::endl;
        }
        else {
            std::cout << "Error creating window..." << std::endl;
        }
        // Create a renderer
        renderer = SDL_CreateRenderer( window, -1, 0 );
        if( renderer ) {
            std::cout << "Renderer created!" << std::endl;
        }
        else {
            std::cout << "Error creating renderer..." << std::endl;
        }
        isRunning = true;
        std::cout << "SDL Initialized successfully!" << std::endl;
    }
    else {
        isRunning = false;
        std::cout << "Error initializing SDL..." << std::endl;
    }
    
    // Initialize game controllers, maximum 2 players
    for( int i = 0; i < 2; i++ ) {
        if( SDL_IsGameController( i ) ) {
            controller[i] = SDL_GameControllerOpen( i );
            if( controller[i] ) {
                std::cout << "Game controller found" << std::endl;
            }
            else {
                std::cout << "Could not open game controller" << std::endl;
            }
        }
    }
    
    // Create game assets
    map = new GameObject( "assets/background.bmp", Game::renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    // Load players
    playerOne = new Character( "assets/player_one.bmp", Game::renderer,  130, SCREEN_HEIGHT - 300 );
    playerTwo = new Character( "assets/player_one.bmp", Game::renderer,  SCREEN_WIDTH - 150, SCREEN_HEIGHT - 300 );
    // Load bullets
    for( int i = 0; i < 10; i++ ) {
        bulletOne[i] = new GameObject( "assets/bullet.bmp", Game::renderer, 0, 0, 5, 5 );
        bulletTwo[i] = new GameObject( "assets/bullet.bmp", Game::renderer, 0, 0, 5, 5 );
    }
    // Load tiles
    tile[0] = new GameObject( "assets/bullet.bmp", Game::renderer, 100, SCREEN_HEIGHT - 250, 100, 10 );
    tile[1] = new GameObject( "assets/bullet.bmp", Game::renderer, (SCREEN_WIDTH/2) - 50, SCREEN_HEIGHT - 300, 100, 10 );
    tile[2] = new GameObject( "assets/bullet.bmp", Game::renderer, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 250, 100, 10 );
}

void Game::Start() {
    int startMenu = 1;
    while( startMenu ) {
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
        SDL_RenderClear( renderer );
        map->Render();
        SDL_RenderPresent( renderer );
        
        SDL_Event event;
        keyState = SDL_GetKeyboardState( NULL );
        
        while( SDL_PollEvent( &event ) != 0 ) {
            if( event.type == SDL_QUIT )
                isRunning = false;
        }
        if( keyState[ SDL_SCANCODE_SPACE ] )
            startMenu = 0;
        if( SDL_GameControllerGetButton( controller[0], SDL_CONTROLLER_BUTTON_A ))
            startMenu = 0;
        if( SDL_GameControllerGetButton( controller[1], SDL_CONTROLLER_BUTTON_A ))
            startMenu = 0;
    }
}

/*                        *
 * EVENTS AND USER INPUTS *
 *                        */

void Game::HandleEvents() {
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 ) {
        if( event.type == SDL_QUIT )
            isRunning = false;
    }
    keyState = SDL_GetKeyboardState( NULL );
    
    /*                        *
     * PLAYER ONE CONTROLLERS *
     *                        */
    
    // Keyboard - Movement
    if( !playerOne->CheckKeyLock() ) {
        // Jump
        if( keyState[ SDL_SCANCODE_W ] && playerOne->velY == 0 )
            playerOne->velY = -20;
        // Movement
        if( keyState[ SDL_SCANCODE_A ] ) {
            playerOne->velX = -7;
            playerOne->Running( 1 );
        }
        else if( keyState[ SDL_SCANCODE_D ] ) {
            playerOne->velX = 7;
            playerOne->Running( 2 );
        }
        else
            playerOne->Running( 0 );
        // Dash
        if( keyState[ SDL_SCANCODE_E ] && playerOne->velX > -2 && playerOne->velX < 5.1 ) {
            playerOne->velX = 15;
            playerOne->KeyLock( 25 );
            playerOne->Invulnerable();
        }
        if( keyState[ SDL_SCANCODE_Q ] && playerOne->velX < 2 && playerOne->velX > -5.1 ) {
            playerOne->velX = -15;
            playerOne->KeyLock( 25 );
            playerOne->Invulnerable();
        }
    }
    // Keyboard - Combat
    playerOne->cooldown++;
    if( !playerOne->CheckKeyLock() && playerOne->cooldown >= 30 ) {
        // Shoot
        if( keyState[ SDL_SCANCODE_G] ) {
            bulletOne[bulletIndex]->x= playerOne->x + 75;
            bulletOne[bulletIndex]->y= playerOne->y + 26;
            combat->Shoot( bulletOne[bulletIndex], 1 );
            playerOne->cooldown = 0;
            if( bulletIndex < 10 )
                bulletIndex++;
        }
        if( keyState[ SDL_SCANCODE_F ] ) {
            bulletOne[bulletIndex]->x = playerOne->x + 50;
            bulletOne[bulletIndex]->y = playerOne->y + 26;
            combat->Shoot( bulletOne[bulletIndex], 2 );
            playerOne->cooldown = 0;
            if( bulletIndex < 10 )
                bulletIndex++;
        }
        // Melee
        if( keyState[ SDL_SCANCODE_R ] ) {
            combat->Melee( playerOne, playerTwo,  1 );
            playerOne->cooldown = 0;
        }
        if( keyState[ SDL_SCANCODE_T ] ) {
            combat->Melee( playerOne, playerTwo, 2 );
            playerOne->cooldown = 0;
        }
        // Block
        if( keyState[ SDL_SCANCODE_C ] )
            playerOne->Block( true );
    }
    // Controller - Movement
    if( !playerOne->CheckKeyLock() ) {
        // Jump
        if( SDL_GameControllerGetButton( controller[0], SDL_CONTROLLER_BUTTON_A ) && playerOne->velY == 0 )
            playerOne->velY = -20;
        // Movement
        if( SDL_GameControllerGetAxis( controller[0], SDL_CONTROLLER_AXIS_LEFTX ) < -15000 )
            playerOne->velX = SDL_GameControllerGetAxis( controller[0], SDL_CONTROLLER_AXIS_LEFTX ) * movementSpeed;
        if( SDL_GameControllerGetAxis( controller[0], SDL_CONTROLLER_AXIS_LEFTX ) > 15000)
            playerOne->velX = SDL_GameControllerGetAxis( controller[0], SDL_CONTROLLER_AXIS_LEFTX ) * movementSpeed;
        // Dash
        if( SDL_GameControllerGetAxis( controller[0], SDL_CONTROLLER_AXIS_RIGHTX ) < -15000 && playerOne->velX > -2 && playerOne->velX <= 5 ) {
            playerOne->velX = -15;
            playerOne->KeyLock( 25 );
        }
        if( SDL_GameControllerGetAxis( controller[0], SDL_CONTROLLER_AXIS_RIGHTX ) > 15000 && playerOne->velX < 2 && playerOne->velX >= -5 ) {
            playerOne->velX = 15;
            playerOne->KeyLock( 25 );
        }
    }
    // Controller - Combat
    playerOne->cooldown++;
    if( !playerOne->CheckKeyLock() && playerOne->cooldown >= 30 ) {
        // Shoot
        if( SDL_GameControllerGetButton( controller[0], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER ) ) {
            bulletOne[bulletIndex]->x= playerOne->x - 16;
            bulletOne[bulletIndex]->y= playerOne->y + 16;
            combat->Shoot( bulletOne[bulletIndex], 1 );
            playerOne->cooldown = 0;
            if( bulletIndex < 10 )
                bulletIndex++;
        }
        if( SDL_GameControllerGetButton( controller[0], SDL_CONTROLLER_BUTTON_LEFTSHOULDER ) ) {
            bulletOne[bulletIndex]->x = playerOne->x + 16;
            bulletOne[bulletIndex]->y = playerOne->y + 16;
            combat->Shoot( bulletOne[bulletIndex], 2 );
            playerOne->cooldown = 0;
            if( bulletIndex < 10 )
                bulletIndex++;
        }
        // Melee
        if( SDL_GameControllerGetAxis( controller[0], SDL_CONTROLLER_AXIS_TRIGGERLEFT ) > 10000 ) {
            combat->Melee( playerOne, playerTwo,  1 );
            playerOne->cooldown = 0;
        }
        if( SDL_GameControllerGetAxis( controller[0], SDL_CONTROLLER_AXIS_TRIGGERRIGHT ) > 10000 ) {
            combat->Melee( playerOne, playerTwo, 2 );
            playerOne->cooldown = 0;
        }
        // Block
        if( SDL_GameControllerGetButton( controller[0], SDL_CONTROLLER_BUTTON_B ) )
            playerOne->Block( true );
    }
    
    /*                        *
     * PLAYER TWO CONTROLLERS *
     *                        */
    
    // Keyboard - Movement
    if( !playerTwo->CheckKeyLock() ) {
        // Jump
        if( keyState[ SDL_SCANCODE_UP ] && playerTwo->velY == 0 )
            playerTwo->velY = -20;
        // Movement
        if( keyState[ SDL_SCANCODE_LEFT ] ) {
            playerTwo->velX = -5;
            playerTwo->Running( 1 );
        }
        else if( keyState[ SDL_SCANCODE_RIGHT ] ) {
            playerTwo->velX = 5;
            playerTwo->Running( 2 );
        }
        else {
            playerTwo->Running( 0 );
        }
        // Dash
        if( keyState[ SDL_SCANCODE_9 ] && playerTwo->velX > -2 && playerTwo->velX <= 5 ) {
            playerTwo->velX = 15;
            playerTwo->KeyLock( 25 );
        }
        if( keyState[ SDL_SCANCODE_8 ] && playerTwo->velX < 2 && playerTwo->velX >= -5 ) {
            playerTwo->velX = -15;
            playerTwo->KeyLock( 25 );
        }
    }
    // Keyboard - Combat
    playerTwo->cooldown++;
    if( !playerTwo->CheckKeyLock() && playerTwo->cooldown >= 30 ) {
        // Shoot
        if( keyState[ SDL_SCANCODE_L ] ) {
            bulletTwo[bulletIndex]->x = playerTwo->x + 75;
            bulletTwo[bulletIndex]->y = playerTwo->y + 26;
            combat->Shoot( bulletTwo[bulletIndex], 1 );
            playerTwo->cooldown = 0;
            if( bulletIndex < 10 )
                bulletIndex++;
        }
        if( keyState[ SDL_SCANCODE_K ] ) {
            bulletTwo[bulletIndex]->x = playerTwo->x + 50;
            bulletTwo[bulletIndex]->y = playerTwo->y + 26;
            combat->Shoot( bulletTwo[bulletIndex], 2 );
            playerTwo->cooldown = 0;
            if( bulletIndex < 10 )
                bulletIndex++;
        }
        // Melee
        if( keyState[ SDL_SCANCODE_I ] ) {
            combat->Melee( playerTwo, playerOne, 1 );
            playerTwo->cooldown = 0;
        }
        if( keyState[ SDL_SCANCODE_O ] ) {
            combat->Melee( playerTwo, playerOne, 2 );
            playerTwo->cooldown = 0;
        }
        // Block
        if( keyState[ SDL_SCANCODE_0 ] )
            playerTwo->Block( true );
    }
    // Controller - Movement
    if( !playerTwo->CheckKeyLock() ) {
        // Jump
        if( SDL_GameControllerGetButton( controller[1], SDL_CONTROLLER_BUTTON_A ) && playerTwo->velY == 0 )
            playerTwo->velY = -20;
        // Movement
        if( SDL_GameControllerGetAxis( controller[1], SDL_CONTROLLER_AXIS_LEFTX ) < -15000 )
            playerTwo->velX = SDL_GameControllerGetAxis( controller[1], SDL_CONTROLLER_AXIS_LEFTX ) * movementSpeed;
        if( SDL_GameControllerGetAxis( controller[1], SDL_CONTROLLER_AXIS_LEFTX ) > 15000 )
            playerTwo->velX = SDL_GameControllerGetAxis( controller[1], SDL_CONTROLLER_AXIS_LEFTX ) * movementSpeed;
        // Dash
        if( SDL_GameControllerGetAxis( controller[1], SDL_CONTROLLER_AXIS_RIGHTX ) < -15000 && playerTwo->velX > -2 && playerTwo->velX <= 5 ) {
            playerTwo->velX = -15;
            playerTwo->KeyLock( 25 );
        }
        if( SDL_GameControllerGetAxis( controller[1], SDL_CONTROLLER_AXIS_RIGHTX ) > 15000 && playerTwo->velX < 2 && playerTwo->velX >= -5 ) {
            playerTwo->velX = 15;
            playerTwo->KeyLock( 25 );
        }
    }
    // Controller - Combat
    playerTwo->cooldown++;
    if( !playerTwo->CheckKeyLock() && playerTwo->cooldown >= 30 ) {
        // Shoot
        if( SDL_GameControllerGetButton( controller[1], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER ) ) {
            bulletTwo[bulletIndex]->x = playerTwo->x - 16;
            bulletTwo[bulletIndex]->y = playerTwo->y + 16;
            combat->Shoot( bulletTwo[bulletIndex], 1 );
            playerTwo->cooldown = 0;
            if( bulletIndex < 5 )
                bulletIndex++;
        }
        if( SDL_GameControllerGetButton( controller[1], SDL_CONTROLLER_BUTTON_LEFTSHOULDER ) ) {
            bulletTwo[bulletIndex]->x = playerTwo->x + 16;
            bulletTwo[bulletIndex]->y = playerTwo->y + 16;
            combat->Shoot( bulletTwo[bulletIndex], 2 );
            playerTwo->cooldown = 0;
            if( bulletIndex < 5 )
                bulletIndex++;
        }
        // Melee
        if( SDL_GameControllerGetAxis( controller[1], SDL_CONTROLLER_AXIS_TRIGGERLEFT ) > 10000 ) {
            combat->Melee( playerTwo, playerOne, 1 );
            playerTwo->cooldown = 0;
        }
        if( SDL_GameControllerGetAxis( controller[1], SDL_CONTROLLER_AXIS_TRIGGERRIGHT ) > 10000 ) {
            combat->Melee( playerTwo, playerOne, 2 );
            playerTwo->cooldown = 0;
        }
        // Block
        if( SDL_GameControllerGetButton( controller[1], SDL_CONTROLLER_BUTTON_B ) )
            playerTwo->Block( true );
    }
}
void Game::Update() {
    // Collision
    collision->Map( playerOne, tile );
    collision->Map( playerTwo, tile );
    for( int i = 0; i < 10; i++ ) {
        collision->Bullet( playerTwo, bulletOne[i] );
        collision->Bullet( playerOne, bulletTwo[i] );
    }
    // Update position
    playerOne->Update();
    playerTwo->Update();
    for( int i = 0; i < 10; i++ ) {
        bulletOne[i]->Update();
        bulletTwo[i]->Update();
    }
    // Winning condition
    if( playerOne->x < 0 || playerOne->x > SCREEN_WIDTH ) {
        std::cout << "Player Two Wins!" << std::endl;
        Game::Reset();
    }
    if( playerTwo->x < 0 || playerTwo->x > SCREEN_WIDTH ) {
        std::cout << "Player One Wins!" << std::endl;
        Game::Reset();
    }
    // Bullet index
    if( bulletIndex >= 10 )
        bulletIndex = 0;
}
void Game::Render() {
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderClear( renderer );
    map->Render();
    tile[0]->Render();
    tile[1]->Render();
    tile[2]->Render();
    playerOne->Render();
    playerTwo->Render();
    for( int i = 0; i < 10; i++ ) {
        bulletOne[i]->Render();
        bulletTwo[i]->Render();
    }
    SDL_RenderPresent( renderer );
}
void Game::Reset() {
    // Reset player one
    playerOne->x = 150;
    playerOne->y = SCREEN_HEIGHT - 250;
    playerOne->velX = 0;
    playerOne->velY = 0;
    playerOne->ResetKnockback();
    
    // Reset player two
    playerTwo->x = SCREEN_WIDTH - 150;
    playerTwo->y = SCREEN_HEIGHT - 250;
    playerTwo->velX = 0;
    playerTwo->velY = 0;
    playerTwo->ResetKnockback();
    
    // Start screen
    Game::Start();
}
void Game::Clean() {
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
    std::cout << "SDL Terminated..." << std::endl;
}
