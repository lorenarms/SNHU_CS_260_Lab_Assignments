//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : JYour name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

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

// FIXME (1): Internal structure for tree node
struct Node {
    Bid bid;
    Node* left;
    Node* right;
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {
    

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void removeNode(Node* node, string bidId);
    void deleteTree(Node* node);        // method to delete all nodes

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

void displayBid(Bid bid);   //forward declaration

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    this->root = NULL;

}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    deleteTree(this->root); // call private method to delete all nodes
    return;
}

// this method recursively deletes each node in the tree
void BinarySearchTree::deleteTree(Node* node) {
    if (node == NULL) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
    node = NULL;
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    if (this->root == NULL) {
        cout << "This tree is empty, try filling it with some bids!" << endl;
        return;
    }

    // call private method to print out the tree in order
    // this method is simple because the tree is already in order

    inOrder(this->root);
    return;
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) Implement inserting a bid into the tree
    Node* curr = new Node();
    Node* toAdd = new Node();

    toAdd->bid = bid;
    toAdd->left = toAdd->right = NULL;

    // this algorithm is the same as the Add() method
    // both methods add bids to the tree in the correct order
    // actual insertion would require tree rearanging

    // tree is empty, make this first node the root
    if (this->root == NULL) {
        this->root = toAdd;
        return;
    }

    //tree is not empty, add to root
    else {
        curr = this->root;
        while (curr != NULL) {
            // check which direction to add to
            if (toAdd->bid.bidId < curr->bid.bidId) {
                if (curr->left == NULL) {
                    curr->left = toAdd;
                    return;
                }
                // left node is not empty
                // make left node current node, loop again
                else {
                    curr = curr->left;
                }
            }
            // same as above, but with right
            else {
                if (curr->right == NULL) {
                    curr->right = toAdd;
                    return;
                }
                else {
                    curr = curr->right;
                }
            }
        }
    }

}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (4a) Implement removing a bid from the tree
    removeNode(root, bidId);    // call to private remove method
    return;
}

void BinarySearchTree::removeNode(Node* node, string bidId) {
    Node* parent = NULL;

    // recursively searches for the desired bidId to delete
    while (node != NULL) {
        if (node->bid.bidId == bidId) {
            // node is a leaf
            if (!node->left && !node->right) {
                if (!parent) {
                    this->root = NULL;
                }
                else if (parent->left == node) {
                    parent->left = NULL;
                }
                else
                    parent->right = NULL;
            }
            // node has left child, no right child
            else if (node->left && !node->right) {
                if (!parent) {
                    this->root = node->left;
                }
                else if (parent->left == node) {
                    parent->left = node->left;
                }
                else
                    parent->right = node->left;
            }
            // node has right child, no left child
            else if (!node->left && node->right) {
                if (!parent) {
                    this->root = node->right;
                }
                else if (parent->left == node) {
                    parent->left = node->right;
                }
                else
                    parent->right = node->right;
            }
            // node has two children
            // must be replaced with another node
            // this algorithm rinds the leftmost node of rightmost sub
            // replaces node to be deleted
            else {
                Node* succ = NULL;
                succ = node->right;
                while (succ->left != NULL) {

                    succ = succ->left;
                }
                node->bid = succ->bid;
                // recursively search for old leaf node and delete it
                // starting at the current node that was just replaced
                removeNode(node->right, succ->bid.bidId);
            }
            return;
        }
        // bid not found yet, set new parent and current
        // loop again
        else if (node->bid.bidId < bidId) {
            parent = node;
            node = node->right;
        }
        else {
            parent = node;
            node = node->left;
        }
    }
    return;
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (3) Implement searching the tree for a bid
    Node* parent = NULL;
    Node* node = root;
    
    // search for the desired bidId while the node is not NULL
    // uses same algorithm as "delete"
    while (node != NULL) {
        // bid has been found
        if (node->bid.bidId == bidId) {
            return node->bid;
        }
        // bid is more, go right
        else if (node->bid.bidId < bidId) {
            parent = node;
            node = node->right;
        }
        // bid is less, go left
        else {
            parent = node;
            node = node->left;
        }
    }
    // bid not found, make empty bid to return
	Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (2b) Implement inserting a bid into the tree

    Node* curr = new Node();
    Node* toAdd = new Node();

    toAdd->bid = bid;
    
    // this algorithm adds nodes in order of bidId
    // this is not the most efficient for tree height, however
    // this does not require sorting afterwards

    if (this->root == NULL) {
        this->root = toAdd;     // make this bid the tree root (tree is empty)
        return;
    }
    else {
        // tree is not empty, loop until an empty node is found
        curr = this->root;
        while (curr != NULL) {
            // search left
            if (toAdd->bid.bidId < curr->bid.bidId) {
                if (curr->left == NULL) {
                    curr->left = toAdd;
                    return;
                }
                else {
                    curr = curr->left;
                }
            }
            // search right
            else {
                if (curr->right == NULL) {
                    curr->right = toAdd;
                    return;
                }
                else {
                    curr = curr->right;
                }
            }
        }
    }
}


void BinarySearchTree::inOrder(Node* node) {
    if (node == NULL) {
        return;
    }

    // recursive call to inOrder to keep loading nodes until the last one is reached
    // then start printing nodes, working upwards 
    inOrder(node->left);
    Bid bid = node->bid;
    displayBid(bid);
    inOrder(node->right);

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
void loadBids(string csvPath, BinarySearchTree* bst) {
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
            bst->Insert(bid);
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

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();

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
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Bad entry. Enter a NUMBER: ";
                cin >> bidKeyAsInt;
            }

            bidKey = to_string(bidKeyAsInt);

            ticks = clock();

            bid = bst->Search(bidKey);

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

            bst->Remove(bidKey);
            break;
        
        // secret method to test tree deletion
        case 5:
            bst->~BinarySearchTree();

            //create a new tree when old one is deleted
            bst = new BinarySearchTree();
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
