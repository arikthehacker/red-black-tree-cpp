/*******************************************************************************
 * [Filename:]  Marchuk_Ariella_Program3_Main.cpp
 * [Author:]    Ariella Marchuk
 * [Email:]     amarchuk@pdx.edu
 * [Course:]    CS302
 * [Assignment] Program #3
 * [Date:]      February 28 2025
 *
 * [Purpose:]   Main function, calls runTestMenu to test everything
 *              in the Race hierarchy and the R-B tree.
 *******************************************************************************/

#include "race.h"
#include <memory>

void runTestMenu(std::shared_ptr<Race>& currentRace, redBlackTree*& rbtree);

int main()
{
    std::shared_ptr<Race> currentRace = nullptr;
    redBlackTree* rbtree = nullptr;

    runTestMenu(currentRace, rbtree);

    if (rbtree)
    {
        delete rbtree;
        rbtree = nullptr;
    }

    return 0;
} 
