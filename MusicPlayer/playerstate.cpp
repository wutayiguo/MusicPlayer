#include "playerstate.h"

PlayerState::PlayerState()
{
    this->isPlaying = false;
    setVolume(50);
}

int PlayerState::getVolume()
{
    return volume;
}

void PlayerState::setVolume(int volume)
{
    this->volume = volume;
}
