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
const UINT GAME_WIDTH =  1152;               // width of game in pixels
const UINT GAME_HEIGHT = 672;               // height of game in pixels

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
const char FOREST_1_IMAGE[] = "pictures\\Forest1.png";
const char FOREST_2_IMAGE[] = "pictures\\Forest2.png";
const char FOREST_3_IMAGE[] = "pictures\\Forest3.png";
const char FOREST_4_IMAGE[] = "pictures\\Forest4.png";
const char CAPTURE_POINT_1[] = "pictures\\capturePoint1.png";
const char CAPTURE_POINT_2[] = "pictures\\capturePoint2.png";
const char BACKGROUND_IMAGE[] = "pictures\\background.PNG";

const int TERRAIN_WIDTH = 96;
const int TERRAIN_HEIGHT = 96;
const int TERRAIN_SCALE = 1;
const float BACKGROUND_IMAGE_SCALE = 1.0f;

const char DUST_IMAGE[] = "pictures\\DustParticle3.png";

const float MAX_PARTICLE_LIFETIME = 1.5f;
const int MAX_NUMBER_PARTICLES = 2000;

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
const char BACKGROUND_MUSIC[] = "backGroundMusic";
const char ARCHER_ATTACK[] = "arrowShot";
const char BERSERKER_ATTACK[] = "swordSlash2";
const char CAVALRY_ATTACK[] = "swordSlice";
const char HUSSAR_ATTACK[] = "swordSlice";
const char INFANTRY_ATTACK[] = "swordSlash";
const char BERSERKER_MOVE[] = "running";
const char CAVALRY_MOVE[] = "horseGalloping";
const char HUSSAR_MOVE[] = "horseGalloping";
const char INFANTRY_MOVE[] = "running";
const char BERSERKER_BATTLECRY[] = "annoyingYell";

enum TerrainTypeEnum {Plains, Hills, Forest, CapturePoint};
enum Country {Norse, Poland, Britain};

#pragma region Newell
const float INFANTRY_SCALING = 1;
const float INFANTRY_ANIMATION_DELAY = 0.1;
const float INFANTRY_SPEED = 100;
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
const int INFANTRY_DEATH_UP_END = 131;
const int INFANTRY_DEATH_DOWN_START = 132;
const int INFANTRY_DEATH_DOWN_END = 141;
const int INFANTRY_DEATH_LEFT_START = 142;
const int INFANTRY_DEATH_LEFT_END = 151;

const float SELECTION_BOX_SCALE = 1;
#pragma endregion

#pragma region Higgs
const float BERSERKER_SCALING = 1;
const float BERSERKER_ANIMATION_DELAY = 0.1;
const float BERSERKER_SPEED = 100;
const int BERSERKER_ATTACK_RIGHT_START = 0;
const int BERSERKER_ATTACK_RIGHT_END = 9;
const int BERSERKER_ATTACK_UP_START = 10;
const int BERSERKER_ATTACK_UP_END  = 19;
const int BERSERKER_ATTACK_DOWN_START = 20;
const int BERSERKER_ATTACK_DOWN_END = 29;
const int BERSERKER_ATTACK_LEFT_START = 30;
const int BERSERKER_ATTACK_LEFT_END = 39;
const int BERSERKER_IDLE_RIGHT_START = 40;
const int BERSERKER_IDLE_RIGHT_END = 47;
const int BERSERKER_IDLE_UP_START = 48;
const int BERSERKER_IDLE_UP_END = 55;
const int BERSERKER_IDLE_DOWN_START = 56;
const int BERSERKER_IDLE_DOWN_END = 63;
const int BERSERKER_IDLE_LEFT_START = 64;
const int BERSERKER_IDLE_LEFT_END = 71;
const int BERSERKER_RUN_RIGHT_START = 72;
const int BERSERKER_RUN_RIGHT_END = 79;
const int BERSERKER_RUN_UP_START = 80;
const int BERSERKER_RUN_UP_END = 87;
const int BERSERKER_RUN_DOWN_START = 88;
const int BERSERKER_RUN_DOWN_END = 95;
const int BERSERKER_RUN_LEFT_START = 96;
const int BERSERKER_RUN_LEFT_END = 103;
const int BERSERKER_DEATH_RIGHT_START = 104;
const int BERSERKER_DEATH_RIGHT_END = 114;
const int BERSERKER_DEATH_UP_START = 115;
const int BERSERKER_DEATH_UP_END = 1125;
const int BERSERKER_DEATH_DOWN_START = 126;
const int BERSERKER_DEATH_DOWN_END = 136;
const int BERSERKER_DEATH_LEFT_START = 137;
const int BERSERKER_DEATH_LEFT_END = 147;

