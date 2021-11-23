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
	if (capacity <= (2 * filled))		// Checks if table needs to be rehashed
	{
		if(!rehash())
			return 2;
	}

	int keyAddress = hash(key);
	int probe = -1;

	while (data[keyAddress].isOccupied)
	{
		if (data[keyAddress].key == key)				// If the key already exists in the table
		{												// and is not deleted, return 1
			if (!(data[keyAddress].isDeleted))
				return 1;
			else 										// If the key already exists in the table
			{											// and was previously deleted, mark it as
				data[keyAddress].isDeleted = false;		// not deleted anymore
				data[keyAddress].pv = pv;
				return 0;								
			}											
		} else if ((data[keyAddress].isDeleted) && (probe == -1))	// Implementation of Linear Probing
		{
			probe = keyAddress;
		}
		keyAddress++;
		if (keyAddress == capacity)		// Prevents accessing an element not in the data vector
			keyAddress = 0;
	}

	if (probe != -1)					// Puts the data in the probed spot
		keyAddress = probe;

	data[keyAddress].key = key;
	data[keyAddress].isOccupied = true;
	data[keyAddress].isDeleted = false;
	data[keyAddress].pv = pv;
	filled++;
	return 0;
}

//Function that searches for the given key and looks for an empty box otherwise
int hashTable::findPos(const string &key){
	unsigned int hashVal = hash(key);
	int i = 0;
	while (data[hashVal].isOccupied){
		if(data[hashVal].key == key){
			if(data[hashVal].isDeleted)
				return -1;
			else
				return hashVal;
		}
		else{
			hashVal++;
			if(hashVal == capacity)	//prevents accesssing an element in the data vector
				hashVal = 0;
		}
	}
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

//Additional Definitions for Assignement 2
//Get the pointer associated with the specified key
//If the key does not exist in the hash table, return nullptr
void * hashTable::getPointer(const string &key, bool *b){
	if(contains(key)){
		int pos = findPos(key);
		if(b != NULL)
			*b = true;
		return data[pos].pv;
	}else{
		if(b != NULL)
			*b = false;
		return NULL;
	}
}

//Set the pointer associated with the specified key
int hashTable::setPointer(const string &key, void *pv){
	if(contains(key)){
		int pos = findPos(key);
		data[pos].pv = pv;
		return 0;
	}else
		return 1;
}

// Delete the item with the specified key
bool hashTable::remove(const string &key){
	if(contains(key)){
		int pos = findPos(key);
		data[pos].isDeleted = true;
		return true;
	}else
		return false;
}


