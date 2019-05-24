#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

using namespace std::chrono;

class Time{
	public:
		Time();
		void setStartTime();
        void setEndTime();
		uint64_t getStartTime();
        uint64_t getEndTime();
        uint64_t getDiff();
	private:
		uint64_t startTime;
        uint64_t endTime;
};

#endif
