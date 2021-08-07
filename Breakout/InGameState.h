#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "Font.h"


class InGameState : public GameState
{
public:
    InGameState(shared_ptr<Font> MyFont);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void CreateObject();
    void OnEnter();

private:
    vector<shared_ptr<GameObject>> m_AllGameObjects;
};

