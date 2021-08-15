#pragma once
#include "Common.h"
#include "GameState.h"
#include "Sound.h"


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
    void PlaySound(const string& FileName);
   
private:
    static Engine* pSingleton;

    bool m_IsRunning = true;
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Window* m_pWindow = nullptr;
    GameState* m_pCurrentState = nullptr;
    vector<unique_ptr<GameState>> m_AllStates;
    vector<shared_ptr<Sound>> m_LoadedSounds;
};

