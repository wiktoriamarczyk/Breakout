#include "GameObject.h"


int GameObject::m_NumOfLivingObjects = 66;


void GameObject::SetObjectPos(vec2 ObjectPos)
{
    m_ObjectCenterPos = ObjectPos;
}

void GameObject::SetObjectStatus(bool IsObjectDead)
{
    m_RemoveObject = IsObjectDead;

    if (IsObjectDead)
    {
        m_NumOfLivingObjects--;
    }
}

bool GameObject::GetObjectStatus()
{
    return m_RemoveObject;
}

vec2 GameObject::GetObjectPos()
{
    return m_ObjectCenterPos;
}

int GameObject::GetNumOfLivingObjects()
{
    return m_NumOfLivingObjects;
}