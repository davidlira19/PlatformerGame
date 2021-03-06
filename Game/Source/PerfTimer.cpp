#include "PerfTimer.h"
#include "SDL\include\SDL_timer.h"

uint PerfTimer::frequency = 0;

// Fill Constructor, Start(),ReadMs() and ReadTicks() methods they are simple, one line each!

PerfTimer::PerfTimer()
{
	if (frequency == 0) frequency = SDL_GetPerformanceFrequency();

	Start();
}

void PerfTimer::Start()
{
	startTime = SDL_GetPerformanceCounter();
}

double PerfTimer::ReadMs() const
{
	return 1000.0 * (double(SDL_GetPerformanceCounter() - startTime) / double(frequency));
}

uint PerfTimer::ReadTicks() const
{
	return SDL_GetPerformanceCounter() - startTime;
}