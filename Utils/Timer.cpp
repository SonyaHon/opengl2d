#include "Timer.h"

Timer::Timer() {

}

void Timer::start() {
	begin = std::chrono::steady_clock::now();
	stopPointLeft = begin;
	stopPointRight = begin;
	end = begin;
	paused = false;
	pause_duration = stopPointRight - stopPointLeft;
}

long long int Timer::getTime(TimeEnum type) {
	if(!paused) {
		end = std::chrono::steady_clock::now();
		if (type == TIME_M_SECS) {
			std::chrono::steady_clock::duration d = end - begin;
			d -= pause_duration;
			return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
		} else {
			std::chrono::steady_clock::duration d = end - begin;
			d -= pause_duration;
			return std::chrono::duration_cast<std::chrono::seconds>(d).count();
		}
	}
	else {
		if (type == TIME_M_SECS) {
			std::chrono::steady_clock::duration d = end - begin;
			d -= pause_duration;
			return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
		} else {
			std::chrono::steady_clock::duration d = end - begin;
			d -= pause_duration;
			return std::chrono::duration_cast<std::chrono::seconds>(d).count();
		}
	}
}

void Timer::pause() {
	paused = true;
	end = std::chrono::steady_clock::now();
	stopPointLeft = std::chrono::steady_clock::now();
	stopPointRight = stopPointLeft;
}

bool Timer::isOver(long time, TimeEnum type) {
		return getTime(type) >= time;
}

void Timer::reset() {
	begin = std::chrono::steady_clock::now();
	stopPointLeft = begin;
	stopPointRight = begin;
	end = begin;
	paused = false;
}

void Timer::unpause() {
	paused = false;
	stopPointRight = std::chrono::steady_clock::now();
	pause_duration = stopPointRight - stopPointLeft;
}

long Timer::getPausedTime(TimeEnum type) {
	return type ==  TIME_M_SECS ? std::chrono::duration_cast<std::chrono::milliseconds>(pause_duration).count() : std::chrono::duration_cast<std::chrono::seconds>(pause_duration).count();
}
