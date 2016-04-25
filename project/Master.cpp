// Master.cpp
// Implementation of Master class to control gameplay
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Master.h"

using namespace std;

Master::Master() {
    Quit = false;
    NextLevel = true; // start game by moving to first level
    // initialize screen
    init();
    // set up textures in composed classes
    player.setUp(Renderer);
    enemy.setUp(Renderer);
    levels.setUp(Renderer);
    // load all pictures/sounds
    loadMedia();
}

Master::~Master() {
    // destroy window    
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    Window = NULL;
    Renderer = NULL;
    // quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Master::init() {
    // set up window
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"); // set texture filtering to linear
    Window = SDL_CreateWindow("Breaking Blue", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // set up renderer for displaying textures
    Renderer = SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // create renderer for window
    SDL_SetRenderDrawColor(Renderer,0xFF,0xFF,0xFF,0xFF); // initialize renderer color
    // add support for png images
    IMG_Init(IMG_INIT_PNG);
    // initialize audio settings
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
}

void Master::loadMedia() {
    // call composed class functions to load images/audio
    player.loadMedia();
    enemy.loadMedia();
    levels.loadMedia();
}

void Master::play() {
    while (!Quit) {
        if (NextLevel) { // check if new/next level
            //levels.setCurrLevel(levels.getCurrLevel() + 1); // go to first/next level
            levels.setCurrLevel(4); // TESTING LEVEL
            levels.playMusic(); // start music
            reset(); // set all initial values
            NextLevel = false; // reset value of next level to play in the new level
            if (levels.getCurrLevel() > 2) // increase jump height
                player.setMaxJumpHeight(180);
        }

        while (levels.getCurrLevel() == 0) { // while in menu screen
            SDL_Event e; // store key pressed
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT)
                    Quit = true;
                else if (e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case SDLK_SPACE: // press space to move to start game
                            NextLevel = true;
                            break;
                        case SDLK_q: // press q to quit game
                            Quit = true;
                            break;
                    }
                }
            }
            if (NextLevel == true || Quit == true)
                break; // break out to move to next level
        }
        if (levels.getCurrLevel() != 0) { // if not menu screen (i.e. gameplay)
            animate(&player); // run through any animations
            if (player.getState() == 1 || player.getState() == 2) // if running or jumping animation
                player.setState(0); // reset state just in case
            if (enemy.getState() == 2) // if jumping
                enemy.setState(0);

            checkKeyPress(); // check short key presses
            jump(&player); // jumping animation
            checkKeyboard(); // check for held key presses

            if (player.getCurrRun() >= 7) // keep in bounds of array for running
                player.setCurrRun(0);

            moveFigure(&player,0,0); // check for collisions/ground and adjust accordingly
            
            if (levels.getCurrLevel() == 4) { // move enemy if exists
                moveFigure(&enemy,enemy.move(player.getXPos(),player.getState()),0); // move x position
                animate(&enemy); // complete any animations
                jump(&enemy);
            }
            
            update(); // update screen animation
        }
    }
}

void Master::reset() {
    // set player's initial position
    player.setInitialPos(levels.getLevelWidth(),levels.getLevelHeight());
    // move display to center over figure
    updateCamera();
    // redraw screen images
    update(false); // do not draw person just yet
    // set player stats
    player.setCurrRun(0);
    player.setCurrRoll(0);
    player.setCurrPunch(0);
    player.setCurrKick(0);
    player.setState(0);
    player.setMoveDir(SDL_FLIP_NONE);
    player.setJumpDir(0);
    player.setJumpHeight(0);
    // set enemy stats
    if (levels.getCurrLevel() == 4) {
        enemy.setCurrRun(0);
        enemy.setCurrRoll(0);
        enemy.setCurrPunch(0);
        enemy.setCurrKick(0);
        enemy.setState(0);
        enemy.setMoveDir(SDL_FLIP_HORIZONTAL);
        enemy.setJumpDir(0);
        enemy.setJumpHeight(0);
    }
    // reset camera/display
    levels.setCameraX(0);
    if (levels.getCurrLevel() == 1 || levels.getCurrLevel() == 2)
        for (int l=0;l<=3;l++)
            levels.setCurrDoor(l,0);
    // move figure to the ground to restart gameplay
    if (levels.getCurrLevel() != 0) { // if not in menu screen
        while (moveFigure(&player,0,15,false) == 2) { // continue until player hits ground or edge of board
            moveFigure(&player,0,15);
            update(); // redraw the change in position
        }
        while (moveFigure(&player,0,1) == 1) { // move to ground if above ground
            update();
        }
    }
    // set enemy initial position based on player
    if (levels.getCurrLevel() == 4) { // in final level
        enemy.setXPos(levels.getLevelWidth()-75);
        enemy.setYPos(player.getYPos());
    }
}

