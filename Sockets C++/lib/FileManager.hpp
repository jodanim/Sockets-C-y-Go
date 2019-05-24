#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <fstream>
#include <iostream>

class FileManager{
	public:
		FileManager(std::string transferFilePath);
		FileManager(std::string csvPath);
		~FileManager();
		void writeln(std::string line);
	private:
		std::ifstream transferFile;
		std::ofstream csv;
};

#endif