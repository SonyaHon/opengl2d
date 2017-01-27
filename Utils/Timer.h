#ifndef INC_2DS_TIMER_H
#define INC_2DS_TIMER_H

#include <iostream>
#include <chrono>
#include "Enums.h"

class Timer {
private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	std::chrono::steady_clock::time_point stopPointLeft;
	std::chrono::steady_clock::time_point stopPointRight;
	std::chrono::steady_clock::duration pause_duration;
	bool paused;

public:
	Timer();
	void start();
	void unpause();
	void pause();
	bool isOver(long time, TimeEnum type);
	void reset();
	long long int getTime(TimeEnum type);
	long getPausedTime(TimeEnum type);

};


#endif //INC_2DS_TIMER_H
