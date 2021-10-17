#include "hash.h"
#include <iostream>

/*
 *Jaewon Cho - DSA2 - Program 1 - Hash Table data Structure
 *
 *
 *
 *
*/

using namespace std;

static unsigned int prime[6] = {100043, 200087, 400187, 800399, 1600811, 3201641};		//Prime numbers
static unsigned int probeLim = 1000;		//Limits the number of linear probing

//Function that gets the smallest prime number that is greater than the given size
//Exits with error if there are no bigger prime numbers
unsigned int hashTable::getPrime(int size){
	for(int i = 0; i < (sizeof(prime)/sizeof(prime[0])); i++){
		if(size < prime[i])
			return prime[i];
	}
	cout << "ERROR: No larger prime number.\n";
	exit(1);
}

//Function that initializes the size of the hash table and checks for memory allocation error
//Sets the capacity and filled
hashTable::hashTable(int size){
	try{
		data.resize(getPrime(size));
	}
	catch(bad_alloc& ba){
		cerr << "ERROR: Memory allocation error: Hash Table too big.\n";
		exit(1);
	}
	filled = 0;
	capacity = getPrime(size)/2;
}

//Funtion that determines the hash value
//This funciton is taken from the textbook: Horner's Rule
int hashTable::hash(const string &key){
	unsigned int hashValue = 0;
	for(char c : key)
		hashValue = hashValue * 37 + c;
	return hashValue % data.size();
}

//Function that resizes the original data array in the case that the capacity is exceeded
//The values of the previous array is stored temporarily and only the active values are transferred
bool hashTable::rehash(){
	vector<hashItem> prevData = data;
	data.clear();
	vector<hashItem>().swap(data);
	try{
		data.resize(getPrime(prevData.size()*2));		//doubles the size
	}
	catch(bad_alloc& ba){
		return false;
	}

	capacity = data.size()/2;		//doubles the capacity
	filled = 0;						//resets the filled
	for(hashItem item : prevData){	//transfers all the data
		if(item.isOccupied && item.isDeleted == false){
			if(item.pv != nullptr)
				insert(item.key, item.pv);
			else
				insert(item.key);
		}
	}
	vector<hashItem>().swap(prevData);
	return true;
}

//Function that inserts the values in the hash table
//This function checks if the key exsists and executes linear probing if it does
int hashTable::insert(const string &key, void *pv){
	int hashVal = hash(key);
	int i = 0;
	do{
		if(data.at(hashVal).key == key)
			return 1;
		if(data.at(hashVal).isOccupied == false && data.at(hashVal).isDeleted == false){
			filled++;
			data.at(hashVal).isOccupied = true;
			data.at(hashVal).key = key;
			if(pv != nullptr)
				data.at(hashVal).pv = pv;

			if(filled == capacity){			//checks if rehashing is needed
				if(rehash())
					return 0;
				else
					return 2;
			}
			return 0;
		}
		else{
			i++;
			hashVal++;
			hashVal = hashVal % data.size();
		}
	}
	while(i < probeLim);		//makes sure not to do too many probing
	return 2;
}

//Function that searches for the given key and looks for an empty box otherwise
int hashTable::findPos(const string &key){
	unsigned int hashVal = hash(key);
	int i = 0;
	do{
		if(data.at(hashVal).key == key){
			
			return hashVal;
		}
		else{
			i++;
			hashVal++;
			hashVal = hashVal % data.size();
		}
	}
	while(i < probeLim);		//makes sure not to do too many probing
	return -1;
}

//Function that checks if the hash table contains the object
bool hashTable::contains(const string &key){
	if(findPos(key) != -1)
		return true;
	else
		return false;
}

//Function used for testing the readDict
void hashTable::showVals(string &out){
	ofstream output;
	output.open(out);

	for(int i = 0; i < data.size(); i++){
		output << i << "      " << data[i].key << '\n';
	}
	output.close();
}
