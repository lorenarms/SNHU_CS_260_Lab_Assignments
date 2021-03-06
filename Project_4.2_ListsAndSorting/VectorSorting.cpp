//============================================================================
// Name        : VectorSorting.cpp
// Author      : Lawrence Artl
// Version     : 1.1
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
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
 * Prompt user for bid information using console (std::in)
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
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
    // declare and set variables for use in loop
    int low = begin;
    int high = end;
    int midpoint = begin + (end - begin) / 2;
    Bid temp;
    Bid pivot = bids.at(midpoint);
    bool done = false;

    // loop until low and high are equal
    while (!done) {

        // if 'low' index bid is less than the pivot bid
        // increment 'low'
        while (bids.at(low).title < pivot.title) {
            ++low;
        }
        // if pivot bid is less than the 'high' index bid
        // decrement 'high'
        while (pivot.title < bids.at(high).title) {
            --high;
        }
        if (low >= high) {
            done = true;
        }

        // bids passed to here will be unequal
        // bid at the 'low' index will be higher than the pivot
        // bid at the 'high' index will be lower than the pivot
        // swap them
        else {
            temp = bids.at(low);
            bids.at(low) = bids.at(high);
            bids.at(high) = temp;

            ++low;
            --high;
        }
    }

    // return the high index, which will be equal to the pivot index
    return high;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
    int j = 0;

    // check if vector size is 0 or 1 / no sorting needed
    if (begin >= end) {
        return;
    }

    // partition the data within the vector at a pivot point
    // low values / pivot / high values
    j = partition(bids, begin, end);

    //recursively sort the low partition (begin to j)
    quickSort(bids, begin, j);

    // recursively sort the high partition (j + 1 to end)
    quickSort(bids, j + 1, end);

    return;

}

// FIXME (1a): Implement the selection sort logic over bid.title

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
    
    // get the size of the bid vector, declare a temporary integer
    int size = bids.size();
    if (size == 0 || size == 1) {
        cout << "There is nothing to sort / list is empty or too small." << endl;
        return;
    }

    int temp;

    // loop through vector starting at 0
    for (int i = 0; i < size - 1; ++i) {

        // get the bid at index 'i', store in 'left', set temp int to 'i'
        Bid left = bids.at(i);
        temp = i;

        // inner loop, loop through vector starting at next index
        for (int j = i + 1; j < size; ++j) {

            // check current index bid title compared to above index bid title
            // if above title is greater than current bid title, swap them
            if (left.title > bids.at(j).title) {
                left = bids.at(j);
                temp = j;
            }
        }
        // if the above condition was false, 'i' and 'temp' will be equal
        // no swap will occur
        swap(bids.at(i), bids.at(temp));
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
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        // FIXME (1b): Invoke the selection sort and report timing results
        case 3:
            // initialize timer
            ticks = clock();

            // call selection sort
            selectionSort(bids);

            cout << bids.size() << " bids sorted by title" << endl;

            // calculate elapsed time, display result
            ticks = clock() - ticks;
            cout << "Time: " << ticks << " CPU clock ticks." << endl;
            cout << "Time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds." << endl;

            break;

        // FIXME (2b): Invoke the quick sort and report timing results
        case 4:
            // initialize timer
            ticks = clock();

            
            // call selection sort
            quickSort(bids, 0, bids.size() - 1);

            cout << bids.size() << " bids QuickSorted by title" << endl;

            // calculate elapsed time, display result
            ticks = clock() - ticks;
            cout << "Time: " << ticks << " CPU clock ticks." << endl;
            cout << "Time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds." << endl;

            break;

        }
    }

    cout << "Good bye." << endl;

    return 0;
}
