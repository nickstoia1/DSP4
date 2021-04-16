/*
 *    Data Structures Featuring C++  (c) 2021 Sridhar Radhakrishnan
 */

#include <iostream>
using namespace std;

#ifndef __BINARYSEARCHTREE__H
#define __BINARYSEARCHTREE__H

#include <cstdlib>


int max (int a, int b)
{
    if (a < b) return b;
    else return a;
}

class Exception {};

class BinaryTreeException : Exception {};
class BinaryTreeMemory : BinaryTreeException {};
class BinaryTreeEmptyTree : BinaryTreeException {};

class BinarySearchTreeException: BinaryTreeException {};
class BinarySearchTreeChangedSubtree : BinarySearchTreeException {};
class BinarySearchTreeNotFound : BinarySearchTreeException {};

template <class DataType>
class BinarySearchTree;

template <class DataType>
ostream& operator << (ostream& s,  BinarySearchTree<DataType>& X);

// /////////////////////////////////////////////////////////////
template <class DataType>
class BinarySearchTree
// /////////////////////////////////////////////////////////////
{
    friend ostream& operator<< <DataType> (ostream& s,  BinarySearchTree<DataType>& X);
protected:
    int id;
    DataType* _root;
    BinarySearchTree<DataType>* _left;
    BinarySearchTree<DataType>* _right;
    BinarySearchTree<DataType>* yTree;
    bool _subtree;
    virtual BinarySearchTree<DataType>* makeSubtree();
    virtual void copyTree (BinarySearchTree<DataType>* bst);
    virtual void _makeNull ();

public:
    BinarySearchTree<DataType>* _find (const DataType& data);
    BinarySearchTree (); // default constructor
    BinarySearchTree (const DataType& data);
    virtual ~BinarySearchTree (); // destructor
    virtual bool isEmpty();
    // returns true if tree is empty,
    // but otherwise returns false
    virtual int height ();
    // returns the height (or depth) of the tree
    virtual int size ();
    // returns the number of nodes in the tree
    virtual DataType& root ();
    // returns data from the root
    virtual BinarySearchTree<DataType>* left ();
    // returns the left subtree
    virtual BinarySearchTree<DataType>* right ();
    // returns the right subtree
    virtual BinarySearchTree<DataType>* getYTree ();
    virtual bool subtree(); // given
    virtual void makeEmpty (); // given
    virtual int find (const DataType& q); // given
    virtual void remove (const DataType& data); // given
    virtual void rangeSearch (const DataType& low, const DataType& high); // given
    virtual BinarySearchTree<DataType>* _insert (const DataType& data); // given
    virtual void insert (DataType& xVal, DataType& yVal, int id); // inserts the xVal into the tree and y val into the ytree
    void rangeSearch(DataType& X1, DataType& X2, DataType& Y1, DataType& Y2); // searches x range then the y trees of the xs for y range
    void inOrder_xTreeDisplay(); // in order output for X
    void preOrder_yTreeDisplay(); // preorder output for Y
    void inOrder_yTreeDisplay(); // in order output for Y
    void preOrder_xTreeDisplay(); // preorder output for X
    void remove(DataType& X, DataType& Y); // removes the Y node in the given xNode -- if there
    int getInorderTraversal(BinarySearchTree<DataType> *node, BinarySearchTree<DataType> **inOrderArray, int index); // given -- returns inorder BSTs
    void rebalanceY(DataType &X); // rebalances the yTree of the X given
    void findXY(DataType& X, DataType& Y); // finds if the coordinate X,Y is there
    BinarySearchTree<DataType>* GlobalRebalance(BinarySearchTree<DataType>** inOrderArray, int l, int r); // rebalances the BST

};
template <class DataType>

ostream& operator<< (ostream& s, BinarySearchTree<DataType>& X) {
    cout << "INORDER TRAVERSAL: " << endl;
    // call the xTree inOrder method
    X.inOrder_xTreeDisplay();
    cout << endl;
    cout << "PREORDER TRAVERSAL: " << endl;
    // call the xTree preOrder method
    X.preOrder_xTreeDisplay();
    return s;
}

