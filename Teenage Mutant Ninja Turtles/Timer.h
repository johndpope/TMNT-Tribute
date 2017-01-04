#ifndef __TIMER_H_
#define  __TIMER_H_

#include <time.h>
#include "SDL/include/SDL.h"

class Timer
{
	public:

		Timer();
		~Timer();

		void setFirstTime();
		void setSecondTime();
		Uint64 getTime();

	public:
		Uint64 t1, t2;
};

#endif