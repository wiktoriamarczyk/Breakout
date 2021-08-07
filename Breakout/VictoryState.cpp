#include "VictoryState.h"
#include "Engine.h"
#include "Ball.h"


VictoryState::VictoryState(shared_ptr<Font> MyFont) : GameState(eStateID::VICTORY)
{
    m_Font = MyFont;
}


void VictoryState::Update(float DeltaTime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        Engine::GetSingleton()->ExitGame();
    }

    if (SDL_IsKeyPressed(SDL_SCANCODE_RETURN))
    {
        m_NextStateID = eStateID::INGAME;
    }
}


void VictoryState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    if ( Ball::m_NumOfLives == 0 )
    {
        m_Font->DrawText(pRenderer, 8, 100, 80, "GAME OVER!");
        m_Font->DrawText(pRenderer, 4, 260, 300, "YOU LOST!");
    }
    else
    {
        m_Font->DrawText(pRenderer, 8, 180, 80, "VICTORY!");
        m_Font->DrawText(pRenderer, 4, 270, 300, "YOU WON!");
    }

    m_Font->DrawText(pRenderer, 1, 250, 450, "CLICK ESC TO EXIT, ENTER TO PLAY AGAIN");

    SDL_RenderPresent(pRenderer);
}