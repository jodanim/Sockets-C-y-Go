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

void FileManager::writeHeader(std::string header){
	csv << header << std::endl;
}

void FileManager::writeTotal(uint64_t time){
    csv << time << std::endl;
}

std::string FileManager::readFile(){
    std::string buffer = "";
    std::string line;
    while(getline(transferFile,line)){	
        buffer += line;
    }
    return buffer;
}
