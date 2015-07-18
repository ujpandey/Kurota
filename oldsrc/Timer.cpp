#include "Timer.h"

Timer::Timer()
    : _ticks(0), _pause_ticks(0), _started(false), _paused(false)
{}

void Timer::start()
{
    _started = true;
    _paused = false;
    
    _ticks = SDL_GetTicks();
    _pause_ticks = 0;
}

void Timer::stop()
{
    _ticks = 0;
    _pause_ticks = 0;
    _started = false;
    _paused = false;
}

void Timer::reset()
{
    bool started = _started;
    bool paused = _paused;
    stop();
    _started = started;
    _paused = paused;
}

void Timer::pause()
{
    if (_started && !_paused)
    {
        _paused = true;
        _pause_ticks = SDL_GetTicks() - _ticks;
    }
}

void Timer::unpause()
{
    if (_paused)
    {
        _paused = false;
        _ticks = SDL_GetTicks() - _pause_ticks;
        _pause_ticks = 0;
    }
}

Uint32 Timer::get_ticks()
{
    if (_started)
    {
        if (_paused)
        {
            return _pause_ticks;
        }
        return SDL_GetTicks() - _ticks;
    }
    return 0;
}

bool Timer::is_started()
{
    return _started;
}

bool Timer::is_paused()
{
    return _paused;
}
