/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The application time based timer
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

//The character that will move around on the screen
class Character
{
    public:
		//The dimensions of the character
		static const int CHAR_WIDTH =  100;
		static const int CHAR_HEIGHT = 100;

		//Maximum axis velocity of the character
		static const int CHAR_VEL = 6;

		//Initializes the variables
		Character();

		//Takes key presses and adjusts the character's velocity
		void handleEvent( SDL_Event& e );

		//Moves the character
        void move();
        void run_left();

		//Shows the character on the screen
		void render(int frame);

    private:
		//The X and Y offsets of the character
		int mPosX, mPosY;

		//The velocity of the character
		int mVelX, mVelY;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Walking animation textures
const int WALKING_ANIMATION_FRAMES = 9;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


Character::Character()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 380;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Character::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= CHAR_VEL; break;
            case SDLK_DOWN: mVelY += CHAR_VEL; break;
            case SDLK_LEFT: mVelX -= CHAR_VEL; break;
            case SDLK_RIGHT: mVelX += CHAR_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += CHAR_VEL; break;
            case SDLK_DOWN: mVelY -= CHAR_VEL; break;
            case SDLK_LEFT: mVelX += CHAR_VEL; break;
            case SDLK_RIGHT: mVelX -= CHAR_VEL; break;
        }
    }
}

void Character::move()
{
    //Move the character left or right
    mPosX += mVelX;

    //If the character went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + CHAR_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    /*Move the character up or down
    mPosY += mVelY;

    //If the character went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + CHAR_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
    */
}

void Character::render(int frame)
{

	//Render current frame
	SDL_Rect* currentClip = &gSpriteClips[ frame / 6]; //!!! /6
	
    gSpriteSheetTexture.render( mPosX, mPosY, currentClip );


}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "/Users/kbarlock/Documents/FundCompII/lab78/Deliverable/neku.png" ) )
    {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else
    {
        const int CLIP_W = 100;
        const int CLIP_H = 100;
        
        //note: using fourth row of neku.png
        
        //Set sprite clips
        gSpriteClips[ 1 ].x = CLIP_W;
        gSpriteClips[ 1 ].y = 321;
        gSpriteClips[ 1 ].w = CLIP_W;
        gSpriteClips[ 1 ].h = CLIP_H;
        
        gSpriteClips[ 2 ].x = CLIP_W*2;
        gSpriteClips[ 2 ].y = 321;
        gSpriteClips[ 2 ].w = CLIP_W;
        gSpriteClips[ 2 ].h = CLIP_H;
        
        gSpriteClips[ 3 ].x = CLIP_W*3;
        gSpriteClips[ 3 ].y = 321;
        gSpriteClips[ 3 ].w = CLIP_W;
        gSpriteClips[ 3 ].h = CLIP_H;
        
        gSpriteClips[ 4 ].x = CLIP_W*4;
        gSpriteClips[ 4 ].y = 321;
        gSpriteClips[ 4 ].w = CLIP_W;
        gSpriteClips[ 4 ].h = CLIP_H;
        
        gSpriteClips[ 5 ].x = CLIP_W*5;
        gSpriteClips[ 5 ].y = 321;
        gSpriteClips[ 5 ].w = CLIP_W;
        gSpriteClips[ 5 ].h = CLIP_H;
        
        gSpriteClips[ 6 ].x = CLIP_W*6;
        gSpriteClips[ 6 ].y = 321;
        gSpriteClips[ 6 ].w = CLIP_W;
        gSpriteClips[ 6 ].h = CLIP_H;
        
        gSpriteClips[ 7 ].x = CLIP_W*7;
        gSpriteClips[ 7 ].y = 321;
        gSpriteClips[ 7 ].w = CLIP_W;
        gSpriteClips[ 7 ].h = CLIP_H;
        
        gSpriteClips[ 8 ].x = CLIP_W*8;
        gSpriteClips[ 8 ].y = 321;
        gSpriteClips[ 8 ].w = CLIP_W;
        gSpriteClips[ 8 ].h = CLIP_H;
        
        //standing still clip:
        gSpriteClips[ 0 ].x = 0;
        gSpriteClips[ 0 ].y = 321;
        gSpriteClips[ 0 ].w = CLIP_W;
        gSpriteClips[ 0 ].h = CLIP_H;
        
    }
    
    return success;
}

void close()
{
    //Free loaded images
    gSpriteSheetTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
            
            //Current animation frame
            int frame = 0;

			//The character that will be moving around on the screen
			Character character;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the character
					character.handleEvent( e );
				}

				//Move the character
                
                //if moving left, increment frame
                if ( e.key.keysym.sym == SDLK_LEFT && e.type == SDL_KEYDOWN ) ++frame;
                // if moving right, decrement frame
                if ( e.key.keysym.sym == SDLK_RIGHT && e.type == SDL_KEYDOWN) --frame;
                // if standing still, go to standing frame
                if ( e.type == SDL_KEYUP ) frame = 0;
                
				character.move();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render objects
				character.render(frame);

				//Update screen
				SDL_RenderPresent( gRenderer );
                
                
                //Cycle animation
                if( e.type == SDL_KEYDOWN && frame / 6 >= WALKING_ANIMATION_FRAMES ){ //cycle forwards (left) running
                    frame = 6;
                }
                else if ( e.type == SDL_KEYDOWN && frame < 6 ){ //cycle backwards (right) running
                    frame = 48;
                }
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}