#pragma endregion

#pragma region Newell
const float CAVALRY_SCALING = 0.66666;
const float CAVALRY_ANIMATION_DELAY = 0.15;
const float CAVALRY_SPEED = 120;
const int CAVALRY_RUN_RIGHT_START = 0;
const int CAVALRY_RUN_RIGHT_END = 11;
const int CAVALRY_RUN_UP_START = 12;
const int CAVALRY_RUN_UP_END  = 23;
const int CAVALRY_RUN_DOWN_START = 24;
const int CAVALRY_RUN_DOWN_END = 35;
const int CAVALRY_RUN_LEFT_START = 36;
const int CAVALRY_RUN_LEFT_END = 47;
const int CAVALRY_IDLE_RIGHT_START = 48;
const int CAVALRY_IDLE_RIGHT_END = 59;
const int CAVALRY_IDLE_UP_START = 60;
const int CAVALRY_IDLE_UP_END = 71;
const int CAVALRY_IDLE_DOWN_START = 72;
const int CAVALRY_IDLE_DOWN_END = 83;
const int CAVALRY_IDLE_LEFT_START = 84;
const int CAVALRY_IDLE_LEFT_END = 95;
const int CAVALRY_ATTACK_RIGHT_START = 96;
const int CAVALRY_ATTACK_RIGHT_END = 103;
const int CAVALRY_ATTACK_UP_START = 104;
const int CAVALRY_ATTACK_UP_END = 111;
const int CAVALRY_ATTACK_DOWN_START = 112;
const int CAVALRY_ATTACK_DOWN_END = 119;
const int CAVALRY_ATTACK_LEFT_START = 120;
const int CAVALRY_ATTACK_LEFT_END = 127;
const int CAVALRY_DEATH_RIGHT_START = 128;
const int CAVALRY_DEATH_RIGHT_END = 133;
const int CAVALRY_DEATH_UP_START = 134;
const int CAVALRY_DEATH_UP_END = 139;
const int CAVALRY_DEATH_DOWN_START = 140;
const int CAVALRY_DEATH_DOWN_END = 145;
const int CAVALRY_DEATH_LEFT_START = 146;
const int CAVALRY_DEATH_LEFT_END = 151;
#pragma endregion

#pragma region Higgs
const float HUSSAR_SCALING = 0.66666f;
const float HUSSAR_ANIMATION_DELAY = 0.1f;
const float HUSSAR_SPEED = 120;
const int HUSSAR_RUN_RIGHT_START = 0;
const int HUSSAR_RUN_RIGHT_END = 11;
const int HUSSAR_RUN_UP_START = 12;
const int HUSSAR_RUN_UP_END  = 23;
const int HUSSAR_RUN_DOWN_START = 24;
const int HUSSAR_RUN_DOWN_END = 35;
const int HUSSAR_RUN_LEFT_START = 36;
const int HUSSAR_RUN_LEFT_END = 47;
const int HUSSAR_IDLE_RIGHT_START = 48;
const int HUSSAR_IDLE_RIGHT_END = 59;
const int HUSSAR_IDLE_UP_START = 60;
const int HUSSAR_IDLE_UP_END = 71;
const int HUSSAR_IDLE_DOWN_START = 72;
const int HUSSAR_IDLE_DOWN_END = 83;
const int HUSSAR_IDLE_LEFT_START = 84;
const int HUSSAR_IDLE_LEFT_END = 95;
const int HUSSAR_ATTACK_RIGHT_START = 96;
const int HUSSAR_ATTACK_RIGHT_END = 103;
const int HUSSAR_ATTACK_UP_START = 104;
const int HUSSAR_ATTACK_UP_END = 111;
const int HUSSAR_ATTACK_DOWN_START = 112;
const int HUSSAR_ATTACK_DOWN_END = 119;
const int HUSSAR_ATTACK_LEFT_START = 120;
const int HUSSAR_ATTACK_LEFT_END = 127;
const int HUSSAR_DEATH_RIGHT_START = 128;
const int HUSSAR_DEATH_RIGHT_END = 133;
const int HUSSAR_DEATH_UP_START = 134;
const int HUSSAR_DEATH_UP_END = 139;
const int HUSSAR_DEATH_DOWN_START = 140;
const int HUSSAR_DEATH_DOWN_END = 145;
const int HUSSAR_DEATH_LEFT_START = 146;
const int HUSSAR_DEATH_LEFT_END = 151;

