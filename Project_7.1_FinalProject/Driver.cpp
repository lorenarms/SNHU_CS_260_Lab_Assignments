//============================================================================
// Name        : FinalProject.cpp
// Author      : Lawrence Artl 
// Version     : 1.0.1
// Copyright   : Copyright © 2020 Artl
// Description : Hash Table implementation for Auction bid in CSV files
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include <list>
#include <iterator>
#include <vector>
#include <conio.h>

#include "HashTable.h"
#include "Bid.h"
#include "MenuDriver.h"
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

//static unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);
//int MainMenu(MenuDriver mainMenu, MenuDriver newCursor);
void FunctionToLoadBids(string csvPath, HashTable* bidTable, MenuDriver newMenu);
void FunctionToSearchForBids(MenuDriver newMenu, HashTable* bidTable);
void FunctionToRemoveBid(MenuDriver newMenu, HashTable* bidTable);
void BannerConstructor(string banner[]);


//============================================================================
// Methods for handling bids
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

    csv::Parser file = csv::Parser(csvPath);
    int rows = file.rowCount();
    hashTable->DEFAULT_SIZE = rows;
    
    MenuDriver shortMenu;
    MenuDriver shortCursor;

    if (!hashTable->IsEmpty(hashTable)) {
        
        // Check if the hashtable is empty so the user doesn't
        // double up bids in the list
        shortMenu.SetRow(12);
        vector <string> menu = { "yes", "no "};
        int m = shortMenu.MenuModifier(menu);
        int choice = 2;
        bool run = true;
        cin.clear();
        cout << "The list is not empty... do you want to add to it?";
        while (run) {
            shortMenu.RunMenu(menu, choice, 1);
            switch (choice) {
            case 1: {
                run = false;
                break;
            }
            case 2: {
                run = false;
                return;
            }
            
            default:
                run = false;
                break;
            }
        }

    }
    
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    
    
   
    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            
            // push this bid to the end
            hashTable->Insert(bid);
        }
    }
    catch (csv::Error& e) {
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

    // Determine the amount of table spaces needed
    // open the file and read the number of rows
    csv::Parser file = csv::Parser(csvPath);
    int rows = file.rowCount();
    file.~Parser();

    // Create objects for use in main menu
    Bid bid;
    clock_t ticks;
    MenuDriver newMenu;
    MenuDriver newCursor;
    HashTable* bidTable;
    string banner[3];
    
    // Create the hash table with the correct number of rows
    bidTable = new HashTable(rows);
    
    
    // Create the banner for the main page
    // Find the banner width and modify for centering 
    BannerConstructor(banner);
    int bannerWidth = banner[0].length();
    bannerWidth /= 2;
    
    // Create primatives for use in main menu
    int bidKeyAsInt;
    int selection = 1;
    bool run = true;

    // Main menu options
    vector <string> menu = { "Load Bids", "Display All Bids", "Find Bid" , "Remove Bid", "Delete Table", "Exit" };
    
    // vars for menu centering
    int m = newMenu.MenuModifier(menu);
    int windowWidth = newCursor.GetWindowWidth();		//center's menu
    int menuDrawCol = windowWidth / 2;
    menuDrawCol -= (m / 2);
    newCursor.HideCursorBlink();
    
    // Main menu
    while (run) {
        // Draw the headline
        newMenu.SetColor(12);
        for (int i = 0; i < 3; i++) {
            newMenu.SetNewCursor(i, (windowWidth / 2) - bannerWidth);
            cout << banner[i];
        }

        // Set menu position and color, draw it
        newMenu.SetColor(15);
        newMenu.SetRow(5);
        newMenu.RunMenu(menu, selection, menuDrawCol);
        
        // Clear the cin cache, keeps '\n' from affecting output
        cin.sync();
        while (_kbhit()) _getch();
        
        // Options for main menu
        switch (selection) {
        
        case 1:
            FunctionToLoadBids(csvPath, bidTable, newMenu);
            break;

        case 2:

            // Function to print all bids
            system("cls");
            bidTable->PrintAll();
            newMenu.SetColor(14);
            cout << "PRESS ENTER TO CLEAR AND CONTINUE..." << endl;
            newMenu.SetColor(15);
            cin.clear();
            while (newMenu.CheckKeyPress() != 2) {

            }
            system("cls");
            cin.clear();
            cin.ignore();
            break;
        
        case 3:
            FunctionToSearchForBids(newMenu, bidTable);
            selection = 3;
            break;
        
        case 4:
            FunctionToRemoveBid(newMenu, bidTable);
            selection = 4;
            break;
        case 5: {

            // create a new menu, display it for confirmation
            MenuDriver shortMenu;
            MenuDriver shortCursor;
            shortMenu.SetRow(12);
            vector <string> menu = { "yes", "no "};
            int m = shortMenu.MenuModifier(menu);
            int choice = 2;
            bool run = true;
            cin.clear();
            cout << "Are you sure you want to delete the table?";
            while (run) {
                shortMenu.RunMenu(menu, choice, 1);
                switch (choice) {
                case 1: {

                    // delete the hashTable, create a new hashTable, display messages for user
                    bidTable->~HashTable();
                    bidTable = new HashTable(rows);
                    cout << "Table deleted." << endl;
                    newMenu.SetColor(14);
                    cout << "PRESS ENTER TO CLEAR AND CONTINUE..." << endl;
                    newMenu.SetColor(15);
                    while (newMenu.CheckKeyPress() != 2) {}
                    system("cls");
                    run = false;
                    break;
                }
                case 2: {
                    run = false;
                    break;
                }
                default:
                    run = false;
                    break;
                }
            }
            break;
        }

        case 6:
            run = false;
            break;
        default:
            break;
        }
    }
   
    cout << "Good bye." << endl;
    return 0;
}

