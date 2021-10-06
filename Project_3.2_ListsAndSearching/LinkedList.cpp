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
    
    // allocate a new Node, copy head to 'last' Node
    Node* app = new Node();        
    Node* last = this->_head;

    // add bid to new Node 'app'
    // set 'next' pointer to NULL bc it will be last in list
    app->_bid = bid;
    app->_next = NULL;

    // list is empty ie 'head' is empty
    // new node becomes head, set 'prev' pointer to NULL
    if (this->_head == NULL) {
        app->_prev = NULL;
        this->_head = app;
        return;
    }

    // iterate through list, check for NULL value at 'next'
    while (last->_next != NULL) {
        last = last->_next;
    }

    // set last Node to point to the new Node
    // set the new Node 'prev' to point to (now former) last Node
    last->_next = app;
    app->_prev = last;

    return;

    // FIXME (3): Implement append logic
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // allocate a new Node
    Node* pre = new Node();            
    
    // add 'bid' to new Node, set 'next' pointer to head of list
    // set 'prev' of new Node to 'NULL' bc it's the front
    pre->_bid = bid;
    pre->_next = this->_head;
    pre->_prev = NULL;
    
    // if the current head is not empty
    if (this->_head != NULL) { 
        
        // set the head 'prev' to the new Node
        this->_head->_prev = pre;
    }
    this->_head = pre;



    // FIXME (4): Implement prepend logic
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (5): Implement print logic

    // create a Node called 'print' and an empty bid
    // create an int for displaying numbers
    Node* print = new Node();
    Bid bid;
    int bidCount = 0;
    
    // 'head' to 'print'
    print = this->_head;

    // if list is empty
    if (print == NULL) {
        cout << "There are no bids to display / list is empty." << endl;
        return;
    }

    // loop thru list check for NULL pointer in 'next'
    while (print->_next != NULL) {
        bid = print->_bid;
        print = print->_next;
        bidCount++;
        // display the bid
        cout << bidCount << ": " << bid.bidId << ": " << bid.title << " | " << bid.amount       
            << " | " << bid.fund << endl;
        
    }

    // display the very last bid
    bidCount++;
    bid = print->_bid;
    cout << bidCount << ": " << bid.bidId << ": " << bid.title << " | " << bid.amount       
        << " | " << bid.fund << endl;
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (6): Implement remove logic
    
    // create a new Node, point it to the head of the list
    Node* del;
    del = this->_head;

    // list is empty, return
    if (del == NULL) {
        cout << "The list is empty, there is nothing to delete." << endl;
        return;
    }
    
    // search for the Node to be deleted
    while (del->_bid.bidId != bidId) {
        del = del->_next;

        // if the next Node is NULL AND the bidId's don't match
        if (del->_next == NULL && del->_bid.bidId != bidId) {       
            cout << "BidID cannot be found; nothing was deleted." << endl;
            return;
        }
    }

    // if last node is not being deleted
    // change the 'prev' of the 'next' Node
	// to the 'prev' of the deleted Node
    if (del->_next != NULL) {
        del->_next->_prev = del->_prev;
    }
    
    // if the first node is not being deleted
    // change the 'next' of the 'prev' Node to
	// the 'next' of the deleted Node
    if (del->_prev != NULL) {
        del->_prev->_next = del->_next;
    }
    delete del;
    cout << "Bid " << bidId << " was successfully " <<
		"deleted from the list." << endl;

    return;
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIXME (7): Implement search logic

    // create a Node call search, create an empty bid, set 'search' to 'head' of list
    Node* search = new Node();
    Bid bid;
    search = this->_head;

    // if list is empty, return empty bid
    if (search == NULL) {
        return bid;
    }

    // 'head' Node is the search, return it
    if (search->_bid.bidId == bidId) {
        bid = search->_bid;         
        return bid;
    }
    
    // iterate through list looking for search ID
    while (search->_bid.bidId != bidId) {
        search = search->_next;
        
        // if the next Node is NULL AND the bidId's don't match
        if (search->_next == NULL && search->_bid.bidId != bidId) {     
            return bid;
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
