/*******************************************************************************
* [Filename:]  Marchuk_Ariella_Program3_Race.h
* [Author:]    Ariella Marchuk
* [Email:]     amarchuk@pdx.edu
* [Course:]    CS302
* [Assignment] Program #3
* [Date:]      February 28 2025
*
* [Purpose:]   Header for the following classes:
*                       ☣ Race
*                           ↳ kidsRun
*                           ↳ raceWalk
*                       ☣ redBlackTree 
*                       ☣ rbNode [struct]
*******************************************************************************/
#ifndef MARCHUK_ARIELLA_PROGRAM3_RACE_H
#define MARCHUK_ARIELLA_PROGRAM3_RACE_H

#include <string>
#include <iostream>
#include <memory>

/****************************************************************
/ Abstract Base Class: Race
****************************************************************/
class Race 
{
    public:
        // constructor and virtual destructor 
        Race(const std::string& name, const std::string& date);
        virtual ~Race(); 

        // pure virtual abstract method 
        virtual bool registerRace(const std::string& participant) = 0;

        // virtual methods 
        virtual void startRace();
        virtual void stopRace();

        std::string raceInstance() const;

    protected:
        // all derived share these 
        std::string raceName;
        std::string raceDate;
};

/****************************************************************
/ Derived Class: kidsRace
****************************************************************/
class kidsRun : public Race 
{
    public:
        // constructor/destructor 
        kidsRun(const std::string& name,
                const std::string& date,
                const std::string& guardian,
                int minAge);
        virtual ~kidsRun();

        // overrides from base 
        bool registerRace(const std::string& participant) override;
        void startRace() override;
        void stopRace() override;
        
        // unique method
        void requestSnackBreak();

    private:
        std::string guardianName;
        int minAgeLimit; // age limit is 15 max min 8
};

//****************************************************************
// Derived Class: raceWalk 
//****************************************************************
class raceWalk : public Race 
{
    public:
        // constructor/destructor 
        raceWalk(const std::string& name,
                 const std::string& date,
                 int penaltyCt,
                 bool disqualified);
        virtual ~raceWalk();

        // overrides from base 
        bool registerRace(const std::string& participant) override;
        void startRace() override;
        void stopRace() override;

        // unique methods
        void markDisqualified();
        void administerPenalty();

    private:
        bool disqualifiedFlag; // according to racewalking rules, 7 penalties = disqualification
        int penaltyCount;      // penalties places a 2-3 minute timeout for contestant
};

/****************************************************************
/ Derived Class: halfMarathon 
****************************************************************/
class halfMarathon : public Race 
{
    public:
        // constructor/destructor 
        halfMarathon(const std::string& name,
                     const std::string& date,
                     double avgPace, int restStops);
        virtual ~halfMarathon();

        // overrides from base
        bool registerRace(const std::string& participant) override;
        void startRace() override;
        void stopRace() override;

        // unique methods
        void administerElectrolytes(); // will decrease avg pace (helps maintain energy)
        int estimatedFinish();         // uses calculated avg pace and number of rest stops passed to estimate finish time
        double calculateAvgPace();

    private:
        int numRestStops;
        double avgPace;
};

/****************************************************************
/ data structure struct: rbNode
/    - node for the redblacktree storing Race objects
****************************************************************/
enum class Color { RED, BLACK };

struct rbNode
{
    std::string key;
    std::shared_ptr<Race> data;
    Color color;
    rbNode* parent;
    rbNode* left;
    rbNode* right;

    // constructor/destructor
    rbNode(const std::string& key, std::shared_ptr<Race> racePtr)
        : key(key), data(std::move(racePtr)), color(Color::RED),
          parent(nullptr), left(nullptr), right(nullptr) {}
};

/****************************************************************
/ data structure class: redBlackTree
/    - holds Race objects (base class pointers)
****************************************************************/
class redBlackTree
{
    public:
        // constructor/destructor
        redBlackTree();
        ~redBlackTree();

        // public methods
        bool insert(std::shared_ptr<Race> racePtr);
        void removeAll();
        void displayAll() const;

    private:
        rbNode* root;

        // recursive helpers
        bool insertHelper(rbNode*& node, rbNode* newNode, rbNode* parent);
        void fixInsertion(rbNode* node);
        void rotateLeft(rbNode* x);
        void rotateRight(rbNode* x);

        void removeAll(rbNode*& node);
        void displayAll(rbNode* node) const;
};

#endif  // Marchuk_Ariella_Program3_Race_H

