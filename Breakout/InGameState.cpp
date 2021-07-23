#include "InGameState.h"
#include "Engine.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"


InGameState::InGameState() : GameState (eStateID::INGAME)
{
    CreateObject();
}

void InGameState::CreateObject()
{
    m_AllGameObjects.clear();

    // inicjalizacja pilki
    shared_ptr<Ball> MyBall = make_shared<Ball>();
    MyBall->InitializeBall(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200);

    // inicjalizacja paletki
    shared_ptr<Paddle> MyPaddle = make_shared<Paddle>(MyBall);
    MyPaddle->InitializePaddle(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, SDL_SCANCODE_A, SDL_SCANCODE_D);
    
    // inicjalizacja cegiel
    int  PosX = 0, PosY = 0;

    for (int column = 0; column < SCREEN_WIDTH / PADDLE_WIDTH; ++column)
    {
        for (int row = 0; row < SCREEN_WIDTH / PADDLE_WIDTH; ++row)
        {
            PosX = row * PADDLE_WIDTH + PADDLE_WIDTH / 2 + 0 * row;
            PosY = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT * column - BRICK_SPACING * column;
            m_AllGameObjects.push_back(make_shared<Brick>(PosX, PosY, MyBall));
        }
    }

    m_AllGameObjects.push_back(move(MyBall));
    m_AllGameObjects.push_back(move(MyPaddle));
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
        m_AllGameObjects[i]->Update(DeltaTime);
    }
}

void InGameState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);
    
    // render wszystkich obiektow w tym stanie
    for (int i = 0; i < m_AllGameObjects.size(); ++i)
    {
        m_AllGameObjects[i]->Render(pRenderer);
    }
    SDL_RenderPresent(pRenderer);
}