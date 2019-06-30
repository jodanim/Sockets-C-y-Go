#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <vector>
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
		std::string readSome(int bytes);
		int getBytes();
	private:
		std::fstream file;
		std::string unbuffered = "";
		std::vector<std::string> files;
		std::string path;
};

#endif