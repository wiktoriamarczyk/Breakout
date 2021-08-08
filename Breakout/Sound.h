#pragma once
#include "Common.h"


class Sound
{
public:
    Sound()=default;
    ~Sound();
    bool Load(const string& FileName);
    void Play()const;

private:
    Mix_Chunk* m_pSoundData = nullptr;
 
};

