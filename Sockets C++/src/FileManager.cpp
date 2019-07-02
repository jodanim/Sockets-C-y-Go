#include "../lib/FileManager.hpp"

FileManager::FileManager(){}

FileManager::~FileManager(){
    close();
}

void FileManager::open(std::string path, bool write){
    if(write)
        file.open(path,std::fstream::out | std::fstream::app | std::fstream::binary);
    else
        file.open(path, std::fstream::in | std::fstream::binary);
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

char* FileManager::readFile(int *file_size){
    file.seekg(0, std::ios::end);
    *file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    char * buffer = new char[*file_size];
    file.read(buffer, *file_size);

    if(file.fail()) {
        std::cout << "Some error happened while reading" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << std::endl << "Read \033[33m" << *file_size << "\033[0m bytes from file" << std::endl;

    return buffer;
}
std::string FileManager::readSome(int bytes){
    if(!file.eof()){
        std::string buffer = unbuffered;
        unbuffered = "";
        std::string line;
        while (!file.eof() && buffer.size() < bytes) {
            getline(file,line);
            line += "\n";
            buffer += line;
        }
        if(buffer.size() > bytes){
            unbuffered = buffer.substr(bytes);
            buffer = buffer.substr(0,bytes);
        }
        if(file.eof()){
            buffer.resize(buffer.size()-1);
        }
        return buffer;
    }
    return "";
}

int FileManager::getBytes(){
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    return fileSize;
}
