#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <locale>
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

	struct IsValidField {
	public:
		static std::vector<Data> duplicates; 

		IsValidField(const size_t nameindex, const size_t phoneindex):nameindex_(nameindex), phoneindex_(phoneindex) {}
		bool operator()(Data& record) {
			std::vector<std::string> phonecounter; //keep track of multiple phone numbers per one individual

			bool found = false; 
			if(record.getAtIndex(phoneindex_) == "n/a" || record.getAtIndex(phoneindex_) == record.withQuotes("n/a")) {
				return !found;
			}

			auto phonebook = record.getPhonebook(phoneindex_);
			auto names = record.getNames(nameindex_);
			for(auto it=phonebook.begin(); it!=phonebook.end(); ++it) {
				if(compareNameAndPhonebook(names, it->first)) {
					if(!found) {
						record.formatphone(phoneindex_, it->second);
						phonecounter.push_back(record.getAtIndex(phoneindex_));
						found = true;
					} else {
						//push to duplicates
						Data temp(record); 
						temp.formatphone(phoneindex_, it->second);
						if(std::find(phonecounter.begin(), phonecounter.end(), temp.getAtIndex(phoneindex_)) == phonecounter.end()) {
							phonecounter.push_back(record.getAtIndex(phoneindex_));
							duplicates.push_back(temp);
						}
					}
				}
			}
			return !found; //if found, return false -- do not remove
		}
		bool compareNameAndPhonebook(std::vector<std::string> names, std::string phonebookname);
	private:
		size_t nameindex_; 
		size_t phoneindex_;
	};

	/*Print*/
	void print(Data& data); 
	void output();
	 
private: 
	std::string 	   filename_;
	Data		   	   headings_;
	std::vector<Data>  records_; 
}; 
#endif 