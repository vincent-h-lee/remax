#ifndef RECORDS_H
#define RECORDS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
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
			auto phonebook = Records::getPhonebook(record.getAtIndex(phoneindex_));
			auto names = Records::getNames(record.getAtIndex(nameindex_));
			bool found = false; 
			for(auto it=phonebook.begin(); it!=phonebook.end(); ++it) { //TODO change this to iterator and pass in key not value
				if(compareNameAndPhonebook(names, it->first)) {
					if(!found) {
						//record[phoneindex_] = format(phonebook[i]);
						found = true;
					} else {
						//push to duplicates
						//Data temp(record); 
						//temp[phoneindex_] = format(phonebook[i])
						//duplicates.push(temp);
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