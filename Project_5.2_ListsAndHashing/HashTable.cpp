//============================================================================
// Name        : HashTable.cpp
// Author      : Lawrence Artl 
// Version     : 1.1
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hash Table implementation for Auction bid in CSV files
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include <list>
#include <iterator>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // FIXME (1): Define structures to hold bids

    // pointer list to hold bids
    list<Bid>* _bidTable;

    unsigned int hash(int key);

public:
    HashTable();
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    bool IsEmpty(HashTable* hashTable);
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // FIXME (2): Initialize the structures used to hold bids
    
    // set the list to the deafault size
    _bidTable = new list<Bid>[DEFAULT_SIZE];
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    // FIXME (3): Implement logic to free storage when class is destroyed

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
    // FIXME (4): Implement logic to calculate a hash value
    
    // key will be bidId % size-of-list
    return key % DEFAULT_SIZE;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // FIXME (5): Implement logic to insert a bid

    // convert bidId string to int, hash the key
    // at key index, add bid
    int index = hash(stoi(bid.bidId));
    _bidTable[index].push_back(bid);
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (6): Implement logic to print all bids
    
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
    // FIXME (7): Implement logic to remove a bid
    
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
    // FIXME (8): Implement logic to search for and return a bid
    
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

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    
    if (!hashTable->IsEmpty(hashTable)) {
        int choice = 0;
        cout << "The list is not empty... do you want to add to it? 1:y, 2:n";
        cin >> choice;
        switch (choice) {
        case 1: {
            break;
        }
        case 2: {
            return;
        }
        default:
            break;
        }
        
    }

    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    /*vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;*/

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    int bidKeyAsInt;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;
    bidTable = new HashTable();
    

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            // prompt user for bidKey to search for
            // check that input is an integer
            // convert to string for method call
            cout << "Enter a bidID to search for: ";
            cout << "Enter a number: ";
            cin >> bidKeyAsInt;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Bad entry. Enter a NUMBER: ";
                cin >> bidKeyAsInt;
            }

            bidKey = to_string(bidKeyAsInt);

            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            cout << "Enter a bidID to search for: ";
            cout << "Enter a number: ";
            cin >> bidKeyAsInt;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Bad entry. Enter a NUMBER: ";
                cin >> bidKeyAsInt;
            }

            bidKey = to_string(bidKeyAsInt);
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
