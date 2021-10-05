#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h> 
#include <unistd.h> 
#include <unordered_map>
#include <queue>
using namespace std;




int main(int argc, char* argv[]){
	int opt;
	string date = "";
	while((opt = getopt(argc, argv, "d:")) != -1){  // process date as a command line argument
		switch(opt){
			case 'd':
			  date += optarg;
			  
		}
	}
	
   
	string csv_file = argv[3];  // process filename
	
	
	unordered_map<string, int> map_cookies;  
	ifstream csv_reader(csv_file);   // use a ifstream object to read the csv file
	
	string each_line = "";
	while(getline(csv_reader, each_line)){
		string cookie = each_line.substr(0, each_line.find(','));  // split cookie and timestamp from line read
		string timestamp = each_line.substr(each_line.find(',') + 1, each_line.find('T') - each_line.find(',') - 1);
		
		if(timestamp == date){ // check whether timestamp matches particular day we're looking for
			map_cookies[cookie] += 1;  // keep a counter of the activities of all cookies recorded on a particular day
		}
		
	}
	
	vector<string> cookies; // list of all cookies with highest activity
	int max_frequency = 0;
	for(auto i = map_cookies.begin(); i != map_cookies.end(); i++){
		max_frequency = max(i->second, max_frequency);
	}
	
	// Once max frequency of any one cookie is found, we can use that as the parameter to collect all cookies with that frequency
	for(auto i = map_cookies.begin(); i != map_cookies.end(); i++){
		if(i->second == max_frequency){
			cookies.push_back(i->first);
		}
	}
	
	// print out most frequently recorded cookies on the day
	for(int i = 0; i < cookies.size(); i++){
		cout << cookies[i] << endl;
	}
	
	// Some edge test cases tested:
	// Date which does not exist in the csv file (program does not print anything)
	
	return 0;
}