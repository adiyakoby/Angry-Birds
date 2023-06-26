#pragma once
#include <array>

//usings:
using arrData = std::array<int, 3>;

//Const variables for window size:


const int MAX_LEVEL = 6;

//original is 1400 800
const unsigned int WINDOW_WIDTH = 1400;
const unsigned int WINDOW_HEIGHT = 800;

const float SCALE = 100.0f; // Scale factor between Box2D and SFML
const float MAX_DISTANCE = 150.f;


//enum classes
enum class menuCommand { PLAY, HELP, EXIT, BACK, SOUND, MUTE, DEFAULT };
enum class helpScreenCommand { BACK, SOUND, MUTE, DEFAULT };
enum class GameData {LEVEL, SCORE}; //Game Data - (level num , Score) //maybe after creating the level state it will not needed any more 
enum class musicCommand {PLAY,PAUSE};
enum class gameSounds {BACKGROUND,WOOD_CRASH,IRON_CRASH,ICE_CRASH,PIG_CRASH};
/* POSITIONS :*/
const float ROGATKA_X{ 300.f };
const float ROGATKA_Y{ 630.f };
const float BLUE_BIRDS_DISTANCE = 100.f;
const float BLUE_BIRD_SPLIT_RADIUS = 15.f;
const float BOMB_SIZE = 15.f;
const float BOMB_DISTANCE = 500.f;

// Game Score
const int ICE_SCORE = 5;
const int WOOD_SCORE = 10;
const int IRON_SCORE = 15;
const int PIG_SCORE = 20;

// Obstacles HP :
const int IRON_HP = 400;
const int WOOD_HP = 200;
const int ICE_HP = 100;
const int PIG_HP = 100;
const int BIRD_HP = 20;

