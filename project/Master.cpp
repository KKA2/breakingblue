// Master.cpp
// Implementation of Master class to control gameplay
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Master.h"

using namespace std;

Master::Master() {
    init();
    person.setUp(Window,Renderer);
    levels.setUp(Window,Renderer);
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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"); // set texture filtering to linear
    Window = SDL_CreateWindow("Breaking Blue", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    Renderer = SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // create renderer for window
    SDL_SetRenderDrawColor(Renderer,0xFF,0xFF,0xFF,0xFF); // initialize renderer color
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
}

void Master::loadMedia() {
    person.loadMedia();
    levels.loadMedia();
}

void Master::play() {
    bool quit = false;
    SDL_Event e;

    double maxJumpHeight = 120;
    int speed = 30;

    levels.setCurrLevel(1);

    updateCamera();
    update();

    levels.playMusic();

    int notOnGround = checkGround(&person);
    while (notOnGround) { // continue until player hits ground or edge of board
        // updateCamera();
        person.setYPos(person.getYPos() + 2); // shift player down
        notOnGround = checkGround(&person);
        update();
    }

    while (!quit) {
        // check if a door is hit down
        if (levels.getCurrLevel() == 1) {
            if (levels.getCurrDoor(0) == 1) { // hit down first door
                while (levels.getCurrDoor(1) < 6) {
                    levels.setCurrDoor(1,levels.getCurrDoor(1) + .2);
                    update();
                }
                levels.setCurrDoor(1,6); // error check
            }
            else if (levels.getCurrDoor(0) == 2) { // hit down second door
                while (levels.getCurrDoor(2) < 6) {
                    levels.setCurrDoor(2,levels.getCurrDoor(2) + .2);
                    update();
                }
                levels.setCurrDoor(2,6); // error check
            }
            else if (levels.getCurrDoor(0) == 3) { // hit down third door
                while (levels.getCurrDoor(3) < 6) {
                    levels.setCurrDoor(3,levels.getCurrDoor(3) + .2);
                    update();
                }
                levels.setCurrDoor(3,6); // error check
            }
        }
        while (person.getState() == 4) { // rolling
            person.setCurrRoll(person.getCurrRoll() + .5);
            if (person.getMoveDir() == SDL_FLIP_NONE) // check direction for movement
                moveFigure(8,0);
            else
                moveFigure(-8,0);
            
            if (person.getCurrRoll() < 8)
                update();
            else {
                person.setCurrRoll(0);
                person.setState(3);
            }
        }
        while (person.getState() == 5) { // punching
            // check for collision
            int hasCollided = checkCollision(&person);
            if (hasCollided) { // add to punch only once (four punches must collide)
                if (levels.getCurrLevel() == 1)
                    levels.setCurrDoor(0,levels.getCurrDoor(0) + .25);
                sound.playSound(3);

                do { // fix collision
                    fixCollision(&person,hasCollided);
                    hasCollided = checkCollision(&person);
                } while (hasCollided);
            }

            if (person.getCurrPunch() == 0)
                moveFigure(4,0);
            if (person.getCurrPunch() < 6)
                person.setCurrPunch(person.getCurrPunch() + .4);
            else if (person.getCurrPunch() < 8)
                person.setCurrPunch(person.getCurrPunch() + .25);
            else
                person.setCurrPunch(person.getCurrPunch() + 1);

            if (person.getCurrPunch() < 13)
                update();
            else {
                person.setCurrPunch(0);
                person.setState(0);
            }
        }

        while (person.getState() == 6) { // kicking
            if (person.getCurrKick() < 5)
                person.setCurrKick(person.getCurrKick() + .45);
            else if (person.getCurrKick() < 6)
                person.setCurrKick(person.getCurrKick() + .1);
            else
                person.setCurrKick(person.getCurrKick() + .8);

            if (person.getCurrKick() < 11)
                update();
            else {
                person.setCurrKick(0);
                person.setState(0);
            }
        }

        person.setState(0);

        while (SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                quit = true;
            else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP: 
                        person.setState(2);
                        if (person.getJumpHeight() == 0)
                            person.setJumpDir(-1);
                        break;
                    case SDLK_SPACE:
                        person.setState(5);
                        break;
                    case SDLK_RETURN:
                        person.setState(6);
                        break;
                    case SDLK_q:
                        quit = true;
                        break;
                }
            }
        }

        double changeY =  person.getJumpDir() * ((maxJumpHeight+10 - person.getJumpHeight())/(maxJumpHeight+10)) * speed;    
        person.setJumpHeight(person.getJumpHeight() - changeY);
        if (person.getJumpDir() == -1) {
            moveFigure(0,changeY);
            person.setState(2);
            if (person.getJumpHeight() >= maxJumpHeight)
                person.setJumpDir(1);
            else if (person.getYPos() < 5) { // hit ceiling
                person.setJumpDir(1);
                if (person.getJumpHeight() < 50) // if short fall
                    speed = 5; // temp adjust speed
            }

        }
        else if (person.getJumpDir() == 1) {
            person.setState(2);
            if (moveFigure(0,changeY,false) == 2) { // jump below ground
                sound.playSound(1);
                person.setState(0);
                person.setJumpDir(0);
                person.setJumpHeight(0);
                speed = 30;
                while (moveFigure(0,5) == 1); // move to ground if above ground
            }
            else { // if can still jump down
                moveFigure(0,changeY);
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_DOWN]) { // duck
            if (person.getState() != 2) {
                person.setState(3);
                if (state[SDL_SCANCODE_LEFT]) {
                    person.setMoveDir(SDL_FLIP_HORIZONTAL);
                    person.setState(4);
                }
                else if (state[SDL_SCANCODE_RIGHT]) {
                    person.setMoveDir(SDL_FLIP_NONE);
                    person.setState(4);
                }
            }
        }
        else if (state[SDL_SCANCODE_LEFT]) { // run left
            person.setMoveDir(SDL_FLIP_HORIZONTAL);
            if (person.getState() != 2) { // if not jumping
                sound.playSound(2);
                person.setState(1);
            }
            moveFigure(-10,0);
            if (person.getJumpHeight() == 0)
                person.setCurrRun(person.getCurrRun() + .3);
        }
        else if (state[SDL_SCANCODE_RIGHT]) { // run right
            person.setMoveDir(SDL_FLIP_NONE);
            if (person.getState() != 2) {
                sound.playSound(2);
                person.setState(1);
            }
            moveFigure(10,0);
            if (person.getJumpHeight() == 0)
                person.setCurrRun(person.getCurrRun() + .3);
        }
        else {
            person.setCurrRun(0);
        }

        if (person.getCurrRun() >= 7) // keep in bounds of array for running
            person.setCurrRun(0);

        moveFigure(0,0);
        update();
    }
}

