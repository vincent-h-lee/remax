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
int main(int argc, char* argv[]) 
{
	cerr << argc << endl;
	Records records(argv[1]);
	records.init(); //read, remove cols, change headings
	records.process();
	records.output();
	return 0;
}
