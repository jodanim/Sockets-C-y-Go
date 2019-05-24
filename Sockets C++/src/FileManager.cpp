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

void FileManager::writeln(std::string line){
    csv << line << std::endl;
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