void Master::updateCamera() {
    // center camera over the player
    levels.setCameraX(player.getXPos() + 75 - SCREEN_WIDTH/2);
    levels.setCameraY(player.getYPos() + 94 - SCREEN_HEIGHT/2);
    // keep camera in bounds
    // horizontal bounds
    if (levels.getCameraX() < 0)
        levels.setCameraX(0);
    else if (levels.getCameraX() > levels.getLevelWidth() - SCREEN_WIDTH)
        levels.setCameraX(levels.getLevelWidth() - SCREEN_WIDTH);
    // vertical bounds
    if (levels.getCameraY() < 0)
        levels.setCameraY(0);
    else if (levels.getCameraY() > levels.getLevelHeight() - SCREEN_HEIGHT)
        levels.setCameraY(levels.getLevelHeight() - SCREEN_HEIGHT);
}

void Master::update(bool interactive) {
    SDL_RenderClear(Renderer); // clear screen to redraw
    levels.display(); // draw background/foreground
    if (interactive) { // only draw player if in interactive mode
        player.draw(levels.getCameraX(),levels.getCameraY()); // draw player
        if (levels.getCurrLevel() == 4) // if in final level
            enemy.draw(levels.getCameraX(),levels.getCameraY()); // draw enemy
    }

    SDL_RenderPresent(Renderer); // update screen
}

void Master::animate(Person *person) {
    // check if a door is hit down
    if (levels.getCurrLevel() == 1 || levels.getCurrLevel() == 2) { // first or second level
        if (levels.getCurrDoor(0) >= 3) { // hit down third door
            while (levels.getCurrDoor(3) < 6) {
                levels.setCurrDoor(3,levels.getCurrDoor(3) + .2);
                update();
            }
            levels.setCurrDoor(3,6); // error check
        }
        else if (levels.getCurrDoor(0) >= 2) { // hit down second door
            while (levels.getCurrDoor(2) < 6) {
                levels.setCurrDoor(2,levels.getCurrDoor(2) + .2);
                update();
            }
            levels.setCurrDoor(2,6); // error check
        }
        else if (levels.getCurrDoor(0) >= 1) { // hit down first door
            while (levels.getCurrDoor(1) < 6) {
                levels.setCurrDoor(1,levels.getCurrDoor(1) + .2);
                update();
            }
            levels.setCurrDoor(1,6); // error check
        }
    }
    // move person
    if (person->getState() == 4) { // rolling
        person->setCurrRoll(person->getCurrRoll() + 1);
        if (person->getMoveDir() == SDL_FLIP_NONE) // check direction for movement
            moveFigure(person,16,0);
        else
            moveFigure(person,-16,0);
        
        if (person->getCurrRoll() < 8) {
            update();
        }
        else {
            person->setCurrRoll(0);
            person->setState(3);
        }
    }
    if (person->getState() == 5) { // punching
        // check for collision
        if (int(person->getCurrPunch()) == 6) { // only check frames between 6/7
            int hasCollided = checkCollision(person);
            if (hasCollided) { // five must collide
                if (levels.getCurrLevel() == 1 || levels.getCurrLevel() == 2)
                    levels.setCurrDoor(0,levels.getCurrDoor(0) + .2);
                sound.playSound(3);

                do { // fix collision
                    fixCollision(person,hasCollided);
                    hasCollided = checkCollision(person);
                } while (hasCollided);
            }
        }
        if (person->getCurrPunch() == 0) { // if beginning punch
            if (person->getMoveDir() == SDL_FLIP_NONE) // move in direction punching
                moveFigure(person,4,0);
            else
                moveFigure(person,-4,0);
        }
        if (person->getCurrPunch() < 6)
            person->setCurrPunch(person->getCurrPunch() + .8);
        else if (person->getCurrPunch() < 8)
            person->setCurrPunch(person->getCurrPunch() + .5);
        else
            person->setCurrPunch(person->getCurrPunch() + 2);

        if (person->getCurrPunch() < 13) {
            update();
        }
        else {
            person->setCurrPunch(0);
            person->setState(0);
        }
    }

    if (person->getState() == 6) { // kicking
        // check for collision
        int hasCollided = checkCollision(person);
        if (hasCollided) { // five must collide
            if (levels.getCurrLevel() == 1 || levels.getCurrLevel() == 2)
                levels.setCurrDoor(0,levels.getCurrDoor(0) + .2);
            sound.playSound(3);

            do { // fix collision
                fixCollision(person,hasCollided);
                hasCollided = checkCollision(person);
            } while (hasCollided);
        }

        if (person->getCurrKick() < 5)
            person->setCurrKick(person->getCurrKick() + .8);
        else if (person->getCurrKick() < 6)
            person->setCurrKick(person->getCurrKick() + .2);
        else
            person->setCurrKick(person->getCurrKick() + 1.4);

        if (person->getCurrKick() < 11) {
            update();
        }
        else {
            person->setCurrKick(0);
            person->setState(0);
        }
    }
}

