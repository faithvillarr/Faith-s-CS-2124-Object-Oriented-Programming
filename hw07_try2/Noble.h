/* Author: Faith Villarreal
 * File Name: Noble.cpp
 * Purpose: Defines all methods of Noble class and derived classes Lord and
 *          PersonWithStrengthToFight */


#ifndef HW07_NOBLE_H
#define HW07_NOBLE_H

using namespace std;
#include <vector>
#include <string>

namespace WarriorCraft {
    /*!
     * NOBLE
     !*/
    class Noble{
        //Output Operator
        friend ostream& operator<<(ostream&, const Noble&);
    private:
        //Same thing. Could've made these both protected.
        //Could've gotten rid of getters.
        string name;
        bool alive = true;
    public:
        //constructor
        Noble(string n);

        //GETTERS
        // isAlive() returns private data member 'alive';
        bool isAlive() const;
        // getName() returns ref to private data member 'name'
        const string& getName() const;

        //HELPER METHODS
        // change the strength of the noble depending on the type of noble
        // sets alive to false in Noble class scope
        virtual void die();
        // getStrength returns strength of noble depending on their type
        // not defined in Noble class. this is okay because the Noble class
        // is an abstract class.
        virtual double getStrength() const = 0;

        //Methods required by assignment
        // simulates battle between this noble and the one passed through
        void battle(Noble & enemy);
        //print() used to output in the format used for each type of Noble
        virtual const ostream& print(ostream&) const = 0;
        //defend() requires all nobles to make a battle cry or call for
        //      their soldiers to make a battlecry
        virtual void defend() const = 0;
        //win() reduces the winners strength proportionally to loser's strength
        virtual void win(double winner_str, double loser_str) = 0;

    };

    /*!
     * NOBLE W/ STRENGTH TO FIGHT
     !*/
    class PersonWithStrengthToFight : public Noble{
    private:
        double strength; //wouldn't be protected bc no derived classes
    public:
        //Constructor. Calls Noble constructor for string n.
        PersonWithStrengthToFight(string n, double s);

        //GETTERS
        //getStrength() returns private data member 'strength'
        double getStrength() const;

        //HELPER METHODS
        //print() outputs information on this noble in the format used for
        //      nobles with strength to fight.
        const ostream& print(ostream&) const;
        //die() sets private data member 'strength' to 0
        void die();
        // win() reduces this noble's strength proportionally
        //      to the loser's strength
        void win(double winner_strength, double loser_strength);

        //REQUIRED METHOD
        // defend() outputs "Ugh!" the format expected of nobles
        //      with the strength to fight.
        void defend() const;
    };

    /*!
     * LORD
     !*/
    class Protector;
    class Lord : public Noble{
    private:
        //vector of all Protectors employed by this Noble
        vector<Protector*> army;
    public:
        //Constructor. Calls Noble constructor.
        Lord(string n);

        //HELPER METHODS
        //print() outputs information on this noble in the format used for
        //      lords.
        const ostream& print(ostream&) const;
        //die() sets all protector's strength to zero
        void die();
        //getStrength() adds up all Protector's strength
        double getStrength() const;
        // win() reduces strength of all protectors based on the ratio
        //      of total strength between the two nobles
        void win(double winner_strength, double loser_strength);
        //removeWarr() aids runaway method and fires method
        //Returns true if the protector was employed by this Noble
        //      and the protector is not dead (which implies the Noble
        //      is also not dead).
        bool removeWarr(Protector& p);

        // METHODS REQUIRED BY ASSIGNMENT
        //defend() calls the defend() method of all Protectors
        //      employed by this Noble
        void defend() const;
        //hires() hires a protector employed by this Noble
        void hires(Protector &);
        //fires() fires a protector employed by this Noble
        void fires(Protector &);
    };
}

#endif //HW07_NOBLE_H
