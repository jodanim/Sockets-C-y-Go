#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "../lib/Time.hpp"

class FileManager{
	public:
		FileManager();
		~FileManager();
		void openTransferFile(std::string transferFilePath);
		void openCsv(std::string csvPath);
		void closeTransferFile();
		void writeTime(std::chrono::high_resolution_clock::time_point time);
		void writeTotal(std::chrono::duration<double, std::milli> time);
		std::string readFile();
	private:
		std::ifstream transferFile;
		std::ofstream csv;
};

#endif