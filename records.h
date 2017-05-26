#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "data.h"

class Records {
public:
	//Constructor
	Records(const std::string filename) : filename_(filename){}
	void init();
	int readcsv(); 
	//int readline(const std::string& line, Data& data);
	void print(Data& data); 
	void printHeadings(); 
	void printRecords(); 
	void printAll();
	void output();
private: 
	std::string 	   filename_;
	Data		   	   headings_;
	std::vector<Data>  records_; 
}; 
#endif 