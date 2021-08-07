#pragma once

#include "Common.h"
#include "Font.h"

class Engine;

class GameState
{
public:
    GameState(eStateID StateID);
    virtual void Update (float DeltaTime) = 0;
    virtual void Render (SDL_Renderer* pRenderer) = 0;
    virtual void OnKeyDown(SDL_Scancode KeyCode) {};
    eStateID GetStateID()const;
    eStateID GetNextStateID()const;
    // funkcja ustawiajaca na starcie aktualny stan jako ten nastepny, by uniknac zapetlajacego sie przeskakiwania miedzy stanami 
    virtual void OnEnter();

protected:
    eStateID m_NextStateID = eStateID::UNKNOWN;
    shared_ptr<Font> m_Font;

private:
    const eStateID m_StateID = eStateID::UNKNOWN;
};

