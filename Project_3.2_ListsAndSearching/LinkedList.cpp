//============================================================================
// Name        : LinkedList.cpp
// Author      : Lawrence Artl III
// Version     : 1.1
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

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
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    class Node {
    public:
        Bid _bid;
        Node* _next;
        Node* _prev;
    };

    Node* _head;
    
public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    _head = NULL;           // give the list a 'head' to reference for the front of the list
    
    // FIXME (2): Initialize housekeeping variables
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    
    Node* new_node = new Node();        // allocate a new Node
    Node* last = this->_head;           // copy 'head' to new Node called 'last'

    new_node->_bid = bid;               // add 'bid' to the new Node
    new_node->_next = NULL;             // set the 'next' pointer to NULL (this node will be the last in the list)

    if (this->_head == NULL) {          // if the 'head' is empty, ie list is empty
        new_node->_prev = NULL;         // set the new Node's 'prev' pointer to NULL
        this->_head = new_node;         // make the new Node the head
        return;                         // done now, return
    }

    while (last->_next != NULL) {       // otherwise, loop through the list
        last = last->_next;             // start at the head ('last' Node) and keep checking for a
    }                                   // NULL value for the 'next' pointer at each Node

    last->_next = new_node;             // once the last Node is found, set its 'next' point to the new Node
    new_node->_prev = last;             // set the new Node's prev pointer to the Node we just found

    return;                             // done, return

    // FIXME (3): Implement append logic
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    Node* new_node = new Node();            // allocate a new Node
    new_node->_bid = bid;                   // add 'bid' to the new Node
    new_node->_next = this->_head;          // set the 'next' pointer to point to the current head of the list
    new_node->_prev = NULL;                 // set the 'prev' of the new Node to 'NULL' since it's at the front of the list
    if (this->_head != NULL) {              // if the current head is not empty
        this->_head->_prev = new_node;      // set it's prev pointer to point to the new Node, which is the new head
    }
    this->_head = new_node;                 // set the head of the list as the new node

    // FIXME (4): Implement prepend logic
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (5): Implement print logic

    Node* print = new Node();        // create a new Node called 'print'
    Bid bid;                         // create empty bid
    int bidCount = 0;                // for displaying a number next to each bid
    print = this->_head;             // add 'head' into 'last'
    if (print == NULL) {             // if 'head' is NULL, list is empty, return
        cout << "There are no bids to display / list is empty." << endl;
        return;
    }


    while (print->_next != NULL) {          // otherwise, loop through the list
        bid = print->_bid;                  // set 'bid' equal the bid in node 'print'
        print = print->_next;               // increment 'print' to the next node
        bidCount++;                         // increment bid count to display a number in front of each bid
        cout << bidCount << ": " << bid.bidId << ": " << bid.title << " | " << bid.amount       // display the bid
            << " | " << bid.fund << endl;
        
    }
    bidCount++;
    bid = print->_bid;
    cout << bidCount << ": " << bid.bidId << ": " << bid.title << " | " << bid.amount       // display the very last bid
        << " | " << bid.fund << endl;
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (6): Implement remove logic


}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIXME (7): Implement search logic

    Node* search = new Node();              // create new Node called 'search'
    Bid bid;                                 // create new empty Bid
    search = this->_head;                    // set 'search' equal to 'head' of list
    if (search == NULL) {                       // list is empty
        return bid;                             // return empty bid
    }
    if (search->_bid.bidId == bidId) {      // head contains search
        bid = search->_bid;         
        return bid;                 // return head bid
    }
    
    while (search->_bid.bidId != bidId) {                               // while the bid ID of search is not the same as the passed bidID
        search = search->_next;                                          // set 'search' to the next Node
        if (search->_next == NULL && search->_bid.bidId != bidId) {     // if the next Node is NULL AND the bidId's don't match
            return bid;                                                  // return an empty bid for the error
        }

    }
    bid = search->_bid;     // otherwise, set 'bid' to be equal to the bid in node 'search'
    return bid;             // return the bid
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    
    Node* last = new Node();        // create a new Node called 'last'
    last = this->_head;             // add 'head' into 'last'
    if (last == NULL) {             // if 'head' is NULL, list is empty, return '0'
        return 0;
    }
    else if (last->_next == NULL && last->_prev == NULL && last != NULL) {
        return 1;                   // if head has no pointers but isn't null, list has 1 item, return '1'
    }

    int size = 1;                   // list isn't empty, has at least 1 item
    while (last->_next != NULL) {   // otherwise, loop through the list
        last = last->_next;         // start at the head ('last' Node) and keep checking for a
        ++size;                     // increment size
    }

    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
            //cout << bid.bidId << endl;
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
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
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
        bidKey = "98157";
    }

    clock_t ticks;

    LinkedList bidList;
    
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
