#include "Sound.h"


Sound::~Sound()
{
    Mix_FreeChunk(m_pSoundData);
    m_pSoundData = nullptr;
}

bool Sound::Load(const string& FileName)
{
    m_FileName = FileName;
    m_pSoundData = Mix_LoadWAV(("../Data/" + FileName).c_str());
    if (m_pSoundData == nullptr)
    {
        printf("Sound could not be loaded! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void Sound::Play()const
{
    Mix_PlayChannel(-1, m_pSoundData, 0);
}

string Sound::GetName()const
{
    return m_FileName;
}