#include "records.h"

void Records::init() {
	Records::readcsv();
}

int Records::readcsv() {
	std::fstream file(filename_, std::ios_base::in|std::ios_base::out);
	if(!file) {
		std::cerr << "Error: could not read file" << std::endl; 
		return 1; 
	}
	std::string line; 
	if(getline(file, line)) {
		headings_.parseData(line);
	} else {
		std::cerr << "Error: could not read headings" << std::endl; 
		return 2;
	}
	while(getline(file, line)) {
		Data record(line);
		records_.push_back(record);
	}
	return 0; 
}

void Records::printHeadings() {
	std::cerr << "Printing headings" << std::endl;
	Records::print(headings_); 
}

void Records::printRecords() {
	std::cerr << "Printing records" << std::endl;
	for(auto it=records_.begin(); it!=records_.end(); ++it) {
		Records::print(*it);
	}
}

void Records::printAll() {
	std::cerr << "Printing all" << std::endl; 
	Records::printHeadings();
	Records::printRecords();
}

void Records::output() {
	headings_.output(); 
	for(auto it=records_.begin(); it!=records_.end(); ++it) {
		(*it).output();
	}
}

void Records::print(Data& data) {
	data.print();
}