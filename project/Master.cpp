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
    levels.loadMedia();
}

void Master::play() {
    while (!Quit) {
        if (NextLevel) { // check if new/next level
            levels.setCurrLevel(levels.getCurrLevel() + 1); // go to first/next level
            //levels.setCurrLevel(3); // TESTING LEVEL 3
            levels.playMusic(); // start music
            reset(); // set all initial values
            NextLevel = false; // reset value of next level to play in the new level
            if (levels.getCurrLevel() > 2) // double jump height
                player.setMaxJumpHeight(240);
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
            if (NextLevel == true)
                break; // break out to move to next level
        }
        if (levels.getCurrLevel() != 0) { // if not menu screen (i.e. gameplay)
            animate(); // run through any animations
            player.setState(0); // reset state (draw standing if not changed)

            checkKeyPress(); // check short key presses
            jump(); // jumping animation
            checkKeyboard(); // check for held key presses

            if (player.getCurrRun() >= 7) // keep in bounds of array for running
                player.setCurrRun(0);

            moveFigure(0,0); // check for collisions and adjust accordingly
            update();
        }
    }
}

void Master::reset() {
    // set player's initial position
    player.setInitialPos(levels.getLevelWidth(),levels.getLevelHeight());
    // move display to center over figure
    updateCamera();
    // redraw screen images
    update(false);
    // set player stats
    player.setCurrRun(0);
    player.setCurrRoll(0);
    player.setCurrPunch(0);
    player.setCurrKick(0);
    player.setState(0);
    player.setMoveDir(SDL_FLIP_NONE);
    player.setJumpDir(0);
    player.setJumpHeight(0);
    // reset camera/display
    levels.setCameraX(0);
    if (levels.getCurrLevel() == 1)
        for (int l=0;l<=3;l++)
            levels.setCurrDoor(l,0);
    // move figure to the ground to restart gameplay
    if (levels.getCurrLevel() != 0) { // if not in menu screen
        while (moveFigure(0,15,false) == 2) { // continue until player hits ground or edge of board
            moveFigure(0,15);
            update(); // redraw the change in position
        }
        while (moveFigure(0,1) == 1) { // move to ground if above ground
            update();
        }
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
    if (interactive) // only draw player if in interactive mode
        player.draw(levels.getCameraX(),levels.getCameraY()); // draw player
    SDL_RenderPresent(Renderer); // update screen
}

void Master::animate() {
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
    while (player.getState() == 4) { // rolling
        player.setCurrRoll(player.getCurrRoll() + .5);
        if (player.getMoveDir() == SDL_FLIP_NONE) // check direction for movement
            moveFigure(8,0);
        else
            moveFigure(-8,0);
        
        if (player.getCurrRoll() < 8)
            update();
        else {
            player.setCurrRoll(0);
            player.setState(3);
        }
    }
    while (player.getState() == 5) { // punching
        // check for collision
        int hasCollided = checkCollision();
        if (hasCollided) { // add to punch only once (four punches must collide)
            if (levels.getCurrLevel() == 1)
                levels.setCurrDoor(0,levels.getCurrDoor(0) + .25);
            sound.playSound(3);

            do { // fix collision
                fixCollision(hasCollided);
                hasCollided = checkCollision();
            } while (hasCollided);
        }

        if (player.getCurrPunch() == 0)
            moveFigure(4,0);
        if (player.getCurrPunch() < 6)
            player.setCurrPunch(player.getCurrPunch() + .4);
        else if (player.getCurrPunch() < 8)
            player.setCurrPunch(player.getCurrPunch() + .25);
        else
            player.setCurrPunch(player.getCurrPunch() + 1);

        if (player.getCurrPunch() < 13)
            update();
        else {
            player.setCurrPunch(0);
            player.setState(0);
        }
    }

    while (player.getState() == 6) { // kicking
        if (player.getCurrKick() < 5)
            player.setCurrKick(player.getCurrKick() + .45);
        else if (player.getCurrKick() < 6)
            player.setCurrKick(player.getCurrKick() + .1);
        else
            player.setCurrKick(player.getCurrKick() + .8);

        if (player.getCurrKick() < 11)
            update();
        else {
            player.setCurrKick(0);
            player.setState(0);
        }
    }
}

void Master::jump() {
    int jumpSpeed; // adjust for early termination of jumps/higher jumps
    if (levels.getCurrLevel() > 2)
        jumpSpeed = 40;
    else
        jumpSpeed = 30;

    double changeY =  player.getJumpDir() * ((player.getMaxJumpHeight()+10 - player.getJumpHeight())/(player.getMaxJumpHeight()+10)) * jumpSpeed;    
    player.setJumpHeight(player.getJumpHeight() - changeY);
    if (player.getJumpDir() == -1) {
        moveFigure(0,changeY);
        player.setState(2);
        if (player.getJumpHeight() >= player.getMaxJumpHeight())
            player.setJumpDir(1);
        else if (player.getYPos() < 5) { // hit ceiling
            player.setJumpDir(1);
            if (player.getJumpHeight() < 50) { // if short fall
                if (levels.getCurrLevel() > 2)
                    jumpSpeed = 10;
                else
                    jumpSpeed = 5;
            }
        }

    }
    else if (player.getJumpDir() == 1) {
        player.setState(2);
        if (moveFigure(0,changeY,false) == 2) { // check if will jump below ground
            sound.playSound(1);
            player.setState(0);
            player.setJumpDir(0);
            player.setJumpHeight(0);
            if (levels.getCurrLevel() > 2)
                jumpSpeed = 40;
            else
                jumpSpeed = 30;
            while (moveFigure(0,5) == 1); // move to ground if above ground
        }
        else { // if can still jump down
            moveFigure(0,changeY);
        }
    }
}

void Master::checkKeyboard() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_DOWN]) { // duck
        if (player.getState() != 2) {
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
        if (player.getState() != 2) { // if not jumping
            sound.playSound(2); // play running sound effect
            player.setState(1); // set to running state
        }
        moveFigure(-10,0); // move to the left
        if (player.getJumpHeight() == 0) // if at ground level
            player.setCurrRun(player.getCurrRun() + .3);
    }
    else if (state[SDL_SCANCODE_RIGHT]) { // run right
        player.setMoveDir(SDL_FLIP_NONE); // turn to the right
        if (player.getState() != 2) {
            sound.playSound(2);
            player.setState(1);
        }
        moveFigure(10,0); // move to the right
        if (player.getJumpHeight() == 0)
            player.setCurrRun(player.getCurrRun() + .3);
    }
    else {
        player.setCurrRun(0); // reset frame count
    }
}

