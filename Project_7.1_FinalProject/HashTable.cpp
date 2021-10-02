//============================================================================
// Hash Table class definition
//============================================================================

#include <string>
#include <list>
#include <iostream>

#include "Bid.h"
#include "HashTable.h"

using namespace std;


/**
 * Default constructor
 */
HashTable::HashTable(int size) {
    
    // set the list to the deafault size
    // size passed after reading rows from file
    DEFAULT_SIZE = size;
    _bidTable = new list<Bid>[DEFAULT_SIZE];
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    
    // destructor
    delete _bidTable;
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // key will be bidId % size-of-list
    return key % DEFAULT_SIZE;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // convert bidId string to int, hash the key
    // at key index, add bid
    int index = hash(stoi(bid.bidId));
    _bidTable[index].push_back(bid);
    
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
   // iterate through list one index at a time
    for (int i = 0; i < DEFAULT_SIZE; i++) {

        // at each index, iterate through list, print bid info
        for (auto bid : _bidTable[i]) {
            cout << bid.bidId << " " << bid.title << " $" << bid.amount;
            cout << endl;
        }
    }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
   
    // get key from bidId, create iterator for list at index
    int index = hash(stoi(bidId));
    list <Bid> ::iterator i;
    Bid bid;

    // iterate over list at index
    for (i = _bidTable[index].begin(); i != _bidTable[index].end(); i++) {
        bid = *i;
        if (bid.bidId == bidId) {       //match found
            break;
        }
    }
    // haven't reached the end of list, erase bid
    if (i != _bidTable[index].end()) {
        _bidTable[index].erase(i);
        cout << "Bid Id " << bidId << " removed." << endl;
    }
    // bid wasn't found
    else {
        cout << "Bid Id " << bidId << " not found, was it already removed?" << endl;
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    
    // vars
    Bid bid;
    Bid emptyBid;
    int index = hash(stoi(bidId));

    // iterator for list at index
    list <Bid> ::iterator i;
    for (i = _bidTable[index].begin(); i != _bidTable[index].end(); i++) {
        bid = *i;
        if (bid.bidId == bidId) {   //match found
            return bid;
        }
    }
    // no match found, return an empty bid
    return emptyBid;
}

/**
    check to see if the hashtable is empty
    keep user from doubling up list accidentally
*/
bool HashTable::IsEmpty(HashTable* hashTable) {

    // vars
    Bid bid;
    int bids = 0;
    int index = 0;

    // iterate over table indices
    for (index = 0; index < DEFAULT_SIZE - 1; index++) {
        list<Bid> ::iterator i;

        // iterate over index list, check for bids
        for (i = _bidTable[index].begin(); i != _bidTable[index].end(); i++) {
            bid = *i;
            if (bid.bidId != "") {  //bid is not empty
                bids++;             //increment counter
            }
        }
    }
    if (bids == 0) {    //empty table
        return true;
    }
    else
        return false;   //table has at least one element
}