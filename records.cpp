#include "records.h"

/*Initiation methods */
void Records::init() {
	Records::readcsv();
	Records::removeColumns();
	Records::changeHeadings();
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

void Records::changeHeadings() {
	//rename
	std::map<std::string, std::string> tochange; 
	tochange["Civic Address"] = "Address"; 
	tochange["Registered Owner"] = "Name";
	tochange["Occupant Summary"] ="Phone";
	for(auto it=tochange.begin(); it!=tochange.end(); ++it) {
		if(headings_.findIndex(it->first) != (size_t)-1) {
			headings_.replaceAtIndex(headings_.findIndex(it->first), headings_.withQuotes(it->second));
		}
	}
}

void Records::removeColumns() {
	std::vector<size_t> indices; 
	std::string toremove [] = {"Municipality", "Zone Code", "Zone Description"};
	for(auto& str : toremove) {
		indices.push_back(headings_.findIndex(str)); 
	}
	headings_.removeAtIndex(indices);	
	for(auto it=records_.begin(); it!=records_.end(); ++it) {
		(*it).removeAtIndex(indices);
	}
}

/*Process methods*/
void Records::process() {
	Records::removeInvalidFields(); //not available, not phone numbers
	Records::format(); //phone numbers and store duplicates
}

void Records::extractNumbers(std::string& text); // map<string, vector<string>>
void Records::removeInvalidFields(); //not available, not phone numbers
void Records::format(); //phone numbers and store duplicates

/*Print methods*/
void Records::output() {
	headings_.output(); 
	for(auto it=records_.begin(); it!=records_.end(); ++it) {
		(*it).output();
	}
}

void Records::print(Data& data) {
	data.print();
}