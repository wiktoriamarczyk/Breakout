#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<memory>
#include<SDL.h>
#include<SDL_Mixer.h>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::move;
using std::string;
using std::fstream;
using namespace std::string_literals;


constexpr int BRICK_SPACING = 4;

enum : int
{
    SCREEN_WIDTH = 800,
    SCREEN_HEIGHT = 600,

    BALL_SIZE = 10,
    BALL_SPEED = 300,
    NUM_OF_BALL_LIVES = 3,

    PADDLE_WIDTH = 100,
    PADDLE_HEIGHT = 20,
    PADDLE_SPEED = 800,

};

enum class eStateID
{
    UNKNOWN = 0,
    INGAME = 1,
    VICTORY = 2,
};

struct Color
{
    char R = char(255);
    char G = char(255);
    char B = char(255);
};

// y = ax + b
struct Line
{
    float a = 0.0f;    // a - WSPOLCZYNNIK KIERUNKOWY PROSTEJ 
    float b = 0.0f;    // b - WYRAZ WOLNY PROSTEJ
};

bool SDL_IsKeyPressed(SDL_Scancode Code);