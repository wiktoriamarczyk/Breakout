#pragma once
#include "GameObject.h"
#include "Ball.h"


class Paddle : public GameObject
{
public:
    Paddle(shared_ptr<Ball> MyBall);
    void InitializePaddle(int PaddleCenterPosX, int PaddleCenterPosY, SDL_Scancode Up, SDL_Scancode Down);
    vec2 ReturnPos()const;
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;

private:
    float m_PaddleSpeed = 0.0;
    SDL_Scancode m_KeyToUp = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode m_KeyToDown = SDL_SCANCODE_UNKNOWN;
    shared_ptr<Ball> m_Ball;
};

