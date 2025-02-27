/*******************************************************************************
* [Filename:]  Marchuk_Ariella_Program3_Race.h
* [Author:]    Ariella Marchuk
* [Email:]     amarchuk@pdx.edu
* [Course:]    CS302
* [Assignment] Program #3
* [Date:]      February 26 2025
*
* [Purpose:]   Implementation for the Red-Black Tree: 
*                       ☣ Insert
*                           ↳ i'll place helpers here  
*                       ☣ Display 
*                           ↳ displayAll(node node) const
*                       ☣ Remove All 
*                           ↳ removeAll(node node);
*******************************************************************************/
#include "Marchuk_Ariella_Program3_Race.h"

redBlackTree::redBlackTree() : root(nullptr) {}
redBlackTree::~redBlackTree() { removeAll(); }

//bool redBlackTree::insert(rbNode*& root, rbNode* newNode) {return false;}

void redBlackTree::displayAll() const
{
    displayAll(root);
}

void redBlackTree::displayAll(rbNode* node) const
{
    if (!node) return;
    displayAll(node->left);
    std::cout << "[" << (node->color == Color::RED ? "RED" : "BLACK") << "] "
              << node->key << ": ";
    node->data->startRace(); 
    displayAll(node->right);
}

void redBlackTree::removeAll()
{
    removeAll(root);
    root = nullptr;
}

void redBlackTree::removeAll(rbNode*& node)
{
    if (!node) return;
    removeAll(node->left);
    removeAll(node->right);
    delete node;
    node = nullptr;
}

