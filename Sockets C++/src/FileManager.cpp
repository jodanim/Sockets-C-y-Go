#include "../lib/FileManager.hpp"

FileManager::FileManager(std::string transferFilePath, std::string csvPath){
    transferFile.open(transferFilePath);
    csv.open(csvPath);
}

FileManager::~FileManager(){
    transferFile.close();
    csv.close();
}

void FileManager::writeln(std::string line){
    csv << line << std::endl;
}