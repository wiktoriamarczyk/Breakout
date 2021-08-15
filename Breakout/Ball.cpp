#include "Ball.h"
#include "Engine.h"


int Ball::m_NumOfLives = NUM_OF_BALL_LIVES;

void Ball::InitializeBall(int BallCenterPosX, int BallCenterPosY)
{
    m_ObjectCenterPos.x = float(BallCenterPosX);
    m_ObjectCenterPos.y = float(BallCenterPosY);

    //m_BallSpeed = float(BALL_SPEED);
    m_ObjectSize.x = float(BALL_SIZE);
    m_ObjectSize.y = float(BALL_SIZE);

    vec2 Direction(1, 1);
    m_BallDirection = Direction.GetNormalized();
}

void Ball::Update(float DeltaTime)
{
    float FrameDistance = m_BallSpeed * DeltaTime;
    vec2 FrameDistanceIn2D = m_BallDirection * FrameDistance;
    vec2 NewCenterPosition = m_ObjectCenterPos + FrameDistanceIn2D;

    SetBallDirectionLine(m_ObjectCenterPos, NewCenterPosition);

    m_ObjectCenterPos = NewCenterPosition;

    //----------KOLIZJA Z SUFITEM ORAZ SCIANAMI----------

    if (m_ObjectCenterPos.y <= 0)
    {
        m_BallDirection.y = -m_BallDirection.y;
        Engine::GetSingleton()->PlaySound("wall_sound.wav");
    }
    if (m_ObjectCenterPos.x >= SCREEN_WIDTH)
    {
        m_BallDirection.x = -m_BallDirection.x;
        Engine::GetSingleton()->PlaySound("wall_sound.wav");
    }
    if (m_ObjectCenterPos.x <= 0)
    {
        m_BallDirection.x = -m_BallDirection.x;
        Engine::GetSingleton()->PlaySound("wall_sound.wav");
    }

    //----------BRAK KOLIZJI Z PALETKA----------
    // jesli nie trafimy w paletke, tracimy zycie i pilka spawnuje sie jeszcze raz

    if (m_ObjectCenterPos.y >= SCREEN_HEIGHT - 50 + PADDLE_HEIGHT)
    {
        m_BallSpeed = 10.0;
        m_ObjectCenterPos.x = SCREEN_WIDTH / 2;
        m_ObjectCenterPos.y = SCREEN_HEIGHT - 200;
        m_SlowMotionTimer = 2.0f;
        m_NumOfLives--;
    }

    if (m_SlowMotionTimer >= 0)
    {
        m_BallSpeed = 10.0;
        m_SlowMotionTimer = m_SlowMotionTimer - DeltaTime;
    }

    if (m_SlowMotionTimer <= 0)
    {
        m_BallSpeed = BALL_SPEED;
        m_SlowMotionTimer = 0.0f;
    }

    // pilka bedzie przyspieszac z czasem
    m_BallSpeed = m_BallSpeed + m_Acceleration * DeltaTime;

}

void Ball::Render(SDL_Renderer* pRenderer)
{
    vec2 BallTopLeftCorner = m_ObjectCenterPos - m_ObjectSize / 2;

    SDL_Rect BallDrawRect;
    BallDrawRect.x = (int)BallTopLeftCorner.x;
    BallDrawRect.y = (int)BallTopLeftCorner.y;
    BallDrawRect.w = (int)m_ObjectSize.x;
    BallDrawRect.h = (int)m_ObjectSize.y;

    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(pRenderer, &BallDrawRect);
}

// OldPos - punkt P1(x1, y1) poprzedniej pozycji pilki 
// NewPos - punkt P2(x2, y2) nastepnej pozycji pilki po przemieszczeniu 
void Ball::SetBallDirectionLine(vec2 OldPos, vec2 NewPos)
{
    // y = ax + b
    //obliczenie wspolczynnika kierunkowego a = (y2-y1)/(x2-x1)
    m_BallDirLine.a = (OldPos.y - NewPos.y) / (OldPos.x - NewPos.x);
    // b = y - ax
    m_BallDirLine.b = OldPos.y - m_BallDirLine.a * OldPos.x;
}

Line Ball::GetBallDirectionLine()
{
    return m_BallDirLine;
}

void Ball::ReverseDirectionY()
{
    m_BallDirection.y = -m_BallDirection.y;
}

void Ball::ReverseDirectionX()
{
    m_BallDirection.x = -m_BallDirection.x;
}

// zmiana kierunku pilki w zaleznosci od tego, czy paletka sie poruszala w momencie jej odbicia
void Ball::ModifyBallDirection(vec2 Other, float DeltaTime)
{
    m_BallDirection = ((m_BallDirection * BALL_SPEED * DeltaTime) + Other*0.5).GetNormalized();
}
