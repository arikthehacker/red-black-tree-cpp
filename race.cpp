/*******************************************************************************
* [Filename:]  Marchuk_Ariella_Program3_Race.cpp
* [Author:]    Ariella Marchuk
* [Email:]     amarchuk@pdx.edu
* [Course:]    CS302
* [Assignment] Program #3
* [Date:]      February 28 2025
*
* [Purpose:]   Implementation of Race ABC + 3 Derived Classes
*******************************************************************************/

#include "race.h"
#include <iostream>

/****************************************************************
/ Abstract Base Class: Race Implementations
****************************************************************/

// constructor - initializes race with name and date
Race::Race(const std::string& name, const std::string& date) : raceName(name), raceDate(date)
{
    std::cout << "race created: " << raceName << " on " << raceDate << std::endl;
}

// destructor - announces race destruction
Race::~Race()
{
    std::cout << "race destroyed: " << raceName << std::endl;
}

// startRace - begins the race
void Race::startRace()
{
    std::cout << raceName << " is starting the race." << std::endl;
}

// stopRace - ends the race
void Race::stopRace()
{
    std::cout << "raceWalk \"" << raceName << "\" has stopped the race." << std::endl;
}

// raceInstance - returns race instance
std::string Race::raceInstance() const
{
   return raceName;
}

/****************************************************************
/ Derived Class: kidsRun Implementation 
****************************************************************/

// constructor - initializes kidsRun with guardian and age limit
kidsRun::kidsRun(const std::string& name, const std::string& date,
                 const std::string& guardian, int minAge) : Race(name, date), guardianName(guardian), minAgeLimit(minAge)
{
    std::cout << "kidsRun created with guardian " << guardianName
              << " and minimum age " << minAgeLimit << std::endl;
}

// destructor - announces kidsRun deletion
kidsRun::~kidsRun()
{
    std::cout << "kidsRun destroyed: " << raceName << std::endl;
}

// registerRace - registers a participant for kidsRun
bool kidsRun::registerRace(const std::string& participant)
{
    std::cout << "registering participant \"" << participant
              << "\" for kidsRun: " << raceName << std::endl;

    return true;
}

// startRace - begins the kidsRun race
void kidsRun::startRace()
{
    std::cout << "kidsRun \"" << raceName << "\" is starting!" << std::endl;
}

// stopRace - ends the kidsRun race
void kidsRun::stopRace()
{
    std::cout << "kidsRun \"" << raceName << "\" has ended!" << std::endl;
}

// requestSnackBreak - allows kids to take a break
void kidsRun::requestSnackBreak()
{
    std::cout << "snack break requested for kidsRun \"" << raceName << "\"." << std::endl;
}

/****************************************************************
/ Derived Class: raceWalk Implementation 
****************************************************************/

// constructor - initializes raceWalk with penalties and disqualification status
raceWalk::raceWalk(const std::string& name, const std::string& date, int penaltyCt, bool disqualified)
         : Race(name, date), disqualifiedFlag(disqualified), penaltyCount(penaltyCt)
{
    std::cout << "raceWalk created: " << raceName
              << " with penalty count " << penaltyCount
              << " and disqualified flag "
              << (disqualifiedFlag ? "true" : "false") << std::endl;
}

// destructor - announces raceWalk deletion
raceWalk::~raceWalk()
{
    std::cout << "raceWalk destroyed: " << raceName << std::endl;
}

// registerRace - registers participant unless disqualified
bool raceWalk::registerRace(const std::string& participant)
{
    std::cout << "registering participant \"" << participant
              << "\" for raceWalk: " << raceName << std::endl;

    return !disqualifiedFlag; // if disqualified, registration fails
}

// startRace - begins the raceWalk race
void raceWalk::startRace()
{
    std::cout << "raceWalk \"" << raceName << "\" is starting!" << std::endl;
}

// stopRace - ends the raceWalk race
void raceWalk::stopRace()
{
    std::cout << "raceWalk \"" << raceName << "\" has ended!" << std::endl;
}

// markDisqualified - sets participant as disqualified
void raceWalk::markDisqualified()
{
    disqualifiedFlag = true;
    std::cout << "participant disqualified in raceWalk \"" << raceName << "\"!" << std::endl;
}

// administerPenalty - increases penalty count
void raceWalk::administerPenalty()
{
    penaltyCount++;
    std::cout << "penalty administered in raceWalk \"" << raceName
              << "\". total penalties: " << penaltyCount << std::endl;
}

/****************************************************************
/ Derived Class: halfMarathon Implementation 
****************************************************************/

// constructor - initializes halfMarathon with pace and rest stops
halfMarathon::halfMarathon(const std::string& name, const std::string& date, double avgP, int restStops)
    : Race(name, date), numRestStops(restStops), avgPace(avgP)
{
    std::cout << "halfMarathon created: " << raceName
              << " with average pace " << avgPace
              << " (min/mi) and " << numRestStops << " rest stops." << std::endl;
}

// destructor - announces halfMarathon deletion
halfMarathon::~halfMarathon()
{
    std::cout << "halfMarathon destroyed: " << raceName << std::endl;
}

// registerRace - registers a participant for halfMarathon
bool halfMarathon::registerRace(const std::string& participant)
{
    std::cout << "registering participant \"" << participant
              << "\" for halfMarathon: " << raceName << std::endl;

    return true;
}

// startRace - begins the halfMarathon race
void halfMarathon::startRace()
{
    std::cout << "halfMarathon \"" << raceName << "\" is starting!" << std::endl;
}

// stopRace - ends the halfMarathon race
void halfMarathon::stopRace()
{
    std::cout << "halfMarathon \"" << raceName << "\" has ended!" << std::endl;
}

// administerElectrolytes - decreases avg pace to maintain energy
void halfMarathon::administerElectrolytes()
{
    std::cout << "electrolytes administered in halfMarathon \"" << raceName << "\"." << std::endl;
    avgPace *= 0.98;   // reduce avg pace slightly
}

// estimatedFinish - estimates race completion time
int halfMarathon::estimatedFinish()
{
    // estimated race distance ~13.1 miles
    // finish time = (distance * avgPace) + (2 min per rest stop)
    double baseTime = 13.1 * avgPace;
    int penaltyTime = numRestStops * 2;
    int finishTime = static_cast<int>(baseTime + penaltyTime);

    std::cout << "est. finish time for halfMarathon \"" << raceName
              << "\" is " << finishTime << " minutes." << std::endl;

    return finishTime;
}

// calculateAvgPace - returns average pace of the runner
double halfMarathon::calculateAvgPace()
{
    std::cout << "average pace for halfMarathon \"" << raceName
              << "\" is " << avgPace << " min/km." << std::endl;

    return avgPace;
}
