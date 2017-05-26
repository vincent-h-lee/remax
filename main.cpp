#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <utility>
#include <sstream>
#include "records.h"

using namespace std; 

/**
 * Formats a csv file with correct styles for headings and phone numbers. 
 * Keeps only records where primary occupant and registered owner match. 
 */
int main() 
{
	//check if can open file 
	//read csv 
	//store first line as headings 
	//change headings format 
	Records records("28PowellStreet.csv");
	records.init(); 
	records.output();
	return 0;
}

/**
 * Change headings 
 */ 

/**
 * Extract names and phone numbers from "Phone" field 
 */

/**
 * Compare registered owner to names in phone field.
 * Delete records where they do not match. 
 */ 

/**
 * Edit records to have phone numbers only.
 * Where a record has multiple name matches with different phone numbers, 
 * store as a duplicate record. 
 */ 

/**
 * 
 */ 