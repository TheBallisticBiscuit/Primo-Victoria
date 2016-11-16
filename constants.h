// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.1

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "Collisions";
const char GAME_TITLE[] = "Primo Victoria";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const RECT  COLLISION_RECTANGLE = {-30,-16,30,16};
const RECT  COLLISION_BOX_PADDLE = {-45,-10,45,10};
const RECT COLLISION_BOX_PUCK = {-32, -32, 32, 32};
const float   COLLISION_RADIUS = 29;

#pragma region Higgs
// graphic images
const char TEMP_GRASS[] =	"pictures\\Grass.png";
const char GRASS_1_IMAGE[] = "pictures\\Grass1.png";
const char GRASS_2_IMAGE[] = "pictures\\Grass2.png";
const char GRASS_3_IMAGE[] = "pictures\\Grass3.png";
const char BACKGROUND_IMAGE[] = "pictures\\background.PNG";

const int TERRAIN_WIDTH = 96;
const int TERRAIN_HEIGHT = 96;
const int TERRAIN_SCALE = 1;

#pragma endregion
// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR PADDLE_LEFT    = VK_LEFT;     // left arrow
const UCHAR PADDLE_RIGHT   = VK_RIGHT;    // right arrow
const UCHAR ENTER_KEY    = VK_RETURN; 

//

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\WavesExample1.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\SoundsExample1.xsb";

// audio cues
const char BEEP1[] = "beep1";
const char BEEP2[] = "beep2";
const char BEEP3[] = "beep3";
const char BEEP4[] = "beep4";
const char HIT[]   = "hit";

enum TerrainTypeEnum {Plains, Hills, Forest};


#pragma region Newell
const float INFANTRY_SCALING = 1;
const float INFANTRY_ANIMATION_DELAY = 0.1;
const int INFANTRY_ATTACK_RIGHT_START = 0;
const int INFANTRY_ATTACK_RIGHT_END = 11;
const int INFANTRY_ATTACK_UP_START = 12;
const int INFANTRY_ATTACK_UP_END  = 23;
const int INFANTRY_ATTACK_DOWN_START = 24;
const int INFANTRY_ATTACK_DOWN_END = 35;
const int INFANTRY_ATTACK_LEFT_START = 36;
const int INFANTRY_ATTACK_LEFT_END = 47;
const int INFANTRY_RUN_RIGHT_START = 48;
const int INFANTRY_RUN_RIGHT_END = 55;
const int INFANTRY_RUN_UP_START = 56;
const int INFANTRY_RUN_UP_END = 63;
const int INFANTRY_RUN_DOWN_START = 64;
const int INFANTRY_RUN_DOWN_END = 71;
const int INFANTRY_RUN_LEFT_START = 72;
const int INFANTRY_RUN_LEFT_END = 79;
const int INFANTRY_IDLE_RIGHT_START = 80;
const int INFANTRY_IDLE_RIGHT_END = 88;
const int INFANTRY_IDLE_UP_START = 89;
const int INFANTRY_IDLE_UP_END = 97;
const int INFANTRY_IDLE_DOWN_START = 98;
const int INFANTRY_IDLE_DOWN_END = 106;
const int INFANTRY_IDLE_LEFT_START = 107;
const int INFANTRY_IDLE_LEFT_END = 115;
const int INFANTRY_DEATH_RIGHT_START = 116;
const int INFANTRY_DEATH_RIGHT_END = 121;
const int INFANTRY_DEATH_UP_START = 122;
const int INFANTRY_DEATH_UP_END = 127;
const int INFANTRY_DEATH_DOWN_START = 128;
const int INFANTRY_DEATH_DOWN_END = 133;
const int INFANTRY_DEATH_LEFT_START = 134;
const int INFANTRY_DEATH_LEFT_END = 139;

const float SELECTION_BOX_SCALE = 1;
#pragma endregion
#endif
