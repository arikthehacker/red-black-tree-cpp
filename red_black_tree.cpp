/*******************************************************************************
* [Filename:]  Marchuk_Ariella_Program3_Tree.cpp
* [Author:]    Ariella Marchuk
* [Email:]     amarchuk@pdx.edu
* [Course:]    CS302
* [Assignment] Program #3
* [Date:]      February 28 2025
*
* [Purpose:]   Implementation for the Red-Black Tree Class that is Created in Race.h
*                       ☣ Insert
*                           ↳ insertHelper, ficInsertion, rotateLeft, rotateRight
*                       ☣ Display 
*                           ↳ displayAll
*                       ☣ Remove All 
*                           ↳ removeAll
*******************************************************************************/
#include "race.h"

/*insertion algorithm:***********************************************************
    if tree is empty:
        - set root to new node, color it black
    else:
        - create new node, color it red
        - if parent is black, exit (valid rbtree)
        - if parent is red:
            - if parent's sibling is black or nullptr:
                * apply rotations
                * recolor accordingly
            - if parent's sibling is red:
                * recolor parent -> black
                * recolor sibling -> black
                * recolor grandparent -> red
                * if grandparent is root, do not recolor grandparent 
*******************************************************************************/

/****************************************************************
/ Data Structure: redBlackTree Implementation
/    - self-balancing binary search tree storing Race objects
/    - supports insertion, display, and recursive removal
****************************************************************/

// redBlackTree - constructor
redBlackTree::redBlackTree() : root(nullptr) { }

// ~redBlackTree - destructor
redBlackTree::~redBlackTree()
{
    // call removeAll to delete all nodes
    removeAll();
}

// insert - inserts a new race object into the tree
bool redBlackTree::insert(std::shared_ptr<Race> racePtr)
{
    if (!racePtr) // if null
    {
        std::cerr << "error: cannot insert a null race object." << std::endl;
        return false;
    }

    // create new node
    rbNode* newNode = new rbNode(racePtr->raceInstance(), racePtr);

    // attempt to insert into bst structure
    bool success = insertHelper(root, newNode, nullptr);
    if (!success)
    {
        delete newNode; // delete new node
        std::cerr << "error: duplicate key insert attempted." << std::endl;
        return false;
    }

    // fix any red-black tree violations
    fixInsertion(newNode);
    return true;
}

/****************************************************************
/ Data Structure: Recursive BST Insertion
/    - inserts a node while maintaining bst ordering
****************************************************************/

bool redBlackTree::insertHelper(rbNode*& node, rbNode* newNode, rbNode* parent)
{
    // if there's no node
    if (!node)
    {
        // node doesn't exist yet
        node = newNode;
        node->parent = parent;
        // if no parent => this is root
        if (!parent)
            node->color = Color::BLACK;
        // return true for success
        return true;
    }

    // if newnode key is smaller
    if (newNode->key < node->key)
        return insertHelper(node->left, newNode, node);
    // else if newnode key is bigger
    else if (newNode->key > node->key)
        return insertHelper(node->right, newNode, node);

    // if duplicate
    return false;
}

/****************************************************************
/ Data Structure: Red-Black Tree Fix Insertion
/    - fixes tree properties after inserting a new node
/    - performs recoloring and rotations when needed
****************************************************************/

void redBlackTree::fixInsertion(rbNode* node)
{
    // if node is root => color black
    if (node == root)
    {
        node->color = Color::BLACK;
        return;
    }

    // if parent is black => no violation
    if (node->parent->color == Color::BLACK)
        return;

    // now node->parent is red => possible violation
    rbNode* parent = node->parent;
    rbNode* grandparent = parent->parent;

    // if there's no grandparent => parent is root => color parent black
    if (!grandparent)
    {
        parent->color = Color::BLACK;
        return;
    }

    // determine uncle
    rbNode* uncle = nullptr;
    if (parent == grandparent->left)
        uncle = grandparent->right;
    else
        uncle = grandparent->left;

    // case 1: uncle is red => recolor
    if (uncle && uncle->color == Color::RED)
    {
        parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        grandparent->color = Color::RED;

        // recursively fix grandparent
        fixInsertion(grandparent);
        return;
    }

    // case 2 & 3: uncle is black
    if (parent == grandparent->left)
    {
        // if node is parent's right => rotateleft
        if (node == parent->right)
        {
            rotateLeft(parent);
            node = parent;
            parent = node->parent;
        }
        // recolor and rotateright
        parent->color = Color::BLACK;
        grandparent->color = Color::RED;
        rotateRight(grandparent);
    }
    else
    {
        // parent is right child
        if (node == parent->left)
        {
            rotateRight(parent);
            node = parent;
            parent = node->parent;
        }
        parent->color = Color::BLACK;
        grandparent->color = Color::RED;
        rotateLeft(grandparent);
    }
}

/****************************************************************
/ Data Structure: Rotations
/    - rotates the tree left or right to balance it
****************************************************************/

// rotateLeft - left rotation around node x
void redBlackTree::rotateLeft(rbNode* x)
{
    // if no right child => can't rotate
    rbNode* y = x->right;
    if (!y) return;

    x->right = y->left;
    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;
    // if x is root => now y is root
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// rotateRight - right rotation around node x
void redBlackTree::rotateRight(rbNode* x)
{
    // if no left child => can't rotate
    rbNode* y = x->left;
    if (!y) return;

    x->left = y->right;
    if (y->right)
        y->right->parent = x;

    y->parent = x->parent;
    // if x is root => now y is root
    if (!x->parent)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

/****************************************************************
/ Data Structure: Display (In-Order Traversal)
/    - prints the tree contents in sorted order
****************************************************************/

void redBlackTree::displayAll() const
{
    displayAll(root);
}

// displayAll (recursive) - traverse in order
void redBlackTree::displayAll(rbNode* node) const
{
    if (!node) return;

    displayAll(node->left);
    std::cout << "[" << (node->color == Color::RED ? "RED" : "BLACK") << "] "
              << node->key << ": ";
    node->data->startRace();
    displayAll(node->right);
}

/****************************************************************
/ Data Structure: Recursive Deletion
/    - removes all nodes from the tree recursively
****************************************************************/

void redBlackTree::removeAll()
{
    removeAll(root);
    root = nullptr;
}

// removeAll (recursive) - deletes nodes in post-order
void redBlackTree::removeAll(rbNode*& node)
{
    if (!node) return;

    removeAll(node->left);
    removeAll(node->right);
    delete node;
    node = nullptr;
}
