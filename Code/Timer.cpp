#include<Timer.hpp>

Timer::Timer()
{
    start_time = 0;
    pause_time = 0;
    paused = false;
    started = false;

}

void Timer::start()
{
    started = true;
    paused = false;
    start_time = SDL_GetTicks();
}

void Timer::stop()
{
    paused = false;
    started = false;

}

void Timer::Gpaused()
{
    if(started == true && paused == false)
    {
        paused = true;
        pause_time = SDL_GetTicks() -start_time;
    }
}

void Timer::continued()
{
    if(paused == true)
    {
        paused = false;
        start_time = SDL_GetTicks()- pause_time;
        pause_time = 0;
    }
}

int Timer::get_Ticks()
{
    if(started == true)
    {
        if(paused == true)
        {
            return pause_time;
        }else{
            return SDL_GetTicks() - start_time;
        }
    }
    return 0;
}

bool Timer::is_paused()
{
    return paused;
}

bool Timer::is_started()
{
    return started;
}