#pragma once
#include "GameObject.h"


class Ball : public GameObject
{
public:
    void InitializeBall(int BallCenterPosX, int BallCenterPosY);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void SetBallDirectionLine(vec2 OldPos, vec2 NewPos);
    Line GetBallDirectionLine();
    void ReverseDirectionY();
    void ReverseDirectionX();
    void ModifyBallDirection(vec2 Other, float DeltaTime);
private:
    vec2 m_BallDirection;
    float m_BallSpeed = BALL_SPEED;
    bool m_BallStatus = false;
    Line m_BallDirLine;
    float m_Acceleration = 3.0f;
    float m_SlowmotionTimer = 0.0f;
};

