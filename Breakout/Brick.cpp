#include "Brick.h"


int Brick::m_NumOfBricks = 0;

int Brick::m_NumOfPoints = 0;

constexpr int TABLE_SIZE = 4;

const Color ColorTable[TABLE_SIZE] = { {255, 20, 147}, {36, 105, 25}, {207, 207, 27}, {140, 14, 14} };


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
        if (m_Ball->GetObjectPos().y <= BrickTopLine)
        {
            // y = ax + b
            // x = (y - b) / a
            // oblicz wspolrzedne punktu przeciecia z gorna czescia cegly
            PointOfIntersection_Up.x = (BrickTopLine - m_Ball->GetBallDirectionLine().b) / m_Ball->GetBallDirectionLine().a;
            PointOfIntersection_Up.y = BrickTopLine;

            // sprawdz czy punkt przeciecia znajduje sie miedzy lewym a prawym bokiem paletki
            if (PointOfIntersection_Up.x >= BrickLeftLine && PointOfIntersection_Up.x <= BrickRightLine)
            {
                // wyliczamy odleglosc od pozycji pilki do pkt. przeciecia
                vec2 Distance = PointOfIntersection_Up - m_Ball->GetObjectPos();

                if (Distance.GetLength() <= BALL_SPEED * DeltaTime)
                {
                 std::cout << "od gory" << std::endl;
                // jesli tak, to przemiesc pilke idealnie w pkt. przeciecia oraz odwroc jej kierunek (odbij od paletki)
                m_Ball->SetObjectPos(PointOfIntersection_Up);
                m_Ball->ReverseDirectionY();
                SetObjectStatus(true);
                m_NumOfPoints = m_NumOfPoints + (((m_BrickID / 16) % TABLE_SIZE) * 10);
                return;
                }
            }
        }

        //------SPRAWDZ czy pilka odbije sie od dolnej krawedzi, pilka znajduje sie pod dolna czescia cegly, to znaczy, ze moze sie z nia zderzyc od dolu------
        if (m_Ball->GetObjectPos().y >= BrickBottomLine)
        {
            PointOfIntersection_Bottom.x = (BrickBottomLine - m_Ball->GetBallDirectionLine().b) / m_Ball->GetBallDirectionLine().a;
            PointOfIntersection_Bottom.y = BrickBottomLine;

            if (PointOfIntersection_Bottom.x >= BrickLeftLine && PointOfIntersection_Bottom.x <= BrickRightLine)
            {
                vec2 Distance = PointOfIntersection_Bottom - m_Ball->GetObjectPos();
                // czy w tej klatce pilka przeleci przez pkt. przeciecia
                if (Distance.GetLength() <= BALL_SPEED * DeltaTime)
                {
                std::cout << "od dolu" << std::endl;
                m_Ball->SetObjectPos(PointOfIntersection_Bottom);
                m_Ball->ReverseDirectionY();
                SetObjectStatus(true); 
                m_NumOfPoints = m_NumOfPoints + ((m_BrickID / 16) % TABLE_SIZE) * 10 + 5;
                return;
                }
            }
        }
    }
    //-----SPRAWDZ czy pilka znajduje sie na plaszczyznie OY w miejscu wystepowania cegly (miedzy BottomLine a TopLine)-----
    if (m_Ball->GetObjectPos().y >= BrickTopLine && m_Ball->GetObjectPos().y <= BrickBottomLine)
    {
        //-----SPRAWDZ czy pilka odbije sie od prawej krawedzi-----
        if (m_Ball->GetObjectPos().x >= BrickRightLine)
        {
            // y = ax + b
            // oblicz wspolrzedne punktu przeciecia z prawa czescia cegly
            PointOfIntersection_Right.x = BrickRightLine;
            PointOfIntersection_Right.y = m_Ball->GetBallDirectionLine().a * BrickRightLine + m_Ball->GetBallDirectionLine().b;

            if (PointOfIntersection_Right.y >= BrickTopLine && PointOfIntersection_Right.y <= BrickBottomLine)
            {
                vec2 Distance = PointOfIntersection_Right - m_Ball->GetObjectPos();

                if (Distance.GetLength() <= BALL_SPEED * DeltaTime)
                {
                std::cout << "z prawej" << std::endl;
                m_Ball->SetObjectPos(PointOfIntersection_Right);
                m_Ball->ReverseDirectionX();
                SetObjectStatus(true);
                m_NumOfPoints = m_NumOfPoints + (((m_BrickID / 16) % TABLE_SIZE) * 10);
                return;
                }
            }
        }

        //-----SPRAWDZ czy pilka odbije sie od lewej krawedzi------
        if (m_Ball->GetObjectPos().x <= BrickLeftLine)
        {
            PointOfIntersection_Left.x = BrickLeftLine;
            PointOfIntersection_Left.y = m_Ball->GetBallDirectionLine().a * BrickLeftLine + m_Ball->GetBallDirectionLine().b;

            if (PointOfIntersection_Left.y >= BrickTopLine && PointOfIntersection_Left.y <= BrickBottomLine)
            {
                vec2 Distance = PointOfIntersection_Left - m_Ball->GetObjectPos();

                if (Distance.GetLength() <= BALL_SPEED * DeltaTime)
                {
                std::cout << "z lewej" << std::endl;
                m_Ball->SetObjectPos(PointOfIntersection_Left);
                m_Ball->ReverseDirectionX();
                SetObjectStatus(true);
                m_NumOfPoints = m_NumOfPoints + (((m_BrickID / 16) % TABLE_SIZE) * 10);
                return;
                }
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