//
// Insert a bid function
//
void FunctionToLoadBids(string csvPath, HashTable* bidTable, MenuDriver newMenu) {
    // Initialize a timer variable before loading bids
    clock_t ticks = clock();
    
    // Complete the method call to load the bids
    loadBids(csvPath, bidTable);

    // Calculate elapsed time and display result
    ticks = clock() - ticks; // current clock ticks minus starting clock ticks
    cout << "time: " << ticks << " clock ticks" << endl;
    cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
    
    // Pause and wait for 'enter' from user
    newMenu.SetColor(14);
    cout << "PRESS ENTER TO CLEAR AND CONTINUE..." << endl;
    newMenu.SetColor(15);
    while (newMenu.CheckKeyPress() != 2) {  }
    system("cls");
    return;
}

//
// Search for a bid function
//
void FunctionToSearchForBids(MenuDriver newMenu, HashTable* bidTable) {
    newMenu.SetNewCursor(12, 0);
    cout << "Enter a bidID to search for; enter a number: ";
    int bidKeyAsInt;
    cin >> bidKeyAsInt;
    // check that the entry is valid
    while (cin.fail()) {
        cin.clear();    cin.ignore(INT_MAX, '\n');
        cout << "\nBad entry. Enter a NUMBER: ";
        cin >> bidKeyAsInt;
    }
    //create local variables
    string bidKey = to_string(bidKeyAsInt);
    clock_t ticks = clock();
    Bid bid = bidTable->Search(bidKey);

    ticks = clock() - ticks; // current clock ticks minus starting clock ticks

    //found the bid, display the bid
    if (!bid.bidId.empty()) {
        displayBid(bid);
        cin.clear();    cin.ignore(INT_MAX, '\n');
    }
    // bid didn't exist, display error
    else {
        cout << "Bid Id " << bidKey << " not found." << endl;
        cin.clear();    cin.ignore(INT_MAX, '\n');
    }

    cout << "time: " << ticks << " clock ticks" << endl;
    cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
    newMenu.SetColor(14);
    cout << "PRESS ENTER TO CLEAR AND CONTINUE..." << endl;
    newMenu.SetColor(15);
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    while (newMenu.CheckKeyPress() != 2) {    }
    system("cls");
    
}

//
// Remove bid function
//
void FunctionToRemoveBid(MenuDriver newMenu, HashTable* bidTable) {
    newMenu.SetNewCursor(12, 0);
    cout << "Enter a bidID to search for; enter a number: ";
    int bidKeyAsInt;
    cin >> bidKeyAsInt;
    // check that the entry is valid
    while (cin.fail()) {
        cin.clear();    cin.ignore(INT_MAX, '\n');
        cout << "\nBad entry. Enter a NUMBER: ";
        cin >> bidKeyAsInt;
    }

    // create local variables
    Bid bid;
    string bidKey = to_string(bidKeyAsInt);

    // dispaly the found bid, or display error message
    if (!bid.bidId.empty()) {
        displayBid(bid);
        cin.clear();    cin.ignore(INT_MAX, '\n');
    }
    else {
        cout << "Bid Id " << bidKey << " not found." << endl;
        cin.clear();    cin.ignore(INT_MAX, '\n');
    }
    //remove the bid when found
    bidTable->Remove(bidKey);
    cin.clear();
    newMenu.SetColor(14);
    cout << "PRESS ENTER TO CLEAR AND CONTINUE..." << endl;
    newMenu.SetColor(15);
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    while (newMenu.CheckKeyPress() != 2) {    }
    system("cls");
    cin.clear();
}

//
// Banner function
//
void BannerConstructor(string banner[]) {
    
    // create an array of strings that have the header here
    banner[0] = "____ ___  _ ___     _  _ ____ _  _ ___ _  _ _    _   _    ____ ____ _    ____ ____ ";
    banner[1] = "|___ |__] | |  \\    |\\/| |  | |\\ |  |  |__| |     \\_/     [__  |__| |    |___ [__  ";
    banner[2] = "|___ |__] | |__/    |  | |__| | \\|  |  |  | |___   |      ___] |  | |___ |___ ___] ";
}



