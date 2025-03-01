/*******************************************************************************
 * [Filename:]  Marchuk_Ariella_Program3_MainHelpers.cpp
 * [Author:]    Ariella Marchuk
 * [Email:]     amarchuk@pdx.edu
 * [Course:]    CS302
 * [Assignment] Program #3
 * [Date:]      February 28 2025
 *
 * [Purpose:]   helper functions that test the race hierarchy and redBlackTree  
 *******************************************************************************/

#include "race.h"
#include <iostream>
#include <memory>
#include <limits>
#include <stdexcept>
#include <vector>

// clearCin - clears input buffer for safe user input
static void clearCin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/****************************************************************
/ race creation helpers
/    - creates races and stores them in currentRace
****************************************************************/

// createKidsRun - prompts user for kidsRun data and creates it
static void createKidsRun(std::shared_ptr<Race>& currentRace)
{
    clearCin();
    std::string name, date, guardian;
    int minAge;
    try
    {
        std::cout << "enter kidsRun name: ";
        std::getline(std::cin, name);
        std::cout << "enter date: ";
        std::getline(std::cin, date);
        std::cout << "enter guardian name: ";
        std::getline(std::cin, guardian);
        std::cout << "enter minimum age: ";
        if (!(std::cin >> minAge))
        {
            throw std::invalid_argument("invalid integer for minAge");
        }

        currentRace = std::make_shared<kidsRun>(name, date, guardian, minAge);
        std::cout << "kidsRun created.\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "error creating kidsRun: " << e.what() << std::endl;
    }
}

// createRaceWalk - prompts user for raceWalk data and creates it
static void createRaceWalk(std::shared_ptr<Race>& currentRace)
{
    clearCin();
    std::string name, date;
    int penalty;
    bool dq;
    try
    {
        std::cout << "enter raceWalk name: ";
        std::getline(std::cin, name);
        std::cout << "enter date: ";
        std::getline(std::cin, date);
        std::cout << "enter initial penalty count: ";
        if (!(std::cin >> penalty))
        {
            throw std::invalid_argument("invalid integer for penalty");
        }
        std::cout << "disqualified? (0/1): ";
        if (!(std::cin >> dq))
        {
            throw std::invalid_argument("invalid boolean for dq");
        }

        currentRace = std::make_shared<raceWalk>(name, date, penalty, dq);
        std::cout << "raceWalk created.\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "error creating raceWalk: " << e.what() << std::endl;
    }
}

// createHalfMarathon - prompts user for halfMarathon data and creates it
static void createHalfMarathon(std::shared_ptr<Race>& currentRace)
{
    clearCin();
    std::string name, date;
    double pace;
    int stops;
    try
    {
        std::cout << "enter halfMarathon name: ";
        std::getline(std::cin, name);
        std::cout << "enter date: ";
        std::getline(std::cin, date);
        std::cout << "enter average pace (min/km): ";
        if (!(std::cin >> pace))
        {
            throw std::invalid_argument("invalid double for pace");
        }
        std::cout << "enter number of rest stops: ";
        if (!(std::cin >> stops))
        {
            throw std::invalid_argument("invalid integer for restStops");
        }

        currentRace = std::make_shared<halfMarathon>(name, date, pace, stops);
        std::cout << "halfMarathon created.\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "error creating halfMarathon: " << e.what() << std::endl;
    }
}

/****************************************************************
/ race testing helpers
/    - tests registerRace, startRace, stopRace, plus unique methods
****************************************************************/

// testRegisterRace - registers a participant for the current race
static void testRegisterRace(std::shared_ptr<Race>& currentRace)
{
    if (!currentRace)
    {
        std::cerr << "no current race.\n";
        return;
    }
    try
    {
        bool success = currentRace->registerRace("TestParticipant");
        std::cout << "registerRace => " << (success ? "success" : "fail") << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception in registerRace: " << e.what() << std::endl;
    }
}

// testKidsRunUnique - calls requestSnackBreak if kidsRun
static void testKidsRunUnique(std::shared_ptr<Race>& currentRace)
{
    if (!currentRace)
    {
        std::cout << "no race.\n";
        return;
    }
    kidsRun* kr = dynamic_cast<kidsRun*>(currentRace.get());
    if (!kr)
    {
        std::cout << "this race is not a kidsRun.\n";
        return;
    }
    kr->requestSnackBreak();
}

// testRaceWalkUnique - calls administerPenalty & markDisqualified if raceWalk
static void testRaceWalkUnique(std::shared_ptr<Race>& currentRace)
{
    if (!currentRace)
    {
        std::cout << "no race.\n";
        return;
    }
    raceWalk* rw = dynamic_cast<raceWalk*>(currentRace.get());
    if (!rw)
    {
        std::cout << "this race is not a raceWalk.\n";
        return;
    }
    rw->administerPenalty();
    rw->markDisqualified();
    bool ok = rw->registerRace("AnotherGuy");
    std::cout << "registerRace after disqualification => "
              << (ok ? "success" : "fail") << std::endl;
}

