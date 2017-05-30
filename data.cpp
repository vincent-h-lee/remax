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

std::map<std::string, std::string> Data::getPhonebook(const size_t index) {
	std::string nametoken = ""; 
	std::string phonetoken = "";
	bool onname = true; 
	std::map<std::string, std::string> phonebook; 
	std::string fixlist = data_[index]; //TODO remove the quotations if they exist 
	for(auto it=fixlist.begin()+1; it!=fixlist.end()-1; ++it) {
		if(onname) {
			if((*it) == ':') {
				onname = false;
			} else {
				nametoken+=std::toupper(*it); 
			}
		} else {
			if((*it) == ';') {
				onname = true; 
				//trim whitespace and tokens
				phonebook[nametoken] = phonetoken; //TODO Trim whitespace
				nametoken = "";
				phonetoken = ""; 
			} else {
				phonetoken+=(*it); 
			}
		}
	}
	phonebook[nametoken] = phonetoken; 
	return phonebook; 
}

std::vector<std::string> Data::getNames(const size_t index) {
	std::vector<std::string> names; 
	std::istringstream iss(data_[index]); 
	std::string temp;
	while(iss >> temp) {
		if(temp.find('"') != std::string::npos) {
			temp.erase(temp.find('"'), 1);
		}
		if(temp.find(',') != std::string::npos) {
			temp.erase(temp.find(','), 1);
		}

		names.push_back(temp); 
		temp = "";
	}
	return names;
}


void Data::formatphone(const size_t index, std::string number) {
	std::string phone;
	std::istringstream iss(number); 
	iss>>phone; 
	if(!iss) {
		std::cerr << "Err c.Data.f.formatphone: no valid phone number" << std::endl;
	}
	data_[index] = withQuotes(phone);
	
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