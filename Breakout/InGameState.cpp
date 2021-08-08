#include "InGameState.h"
#include "Engine.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"


InGameState::InGameState(shared_ptr<Font> MyFont) : GameState (eStateID::INGAME)
{
    m_Font = MyFont;
    CreateObject();
}

void InGameState::CreateObject()
{
    m_AllGameObjects.clear();
    Ball::m_NumOfLives = NUM_OF_BALL_LIVES;
    Brick::m_NumOfPoints = 0;

    // inicjalizacja pilki
    shared_ptr<Ball> MyBall = make_shared<Ball>();
    MyBall->InitializeBall(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200);

    // inicjalizacja paletki
    shared_ptr<Paddle> MyPaddle = make_shared<Paddle>(MyBall);
    MyPaddle->InitializePaddle(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, SDL_SCANCODE_A, SDL_SCANCODE_D);
    
    // inicjalizacja cegiel
    float  PosX = 0.0f, PosY = 0.0f;

    for (int column = 0; column < SCREEN_WIDTH / PADDLE_WIDTH; ++column)
    {
        for (int row = 0; row < SCREEN_WIDTH / PADDLE_WIDTH; ++row)
        {
            PosX = row * PADDLE_WIDTH + PADDLE_WIDTH / 2 + 0 * float(row);
            PosY = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT * float(column) - BRICK_SPACING * float(column);
            m_AllGameObjects.push_back(make_shared<Brick>(PosX, PosY, MyBall));
        }
    }

    m_AllGameObjects.push_back(move(MyBall));
    m_AllGameObjects.push_back(move(MyPaddle));
}

void InGameState::OnEnter()
{
    GameState::OnEnter();
    CreateObject();
}

void InGameState::Update(float DeltaTime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        Engine::GetSingleton()->ExitGame();
    }
    // update wszystkich obiektow w tym stanie
    for (int i = 0; i < m_AllGameObjects.size(); ++i)
    {

        if (m_AllGameObjects[i]->GetObjectStatus() == false)
        {
            m_AllGameObjects[i]->Update(DeltaTime);
        }

        if (m_AllGameObjects[i]->GetNumOfLivingObjects() == 2)
        {
            m_NextStateID = eStateID::VICTORY;
        }

        if (Ball::m_NumOfLives == 0)
        {
            m_NextStateID = eStateID::VICTORY;
        }
    }
}

void InGameState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);
    
    // render wszystkich obiektow w tym stanie
    for (int i = 0; i < m_AllGameObjects.size(); ++i)
    {
        if (m_AllGameObjects[i]->GetObjectStatus() == false)
        {
            m_AllGameObjects[i]->Render(pRenderer);
        }  
    }

   // m_Font->DrawText(pRenderer, 5, 200, 20, ToString(m_Points1).c_str());
    m_Font->DrawText(pRenderer, 5, 60, 10, "BALLS:");
    m_Font->DrawText(pRenderer, 5, 300, 10, ToString(Ball::m_NumOfLives).c_str());
    m_Font->DrawText(pRenderer, 5, 420, 10, "SCORE:");
    m_Font->DrawText(pRenderer, 5, 670, 10, ToString(Brick::m_NumOfPoints).c_str());

    SDL_RenderPresent(pRenderer);
}