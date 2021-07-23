#pragma once
#include "GameState.h"
#include "GameObject.h"

class InGameState : public GameState
{
public:
    InGameState();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void CreateObject();
private:
    vector<shared_ptr<GameObject>> m_AllGameObjects;
};

