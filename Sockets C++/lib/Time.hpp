#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

class Time{
	public:
		Time();
		void setStartTime();
        void setEndTime();
		std::chrono::high_resolution_clock::time_point getStartTime();
        std::chrono::high_resolution_clock::time_point getEndTime();
        std::chrono::duration<double, std::milli> getDiff();
	private:
		std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point endTime;
};

#endif