int Master::moveFigure(const double chX, const double chY, bool move) {
    person.setXPos(person.getXPos() + chX);
    person.setYPos(person.getYPos() + chY);

    // check for/respond to collision
    int hasCollided = checkCollision(&person);
    while(hasCollided){  // hasCollided: 1 = topleft; 2 = topright; 3 = right; 4 = left; 0 = no collide
        fixCollision(&person,hasCollided);
        hasCollided = checkCollision(&person);
    }

    int notOnGround = checkGround(&person);
    if (person.getJumpHeight() == 0) { // not jumping
        // ensure person is on ground
        if (notOnGround) { // continue until player hits ground or edge of board
            if (person.getState() != 1)
                person.setState(2); // draw falling figure

            if (notOnGround == 1) { // is in air
                if (move == true)
                    person.setYPos(person.getYPos() + 5); // shift player down (falling)
                notOnGround = checkGround(&person);
                if (!notOnGround)
                    sound.playSound(1);
            }
            else { // is in the ground
                if (move == true)
                    person.setYPos(person.getYPos() - 2); // shift player up (rising)
                notOnGround = checkGround(&person);
            } 
        }
    }
    
    if (person.getXPos() > LEVEL_WIDTH - 75)
        person.setXPos(LEVEL_WIDTH - 75);
    else if (person.getXPos() < 0)
        person.setXPos(0);

    if (person.getYPos() > LEVEL_HEIGHT)
        exit(1);
    else if (person.getYPos() < 0)
        person.setYPos(0);

    if (move == false) {
        person.setXPos(person.getXPos() - chX);
        person.setYPos(person.getYPos() - chY);
    }
    else {
        updateCamera();
    }
    return notOnGround;
}

