#pragma once


//Const variables for window size:

//original is 1400 800
const unsigned int WINDOW_WIDTH = 1400;
const unsigned int WINDOW_HEIGHT = 800;

const float SCALE = 100.0f; // Scale factor between Box2D and SFML
const float MAX_DISTANCE = 150.f;


//enum classes
enum class menuCommand { PLAY, HELP, EXIT, BACK, SOUND, MUTE, DEFAULT };
enum class helpScreenCommand { BACK, SOUND, MUTE, DEFAULT };
enum class GameData {LEVEL, SCORE}; //Game Data - (level num , Score)
/* POSITIONS :*/
const float ROGATKA_X{ 300.f };
const float ROGATKA_Y{ 660.f };



// Game Score
const int WOOD_SCORE = 5;
const int ICE_SCORE = 10;
const int Metal_SCORE = 15;
const int PIG_SCORE = 20;