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

    void PlayBrickSound(int ID)const;
    void PlayWallSound()const;
    void PlayPaddleSound()const;

private:
    static Engine* pSingleton;

    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Window* m_pWindow = nullptr;
    bool m_IsRunning = true;
    GameState* m_pCurrentState = nullptr;
    vector<unique_ptr<GameState>> m_AllStates;

    Sound m_first_block;
    Sound m_second_block;
    Sound m_third_block;
    Sound m_fourth_block;
    Sound m_wall_sound;
    Sound m_paddle_sound;
};