// testHalfMarathonUnique - calls electrolyte, finish estimate, pace if halfMarathon
static void testHalfMarathonUnique(std::shared_ptr<Race>& currentRace)
{
    if (!currentRace)
    {
        std::cout << "no race.\n";
        return;
    }
    halfMarathon* hm = dynamic_cast<halfMarathon*>(currentRace.get());
    if (!hm)
    {
        std::cout << "this race is not a halfMarathon.\n";
        return;
    }
    hm->administerElectrolytes();
    int finishTime = hm->estimatedFinish();
    double finalPace = hm->calculateAvgPace();
    std::cout << "finish time: " << finishTime
              << ", final pace: " << finalPace << " min/km\n";
}

/****************************************************************
/ data structure class: redBlackTree helpers
/    - provides functions for rbTree operations
****************************************************************/

// createRBTree - initializes a new redBlackTree
static void createRBTree(redBlackTree*& rbtree)
{
    if (rbtree)
    {
        delete rbtree;
        rbtree = nullptr;
    }
    rbtree = new redBlackTree();
    std::cout << "redBlackTree created.\n";
}

// insertRBTree - inserts a new race object into the rbTree
static void insertRBTree(redBlackTree*& rbtree)
{
    if (!rbtree)
    {
        std::cerr << "no rbTree. create one first.\n";
        return;
    }
    clearCin();
    std::string name, date;
    try
    {
        std::cout << "enter race name for key: ";
        std::getline(std::cin, name);
        std::cout << "enter race date: ";
        std::getline(std::cin, date);

        auto newRace = std::make_shared<kidsRun>(name, date, "GuardianX", 8);
        bool success = rbtree->insert(newRace);
        std::cout << (success ? "inserted.\n" : "insertion failed (duplicate?).\n");
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception in insertRBTree: " << e.what() << std::endl;
    }
}

// displayRBTree - displays all nodes in-order
static void displayRBTree(const redBlackTree* rbtree)
{
    if (!rbtree)
    {
        std::cerr << "no rbTree.\n";
        return;
    }
    rbtree->displayAll();
}

// removeAllRBTree - removes all nodes from rbTree
static void removeAllRBTree(redBlackTree*& rbtree)
{
    if (!rbtree)
    {
        std::cerr << "no rbTree.\n";
        return;
    }
    rbtree->removeAll();
    std::cout << "all nodes removed from rbTree.\n";
}

// destroyRBTree - deletes rbTree from memory
static void destroyRBTree(redBlackTree*& rbtree)
{
    if (rbtree)
    {
        delete rbtree;
        rbtree = nullptr;
        std::cout << "rbTree destroyed.\n";
    }
    else
    {
        std::cout << "no rbTree to destroy.\n";
    }
}

/****************************************************************
/ test menu - tests core & unique race methods plus rbTree
****************************************************************/

void runTestMenu(std::shared_ptr<Race>& currentRace, redBlackTree*& rbtree)
{
    while (true)
    {
        std::cout << "\n================== shamrock run 2025 =====================\n";
        std::cout << " 1. create kidsRun\n"
                  << " 2. create raceWalk\n"
                  << " 3. create halfMarathon\n"
                  << " 4. registerRace\n"
                  << " 5. startRace\n"
                  << " 6. stopRace\n"
                  << " 7. test kidsRun unique method (snackBreak)\n"
                  << " 8. test raceWalk unique methods (penalty + dq)\n"
                  << " 9. test halfMarathon unique methods\n"
                  << "10. create redBlackTree\n"
                  << "11. insert new race into rbTree\n"
                  << "12. display rbTree\n"
                  << "13. remove all from rbTree\n"
                  << "14. destroy rbTree\n"
                  << "15. exit\n"
                  << "============================================================\n"
                  << "enter choice: ";

        int choice = 0;
        if (!(std::cin >> choice))
        {
            clearCin();
            std::cerr << "invalid input.\n";
            continue;
        }

        try
        {
            switch (choice)
            {
                case 1:
                    createKidsRun(currentRace);
                    break;
                case 2:
                    createRaceWalk(currentRace);
                    break;
                case 3:
                    createHalfMarathon(currentRace);
                    break;
                case 4:
                    testRegisterRace(currentRace);
                    break;
                case 5:
                    if (currentRace)
                    {
                        currentRace->startRace();
                    }
                    else
                    {
                        std::cerr << "no current race to start.\n";
                    }
                    break;
                case 6:
                    if (currentRace)
                    {
                        currentRace->stopRace();
                    }
                    else
                    {
                        std::cerr << "no current race to stop.\n";
                    }
                    break;
                case 7:
                    testKidsRunUnique(currentRace);
                    break;
                case 8:
                    testRaceWalkUnique(currentRace);
                    break;
                case 9:
                    testHalfMarathonUnique(currentRace);
                    break;
                case 10:
                    createRBTree(rbtree);
                    break;
                case 11:
                    insertRBTree(rbtree);
                    break;
                case 12:
                    displayRBTree(rbtree);
                    break;
                case 13:
                    removeAllRBTree(rbtree);
                    break;
                case 14:
                    destroyRBTree(rbtree);
                    break;
                case 15:
                    std::cout << "exiting shamrock run 2025 test menu.\n";
                    if (rbtree)
                    {
                        delete rbtree;
                        rbtree = nullptr;
                    }
                    currentRace.reset();
                    return;
                default:
                    std::cerr << "invalid choice.\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "error: " << e.what() << std::endl;
        }
    }
}

