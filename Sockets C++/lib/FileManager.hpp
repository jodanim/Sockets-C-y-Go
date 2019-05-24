#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <fstream>
#include <iostream>

class FileManager{
	public:
		FileManager();
		~FileManager();
		void openTransferFile(std::string transferFilePath);
		void openCsv(std::string csvPath);
		void closeTransferFile();
		void writeHeader(std::string header);
		void writeTotal(uint64_t time);
		std::string readFile();
	private:
		std::ifstream transferFile;
		std::ofstream csv;
};

#endif
