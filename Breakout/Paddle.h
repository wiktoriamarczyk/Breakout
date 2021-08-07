#pragma once
#include "GameObject.h"
#include "Ball.h"


class Paddle : public GameObject
{
public:
    Paddle(shared_ptr<Ball> MyBall);
    void InitializePaddle(int PaddleCenterPosX, int PaddleCenterPosY, SDL_Scancode Left, SDL_Scancode Right);
    vec2 ReturnPos()const;
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;

private:
    float m_PaddleSpeed = 0.0;
    SDL_Scancode m_KeyToLeft = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode m_KeyToRight = SDL_SCANCODE_UNKNOWN;
    shared_ptr<Ball> m_Ball;
};

