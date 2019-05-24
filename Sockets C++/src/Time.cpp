#include "../lib/Time.hpp"

Time::Time(){
    
}

void Time::setStartTime(){
    startTime = std::chrono::high_resolution_clock::now();
}

void Time::setEndTime(){
    endTime = std::chrono::high_resolution_clock::now();
}

std::chrono::high_resolution_clock::time_point Time::getStartTime(){
    return startTime;
}

std::chrono::high_resolution_clock::time_point Time::getEndTime(){
    return endTime;
}

std::chrono::duration<double, std::milli> Time::getDiff(){
    return endTime - startTime;
}