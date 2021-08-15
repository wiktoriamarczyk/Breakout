#pragma once
#include "GameObject.h"
#include "Ball.h"


class Brick : public GameObject
{
public:
    Brick(float BrickCenterPosX, float BrickCenterPosY, shared_ptr<Ball> MyBall);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* m_pRenderer)override;
    static int m_NumOfPoints;

private:
    int m_BrickID = 0;
    static int m_NumOfBricks;
    Color m_BrickColor;
    shared_ptr<Ball> m_Ball;
    string m_SoundName;
};

