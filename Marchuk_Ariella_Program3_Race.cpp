/*******************************************************************************
* [Filename:]  Marchuk_Ariella_Program3_Race.cpp
* [Author:]    Ariella Marchuk
* [Email:]     amarchuk@pdx.edu
* [Course:]    CS302
* [Assignment] Program #3
* [Date:]      February 21 2025
*
* [Purpose:]   Implementation of Race ABC + 3 Derived Classes
*******************************************************************************/

#include "Marchuk_Ariella_Program3_Race.h"
#include <iostream>

/****************************************************************
/ Abstract Base Class: Race Implementations
****************************************************************/

Race::Race(const std::string& name, const std::string& date) : raceName(name), raceDate(date)
{
    std::cout << "race created: " << raceName << " on " << raceDate << std::endl;
}

Race::~Race()
{
    std::cout << "race destroyed: " << raceName << std::endl;
}

void Race::startRace()
{
    std::cout << raceName << " is starting the race." << std::endl;
}

void Race::stopRace()
{
    std::cout << raceName << " has stopped the race." << std::endl;
}


/****************************************************************
/ Derived Class: kidsRun Implementation 
****************************************************************/

kidsRun::kidsRun(const std::string& name, const std::string& date,
                 const std::string& guardian, int minAge) : Race(name, date), guardianName(guardian), minAgeLimit(minAge)
{
    std::cout << "kidsRun created with guardian " << guardianName
              << " and minimum age " << minAgeLimit << std::endl;
}

kidsRun::~kidsRun()
{
    std::cout << "kidsRun destroyed: " << raceName << std::endl;
}

bool kidsRun::registerRace(const std::string& participant)
{
    std::cout << "registering participant \"" << participant
              << "\" for kidsRun: " << raceName << std::endl;

    return true;
}

void kidsRun::startRace()
{
    std::cout << "kidsRun \"" << raceName << "\" is starting!" << std::endl;
}

void kidsRun::stopRace()
{
    std::cout << "kidsRun \"" << raceName << "\" has ended!" << std::endl;
}

// requestSnackBreak - request a snack break for the kids run
                       // TODO: possibly have this affect something ?
void kidsRun::requestSnackBreak()
{
    std::cout << "snack break requested for kidsRun \"" << raceName << "\"." << std::endl;
}

/****************************************************************
/ Derived Class: raceWalk Implementation 
****************************************************************/

raceWalk::raceWalk(const std::string& name, const std::string& date, int penaltyCt, bool disqualified) 
         : Race(name, date), disqualifiedFlag(disqualified), penaltyCount(penaltyCt) 
{
    std::cout << "raceWalk created: " << raceName
              << " with penalty count " << penaltyCount
              << " and disqualified flag "
              << (disqualifiedFlag ? "true" : "false") << std::endl;
}

raceWalk::~raceWalk()
{
    std::cout << "raceWalk destroyed: " << raceName << std::endl;
}

bool raceWalk::registerRace(const std::string& participant)
{
    std::cout << "registering participant \"" << participant
              << "\" for raceWalk: " << raceName << std::endl;

    return !disqualifiedFlag; // TODO: if a contestant is already disqualified this could fail
}

void raceWalk::startRace()
{
    std::cout << "raceWalk \"" << raceName << "\" is starting!" << std::endl;
}

void raceWalk::stopRace()
{
    std::cout << "raceWalk \"" << raceName << "\" has ended!" << std::endl;
}

// markDisqualified - set disqualifiedFlag to true
void raceWalk::markDisqualified()
{
    disqualifiedFlag = true;

    std::cout << "participant disqualified in raceWalk \"" << raceName << "\"!" << std::endl;
}

// administerPenalty - administer a penalty in the raceWalk
void raceWalk::administerPenalty()
{
    penaltyCount++;

    std::cout << "penalty administered in raceWalk \"" << raceName
              << "\". total penalties: " << penaltyCount << std::endl;
}

/****************************************************************
/ Derived Class: halfMarathon Implementation 
****************************************************************/

halfMarathon::halfMarathon(const std::string& name, const std::string& date, double avgP, int restStops) : Race(name, date), numRestStops(restStops), avgPace(avgP) 
{
    std::cout << "halfMarathon created: " << raceName
              << " with average pace " << avgPace
              << " (min/mi) and " << numRestStops << " rest stops." << std::endl;
}

halfMarathon::~halfMarathon()
{
    std::cout << "halfMarathon destroyed: " << raceName << std::endl;
}

bool halfMarathon::registerRace(const std::string& participant)
{
    std::cout << "registering participant \"" << participant
              << "\" for halfMarathon: " << raceName << std::endl;

    return true;
}

void halfMarathon::startRace()
{
    std::cout << "halfMarathon \"" << raceName << "\" is starting!" << std::endl;
}

void halfMarathon::stopRace()
{
    std::cout << "halfMarathon \"" << raceName << "\" has ended!" << std::endl;
}

// administerElectrolytes - this decreases avgPace slightly
void halfMarathon::administerElectrolytes()
{
    std::cout << "electrolytes administered in halfMarathon \"" << raceName << "\"." << std::endl;

    avgPace *= 0.98;   // decrease avgPace slightly to simulate the electrolytes helping
}

// estimatedFinish - estimating the finish time using calculateAvgPace
int halfMarathon::estimatedFinish()
{
    // estimated race distance is ~13.1 miles 
    // finish time in minutes = (distance * avgPace) + (2 minutes per rest stop)
    double baseTime = 13.1 * avgPace;
    int penaltyTime = numRestStops * 2;
    int finishTime = static_cast<int>(baseTime + penaltyTime);

    std::cout << "est. finish time for halfMarathon \"" << raceName
              << "\" is " << finishTime << " minutes." << std::endl;

    return finishTime;
}

// calculateAvgPace - calculating the average pace of the runner 
double halfMarathon::calculateAvgPace()
{
    std::cout << "average pace for halfMarathon \"" << raceName
              << "\" is " << avgPace << " min/km." << std::endl;

    return avgPace;
}
