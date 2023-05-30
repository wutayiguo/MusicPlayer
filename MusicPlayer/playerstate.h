#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H


class PlayerState
{
public:
    PlayerState();
    bool isPlaying;
    int getVolume();
    void setVolume(int volume);

private:
    int volume;

};

#endif // PLAYERSTATE_H