#pragma region Newell
const float ARCHER_SCALING = 1;
const float ARCHER_ANIMATION_DELAY = 0.1;
const float ARCHER_SPEED = 100;
const int ARCHER_IDLE_RIGHT_START = 0;
const int ARCHER_IDLE_RIGHT_END = 8;
const int ARCHER_IDLE_UP_START = 9;
const int ARCHER_IDLE_UP_END = 17;
const int ARCHER_IDLE_DOWN_START = 18;
const int ARCHER_IDLE_DOWN_END = 26;
const int ARCHER_IDLE_LEFT_START = 27;
const int ARCHER_IDLE_LEFT_END = 35;
const int ARCHER_RUN_RIGHT_START = 36;
const int ARCHER_RUN_RIGHT_END = 43;
const int ARCHER_RUN_UP_START = 44;
const int ARCHER_RUN_UP_END = 51;
const int ARCHER_RUN_DOWN_START = 52;
const int ARCHER_RUN_DOWN_END = 59;
const int ARCHER_RUN_LEFT_START = 60;
const int ARCHER_RUN_LEFT_END = 67;
const int ARCHER_ATTACK_RIGHT_START = 68;
const int ARCHER_ATTACK_RIGHT_END = 80;
const int ARCHER_ATTACK_UP_START = 81;
const int ARCHER_ATTACK_UP_END  = 93;
const int ARCHER_ATTACK_DOWN_START = 94;
const int ARCHER_ATTACK_DOWN_END = 106;
const int ARCHER_ATTACK_LEFT_START = 107;
const int ARCHER_ATTACK_LEFT_END = 119;
const int ARCHER_DEATH_RIGHT_START = 120;
const int ARCHER_DEATH_RIGHT_END = 132;
const int ARCHER_DEATH_UP_START = 133;
const int ARCHER_DEATH_UP_END = 145;
const int ARCHER_DEATH_DOWN_START = 146;
const int ARCHER_DEATH_DOWN_END = 158;
const int ARCHER_DEATH_LEFT_START = 159;
const int ARCHER_DEATH_LEFT_END = 171;

const float LONGBOWMAN_SCALING = 1;
const float LONGBOWMAN_ANIMATION_DELAY = 0.1;
const float LONGBOWMAN_SPEED = 100;
const int LONGBOWMAN_IDLE_RIGHT_START = 0;
const int LONGBOWMAN_IDLE_RIGHT_END = 12;
const int LONGBOWMAN_IDLE_UP_START = 13;
const int LONGBOWMAN_IDLE_UP_END = 25;
const int LONGBOWMAN_IDLE_DOWN_START = 26;
const int LONGBOWMAN_IDLE_DOWN_END = 38;
const int LONGBOWMAN_IDLE_LEFT_START = 39;
const int LONGBOWMAN_IDLE_LEFT_END = 51;
const int LONGBOWMAN_RUN_RIGHT_START = 52;
const int LONGBOWMAN_RUN_RIGHT_END = 59;
const int LONGBOWMAN_RUN_UP_START = 60;
const int LONGBOWMAN_RUN_UP_END = 67;
const int LONGBOWMAN_RUN_DOWN_START = 68;
const int LONGBOWMAN_RUN_DOWN_END = 75;
const int LONGBOWMAN_RUN_LEFT_START = 76;
const int LONGBOWMAN_RUN_LEFT_END = 83;
const int LONGBOWMAN_ATTACK_RIGHT_START = 84;
const int LONGBOWMAN_ATTACK_RIGHT_END = 96;
const int LONGBOWMAN_ATTACK_UP_START = 97;
const int LONGBOWMAN_ATTACK_UP_END  = 109;
const int LONGBOWMAN_ATTACK_DOWN_START = 110;
const int LONGBOWMAN_ATTACK_DOWN_END = 122;
const int LONGBOWMAN_ATTACK_LEFT_START = 123;
const int LONGBOWMAN_ATTACK_LEFT_END = 135;
const int LONGBOWMAN_DEATH_RIGHT_START = 136;
const int LONGBOWMAN_DEATH_RIGHT_END = 146;
const int LONGBOWMAN_DEATH_UP_START = 147;
const int LONGBOWMAN_DEATH_UP_END = 157;
const int LONGBOWMAN_DEATH_DOWN_START = 158;
const int LONGBOWMAN_DEATH_DOWN_END = 168;
const int LONGBOWMAN_DEATH_LEFT_START = 169;
const int LONGBOWMAN_DEATH_LEFT_END = 179;
#pragma endregion

#endif
