#include "SoundPlayer.h"

SoLoud::Soloud* SoundPlayer::soundEngine = nullptr;
void SoundPlayer::init() {
    // May be responsible for creating its own unique instance.
    soundEngine = new SoLoud::Soloud;
    soundEngine->init(); // Initialize SoLoud engine
   
}

void SoundPlayer::playSound(std::string soundName)
{
    soundEngine->play(ResourceManager::GetSound(soundName));
}

void SoundPlayer::stop(int handle)
{
    soundEngine->stop(handle);
}

void SoundPlayer::deInit() {
    soundEngine->deinit();
    delete soundEngine;
}