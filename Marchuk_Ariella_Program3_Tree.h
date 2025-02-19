/*******************************************************************************
* [Filename:]  Marchuk_Ariella_Program3_Tree.h
* [Author:]    Ariella Marchuk
* [Email:]     amarchuk@pdx.edu
* [Course:]    CS302
* [Assignment] Program #3
* [Date:]      February 19 2025
*
* [Purpose:]   Header draft (R-B tree start) 
*******************************************************************************/

#ifndef MARCHUK_ARIELLA_PROGRAM3_TREE_H
#define MARCHUK_ARIELLA_PROGRAM3_TREE_H

#include <string>
#include <iostream>

/*****************************************************************
/  data structure class: red black tree 
/    - holds Race* objects (base class pointers)
*****************************************************************/
class redBlackTree 
{
    public:
        redBlackTree();
        ~redBlackTree();

        bool insert(const std::string& key, Race* racePtr);
        bool remove(const std::string& key);
        void displayAll() const;

    private:
    // R-B tree data members:
    //   - root pointer
    //   - struct for tree nodes
    //   - could add balancing helpers
};

#endif
