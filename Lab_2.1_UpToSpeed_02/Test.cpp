//#include <algorithm>
//#include <iostream>
//#include <time.h>
//#include <string>
//#include <ctime>
//#include <sstream>
//
//#include "CSVparser.hpp"
//
//
//
//using namespace std;
//using namespace csv;
//
//double strToDouble(string str, char ch);
//
//struct Bid {
//    //added extra properties to bids, just in case we want them in the future
//    string title;
//    string articleID;
//    string dept;
//    string closeDate;
//    string inventoryID;
//    string vehicleID;
//    string receipt;
//    string fund;
//    double amount;
//    Bid() {
//        amount = 0.0;
//    }
//};
//
//
//void displayBid(Bid bid) {
//    std::cout << bid.title << " | " << bid.amount << " | " << bid.fund << std::endl;
//    return;
//}
//
//Bid getBid() {
//    Bid bid;
//
//    cout << "Enter title: ";
//    cin.ignore();
//    getline(cin, bid.title);
//
//    cout << "Enter fund: ";
//    cin >> bid.fund;
//
//    cout << "Enter amount: ";
//    cin.ignore();
//    string strAmount;
//    getline(cin, strAmount);
//    bid.amount = strToDouble(strAmount, '$');
//
//    return bid;
//}
//
////separate individual values from string that is passed in
//Bid MakeABid(string row) {
//    Bid newBid;
//    //strings for each column item
//    string articleTitle, articleID, dept, closeDate, winBid, invID, vehID, recNum, fund;
//    //iterator for number of columns
//    int col = 9;
//    //char that marks divide between items once file is parsed
//    string delimiter = "|";
//
//    //delimiter function vars
//    size_t pos = 0;
//    string token;
//
//    while ((pos = row.find(delimiter)) != string::npos) {
//        token = row.substr(0, pos);
//        token.erase(remove(token.begin(), token.end(), ' '), token.end());
//
//        switch (col) {
//        case 9: {
//            articleTitle = token;
//            break;
//        }
//        case 8: {
//            articleID = token;
//            break;
//        }
//        case 7: {
//            dept = token;
//            break;
//        }
//        case 6: {
//            closeDate = token;
//            break;
//        }
//        case 5: {
//            winBid = token;
//            break;
//        }
//        case 4: {
//            invID = token;
//            break;
//
//        }
//        case 3: {
//            vehID = token;
//            break;
//        }
//        case 2: {
//            recNum = token;
//            break;
//        }
//        case 1: {
//            fund = token;
//            break;
//        }
//        }
//        col--;
//        if (col < 1) {
//            col = 9;
//        }
//        row.erase(0, pos + delimiter.length());
//    }
//   
//    newBid.title = articleTitle;
//    newBid.articleID = articleID;
//    newBid.closeDate = closeDate;
//    newBid.dept = dept;
//    newBid.inventoryID = invID;
//    newBid.receipt = recNum;
//    newBid.vehicleID = vehID;
//    newBid.fund = fund;
//    newBid.amount = strToDouble(winBid, '$');
//
//    return newBid;
//
//}
//
//vector<Bid> loadBids(string csvPath) {
//    
//    vector<Bid> theseBids;
//    Bid newBid;
//    string line;
//    ostringstream convert;          //use ostring stream object 'convert' to convert class 'Row' to a string obj
//    
//    // initialize the CSV Parser using the given path
//    
//    Parser file = Parser(csvPath);
//    file.getRow(0);
//
//    // loop to read rows of a CSV file
//    for (int i = 0; i < file.rowCount(); i++) {
//        // FIXME (3): create a data structure to hold data from each row and add to vector
//        
//        
//        convert << file.getRow(i);      //convert the Row at position 'i' to a string
//        line = convert.str();           //store the converted string in 'line'
//        newBid = MakeABid(line);        //send 'line' to 'MakeABid' method for delimination to individual items, returned as a Bid object
//        theseBids.push_back(newBid);    //add 'newBid' to the vector of Bids
//        cout << file[0][0] << endl;
//        
//        //this also works...
//        /*string article = file[i]["ArticleTitle"];
//        string fund = file[i]["Fund"];
//        int bid = strToDouble(file[i]["WinningBid"], '$');*/
//
//        //more info here:
//        //https://github.com/rsylvian/CSVparser
//
//    }
//    return theseBids;
//}
//
//double strToDouble(string str, char ch) {
//    str.erase(remove(str.begin(), str.end(), ch), str.end());
//    return atof(str.c_str());
//}
//
//int main(int argc, char* argv[]) {
//
//    // process command line arguments
//
//    string csvPath;
//    switch (argc) {
//    case 2:
//        csvPath = argv[1];
//        break;
//    default:
//        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
//    }
//
//    // FIXME (4): Define a vector to hold all the bids
//    vector<Bid> ListOfBids;
//    //?type? ?variable?;
//
//    // FIXME (7a): Define a timer variable
//    clock_t start;
//    double duration;
//    //? type ? ? variable ? ;
//
//    int choice = 0;
//    while (choice != 9) {
//        cout << "Menu:" << endl;
//        cout << "  1. Enter a Bid" << endl;
//        cout << "  2. Load Bids" << endl;
//        cout << "  3. Display All Bids" << endl;
//        cout << "  9. Exit" << endl;
//        cout << "Enter choice: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1:
//            cout << "Not currently implemented." << endl;
//
//            break;
//        case 2:
//            // FIXME (7b): Initialize a timer variable before loading bids
//            start = clock();    //get the start time for now
//            // FIXME (5): Complete the method call to load the bids
//            ListOfBids = loadBids(csvPath);
//
//            // FIXME (7c): Calculate elapsed time and display result
//            duration = ((double)clock() - start) / (double)CLOCKS_PER_SEC;  //cast to double so no overflow occurs
//            cout << "Loaded bids in " << duration << " seconds." << '\n';   //show change in time
//
//            break;
//        case 3:
//            // FIXME (6): Loop and display the bids read
//            for (int i = 0; i < ListOfBids.size() ; ++i) {
//                displayBid(ListOfBids.at(i));
//            }
//            cout << endl;
//
//            break;
//        }
//    }
//
//    cout << "Good bye." << endl;
//
//    return 0;
//}