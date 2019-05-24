#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"

int main(int argc, char**argv){
    Time t;
    FileManager fm;
	fm.openCsv("output.csv")
    std::cout << t.getDiff().count() << std::endl;
	char buffer[8192];
	Socket s('s',false);
	s.Connect((char*)"192.168.0.16", 11011);
    for(int j = 0; j < 10; j++){
        for(int i = 0; i < 100; i++){
            t.setStartTime();
            s.Write(argv[1]);
            s.Read(buffer, 1024);
            t.setEndTime();
            fm.writeTime(t.getStartTime);
            fm.writeTime(t.getEndTime);
            fm.writeTotal(t.getDiff);
        }
    }
	return 0;	
}
