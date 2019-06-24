#include "../lib/FileManager.hpp"

FileManager::FileManager(){}

FileManager::~FileManager(){
    close();
}

void FileManager::open(std::string path, bool write){
    if(write)
        file.open(path,std::fstream::out | std::fstream::trunc);
    else
        file.open(path);
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
    }
    return buffer;
}