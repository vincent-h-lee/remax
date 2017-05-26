#include "data.h"

void Data::parseData(std::string& data) {
	std::string 	token; 
	bool 			escaped = false;  

	for(auto& ch:data) {
		if(escaped) {
			token+=ch;
			if(ch == '"') {
				escaped = false;
			} 
		} else {
			if(ch == ',') {
				data_.push_back(token);
				token = "";
			} else {
				token+=ch; 
				escaped = (ch == '"') ? true : false; 
			}
		}
	}
	data_.push_back(token);
	//TODO trim each string 
}

void Data::print() {
	for(auto it=data_.begin(); it!=data_.end(); ++it) {
		std::cout << *it << " " << std::endl;
	}
}

void Data::output() {
	for(auto it=data_.begin(); it!=data_.end(); ++it) {
		std::cout << *it;
		if(it != data_.end()-1) {
			std::cout<<",";
		}
	}
}