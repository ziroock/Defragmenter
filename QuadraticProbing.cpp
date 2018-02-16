#include "QuadraticProbing.h"
#include "mynew.h"
#include <iostream>
using namespace std;


/**
* Internal method to test if a positive number is prime.
* Not an efficient algorithm.
*/
template <class HashedObj>
bool QuadraticHashTable<HashedObj>::isPrime(int n) const
{
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

/**
* Internal method to return a prime number at least as large as n.
* Assumes n > 0.
*/
template <class HashedObj>
int QuadraticHashTable<HashedObj>::nextPrime(int n) const
{
	if (n % 2 == 0)
		n++;

	for (; !isPrime(n); n += 2)
		;

	return n;
}

/**
* Construct the hash table.
*/
template <class HashedObj>
QuadraticHashTable<HashedObj>::QuadraticHashTable(const HashedObj & notFound, int size)
	: array(nextPrime(size)), ITEM_NOT_FOUND(notFound)
{
	makeEmpty();
}


/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/
template <class HashedObj>
void QuadraticHashTable<HashedObj>::insert(int oldLoc, const HashedObj & x)
{

	int currentPos = findPos(oldLoc);
	if (isActive(currentPos)) {
		return;
	}
	array[currentPos] = HashEntry(oldLoc, x);
}



template <class HashedObj>
int QuadraticHashTable<HashedObj>::findPos(int oldLoc) const
{
	/* 1*/      int collisionNum = 0;
	/* 2*/      int currentPos = hash(oldLoc, array.size());

	/* 3*/      while (array[currentPos].oldBlockID != 0 &&
		array[currentPos].oldBlockID != oldLoc)
	{

		currentPos += 2 * ++collisionNum - 1;  // Compute ith probe
		/* 5*/          if (currentPos >= array.size())
			/* 6*/              currentPos -= array.size();
	}

	/* 7*/      return currentPos;
}


/**
* Remove item x from the hash table.
*/
template <class HashedObj>
void QuadraticHashTable<HashedObj>::remove(int oldLoc)
{
	int currentPos = findPos(oldLoc);
	if (isActive(currentPos))
		array[currentPos].oldBlockID = 1;
}

/**
* Find item x in the hash table.
* Return the matching item, or ITEM_NOT_FOUND, if not found.
*/
template <class HashedObj>
const HashedObj & QuadraticHashTable<HashedObj>::find(int oldLoc)
{
	int currentPos = findPos(oldLoc);
	return isActive(currentPos) ? array[currentPos].newBlockID : ITEM_NOT_FOUND;
}

/**
* Make the hash table logically empty.
*/
template <class HashedObj>
void QuadraticHashTable<HashedObj>::makeEmpty()
{
	// cout << "making empty" << endl;
	currentSize = 0;
	for (int i = 0; i < array.size(); i++)
		array[i].oldBlockID = 0;
}



/**
* Return true if currentPos exists and is active.
*/
template <class HashedObj>
bool QuadraticHashTable<HashedObj>::isActive(int currentPos) const
{
	return array[currentPos].oldBlockID > 1;
}


/**
* A hash routine for ints.
*/
template <class HashedObj>
int QuadraticHashTable<HashedObj>::hash(int key, int tableSize) const
{
	if (key < 0) key = -key;
	return key % tableSize;
}



