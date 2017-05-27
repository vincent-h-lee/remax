#include <algorithm>
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
	for(auto it=data_.begin(); it!=data_.end(); ++it) {
		if((*it)[0] != '"' && (*it)[(*it).size()-1] != '"') {
			*it = Data::withQuotes(*it);
		}
	}
}
/* Indexing */
void Data::removeAtIndex(std::vector<size_t> indices) {
	int i = indices.size() -1; 
	while(i > -1) {
		data_.erase(data_.begin() + indices[i]); //erase from the end
		i--;
	}
}

void Data::replaceAtIndex(const size_t index, const std::string& text) {
	data_[index] = text; 
}

size_t Data::findIndex(std::string data) {
	for(size_t i=0; i<data_.size(); i++) {
		if(data_[i] == data || data_[i] == Data::withQuotes(data)) {
			return i; 
		}
	}
	return (size_t) -1;
}

std::string Data::getAtIndex(const size_t index) {
	return data_[index];
}

//make this static
/* Data processing*/
std::string Data::withQuotes(const std::string& text) {
	return '"' + text + '"';
}

std::map<std::string, std::string> Data::getPhonebook(std::string& list) {
	std::string nametoken = ""; 
	std::string phonetoken = "";
	bool onname = true; 
	std::map<std::string, std::string> phonebook; 
	std::string fixlist = list; //TODO remove the quotations if they exist 
	for(auto& ch:fixlist) {
		if(onname) {
			if(ch == ':') {
				onname = false;
			} else {
				nametoken+=ch; 
			}
		} else {
			if(ch == ';') {
				onname = true; 
				phonebook[nametoken] = phonetoken; //TODO Trim whitespace
				nametoken = "";
				phonetoken = ""; 
			} else {
				phonetoken+=ch; 
			}
		}
	}
	return phonebook; 
}

std::vector<std::string> Data::getNames(std::string& name) {
	std::vector<std::string> names; 
	std::istringstream iss(name); 
	std::string temp;
	while(iss >> temp) {
		names.push_back(temp); 
		temp = "";
	}
	return names;
}

/* Output */
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