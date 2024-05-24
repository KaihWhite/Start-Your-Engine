#pragma once
#include "soloud.h"
#include "soloud_wav.h"
#include <string>
#include "resource_manager.h"
class SoundPlayer
{
public:
    static void init();
    static void playSound(std::string soundName);
    static void stop(int handle);
    static void deInit();

private:
 
    static SoLoud::Soloud* soundEngine;
    SoundPlayer() = default;
    ~SoundPlayer() = default;
    
};

