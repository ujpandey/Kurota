#ifndef TIMER_H
#define TIMER_H

#include "Includes.h"

class Timer
{
public:
    Timer();
    
    void start();
    void stop();
    void reset();
    void pause();
    void unpause();
    
    Uint32 get_ticks();

    bool is_started();
    bool is_paused();
    
private:
    Uint32 _ticks;
    Uint32 _pause_ticks;
    bool _started;
    bool _paused;
};

#endif
