#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
#include <string>
#include <vector>
#include "headings.h"
#include "record.h"

class Records {
public:
	//Constructor
	Records(const std::string filename) : filename_(filename){}
	int readcsv(); 
	int readline();
	int storeheadings();
private: 
	std::string 	filename_;
	Headings  		headings_;
	std::vector<Record>  records_; 
}; 

