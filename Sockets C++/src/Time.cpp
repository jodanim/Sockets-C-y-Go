#include "../lib/Time.hpp"


Time::Time(){
    
}

void Time::setStartTime(){
    startTime = duration_cast<nanoseconds>
              (high_resolution_clock::now().time_since_epoch()).count();
}

void Time::setEndTime(){
    endTime =  duration_cast<nanoseconds>
              (high_resolution_clock::now().time_since_epoch()).count();
}

uint64_t Time::getStartTime(){
	return startTime;
}

uint64_t Time::getEndTime(){
    return endTime;
}

uint64_t Time::getDiff(){
    return endTime - startTime;
}