void Master::updateCamera() {
    // center camera over the player
    levels.setCameraX(person.getXPos() + 75 - SCREEN_WIDTH/2);
    // keep camera in bounds
    if (levels.getCameraX() < 0)
        levels.setCameraX(0);
    else if (levels.getCameraX() > levels.getLevelWidth() - SCREEN_WIDTH)
        levels.setCameraX(levels.getLevelWidth() - SCREEN_WIDTH);
}

void Master::update() {
    SDL_RenderClear(Renderer);
    levels.display();
    // foreground
    person.draw(levels.getCameraX());
    // update screen
    SDL_RenderPresent(Renderer);
}

void Master::fixCollision(Person *person, int collisionType){
    // return values: 1 = topleft; 2 = topright; 3 = right; 4 = left;
    
    if (collisionType == 4){ // left side
        person->setXPos(person->getXPos() + 5); // kick to the right
    }
    else if (collisionType == 3){ // right
        person->setXPos(person->getXPos() - 5); // kick to the left
    }
    else if (collisionType == 2){ // topright
        person->setYPos(person->getYPos() + 5); // move player back down
        person->setXPos(person->getXPos() - 10); // kick to the left 
    }
    else { // topleft
        person->setYPos(person->getYPos() + 5); // move player back down
        person->setXPos(person->getXPos() + 10); // kick to the right
    }
}

int Master::checkCollision(Person *person) {
    // compare current player image to foreground and detect collision/collision type
    // return values: 1 = topleft; 2 = topright; 3 = right; 4 = left; 0 = no collide

    int boundingH = 94, boundingW = 75; // height and width of player image
    Uint8 personAlpha, alpha; // store alpha levels 
    Uint32 personPixel, pixel; // store current pixel for for loop
    
    // access current player texture
    int state = person->getState();
    Texture * playerTex = person->getTexture(state);

    // access current frame value within texture (or access only frame)
    double frame = 0; // current frame in sprite
    switch (state) {
        case 1: // running
            frame = person->getCurrRun();
            break;
        case 3: // ducking
            boundingH = 35; 
            break;
        case 4: // rolling
            boundingH = 35; 
            frame = person->getCurrRoll();
            break;
        case 5: // punching
            frame = person->getCurrPunch();
            break;
        default: // standing, jumping
            break; // for textures with only one frame
    }

    // set bounds for collisions check (actually denote the current frame)
    int leftEdge = int(frame) * boundingW;
    //int rightEdge = leftEdge + boundingW;

    // loops through bounding box of the player, compares alpha of both char and player
    for(int y = boundingH; y > 0; y--) { 
        for(int x = 0; x < boundingW; x++) { 
            personPixel = playerTex->getPixel(x+leftEdge, y); // access current pixel
            personAlpha = playerTex->getAlpha(personPixel); // access alpha value of pixel (i.e. transparency)
            if (personAlpha > 0) { // if part of player on current pixel
                pixel = levels.getForeground()->getPixel(person->getXPos()+x, y); // get foreground pixel
                alpha = levels.getForeground()->getAlpha(pixel); // check foreground transparency
                if (alpha > 0) { // collision (assume collision on right side if none else found)
                    if ((y < boundingH/6) && (x < boundingW/2)) // hit top left
                        return 1;
                    else if ((y < boundingH/6) && (x >= boundingW/2)) // hit top right
                        return 2;
                    else if (x >= boundingW/2) // just right
                        return 3;
                    else // just left
                        return 4;
                }   
            }
        }
    }
    return 0; // no collision
}

int Master::checkGround(Person *person) {
    // get value of pixel at current position of player on foreground
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
