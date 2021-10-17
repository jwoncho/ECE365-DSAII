#include "hash.h"

/*
 *Jaewon Cho - DSA2 Program 1 - Hash Table
 *
 *
 *
 *
*/


using namespace std;

//Function that helps with the detection of invalid characters
//This function allows the spell checker to ignore these characters and only take in the valid words
int invalidDetec(string &line, int pos){
	int inValShift = 0;
	int j = pos;
	while((isalnum(line[j]) || (line[j] == '\'') || (line[j] == '-'))==false){
		j++;
		inValShift++;
	}
	return inValShift;
}

//Function that helps with the detection of the valid words
//This function returns the valid word in a string
//It starts the detection at a valid character and continues until an invalid character is detected
string wordDetec(string &line, int pos){
	string word = "";
	for(int i = pos; i < line.size(); i++){
		if(isalnum(line[i]) || (line[i] == '\'') || (line[i] == '-'))
			word += line[i];
		else
			break;
	}
	return word;
}

//This function detects if the word includes digits
//This allows certain technically valid words to be ignored by the spell checker
bool digitCheck(string &word){
	for(int i = 0; i < word.size(); i++){
		if(isdigit(word[i]))
			return true;
	}
	return false;
}

//This function goes through the input file line by line and utilzies the wordDetect and invalidDetec functions
//This function seperates the valid words from the line and checks the hash table
//This function also checks for long words
void spellCheck(string &doc, string &out, hashTable &table){
	string line, word;
	int inValShift;
	ifstream document;
	ofstream output;
	output.open(out);
	document.open(doc);
	
	int lineNumber = 1;
	while(getline(document, line)){
		transform(line.begin(), line.end(), line.begin(), ::tolower);

		int pos = 0;
		while(pos < line.size()){
			pos += invalidDetec(line, pos);
			word = wordDetec(line, pos);
			pos += word.size();

			if(word == "")
				break;

			if(digitCheck(word))
				continue;

			if(word.size() > 20){
				output << "Long word at line " << lineNumber << ", starts: " << word.substr(0,20) << '\n';
				continue;
			}
			else{
				if(table.contains(word) == false){
					output << "Unknown word at line " << lineNumber << ": " << word << '\n';
					continue;
				}
			}
		}
		lineNumber++;
	}
}

//Function for getting time
double getTime(){
	return (double) clock()/CLOCKS_PER_SEC;
}

//Function to read in the dictionary
//This function also uses wordDetec to ignore the \n characters
void readDict(string &dict, hashTable &table){
	string line;
	ifstream dictionary;
	dictionary.open(dict);

	while(getline(dictionary, line)){
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		int pos = 0;
		table.insert(wordDetec(line, pos));
	}

	dictionary.close();
}

//Main function that reports the cpu time and request the necessary file names
//Calls on other functions to execute spell checking
int main(){
	string doc, dict, out;
	hashTable table(100000);
	cout << "Enter name of a dictionary: ";
	cin >> dict;

	double start = getTime();
	readDict(dict, table);
	double end = getTime();
	double duration = end - start;
	cout << "Total time (in seconds) to load dictionary: " << duration << '\n';

	cout << "Enter name of input file: ";
	cin >> doc;
	cout << "Enter name of ouput file: ";
	cin >> out;

	double start2 = getTime();
	spellCheck(doc, out, table);
	double end2 = getTime();
	double duration2 = end2 - start2;
	cout << "Total time (in seconds) to check document: " << duration2 << '\n';
	
	string test = "values.txt";
	table.showVals(test);

	return 0;
}