void Master::checkKeyPress() {
    SDL_Event e; // store key pressed
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            Quit = true;
        else if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_UP: 
                    player.setState(2); // jump
                    if (player.getJumpHeight() == 0) // if not already jumping
                        player.setJumpDir(-1); // start moving upwards
                    break;
                case SDLK_SPACE:
                    player.setState(5); // punch
                    break;
                case SDLK_RETURN:
                    player.setState(6); // kick
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

int Master::moveFigure(double chX, double chY, bool move) {
    player.setXPos(player.getXPos() + chX);
    player.setYPos(player.getYPos() + chY);

    // check for/respond to collision
    int hasCollided = checkCollision();
    while(hasCollided){ // hasCollided: 1 = topleft; 2 = topright; 3 = right; 4 = left; 0 = no collide
        fixCollision(hasCollided);
        hasCollided = checkCollision();
    }

    int notOnGround = checkGround();
    if (player.getJumpHeight() == 0) { // not jumping
        // ensure player is on ground
        if (notOnGround) { // continue until player hits ground or edge of board
            if (player.getState() != 1)
                player.setState(2); // draw falling figure

            if (notOnGround == 1) { // is in air
                if (move == true)
                    player.setYPos(player.getYPos() + 5); // shift player down (falling)
                notOnGround = checkGround();
                if (!notOnGround)
                    sound.playSound(1);
            }
            else { // is in the ground
                if (move == true)
                    player.setYPos(player.getYPos() - 2); // shift player up (rising)
                notOnGround = checkGround();
            } 
        }
    }

    if (move == false) { // if not actually moving the character
        player.setXPos(player.getXPos() - chX);
        player.setYPos(player.getYPos() - chY);
    }
    else {
        if (player.getXPos() > levels.getLevelWidth() - 75) { // overstep right boundary
            if (levels.getCurrLevel() < 3) // if in first or second level
                NextLevel = true; // move to next level when hit end
            else
                player.setXPos(levels.getLevelWidth()  - 75); // fix overstep
        }
        else if (player.getXPos() < 0) // overstep left boundary
            player.setXPos(0);

        if (player.getYPos() > levels.getLevelHeight()) { // overstep bottom boundary
            reset();
        }
        else if (player.getYPos() < 0) // overstep top boundary
            player.setYPos(0);
        updateCamera();
    }
    return notOnGround;
}

int Master::checkCollision() {
    // compare current player image to foreground and detect collision/collision type
    // return values: 1 = topleft; 2 = topright; 3 = right; 4 = left; 0 = no collide
    int boundingH = 94, boundingW = 75; // height and width of player image
    Uint8 playerAlpha, alpha; // store alpha levels 
    Uint32 playerPixel, pixel; // store current pixel for for loop

    // access current frame value within texture (or access only frame)
    double frame = 0; // current frame in sprite
    switch (player.getState()) {
        case 1: // running
            frame = player.getCurrRun();
            break;
        case 4: // rolling
            frame = player.getCurrRoll();
            break;
        case 5: // punching
            frame = player.getCurrPunch();
            break;
        default: // standing, jumping, ducking
            break;
    }

    // set bound for collisions check
    int leftEdge = int(frame)*boundingW;
    SDL_RendererFlip MoveDir = player.getMoveDir();

    Texture * playerTex = player.getTexture(player.getState());

    // loops through bounding box of the player, compares alpha of both char and player
    int playerXPos = player.getXPos(), playerYPos = player.getYPos();
    for(int y = 2*boundingH/3; y > 0; y--) { 
        for(int x = boundingW; x > 0; x--) { 
            //get current player pixel 
            if(MoveDir == SDL_FLIP_HORIZONTAL) //if facing left
                playerPixel = playerTex->getPixel(leftEdge+boundingH-x,y);
            else 
                playerPixel = playerTex->getPixel(leftEdge+x,y); // access current pixel
            // access alpha value of pixel (i.e. transparency)
            playerAlpha = playerTex->getAlpha(playerPixel); 
            
            if (int(playerAlpha) > 10) { //if player is present, check for overlap with foreground
                //get foreground pixel
                if (MoveDir == SDL_FLIP_HORIZONTAL) //facing left
                    pixel = levels.getForeground()->getPixel(playerXPos+boundingH-x, playerYPos+y);
                else //facing right
                    pixel = levels.getForeground()->getPixel(playerXPos+x, playerYPos+y);
                // check foreground transparency
                alpha = levels.getForeground()->getAlpha(pixel);
                if (int(alpha) > 10) { // collision
                    if (y < boundingH/6)// top
                        return 1;
                    if (MoveDir == SDL_FLIP_HORIZONTAL){ //return response for left facing player
                        if (x < boundingW/2) //right col
                            return 2;
                        else //left col
                            return 3;
                    }
                    else { //return response for right facing player
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

void Master::fixCollision(int collisionType){
    // return values: 1 = topleft; 2 = topright; 3 = right; 4 = left;
    if (collisionType == 3) { // left side
        player.setXPos(player.getXPos() + 5); // kick to the right
    }
    else if (collisionType == 2) { // right
        player.setXPos(player.getXPos() - 5); // kick to the left
    }
    else { // top
        if (levels.getCurrLevel() == 1)
            reset();
        else
            player.setYPos(player.getYPos() + 5); // move player back down
    }
}

int Master::checkGround() {
    // get value of pixel at current position of player on foreground
    Uint32 pixel, abovePixel;
    pixel = levels.getForeground()->getPixel(player.getXPos()+40,player.getYPos()+93);
    abovePixel = levels.getForeground()->getPixel(player.getXPos()+40,player.getYPos()+90);
    
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
