#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <vector> 

class Data {
public:
	Data() {}
	Data(std::string& data) {
		parseData(data);
	}
	void parseData(std::string& data); 
	size_t find();
	std::string withQuotes(const std::string& text);
	void print(); 
	void output();
private: 
	std::vector<std::string>	data_; 
};
#endif 