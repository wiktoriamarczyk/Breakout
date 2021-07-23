#include "GameObject.h"


void GameObject::SetObjectPos(vec2 ObjectPos)
{
    m_ObjectCenterPos = ObjectPos;
}

void GameObject::SetObjectStatus(bool IsObjectDead)
{
    m_RemoveObject = IsObjectDead;
}

bool GameObject::GetObjectStatus()
{
    return m_RemoveObject;
}

vec2 GameObject::GetObjectPos()
{
    return m_ObjectCenterPos;
}
