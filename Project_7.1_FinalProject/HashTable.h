#pragma once

#include "Bid.h"
#include <cstddef>

using namespace std;

class HashTable {

private:
    
    list<Bid>* _bidTable;
    
    unsigned int hash(int key);

public:

    
    int DEFAULT_SIZE;
    HashTable(int DEFAULT_SIZE);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    bool IsEmpty(HashTable* hashTable);
};
