#ifndef TIME_HPP
#define TIME_HPP

#include <string>
#include <chrono>

enum TimeUnit:int{nanoseconds,microseconds,miliseconds,seconds,minutes,hours};

class Time{
	public:
		Time(TimeUnit unit = nanoseconds);
		std::string getTimeUnit();
		void start();
		double end();
	private:
		double startTime;
		TimeUnit unit;
		double now();
};

#endif /* TIME_HPP */