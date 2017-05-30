#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <vector> 
#include <map>
#include <sstream>
#include <locale>

class Data {
public:
	Data() {}
	Data(std::string& data) {
		parseData(data);
	}
	Data(const Data& rhs) {
		data_ = rhs.data_;
	}

	void parseData(std::string& data); 
	void removeAtIndex(std::vector<size_t> indices);
	void replaceAtIndex(const size_t index, const std::string& text);
	size_t findIndex(std::string data);
	std::string getAtIndex(const size_t index);
	std::string withQuotes(const std::string& text);
	std::map<std::string, std::string> getPhonebook(const size_t index); 
	std::vector<std::string> getNames(const size_t index); //first, last, company 		
	void formatphone(const size_t index, std::string number);
	void print(); 
	void output();
private: 
	std::vector<std::string>	data_; 
};
#endif 