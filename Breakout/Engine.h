#pragma once

#include "Common.h"
#include "GameState.h"

class Engine
{
public:
    Engine();
    ~Engine();
    static Engine* GetSingleton();
    bool Initialize();
    void Loop();
    void ChangeState(eStateID StateID);
    void ExitGame();

private:
    static Engine* pSingleton;

    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Window* m_pWindow = nullptr;
    bool m_IsRunning = true;
    GameState* m_pCurrentState = nullptr;
    vector<unique_ptr<GameState>> m_AllStates;
};

