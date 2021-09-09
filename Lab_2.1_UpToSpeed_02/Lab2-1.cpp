//============================================================================
// Name        : Lab2-2.cpp
// Course      : CS260-T1002 21EW1
// Author      : Lawrence Artl
// Version     : 1.1
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 2-2 Up to Speed in C++, Part 2
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

#include "CSVparser.hpp"


 //FIXME (1): Reference the CSVParser library

using namespace std;
using namespace csv;


//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

struct Bid {
    //added extra properties to bids, just in case we want them in the future

    string title;
    string articleID;
    string dept;
    string closeDate;
    string inventoryID;
    string vehicleID;
    string receipt;
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
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    std::cout << bid.title << " | " << bid.amount << " | " << bid.fund << std::endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter title: ";
    cin.ignore();
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

// Custom method to take a row object, converted to a string, then 
// delimited by spaces to individual properties, to be stored
// in a 'Bid' object

Bid MakeABid(string row) {
    Bid newBid;
    //strings for each column item
    string articleTitle, articleID, dept, closeDate, winBid, invID, vehID, recNum, fund;
    //iterator for number of columns
    int col = 9;
    //char that marks divide between items once file is parsed
    string delimiter = "|";

    //delimiter function vars
    size_t pos = 0;
    string token;

    while ((pos = row.find(delimiter)) != string::npos) {
        token = row.substr(0, pos);
        token.erase(remove(token.begin(), token.end(), ' '), token.end());

        switch (col) {
        case 9: {
            articleTitle = token;
            break;
        }
        case 8: {
            articleID = token;
            break;
        }
        case 7: {
            dept = token;
            break;
        }
        case 6: {
            closeDate = token;
            break;
        }
        case 5: {
            winBid = token;
            break;
        }
        case 4: {
            invID = token;
            break;

        }
        case 3: {
            vehID = token;
            break;
        }
        case 2: {
            recNum = token;
            break;
        }
        case 1: {
            fund = token;
            break;
        }
        }
        col--;
        if (col < 1) {
            col = 9;
        }
        row.erase(0, pos + delimiter.length());
    }

    newBid.title = articleTitle;
    newBid.articleID = articleID;
    newBid.closeDate = closeDate;
    newBid.dept = dept;
    newBid.inventoryID = invID;
    newBid.receipt = recNum;
    newBid.vehicleID = vehID;
    newBid.fund = fund;
    //newBid.amount = winBid;
    newBid.amount = strToDouble(winBid, '$');

    return newBid;

}


/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
	// FIXME (2): Define a vector data structure to hold a collection of bids.

    vector<Bid> theseBids;
    Bid newBid;
    string line, article, winBid, fund;
    double amount;
    ostringstream convert;          //use ostring stream object 'convert' to convert class 'Row' to a string obj
    

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

	// loop to read rows of a CSV file
    for (int i = 0; i < file.rowCount(); i++) {
        // FIXME (3): create a data structure to hold data from each row and add to vector
        article = file[i][0];
        fund = file[i][8];
        /*cout << file[i][4] << endl;
        cout << strToDouble(file[i][4], '$') << endl;*/
        winBid = file[i][4];
        amount = strToDouble(winBid, '$');

        newBid.title = article;
        newBid.fund = fund;
        newBid.amount = amount;
        
        //displayBid(newBid);
        theseBids.push_back(newBid);    //add 'newBid' to the vector of Bids
        
        //this also works...
        //convert << file.getRow(i);      //convert the Row at position 'i' to a string
        //line = convert.str();           //store the converted string in 'line'
        //newBid = MakeABid(line);        //send 'line' to 'MakeABid' method for delimination to individual items, returned as a Bid object

        //more info here:
        //https://github.com/rsylvian/CSVparser
    }
    return theseBids;
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
    //this handles numbers above 999.99 strangely
    //these numbers are converted to '0' when made into doubles
    str.erase(remove(str.begin(), str.end(), ','));
    str.erase(remove(str.begin(), str.end(), ch));
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
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // FIXME (4): Define a vector to hold all the bids
    vector<Bid> ListOfBids;
    //?type? ?variable?;

    // FIXME (7a): Define a timer variable
    clock_t start;
    double duration;
    //?type? ?variable?;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
        	cout << "Not currently implemented." << endl;

            break;
        case 2:
            // FIXME (7b): Initialize a timer variable before loading bids
            start = clock();    //get the start time for now

            // FIXME (5): Complete the method call to load the bids
            ListOfBids = loadBids(csvPath);

            // FIXME (7c): Calculate elapsed time and display result
            duration = ((double)clock() - start) / (double)CLOCKS_PER_SEC;  //cast to double so no overflow occurs
            cout << "Loaded bids in " << duration << " seconds." << '\n';   //show change in time

            
            break;
        case 3:
            // FIXME (6): Loop and display the bids read
            if (ListOfBids.size() == 0) {
                cout << "Please select '2' to Load Bids first!" << endl;
                break;
            }
            
            for (int i = 0; i < ListOfBids.size(); ++i) {
                displayBid(ListOfBids.at(i));
            }
            cout << endl;

            break;

        // custom case for testing 'stringToDouble' method

        case 4:
            string num;
            double newNum;
            cout << "Enter a number to convert to a string: ";
            cin >> num;
            cout << endl;
            num = '$' + num + ".00";
            newNum = strToDouble(num, '$');
            cout << "Number " << num << " is now : " << newNum << endl;
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