void Master::jump(Person *person) {
    int jumpSpeed; // adjust for early termination of jumps/higher jumps
    if (levels.getCurrLevel() > 2)
        jumpSpeed = 40;
    else
        jumpSpeed = 30;

    double changeY =  person->getJumpDir() * ((person->getMaxJumpHeight()+10 - person->getJumpHeight())/(person->getMaxJumpHeight()+10)) * jumpSpeed;    
    person->setJumpHeight(person->getJumpHeight() - changeY);
    if (person->getJumpDir() == -1) {
        moveFigure(person,0,changeY);
        person->setState(2);
        if (person->getJumpHeight() >= person->getMaxJumpHeight())
            person->setJumpDir(1);
        else if (person->getYPos() < 5) { // hit ceiling
            person->setJumpDir(1);
            if (person->getJumpHeight() < 50) { // if short fall
                if (levels.getCurrLevel() > 2)
                    jumpSpeed = 10;
                else
                    jumpSpeed = 5;
            }
        }

    }
    else if (person->getJumpDir() == 1) {
        person->setState(2);
        if (moveFigure(person,0,changeY,false) == 2) { // check if will jump below ground
            sound.playSound(1);
            person->setState(0);
            person->setJumpDir(0);
            person->setJumpHeight(0);
            if (levels.getCurrLevel() > 2)
                jumpSpeed = 40;
            else
                jumpSpeed = 30;
            while (moveFigure(person,0,5) == 1); // move to ground if above ground
        }
        else { // if can still jump down
            moveFigure(person,0,changeY);
        }
    }
}

void Master::checkKeyboard() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (FlyingEnabled) { // in third level (add flying)
        if (state[SDL_SCANCODE_UP]) {
            player.setState(7);
            moveFigure(&player,0,-10);
        }
    }

    if (state[SDL_SCANCODE_DOWN]) { // duck
        if (player.getState() != 2 && player.getState() != 7) { // if not jumping or flying
            player.setState(3); // set to ducking state
            if (state[SDL_SCANCODE_LEFT]) { // left key pressed
                player.setMoveDir(SDL_FLIP_HORIZONTAL); // turn to the left
                player.setState(4); // set to rolling state
            }
            else if (state[SDL_SCANCODE_RIGHT]) { // right key pressed
                player.setMoveDir(SDL_FLIP_NONE); // turn to the right
                player.setState(4);
            }
        }
    }
    else if (state[SDL_SCANCODE_LEFT]) { // run left
        player.setMoveDir(SDL_FLIP_HORIZONTAL); // turn to the left
        if (player.getState() != 2 && player.getState() != 7) { // if not jumping or flying
            sound.playSound(2); // play running sound effect
            if (moveFigure(&player,0,0,false) != 1) { // if not above ground
                player.setState(1); // set to running state
                player.setCurrRun(player.getCurrRun() + .3); // change frame
            }
        }
        moveFigure(&player,-10,0); // move to the left
    }
    else if (state[SDL_SCANCODE_RIGHT]) { // run right
        player.setMoveDir(SDL_FLIP_NONE); // turn to the right
        if (player.getState() != 2 && player.getState() != 7) {
            sound.playSound(2);
            if (moveFigure(&player,0,0,false) != 1) { // if not above ground
                player.setState(1);
                player.setCurrRun(player.getCurrRun() + .3);
            }
        }
        moveFigure(&player,10,0); // move to the right
    }
    else {
        player.setCurrRun(0); // reset frame count
    }
}

