<<<<<<< HEAD
/*

Jaewon Cho DSA Program 2 heap.cpp

*/

#include "heap.h"

// Constructor for heap class
heap::heap(int capacity){
=======
#include "heap.h"

// Constructor for heap class
heap::heap(int capacity)
{
>>>>>>> 498cce883d109d5b60bcb9c8f062641210d58dee
	mapping = new hashTable(capacity * 2);		// Make hashtable for the mapping
	data.resize(capacity + 1);  // Allocate space for the nodes (0 slot is not used)
	this->capacity = capacity;	// Set capacity of heap to value provided by user
	size = 0;
}

<<<<<<< HEAD
// This function checks for repeating id and then inserts into the hash table and
// the heap.
int heap::insert(const std::string &id, int key, void *pv){
	if (size < capacity)
{
		if (mapping->contains(id))		// checks if the hash table contains the id
			return 2;
		else{
			size++;						// Inserts into the heap by attaching it
			data[size].id = id;			// at the end of the heap and then percolateUP
			data[size].key = key;		// to maintain the binary heap order
			data[size].pData = pv;
			mapping -> insert(id, &data[size]);	// Inserts into the hash table
			percolateUp(size);
=======
int heap::insert(const std::string &id, int key, void *pv)
{
	if (size < capacity)
	{
		if (mapping->contains(id))		// Checks if hash table has the id
			return 2;
		else
		{
			size++;						// Inserts new element into heap and
			data[size].id = id;			// uses percolateUp to preserve structure
			data[size].key = key;
			data[size].pData = pv;
			mapping -> insert(id, &data[size]);
			percolateUp(size);

>>>>>>> 498cce883d109d5b60bcb9c8f062641210d58dee
			return 0;
		}
	}
	else
		return 1;
}

<<<<<<< HEAD
// This function sets the key of an id by checking the id exsists and then updates
// while still maintaining the heap order by comparing the new value to its original
int heap::setKey(const std::string &id, int key){
	if (mapping->contains(id)){
		node *pn = static_cast<node *> (mapping->getPointer(id));	// Points to id value

		int originalKey = pn->key;		// save the original key for comparision

		pn->key = key;
		int pos = getPos(pn);			// position of the key

		if (originalKey < key)			// Compares the two key to determine if the new
			percolateDown(pos);			// key needs to percolateUp or percolateDown
		if (originalKey > key) 
			percolateUp(pos);
=======
int heap::setKey(const std::string &id, int key)
{
	if (mapping->contains(id))
	{
		node *pn = static_cast<node *> (mapping->getPointer(id));	// Points to id value

		int oldKey = pn->key;		// Remember old key for comparison

		pn->key = key;
		int pos = getPos(pn);

		if (oldKey < key)				// Depending on the value of the key, we
			percolateDown(pos);			// either percolate up or down to find its
		if (oldKey > key)				// proper location in the heap
			percolateUp(pos);

>>>>>>> 498cce883d109d5b60bcb9c8f062641210d58dee
		return 0;
	}
	else
		return 1;
}

<<<<<<< HEAD
// Took influence on the example on the textbook (figure 6.8)
// This function takes in the current position of the heap and percolatesUp the id. 
void heap::percolateUp(int curPos){
  node temp = data[curPos];		// Temporary variable to store the item at curPos
	for( ; (curPos > 1) && (temp.key < data[curPos / 2].key); curPos /= 2){  //updates the heap
		data[curPos] = data[curPos / 2];
		mapping -> setPointer(data[curPos].id, &data[curPos]);		// Remaps hash table
	}

	data[curPos] = temp;  //sets the new data to the hole
	mapping -> setPointer(data[curPos].id, &data[curPos]);  //updates the hash table
}

// Took influence on the example on the textbook  (figure 6.12)
// This function takes in the current position of the heap and percolatesDown the id.
void heap::percolateDown(int curPos){
	node temp = data[curPos];	// Temporary variable to store the item at curPos
	int child, l, r;			// local variable for determining left and right

	for ( ; (curPos * 2) <= size; curPos = child){
		l = curPos * 2;
		r = l + 1;

    	// checks which side is smaller
		if ((l < size) && (data[r].key < data[l].key))
			child = r;
		else
			child = l;

		// checks if the key is smaller
		if (data[child].key < temp.key){
			data[curPos] = data[child];								// updates the heap
			mapping -> setPointer(data[curPos].id, &data[curPos]);	// updates hash table
		} else
			break;
	}

	data[curPos] = temp;		// places the id into its new place
	mapping -> setPointer(data[curPos].id, &data[curPos]);		// updates the hash table
}

// Taken directly from the example given on assignment
// This function gets the position of the heap
int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return pos;
}

// Function that removes a certain id from the heap while checking for predetermined key
// or data.
int heap::remove(const std::string &id, int *pKey, void *ppData){
	// Check if node with given id exists
	if (mapping -> contains(id)){
		node *pn = static_cast<node *> (mapping -> getPointer(id)); 	// Reference to specified node
		int originalKey = pn -> key;			// save the original key for comparision
=======
int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
	if (size != 0)
	{
		// Write to the proper addresses if they are specifified
		if (pId != NULL)
			*pId = data[1].id;

		if (pKey != NULL)
			*pKey = data[1].key;

		if (ppData != NULL)
			*(static_cast<void **> (ppData)) = data[1].pData;


		// Deletion implementation influenced by Figure 6.12 in our textbook
		mapping -> remove(data[1].id);
		data[1] = data[size];
		size--;
		percolateDown(1);

		return 0;
	} else
		return 1;
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
	// Check if node with given id exists
	if (mapping -> contains(id))
	{
		node *pn = static_cast<node *> (mapping -> getPointer(id)); 	// Reference to specified node
		int oldKey = pn -> key;
>>>>>>> 498cce883d109d5b60bcb9c8f062641210d58dee

		// Write to the proper addresses if they are specifified
		if (pKey != NULL)
			*pKey = pn -> key;
<<<<<<< HEAD
=======

>>>>>>> 498cce883d109d5b60bcb9c8f062641210d58dee
		if (ppData != NULL)
			*(static_cast<void **> (ppData)) = pn -> pData;

		// Remove id from hash table and update pn
		mapping -> remove(id);
		*pn = data[size];
		int newKey = pn -> key;
		size--;
<<<<<<< HEAD
		
		int pos = getPos(pn);
		// Maintain structure of heap
		if (newKey < originalKey)
			percolateUp(pos);
		else if (newKey > originalKey)
=======

		int pos = getPos(pn);

		// Maintain structure of heap
		if (newKey < oldKey)
			percolateUp(pos);
		else if (newKey > oldKey)
>>>>>>> 498cce883d109d5b60bcb9c8f062641210d58dee
			percolateDown(pos);

		return 0;
	} else
		return 1;
}

<<<<<<< HEAD
// Function that removes the smallest key
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
	if (size != 0){
		// Write to the proper addresses if they are specifified
		if (pId != NULL)
			*pId = data[1].id;
		if (pKey != NULL)
			*pKey = data[1].key;
		if (ppData != NULL)
			*(static_cast<void **> (ppData)) = data[1].pData;

		// Deletion implementation influenced by Figure 6.12 in our textbook
		mapping -> remove(data[1].id);
		data[1] = data[size];
		size--;
		percolateDown(1);

		return 0;
	} else
		return 1;
=======
// Implementation influenced by Figure 6.8 in our textbook 
void heap::percolateUp(int curPos)
{
  node temp = data[curPos];		// Temporary variable to store the item at curPos
	for( ; (curPos > 1) && (temp.key < data[curPos / 2].key); curPos /= 2)  //updates the heap
	{
		data[curPos] = data[curPos / 2];
		mapping -> setPointer(data[curPos].id, &data[curPos]);		// Remaps hash table
	}

	data[curPos] = temp;  //sets the new data to the hole
	mapping -> setPointer(data[curPos].id, &data[curPos]);  //updates the hash table
}

// Implementation influenced by Figure 6.12 in our textbook
void heap::percolateDown(int curPos)
{
	node temp = data[curPos];
	int child, l, r;

	for ( ; (curPos * 2) <= size; curPos = child)
	{
		l = curPos * 2;
		r = l + 1;

    //checks which side is smaller
		if ((l < size) && (data[r].key < data[l].key))
			child = r;
		else
			child = l;

		if (data[child].key < temp.key)
		{
			data[curPos] = data[child];
			mapping -> setPointer(data[curPos].id, &data[curPos]);
		} else
			break;
	}

	data[curPos] = temp;
	mapping -> setPointer(data[curPos].id, &data[curPos]);	
}

int heap::getPos(node *pn)
{
	int pos = pn - &data[0];
	return pos;
>>>>>>> 498cce883d109d5b60bcb9c8f062641210d58dee
}