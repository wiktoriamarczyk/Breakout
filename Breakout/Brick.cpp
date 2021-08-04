#include "Brick.h"


int Brick::m_NumOfBricks = 0;

constexpr int TABLE_SIZE = 4;

const Color ColorTable[TABLE_SIZE] = { {207, 207, 27}, {36, 105, 25}, {201, 114, 26}, {140, 14, 14} };


Brick::Brick(float BrickCenterPosX, float BrickCenterPosY, shared_ptr<Ball> MyBall)
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

    float BrickTopLine = BrickTopLeftCorner.y;
    float BrickBottomLine = BrickBottomRightCorner.y;
    float BrickLeftLine = BrickTopLeftCorner.x;
    float BrickRightLine = BrickBottomRightCorner.x;
    // punkt przeciecia prostej TopLine z prosta wyznaczana przez tor lotu pilki 
    vec2 PointOfIntersection_Up;
    vec2 PointOfIntersection_Bottom;
    vec2 PointOfIntersection_Right;
    vec2 PointOfIntersection_Left;

    //-----SPRAWDZ czy pilka znajduje sie na plaszczyznie OX w miejscu wystepowania cegly (miedzy LeftLine a RightLine)-----
    if (m_Ball->GetObjectPos().x >= BrickLeftLine && m_Ball->GetObjectPos().x <= BrickRightLine)
    {
        //----- SPRAWDZ czy pilka odbije sie od gornej krawedzi, jesli pilka znajduje sie nad gorna czescia cegly, to znaczy, ze moze sie z nia zderzyc od gory------
        if (m_Ball->GetObjectPos().y <= this->m_ObjectCenterPos.y)
        {
            // y = ax + b
            // x = (y - b) / a
            // oblicz wspolrzedne punktu przeciecia z gorna czescia cegly
            PointOfIntersection_Up.x = (BrickTopLine - m_Ball->GetBallDirectionLine().b) / m_Ball->GetBallDirectionLine().a;
            PointOfIntersection_Up.y = BrickTopLine;
            // w OX cegly juz sie znajdujemy, zatem sprawdz czy wspolrzedna Y polozenia pilki jest rowna Y punktu przeciecia
            if (m_Ball->GetObjectPos().y >= PointOfIntersection_Up.y)
            {
                std::cout << "od gory" << std::endl;
                // jesli tak, to przemiesc pilke idealnie w pkt. przeciecia oraz odwroc jej kierunek (odbij od paletki)
                m_Ball->SetObjectPos(PointOfIntersection_Up);
                m_Ball->ReverseDirectionY();
                SetObjectStatus(true);
            }
        }

        //------SPRAWDZ czy pilka odbije sie od dolnej krawedzi, pilka znajduje sie pod dolna czescia cegly, to znaczy, ze moze sie z nia zderzyc od dolu------
        if (m_Ball->GetObjectPos().y >= this->m_ObjectCenterPos.y)
        {
            PointOfIntersection_Bottom.x = (BrickBottomLine - m_Ball->GetBallDirectionLine().b) / m_Ball->GetBallDirectionLine().a;
            PointOfIntersection_Bottom.y = BrickBottomLine;

            if (m_Ball->GetObjectPos().y <= PointOfIntersection_Bottom.y)
            {
                std::cout << "od dolu" << std::endl;
                m_Ball->SetObjectPos(PointOfIntersection_Bottom);
                m_Ball->ReverseDirectionY();
                SetObjectStatus(true); 
            }
        }
    }
    //-----SPRAWDZ czy pilka znajduje sie na plaszczyznie OY w miejscu wystepowania cegly (miedzy BottomLine a TopLine)-----
    else if (m_Ball->GetObjectPos().y >= BrickTopLine && m_Ball->GetObjectPos().y <= BrickBottomLine)
    {
        //-----SPRAWDZ czy pilka odbije sie od prawej krawedzi-----
        if (m_Ball->GetObjectPos().x >= BrickRightLine)
        {
            // y = ax + b
            // oblicz wspolrzedne punktu przeciecia z prawa czescia cegly
            PointOfIntersection_Right.x = BrickRightLine;
            PointOfIntersection_Right.y = m_Ball->GetBallDirectionLine().a * BrickRightLine + m_Ball->GetBallDirectionLine().b;

            // w OY cegly juz sie znajdujemy, zatem sprawdz czy wspolrzedna X pilki jest rowna X punktu przeciecia
            if (m_Ball->GetObjectPos().x <= PointOfIntersection_Right.x)
            {
                std::cout << "z prawej" << std::endl;
                m_Ball->SetObjectPos(PointOfIntersection_Right);
                m_Ball->ReverseDirectionX();
                SetObjectStatus(true);
            }
        }

        //-----SPRAWDZ czy pilka odbije sie od lewej krawedzi------
        if (m_Ball->GetObjectPos().x <= BrickLeftLine)
        {
            PointOfIntersection_Left.x = BrickLeftLine;
            PointOfIntersection_Left.y = m_Ball->GetBallDirectionLine().a * BrickLeftLine + m_Ball->GetBallDirectionLine().b;

            if (m_Ball->GetObjectPos().x >= PointOfIntersection_Left.x)
            {
                std::cout << "z lewej" << std::endl;
                m_Ball->SetObjectPos(PointOfIntersection_Left);
                m_Ball->ReverseDirectionX();
                SetObjectStatus(true);
            }
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


