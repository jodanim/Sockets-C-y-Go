#include "../lib/FileManager.hpp"

FileManager::FileManager(){}

FileManager::~FileManager(){
    transferFile.close();
    csv.close();
}

void FileManager::openTransferFile(std::string transferFilePath){
    transferFile.open(transferFilePath);
}

void FileManager::openCsv(std::string csvPath){
    csv.open(csvPath);
}

void FileManager::closeTransferFile(){
    transferFile.close();
}

void FileManager::writeTime(std::chrono::high_resolution_clock::time_point time){   
    csv << time << ",";
}

void FileManager::writeTotal(std::chrono::duration<double, std::milli> time){
    csv << time.count() << "endl";
}

std::string FileManager::readFile(){
    std::string buffer = "";
    std::string line;
    do{
        std::getline(transferFile,line);
        buffer += line;
    }while(transferFile);
    return buffer;
}