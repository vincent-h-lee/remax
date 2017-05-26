#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "data.h"

class Records {
public:
	//Constructor
	Records(const std::string filename) : filename_(filename){}

	/*Initiation*/
	void init();
	int readcsv(); 
	void changeHeadings(); 
	void removeColumns(); 

	/*Process*/
	void process();
	void extractNumbers(std::string& text); // map<string, vector<string>>
	void removeInvalidFields(); //not available, not phone numbers
	void format(); //phone numbers and store duplicates

	/*Print*/
	void print(Data& data); 
	void output();
private: 
	std::string 	   filename_;
	Data		   	   headings_;
	std::vector<Data>  records_; 
}; 
#endif 