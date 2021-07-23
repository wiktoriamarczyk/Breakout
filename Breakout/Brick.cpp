#include "Brick.h"


int Brick::m_NumOfBricks = 0;

constexpr int TABLE_SIZE = 4;

const Color ColorTable[TABLE_SIZE] = { {207, 207, 27}, {36, 105, 25}, {201, 114, 26}, {140, 14, 14} };


Brick::Brick(int BrickCenterPosX, int BrickCenterPosY, shared_ptr<Ball> MyBall)
{
    m_Ball = MyBall;

    m_ObjectCenterPos.x = BrickCenterPosX;
    m_ObjectCenterPos.y = BrickCenterPosY;

    m_ObjectSize.x = float(PADDLE_WIDTH);
    m_ObjectSize.y = float(PADDLE_HEIGHT);

    m_BrickID = m_NumOfBricks;
    m_NumOfBricks++;

    m_BrickColor = ColorTable[(m_BrickID / 16) % TABLE_SIZE];
}

void Brick::Update(float DeltaTime)
{
    vec2 BrickTopLeftCorner = m_ObjectCenterPos - m_ObjectSize / 2;
    vec2 BrickBottomRightCorner = m_ObjectCenterPos + m_ObjectSize / 2;

    int BrickTopLine = BrickTopLeftCorner.y;
    int BrickBottomtLine = BrickBottomRightCorner.y;
    int BrickLeftLine = BrickTopLeftCorner.x;
    int BrickRightLine = BrickBottomRightCorner.x;
    // punkt przeciecia prostej TopLine z prosta wyznaczana przez tor lotu pilki 
    vec2 PointOfIntersection_Up;
    vec2 PointOfIntersection_Bottom;

    // sprawdz czy pilka znajduje sie na plaszczyznie OX w miejscu wystepowania cegly (miedzy LeftLine a RightLine)
    if (m_Ball->GetObjectPos().x >= BrickLeftLine && m_Ball->GetObjectPos().x <= BrickRightLine)
    {
        // oblicz wspolrzedne punktu przeciecia z gorna czescia cegly
        PointOfIntersection_Up.x = (BrickTopLine - m_Ball->GetBallDirectionLine().b) / m_Ball->GetBallDirectionLine().a;
        PointOfIntersection_Up.y = BrickTopLine;

        // jesli pilka znajduje sie nad gorna czescia cegly, to znaczy, ze moze sie z nia zderzyc od gory, jesli nie, to moze sie z nia zderzyc od dolu
        if (m_Ball->GetObjectPos().y <= BrickTopLine)
        {
            // w OX cegly juz sie znajdujemy, zatem sprawdz czy wspolrzedna Y polozenia pilki jest rowna Y punktu przeciecia
            if (m_Ball->GetObjectPos().y >= PointOfIntersection_Up.y)
            {
                // jesli tak, to przemiesc pilke idealnie w pkt. przeciecia oraz odwroc jej kierunek (odbij od paletki)
                m_Ball->SetObjectPos(PointOfIntersection_Up);
                m_Ball->ReverseDirectionY();
            }
        }
        
        // oblicz wspolrzedne punktu przeciecia z dolna czescia cegly
        PointOfIntersection_Bottom.x = (BrickTopLine - m_Ball->GetBallDirectionLine().b) / m_Ball->GetBallDirectionLine().a;
        PointOfIntersection_Bottom.y = BrickBottomtLine;

        if (m_Ball->GetObjectPos().y <= PointOfIntersection_Bottom.y)
        {
            m_Ball->SetObjectPos(PointOfIntersection_Bottom);
            m_Ball->ReverseDirectionY();
        }
    }
}

void Brick::Render(SDL_Renderer* m_pRenderer)
{
    vec2 BrickTopLeftCorner = m_ObjectCenterPos - m_ObjectSize / 2;

    SDL_Rect BrickDrawRect{};
    BrickDrawRect.x = int(BrickTopLeftCorner.x);
    BrickDrawRect.y = int(BrickTopLeftCorner.y);
    BrickDrawRect.w = int(m_ObjectSize.x) - BRICK_SPACING;
    BrickDrawRect.h = int(m_ObjectSize.y);

    SDL_SetRenderDrawColor(m_pRenderer, m_BrickColor.R, m_BrickColor.G, m_BrickColor.B, 255);
    
    SDL_RenderFillRect(m_pRenderer, &BrickDrawRect);
}

bool Brick::HasBrickBeenCrossed(vec2 BallPos)
{
    return false;
}