void Master::run(Person *, SDL_RendererFlip direction) {

} 

void Master::checkKeyPress() {
    SDL_Event e; // store key pressed
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            Quit = true;
        else if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_UP:
                    if (!FlyingEnabled) {
                        player.setState(2); // jump
                        if (player.getJumpHeight() == 0) // if not already jumping
                            player.setJumpDir(-1); // start moving upwards
                    }
                    break;
                case SDLK_SPACE:
                    player.setState(5); // punch
                    break;
                case SDLK_RETURN:
                    if (levels.getCurrLevel() >= 2) // if kicking ability enabled
                        player.setState(6); // kick
                    break;
                case SDLK_RSHIFT:
                    if (levels.getCurrLevel() >= 2) { // if flying ability enabled
                        if (levels.getCurrLevel() == 2 && levels.getCurrDoor(0) > 3) { // unlock door past the third door in level 2
                            // change mode
                            if (FlyingEnabled)
                                FlyingEnabled = false;
                            else
                                FlyingEnabled = true;
                        }
                    }
                    break;
                case SDLK_q:
                    Quit = true;
                    break;
                case SDLK_c:
                    levels.setCurrText();
                    break;
            }
        }
    }
}

int Master::moveFigure(Person *person, double chX, double chY, bool move) {
    // set new position so as to allow ground/collision checking
    person->setXPos(person->getXPos() + chX);
    person->setYPos(person->getYPos() + chY);

    // check for/respond to collision
    int hasCollided = checkCollision(person);
    while(hasCollided){ // hasCollided: 1 = topleft; 2 = topright; 3 = right; 4 = left; 0 = no collide
        fixCollision(person,hasCollided);
        hasCollided = checkCollision(person);
    }

    // check relationship to the ground
    int notOnGround = checkGround(person);
    if (!(person->getState() == 2 && person->getJumpDir() == -1)) { // if not rising in jump
        if (person->getState() != 7) { // not flying
            // ensure person is on ground
            if (notOnGround) { // continue until person hits ground or edge of board
                if (person->getState() != 1)
                    person->setState(2); // draw falling figure

                if (notOnGround == 1) { // is in air
                    if (move == true)
                        person->setYPos(person->getYPos() + 6); // shift person down (falling)
                    notOnGround = checkGround(person);
                    if (!notOnGround)
                        sound.playSound(1);
                }
                else { // is in the ground
                    if (move == true)
                        person->setYPos(person->getYPos() - 1); // shift person up (rising)
                    notOnGround = checkGround(person);
                } 
            }
        }
    }

    if (move == false) { // if not actually moving the character
        person->setXPos(person->getXPos() - chX);
        person->setYPos(person->getYPos() - chY);
    }
    else {
        if (person->getXPos() > levels.getLevelWidth() - 75) { // overstep right boundary
            if (levels.getCurrLevel() == 1) // if in first level
                NextLevel = true; // move to next level when hit end
            else
                person->setXPos(levels.getLevelWidth()  - 75); // fix overstep
        }
        else if (person->getXPos() < 0) // overstep left boundary
            person->setXPos(0);

        if (person->getYPos() > levels.getLevelHeight()) { // overstep bottom boundary
            reset();
        }
        else if (person->getYPos() < 0) { // overstep top boundary
            if (levels.getCurrLevel() == 2 || levels.getCurrLevel() == 3) // if in third level
                NextLevel = true;
            else
                person->setYPos(0);
        }

        updateCamera();
    }
    return notOnGround;
}

