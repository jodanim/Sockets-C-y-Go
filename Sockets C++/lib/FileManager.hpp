#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <fstream>
#include <iostream>

class FileManager{
	public:
		FileManager();
		~FileManager();
		void open(std::string path, bool write = false);
		void close();
		void writeln(std::string data);
		void write(std::string data);
		std::string readFile();
	private:
		std::fstream file;
};

#endif
