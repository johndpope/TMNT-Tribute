#include "Timer.h"

Timer::Timer()
{}

Timer::~Timer()
{}

void Timer::setFirstTime()
{
	t1 = SDL_GetPerformanceCounter();
}

void Timer::setSecondTime()
{
	t2 = SDL_GetPerformanceCounter();
}

Uint64 Timer::getTime()
{
	return (double)((t2 - t1) * 1000 / SDL_GetPerformanceFrequency());
}
