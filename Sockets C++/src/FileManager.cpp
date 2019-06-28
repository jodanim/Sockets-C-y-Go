#include "../lib/FileManager.hpp"

FileManager::FileManager(){}

FileManager::~FileManager(){
    close();
}

void FileManager::open(std::string path, bool write){
    if(write)
        file.open(path,std::fstream::out | std::fstream::app);
    else
        file.open(path);
        if(file.fail()){
            std::cout<<"\033[1;31mERROR: the file \033[0;33m\""<<path<<"\"\033[1;31m doesn't exists\n\033[0m";
            exit(EXIT_FAILURE);
        }
}

void FileManager::close(){
    file.close();
}

void FileManager::writeln(std::string data){
	file << data << std::endl;
}

void FileManager::write(std::string data){
	file << data;
}

std::string FileManager::readFile(){
    std::string buffer = "";
    std::string line;
    while(getline(file,line)){
        buffer += line;
        buffer += "\n";
    }
    return buffer;
}
std::string FileManager::readSome(int bytes){ 
    if(!file.eof()){
        std::string buffer = unbufered;
        unbufered = "";
        int bufferSize = buffer.size();
        std::string line;
        while (!file.eof() && bufferSize < bytes) {
            getline(file,line);
            buffer += line;
            buffer += "\n";
            bufferSize += line.size()+1;
        }
        if(buffer.size() > bytes){
            unbufered = buffer.substr(bytes);
            buffer = buffer.substr(0,bytes);
        }
        return buffer;
    }else{
        return "";
    }
}

int FileManager::getBytes(){
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    return fileSize;
}