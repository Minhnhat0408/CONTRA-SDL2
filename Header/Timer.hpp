#pragma once
#include<SDL2/SDL.h>
using namespace std;

class Timer
{
    public:
        Timer();
        void start();
        void stop();
        void Gpaused();
        void continued();

        int get_Ticks();
        bool is_paused();
        bool is_started();

    private:
        int start_time;
        int pause_time;

        bool started;
        bool paused;
};