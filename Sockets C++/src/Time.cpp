#include "../lib/Time.hpp"

Time::Time(TimeUnit unit){ 
	this->unit = unit;
	initialTime = now();
}

std::string Time::getTimeUnit(){
	switch (unit){
		default:			return "nanoseconds";
		case microseconds:	return "microseconds";
		case miliseconds: 	return "miliseconds";
		case seconds:		return "seconds";
		case minutes:		return "minutos";
		case hours:			return "horas";
	}
}
void Time::start(){	startTime = now(); }

double Time::end(){ return now()-startTime; }

void Time::programEnd(){ 
	std::cout<<std::endl<<"Elapsed Time: "<< now() - initialTime << " " <<getTimeUnit()<<std::endl;
}

double Time::now(){
	std::chrono::nanoseconds now = std::chrono::high_resolution_clock::now().time_since_epoch();
	switch (unit){
		default:
			return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
		case microseconds: 
			return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(now).count()*0.001;
		case miliseconds: 	
			return (double)std::chrono::duration_cast<std::chrono::microseconds>(now).count()*0.001;
		case seconds:		
			return (double)std::chrono::duration_cast<std::chrono::milliseconds>(now).count()*0.001;
		case minutes:		
			return (double)std::chrono::duration_cast<std::chrono::seconds>(now).count()/60;
		case hours:			
			return (double)std::chrono::duration_cast<std::chrono::minutes>(now).count()/60;
	}
}
