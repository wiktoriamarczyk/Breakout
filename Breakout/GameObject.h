#pragma once
#include "Common.h"
#include "vec2.h"


class GameObject
{
public:
    virtual void Update(float DeltaTime) = 0;
    virtual void Render(SDL_Renderer* pRenderer) = 0;
    vec2 GetObjectPos();
    void SetObjectPos(vec2 ObjectPos);
    void SetObjectStatus(bool IsObjectDead);
    bool  GetObjectStatus();
    static int GetNumOfLivingObjects();

protected:
    vec2 m_ObjectCenterPos;
    vec2 m_ObjectSize;
    bool m_RemoveObject = false;

   static int m_NumOfLivingObjects;
};
