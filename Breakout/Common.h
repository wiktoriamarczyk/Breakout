#pragma once

#include<iostream>
#include<vector>
#include<memory>
#include<SDL.h>
#include<SDL_Mixer.h>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::move;


constexpr int BRICK_SPACING = 4;

enum : int
{
    SCREEN_WIDTH = 800,
    SCREEN_HEIGHT = 600,

    BALL_SIZE = 10,
    BALL_SPEED = 300,

    PADDLE_WIDTH = 100,
    PADDLE_HEIGHT = 20,
    PADDLE_SPEED = 400,

};

enum class eStateID
{
    UNKNOWN = 0,
    INGAME = 1,
    VICTORY = 2,
};

struct Color
{
    char R = 255;
    char G = 255;
    char B = 255;
};

// y = ax + b
struct Line
{
    float a;    // a - WSPOLCZYNNIK KIERUNKOWY PROSTEJ 
    float b;    // b - WYRAZ WOLNY PROSTEJ
};

bool SDL_IsKeyPressed(SDL_Scancode Code);