int Master::checkCollision(Person *person) {
    // compare current person image to foreground and detect collision/collision type
    // return values: 1 = topleft; 2 = topright; 3 = right; 4 = left; 0 = no collide
    int boundingH = 94, boundingW = 75; // height and width of person image
    Uint8 personAlpha, alpha; // store alpha levels 
    Uint32 personPixel, pixel; // store current pixel for for loop

    // access current frame value within texture (or access only frame)
    double frame = 0; // current frame in sprite
    switch (person->getState()) {
        case 1: // running
            frame = person->getCurrRun();
            break;
        case 4: // rolling
            frame = person->getCurrRoll();
            break;
        case 5: // punching
            frame = person->getCurrPunch();
            break;
        case 6: // kicking
            frame = person->getCurrKick();
            break;
        default: // standing, jumping, ducking
            break;
    }

    // set bound for collisions check
    int leftEdge = int(frame)*boundingW;

    Texture * personTex = person->getTexture(person->getState());

    // loops through bounding box of the person, compares alpha of both char and person
    for(int y = 2*boundingH/3; y > 0; y--) { 
        for(int x = boundingW; x > 0; x--) { 
            // get current person pixel 
            if (person->getMoveDir() == SDL_FLIP_HORIZONTAL) // if facing left
                personPixel = personTex->getPixel(leftEdge+boundingW-x,y);
            else 
                personPixel = personTex->getPixel(leftEdge+x,y); // access current pixel
            // access alpha value of pixel (i.e. transparency)
            personAlpha = personTex->getAlpha(personPixel); 
            
            if (int(personAlpha) > 10) { // if person is present, check for overlap with foreground
                // get foreground pixel
                if (person->getMoveDir() == SDL_FLIP_HORIZONTAL) // facing left
                    pixel = levels.getForeground()->getPixel(person->getXPos()+boundingW-x,person->getYPos()+y);
                else //facing right
                    pixel = levels.getForeground()->getPixel( person->getXPos()+x,person->getYPos()+y);
                // check foreground transparency
                alpha = levels.getForeground()->getAlpha(pixel);
                if (int(alpha) > 10) { // collision
                    if (y < boundingH/6) // top
                        return 1;
                    if (person->getMoveDir() == SDL_FLIP_HORIZONTAL) { // return response for left facing person
                        if (x < boundingW/2) // right col
                            return 2;
                        else // left col
                            return 3;
                    }
                    else { // return response for right facing person
                        if (x > boundingW/2) // right
                            return 2;
                        else // left
                            return 3;
                    }
                }
            }
        }
    }
    return 0; // no collision
}

void Master::fixCollision(Person *person, int collisionType){
    // return values: 1 = topleft; 2 = topright; 3 = right; 4 = left;
    if (collisionType == 3) { // left side
        person->setXPos(person->getXPos() + 5); // kick to the right
    }
    else if (collisionType == 2) { // right
        person->setXPos(person->getXPos() - 5); // kick to the left
    }
    else { // top
        if (levels.getCurrLevel() == 1)
            reset();
        else
            person->setYPos(person->getYPos() + 5); // move person back down
    }
}

int Master::checkGround(Person *person) {
    // get value of pixel at current position of person on foreground
    Uint32 pixel, abovePixel;
    pixel = levels.getForeground()->getPixel(person->getXPos()+40,person->getYPos()+93);
    abovePixel = levels.getForeground()->getPixel(person->getXPos()+40,person->getYPos()+90);
    
    // convert to RGBA values
    Uint8 alpha;
    alpha = levels.getForeground()->getAlpha(pixel);

    Uint8 beta;
    beta = levels.getForeground()->getAlpha(abovePixel);
    if(int(alpha) < 10) // transparent pixel; is in air
        return 1;
    if(int(beta) > 10) // pixel is not transparent
        return 2;

    return 0;
}
