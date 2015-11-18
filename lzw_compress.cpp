#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <sstream>
#include <map>
#include <bitset>

using namespace std;

bitset<16> NumberToBinary(unsigned long  num) {
	// string ret("0000000000000000");
	// The string will be of 16 bit.
	bitset<16> ret(0x10);
	for(int i = 15; i >= 0 ; i--) {
		if(num % 2 == 1)
			ret.set(i,1);
		num = num/2;
	}
	return ret;
}
bitset<16> stringToBitset(string alpha){
	bitset<16> ret(alpha);
	return ret;
}
string NumberToString ( unsigned long  Number ) {
	stringstream ss;
	ss << Number;
	return ss.str();
}
string CharToString( char rd) {
	string ret;
	stringstream ss;
	ss << rd;
	ss >> ret;
	return ret;
}

 
int main(){
	map< string, unsigned long  > dict;
	bitset<16> bits;
	ifstream inFile("45.txt", ifstream::in);
	ofstream outFile("45_compressed.myZip", ios::binary | ofstream::out | ofstream::trunc);
	string CHAR, STRING;
	unsigned long n;
	char rd;	
	map< string, unsigned long  >::iterator IDX;
	STRING.clear();
	// Initialising the dictionary
	dict["0"] = (unsigned long )0;
	dict["1"] = (unsigned long )1;
/*
% How it encodes:
%
% STRING = get input character
% WHILE there are still input characters DO
%     CHARACTER = get input character
%     IF STRING+CHARACTER is in the string table then
%         STRING = STRING+character
%     ELSE
%         output the code for STRING
%         add STRING+CHARACTER to the string table
%         STRING = CHARACTER
%     END of IF
% END of WHILE
% output the code for STRING
*/
	inFile.get(rd);
	STRING = CharToString(rd);
	// cout << dict.size() << " 94\n";
	// dict.add(context);
	while(!inFile.eof()) {
		if((unsigned long )dict.size() >= 65536) {
			// cout << dict.size() << " 97\n";
			// flushing the dictionary 
			dict.clear();
			// debug statement
			// cout << "So, Do i really flush?  " << dict.size() << endl;
			// Initialising the dictionary
			dict["0"] = (unsigned long )0;
			dict["1"] = (unsigned long )1;
		}
		// As long as the file isn't read completely.
		inFile.get(rd); // reading a single char into char * rd
		CHAR = CharToString(rd); // converting a char * into a string
		IDX = dict.find(STRING + CHAR); // searching for it in the dictionary
		if(IDX != dict.end()) { // it belongs in the dictionary
			STRING = STRING + CHAR; // if found
		}
		else{   
			//outFile << NumberToBinary(dict.find(STRING)->second);
			// outFile.write((char*)dict.find(STRING)->second,sizeof(unsigned long int));
			// cout << NumberToBinary(dict.search(STRING)) << endl;
			// convert unsigned long int to binary and write to binary file
			// bitset<16> bits(dict.find(STRING)->second);
			bits = NumberToBinary(dict.find(STRING)->second);
			n = bits.to_ulong();
			outFile.write( reinterpret_cast<char*>(&n), sizeof(n));
			dict[STRING + CHAR] = (unsigned long )(dict.size() + 1);
			STRING = CHAR;
		}
	}
	//outFile << NumberToBinary(dict.find(CHAR)->second);
	bits = NumberToBinary(dict.find(STRING)->second);
	n = bits.to_ulong();
	outFile.write( reinterpret_cast<char*>(&n), sizeof(n));
	// cout << NumberToBinary(dict.search(CHAR)) << endl;
	return 0; 
}