// ==============================================================
template <class DataType>
// default with the ytree added in now
BinarySearchTree<DataType>::BinarySearchTree ()
{
    yTree = NULL;
    _root = NULL;
    _left = NULL;
    _right = NULL;
    _subtree = false;
    id = 0;
}
// --------------------------------------------------------------
template <class DataType>
// given
BinarySearchTree<DataType>::BinarySearchTree (const DataType& data)
{
    _subtree = false;
    _root = new DataType(data);
    //if (data == NULL) throw BinaryTreeMemory();
    _left = makeSubtree ();
    _right = makeSubtree ();
}
// --------------------------------------------------------------
template <class DataType>
// given
BinarySearchTree<DataType>* BinarySearchTree<DataType>::makeSubtree()
{
    BinarySearchTree<DataType>* bst = new BinarySearchTree<DataType> ();
    bst->_subtree = true;
    return bst;
}
// --------------------------------------------------------------
template <class DataType>
// destructor -- updated with the yTree
BinarySearchTree<DataType>::~BinarySearchTree ()
{
    if (_root != NULL)
        delete _root;
    _root = NULL;
    if (_left != NULL)
        delete _left;
    _left = NULL;
    if (_right != NULL)
        delete _right;
    _right = NULL;
    if (yTree != NULL)
        delete yTree;
    yTree = NULL;
}
// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::isEmpty()
{
    return (_root == NULL);
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::height ()
{
    if (isEmpty()) return 0;
    return (1 + max (_left->height(), _right->height()));
    // max() is in stdlib.h
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::size ()
// returns the number of nodes in the tree
{
    if (isEmpty())
        return 0;
    return (1 + _left->size() + _right->size());
}
// --------------------------------------------------------------
template <class DataType>
DataType& BinarySearchTree<DataType>::root ()
{
    if (isEmpty()) throw BinaryTreeEmptyTree();
    return *_root;
}
// returns data from the root
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::left () { return _left; }
// returns the left subtree
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::right (){ return _right; }
// returns the right subtree
// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::subtree() { return _subtree; }
// --------------------------------------------------------------
template <class DataType>
// makes he bst empty -- updated with ytree
void BinarySearchTree<DataType>::makeEmpty ()
{
    if (_subtree) throw BinarySearchTreeChangedSubtree();
    if (_root != NULL)
        delete _root;
    _root = NULL;
    if (_left != NULL)
        delete _left;
    _left = NULL;
    if (_right != NULL)
        delete _right;
    _right = NULL;
    if (yTree != NULL)
        delete yTree;
    yTree = NULL;
}
// --------------------------------------------------------------
template <class DataType>
// copies the given bst
void BinarySearchTree<DataType>::copyTree(BinarySearchTree<DataType>* bst)
{
    _root = bst->_root;
    _left = bst->_left;
    _right = bst->_right;
    yTree = bst->yTree;
    id = bst->id;
}
// --------------------------------------------------------------
template <class DataType>
// updated to make ytree null too
void BinarySearchTree<DataType>::_makeNull ()
{
    _root = NULL;
    _left = NULL;
    _right = NULL;
    yTree = NULL;
}
// --------------------------------------------------------------
template <class DataType>
// given
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_find (const DataType& data)
{
    BinarySearchTree<DataType>* bst = this;
    while (true)
    {
        if (bst->isEmpty())
            return bst;
        if (*(bst->_root) < data)
        {
            bst = bst->_right;
        }
        else if (*(bst->_root) > data)
        {
            bst = bst->_left;
        }
        else
        {
            return bst;
        }
    }
}
// --------------------------------------------------------------
template <class DataType>
// given but modified to return 1 if found 0 if not
int BinarySearchTree<DataType>::find (const DataType& q)
{
    BinarySearchTree<DataType>* bst = _find (q);

        if (bst->isEmpty()) return 0;
        //cout<<"\nThe element "<<bst->root()<<" is found in the tree"<<endl;
        return 1;


}
// --------------------------------------------------------------
template <class DataType>
// given
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_insert (const DataType& data)
{
 //   if (_subtree) throw BinarySearchTreeChangedSubtree();
    BinarySearchTree<DataType>* bst = _find (data);
    if (bst->isEmpty())
    {
        bst->_root = new DataType (data);
        bst->_left = makeSubtree ();
        bst->_right = makeSubtree ();
    }
    else
    {
        delete bst->_root;
        bst->_root = new DataType (data);
    }
    return bst;
}
// --------------------------------------------------------------
template <class DataType>
// given
void BinarySearchTree<DataType>::remove (const DataType& data)
{
    if (_subtree) throw BinarySearchTreeChangedSubtree();
    BinarySearchTree<DataType>* bst;
    BinarySearchTree<DataType>* bst2;
    BinarySearchTree<DataType>* bst3;

    bst = _find (data);
    if (bst->isEmpty()) throw BinarySearchTreeNotFound();

    // dispose of the existing data; the pointer will be overwritten
    delete bst->_root;

    // .............................................................
    if (bst->_left->isEmpty())
    {
        // the left subtree exists, but the pointer will be overwritten,
        // so we must dispose of it
        delete bst->_left;
        bst2 = bst->_right;		// save the pointer to the right subtree
        bst->copyTree (bst2);	// copy the right subtree;
        // this empties tree if right empty
        bst2->_makeNull ();		// prepare right subtree for deletion
        delete bst2;				// delete right subtree to avoid garbage
    }

    else if (bst->_right->isEmpty())
    {
        // the right subtree exists, but the pointer will be overwritten,
        // so we must dispose of it
        delete bst->_right;
        bst2 = bst->_left;		// save the pointer to the left subtree
        bst->copyTree (bst2);	// copy the left subtree
        bst2->_makeNull ();		// prepare left subtree for deletion
        delete bst2;				// delete left subtree to avoid garbage
    }

    else		// both subtrees non-empty
    {
        // move to the right
        bst2 = bst->_right;
        // then move down to the left as far as possible
        while (!bst2->_left->isEmpty()) bst2 = bst2->_left;
        // overwrite the data pointer
        bst->_root = bst2->_root;

        // bst2's left child is known to be empty and pointer will be overwritten
        delete bst2->_left;
        // now bst2's right child is copied into it
        if (bst2->_right->isEmpty())
        {
            delete bst2->_right;
            bst2->_makeNull();
        }
        else
        {
            bst3 = bst2->_right;
            bst2->copyTree(bst2->_right);
            bst3->_makeNull ();
            delete bst3;
        }
    }
}
// --------------------------------------------------------------
template <class DataType>
// given
void BinarySearchTree<DataType>::rangeSearch (const DataType& low, const DataType& high)
{
    if (isEmpty()) return;
    if (*_root >= low)
    {
        _left->rangeSearch(low,high);
        if (*_root <= high)
        {
            cout << *_root << "  ";
        }
    }
    if (*_root <= high)
        _right->rangeSearch(low,high);
}
// yTree accessor
template<class DataType>
BinarySearchTree<DataType> *BinarySearchTree<DataType>::getYTree() {
    return yTree;
}

template<class DataType>
void BinarySearchTree<DataType>::insert(DataType &xVal, DataType &yVal, int id) {
    // creates a temp BST to hold the current node
    BinarySearchTree<DataType> *searchBST = _find(xVal);
    // checks is empty -- was not initially found
    if (searchBST->isEmpty()){
        // insert in the xVal
        BinarySearchTree<DataType>* BST1 = _insert(xVal);
        // if the yTree of searchBST is not there create and insert
        if (BST1->getYTree() == NULL){
            BST1->yTree = new BinarySearchTree<DataType>();
            BST1->yTree->_insert(yVal);
            BST1->yTree->id = id;

        }
        else {
            // inserts the new node into the ytree and sets the id
            BinarySearchTree<DataType> *BST2 = new BinarySearchTree<DataType>();
            BST2 = searchBST->yTree->_insert(yVal);
            BST2->yTree->id = id;
        }
    }
    // xNode was already there
    else {
        // checks if the yTree is not already there
        if (getYTree() == NULL){
            // inserts and sets id
            searchBST->yTree->_insert(yVal);
            searchBST->yTree->id = id;
        }
        else {
            // inserts and sets id
            BinarySearchTree<DataType> *BST2 = searchBST->yTree->_insert(yVal);
            BST2->id = id;
        }
    }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class DataType>
// output for in order of the x tree
void BinarySearchTree<DataType>::inOrder_xTreeDisplay ()

{
    if (!(isEmpty())){
        this->_left->inOrder_xTreeDisplay();
        // call the xTree inOrder method with the left pointer object
        if (!this->yTree->isEmpty()){
            cout << this->root () << ": " << endl;
            this->yTree->inOrder_yTreeDisplay();
            cout << endl;
        }
        // call the yTree inOrder method with the yTree pointer object
        this->_right->inOrder_xTreeDisplay();
        // call the xTree inOrder method with the right pointer object
    }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class DataType>
// output for inorder of the y tree
void BinarySearchTree<DataType>::inOrder_yTreeDisplay ()
{
    if (!isEmpty()){
        this->_left->inOrder_yTreeDisplay();
        // call yTree inOrder method with left pointer object
        cout << " " << this->root () << "(" << this->id << ") ";
        this->_right->inOrder_yTreeDisplay();
        // call yTree inOrder method with right pointer object
    }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class DataType>
// out put for preorder of the x tree
void BinarySearchTree<DataType>::preOrder_xTreeDisplay ()

{
    if (!isEmpty()){
        if (!this-> yTree->isEmpty()){
            cout << this->root () << ": " << endl;
            this->yTree->preOrder_yTreeDisplay();
            cout << endl;
        }
        // call the yTree preOrder method with the yTree pointer object
        this->_left->preOrder_xTreeDisplay();
        // call the xTree preOrder method with the left pointer object
        this->_right->preOrder_xTreeDisplay();
        // call the xTree preOrder method with the right pointer object
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class DataType>
// output of preorder for the y tree
void BinarySearchTree<DataType>::preOrder_yTreeDisplay ()

{
    if (!isEmpty()){
        cout << " " << this->root () << "(" << this->id << ") ";
        this->_left->preOrder_yTreeDisplay();
        // call the yTree preOrder method with the left pointer object
        this->_right->preOrder_yTreeDisplay();
        // call the yTree preOrder method with the right pointer object
    }

}
// range search for 2D BST
template<class DataType>
void BinarySearchTree<DataType>::rangeSearch(DataType &X1, DataType &X2, DataType &Y1, DataType &Y2) {
    // checks if empty then does nothing
    if (isEmpty()) return;
    // checks for if root is greater than lower bound
    if (*_root >= X1)
    {
        // checks the left child
        _left->rangeSearch(X1,X2, Y1, Y2);
        // checks if also lower than the upper bound -- in range
        if (*_root <= X2)
        {
            // prints
            cout << *_root << " : ";
            yTree->rangeSearch(Y1,Y2);
            cout << endl;
        }
    }
    // checks if less than upper bound then does right child to get to when not in range
    if (*_root <= X2)
        _right->rangeSearch(X1,X2, Y1, Y2);

}
// removes the yNode in the yTree of the given X
template<class DataType>
void BinarySearchTree<DataType>::remove(DataType &X, DataType &Y) {
    // checks if in the x tree
    int isFound = this->find(X);
    if (isFound == 0){
        cout << "The element you are trying to remove is not in the tree" << endl;
    }
    else {
        // checks if in the y tree
        isFound = _find(X)->yTree->find(Y);
        if (isFound == 0){
            cout << "The element you are trying to remove is not in the tree" << endl;
        }
        else {
            // removes the yNode
            _find(X)->yTree->remove(Y);
            // removes the xNode if the y tree is now size 0
            if (_find(X)->yTree->size()==0){
                remove(X);
            }
        }
    }
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int index)
{
    // Don't really know how this works just given to me
    try{
        if (node->isEmpty()) throw BinarySearchTreeNotFound();
    }
    catch(BinarySearchTreeNotFound e){
        cout << "No tree for inorder traversal" << endl;
        return index;
    }

    //cout << "value: " << this->root() << endl;
    // cout << "left: " << *(this->left()->_root) << endl;
    // cout << "right: " << *(this->right()->_root) << endl;

    if (!this->isEmpty()) {
        if(node->left()->_root != NULL)
        {
            // cout << "\tcalling left" << endl;
            index = node->left()->getInorderTraversal(node->left(), inOrderArray, index);
        }

        inOrderArray[index++] = node;
        // cout << "index: " << index - 1 << " inOrderArray[i]: " << inOrderArray[index - 1]->root() << endl;

        if(node->right()->_root != NULL)
        {
            // cout << "\tcalling right" << endl;
            index = node->right()->getInorderTraversal(node->right(), inOrderArray, index);
        }
    }
    return index;
}
// Rebalances the y tree
template<class DataType>
void BinarySearchTree<DataType>::rebalanceY(DataType& X) {
    // This rebalances the yTree
    BinarySearchTree<DataType>* yTemp = _find(X)->yTree;
    // gets the in order array of BSTs in the yTree
    auto** inOrderArray = new BinarySearchTree<DataType>*[yTemp->size()];
    this->getInorderTraversal(yTemp, inOrderArray, 0);
    // Does the Global Rebalance and sets it back
    _find(X)->yTree->copyTree(_find(X)->GlobalRebalance(inOrderArray, 0, yTemp->size()-1));
}

template<class DataType>
BinarySearchTree<DataType> *
BinarySearchTree<DataType>::GlobalRebalance(BinarySearchTree<DataType> **inOrderArray, int l, int r) {
    // this was given just changed it to properly set the left and right trees
    int mid = 0;
    BinarySearchTree<DataType>* temp = new BinarySearchTree<DataType>();

    if(l <= r)
    {
        mid = ((l + r) / 2);
        temp->copyTree(inOrderArray[mid]);
        temp->_left = GlobalRebalance(inOrderArray, l, mid - 1);
        temp->_right = GlobalRebalance(inOrderArray, mid + 1, r);
    }

    return temp;
}

template<class DataType>
void BinarySearchTree<DataType>::findXY(DataType &X, DataType &Y) {
    // First, checks if the X is in the BST, 0 missing, 1 there
    int isThere = this->find(X);
    // if not there
    if (isThere == 0){
        cout << "Sorry!!! Coordinate is not found in the X tree" << endl;
    }
    // if there
    else {
        //  checks if the y is in the ytree of the X
        isThere = this->_find(X)->yTree->find(Y);
        if (isThere == 0){
            cout << "Sorry!!! Coordinate is not found in the Y tree" << endl;
        }
        else {
            // gets the value of the coordinate
            int top = this->_find(X)->yTree->_find(Y)->id;
            cout << "The coordinates "<< X << ", " << Y << " is found in the tree with ID value " << top << endl;
        }
    }
}


#endif