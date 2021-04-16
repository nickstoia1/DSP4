/*
 *    Data Structures Featuring C++  (c) 2021 Sridhar Radhakrishnan
 */

#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree<int> *bst= new BinarySearchTree<int>();
    char curr; // The character for commands of what to do with the BST
    cin >> curr;
    while (!cin.fail()){
        // This is for inserting into the BST
        if (curr == 'I'){
            int xVal, yVal, id;
            cin >> xVal;
            cin >> yVal;
            cin >> id;
            bst->insert(xVal, yVal, id);
            cout << xVal << " " << yVal << " " << id << endl;
        }
        // This is for printing the BST
        else if(curr == 'P'){
            cout << "Print" << endl;
            cout << *bst;
        }
        // This is for searching the BST
        else if (curr == 'S'){
            int X1, X2, Y1, Y2;
            cin >> X1;
            cin >> X2;
            cin >> Y1;
            cin >> Y2;
            cout << "Range Search" << endl;
            cout << X1 << " " << X2 << " " << Y1 << " " << Y2 << endl;
            bst->rangeSearch(X1, X2, Y1, Y2);
        }
        // This is for removing stuff from the BST
        else if (curr == 'R'){
            int X, Y;
            cin >> X;
            cin >> Y;
            cout << "Remove: " << X << " " << Y << endl;
            bst->remove(X, Y);
        }
        // This is for rebalancing the yTree of a node of the BST
        else if (curr == 'Y'){
            int X;
            cin >> X;
            cout << "Y tree balance" << endl;
            cout << X << endl;
            bst->rebalanceY(X);
        }
        // This is for Finding is something is in the BST
        else if (curr == 'F'){
            int X, Y;
            cin >> X;
            cin >> Y;
            cout << "Find: " << X << " " << Y << endl;
            bst->findXY(X, Y);
        }
        cin >> curr;
    }
    // takes out the trash
    delete bst;
    return 0;
}