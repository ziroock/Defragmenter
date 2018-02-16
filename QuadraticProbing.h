#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_

#include <iostream>
#include "vector.h"
#include "mynew.h"
using namespace std;

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an initialization for ITEM_NOT_FOUND
//               and an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Hashable find( x )     --> Return item that matches x
// void makeEmpty( )      --> Remove all items
// int hash( String str, int tableSize )
//                        --> Static method to hash strings

template <class HashedObj>
class QuadraticHashTable
{
public:
	explicit QuadraticHashTable(const HashedObj & notFound, int size = 101);
	QuadraticHashTable(const QuadraticHashTable & rhs)
		: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
		array(rhs.array), currentSize(rhs.currentSize) { }
	const HashedObj & find(int oldLoc);
	void makeEmpty();
	void insert(int oldLoc, const HashedObj & x);
	void remove(int oldLoc);
	bool isPrime(int n) const;
	int nextPrime(int n) const;
	bool isActive(int currentPos) const;
	int findPos(int oldLoc) const;
	int hash(int key, int tableSize) const;

private:
	struct HashEntry
	{
		int oldBlockID; // any int , 0   , 1
		HashedObj newBlockID;

		HashEntry(int ob = 0, const HashedObj & nb = HashedObj())
			: oldBlockID(ob), newBlockID(nb) { }
	};
	vector<HashEntry> array;
	int currentSize;
	const HashedObj ITEM_NOT_FOUND;
};


#include "QuadraticProbing.cpp"
#endif
