#include "records.h"

std::vector<Data> Records::IsValidField::duplicates; //instantiate static variable 

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
	auto nameindex = headings_.findIndex("Name"); 
	auto phoneindex = headings_.findIndex("Phone");
	Records::IsValidField::duplicates.clear(); 
	records_.erase(remove_if(records_.begin(), records_.end(), IsValidField(nameindex, phoneindex))
		,records_.end());
	for(auto it=Records::IsValidField::duplicates.begin(); it!=Records::IsValidField::duplicates.end(); ++it) {
		records_.push_back(*it); 
	}
}


bool Records::IsValidField::compareNameAndPhonebook(std::vector<std::string> names, std::string phonebookname) {
	//process phonebook name into strings
	std::istringstream iss(phonebookname);
	std::string temp; 
	std::vector<std::string> v;
	while(iss>>temp) {
		v.push_back(temp);
	}
	for(auto& name:names) {
		std::string nameupper(name);
		std::transform(nameupper.begin(), nameupper.end(), nameupper.begin(),
                   [](unsigned char c) { return std::toupper(c); });
		if(std::find(v.begin(), v.end(), nameupper) != v.end()) {
			return true; 
		}
	}
	return false;
}

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
