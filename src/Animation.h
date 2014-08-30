#ifndef ANIMATION_H
#define ANIMATION_H

#include "Timer.h"

class Animation
{
public:
    Animation(const std::string & texture_id,
              const int & num_frames,);
    ~Animation();

private:
    int _num_frames;
    double _interval;
    Timer _timer;
};

#endif
