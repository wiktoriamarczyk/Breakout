#include "GameObject.h"


void GameObject::SetObjectPos(vec2 ObjectPos)
{
    m_ObjectCenterPos = ObjectPos;
}

vec2 GameObject::GetObjectPos()
{
    return m_ObjectCenterPos;
}
