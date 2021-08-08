#include "Engine.h"
#include "InGameState.h"
#include "VictoryState.h"
#include "Font.h"


Engine* Engine::pSingleton = nullptr;

Engine* Engine::GetSingleton()
{
    return pSingleton;
}

Engine::Engine()
{
    pSingleton = this;

    // stworzenie czcionki
    shared_ptr<Font> MyFont = make_shared<Font>();
    MyFont->LoadFont("../Data/FontData.txt");

    // tworzymy wektor wszystkich stanow
    m_AllStates.push_back(make_unique<InGameState>(MyFont));
    m_AllStates.push_back(make_unique<VictoryState>(MyFont));

    // domyslnie pierwszym stanem jest gra
    ChangeState(eStateID::INGAME);
}

Engine::~Engine()
{
    pSingleton = nullptr;
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
    SDL_CloseAudio();
}

bool Engine::Initialize()
{
    // zainicjalizowanie okna oraz dzwieku
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    // utworzenie okna
    m_pWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_pWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    // utworzenie renderera
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_pWindow == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // zanicjalizowanie obiektow klasy dzwiek
    m_wall_sound.Load("wall_sound.wav");
    m_paddle_sound.Load("paddle_sound.wav");
    m_first_block.Load("first_block_sound.wav");
    m_second_block.Load("second_block_sound.wav");
    m_third_block.Load("third_block_sound.wav");
    m_fourth_block.Load("fourth_block_sound.wav");

    return true;
}


void Engine::Loop()
{
    while (m_IsRunning)
    {
        SDL_Event EVENT = {};
        while (SDL_PollEvent (&EVENT))
        {
            if (EVENT.type == SDL_QUIT)
                return;
        }

        SDL_Delay(1000 / 60);

        m_pCurrentState->Update(1.0f / 60.0f);
        m_pCurrentState->Render(m_pRenderer);

        // domyslnie nastepny stan jest UNKNOWN, gdy nie chcemy przechodzic do nowego stanu, zatem jesli jest tam cos innego, tzn. ze bylo zazadanie zmiany stanu
        if (m_pCurrentState->GetNextStateID() != eStateID::UNKNOWN)
        {
            ChangeState(m_pCurrentState->GetNextStateID());
        }
    }
}

void Engine::ChangeState(eStateID StateID)
{
    for (int i = 0; i < m_AllStates.size(); ++i)
    {
        if (m_AllStates[i]->GetStateID() == StateID)
        {
            m_pCurrentState = m_AllStates[i].get();
            m_pCurrentState->OnEnter();
            return;
        }
    }
}

void Engine::ExitGame()
{
    m_IsRunning = false;
}

void Engine::PlayBrickSound(int ID)const
{
    if (ID == 0)
        m_first_block.Play();
    if (ID == 1)
        m_second_block.Play();
    if (ID == 2)
        m_third_block.Play();
    if (ID == 3)
        m_fourth_block.Play();
}

void Engine::PlayWallSound()const
{
    m_wall_sound.Play();
}

void Engine::PlayPaddleSound()const
{
    m_paddle_sound.Play();
}
