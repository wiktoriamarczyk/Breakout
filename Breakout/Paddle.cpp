#include "Paddle.h"
#include "Engine.h"


bool AreFloatsEqual(float A, float B)
{
    float Epsilon = 1;
    return fabs(B - A) <= Epsilon;
}


Paddle::Paddle(shared_ptr<Ball> MyBall)
{
    m_Ball = MyBall;
}

void Paddle::InitializePaddle(int PaddleCenterPosX, int PaddleCenterPosY, SDL_Scancode Left, SDL_Scancode Right)
{
    m_ObjectCenterPos.x = float(PaddleCenterPosX);
    m_ObjectCenterPos.y = float(PaddleCenterPosY);

    m_KeyToLeft = Left;
    m_KeyToRight = Right;

    m_ObjectSize.x = float(PADDLE_WIDTH);
    m_ObjectSize.y = float(PADDLE_HEIGHT);
    m_PaddleSpeed = float(PADDLE_SPEED);
}

vec2 Paddle::ReturnPos()const
{
    return m_ObjectCenterPos;
}

void Paddle::Render(SDL_Renderer* pRenderer)
{
    vec2 PaddleTopLeftCorner = m_ObjectCenterPos - m_ObjectSize / 2;

    SDL_Rect PaddleDrawRect{};
    PaddleDrawRect.x = int(PaddleTopLeftCorner.x);
    PaddleDrawRect.y = int(PaddleTopLeftCorner.y);
    PaddleDrawRect.w = int(m_ObjectSize.x);
    PaddleDrawRect.h = int(m_ObjectSize.y);

    SDL_SetRenderDrawColor(pRenderer, 66, 135, 245, 255);
    SDL_RenderFillRect(pRenderer, &PaddleDrawRect);
}

void Paddle::Update(float DeltaTime)
{
    float FrameDistance = m_PaddleSpeed * DeltaTime;

    //----------KOLIZJA ZE SCIANAMI----------

    vec2 PaddleTopLeftCorner = m_ObjectCenterPos - m_ObjectSize / 2;
    if (SDL_IsKeyPressed(m_KeyToLeft) && PaddleTopLeftCorner.x >= 0)
    {
        m_ObjectCenterPos.x -= FrameDistance;
    }

    vec2 PaddleBottomRightCorner = m_ObjectCenterPos + m_ObjectSize / 2;
    if (SDL_IsKeyPressed(m_KeyToRight) && PaddleBottomRightCorner.x <= SCREEN_WIDTH)
    {
        m_ObjectCenterPos.x += FrameDistance;
    }

    //----------KOLIZJA Z PILKA----------
    /*
    _____________________<--- TopLine
    |                     |
    |_____________________|
    ^                     ^
    |                     |
    LeftLine              RightLine
    */

    int PaddleTopLine = PaddleTopLeftCorner.y;
    int PaddleLeftLine = PaddleTopLeftCorner.x;
    int PaddleRightLine = PaddleBottomRightCorner.x;

    // punkt przeciecia prostej TopLine z prosta wyznaczana przez tor lotu pilki 
    vec2 PointOfIntersection;

    // sprawdz czy pilka znajduje sie na plaszczyznie OX w miejscu wystepowania paletki (miedzy LeftLine a RightLine)
    if (m_Ball->GetObjectPos().x >= PaddleLeftLine && m_Ball->GetObjectPos().x <= PaddleRightLine)
    {
        // oblicz wspolrzedne punktu przeciecia
        PointOfIntersection.x = (PaddleTopLine - m_Ball->GetBallDirectionLine().b) / m_Ball->GetBallDirectionLine().a;
        PointOfIntersection.y = PaddleTopLine;

        // w OX paletki juz sie znajdujemy, zatem sprawdz czy wspolrzedna Y polozenia pilki jest rowna Y punktu przeciecia (lub wieksza, jesli pilka znajduje sie juz nieco 'w paletce')
        if (m_Ball->GetObjectPos().y >= PointOfIntersection.y)
        {
            // jesli tak, to przemiesc pilke idealnie w pkt. przeciecia oraz odwroc jej kierunek (odbij od paletki)
            m_Ball->SetObjectPos(PointOfIntersection);
            m_Ball->ReverseDirectionY();
            Engine::GetSingleton()->PlayPaddleSound();

            if (SDL_IsKeyPressed(m_KeyToRight))
            {
                vec2 PaddleDir(PADDLE_SPEED * DeltaTime, 0.0);
                m_Ball->ModifyBallDirection(PaddleDir, DeltaTime);
            }
            if (SDL_IsKeyPressed(m_KeyToLeft))
            {
                vec2 PaddleDir(PADDLE_SPEED * DeltaTime, 0.0);
                m_Ball->ModifyBallDirection(-PaddleDir, DeltaTime);
            }
        }
    }
}