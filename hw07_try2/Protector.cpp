/* Author: Faith Villarreal
 * File Name: Protector.cpp
 * Purpose: Defines all methods of Protector class and derived classes
 *          Wizards and Warrior. Also defines derived classes of Warrior:
 *          Archer and Swordsman.
 */

#include "Protector.h"
#include "Noble.h"
#include <iostream>
#include <string>

using namespace std;
namespace WarriorCraft {

    /*!
     * PROTECTOR METHOD DEFINITIONS
     !*/

    // Constructor
    Protector::Protector(string n, double s): name(n), strength(s){};

    // Output Operator
    // A friend to Protector
    // Calls each derived classes print method for specific formatting.
    ostream& operator<<(ostream& os, const Protector& p){
        os << p.name << " has strength " << p.strength;
        return os;
    }

    //SETTERS
    //setLord(Lord*) changes myLord to the passed in Lord*
    void Protector::setLord(Lord * newLord) { myLord = newLord; }
    //changeStrength(double) changes strength to whatever double was passed in
    void Protector::changeStrength(double newStr){ strength = newStr; }

    //GETTERS
    //getLord() returns a reference to the lord a protector serves
    const Lord & Protector::getLord() const { return *myLord; }
    //getName() returns private data member 'name'
    const string& Protector::getName() const{ return name; }
    //getStrenth() returns private data member 'strength'
    const double Protector::getStrength() const { return strength; }

    /* runaway() method defined as outlined in prompt.
     * Removes the protector from thier lord's army and sets the myLord
     *      pointer to nullptr.
     * Works only if they're not dead nor unemployed.     */
    void Protector::runaway(){
        if(strength == 0){//they're dead
            cout << name << " is already dead and cannot runaway!" << endl;
        }else if(myLord == nullptr){//they're unemployed
            cout << name << ", you're not employed lazy bum."
                            " There's no one to runaway from stupid.";
        }else {//you're good to go now
            cout << name << " flees in terror, abandoning his lord, "
                 << myLord->getName() << endl;
            myLord->removeWarr(*this);
        }
    }

    /*!
     * WIZARD METHOD DEFINITIONS
     !*/
    //Constructor. Passed directly to Protector constructor
    Wizard::Wizard(string n, double s): Protector(n,s){};
    // defend() outputs a battle-cry when their lord goes to battle.
    void Wizard::defend() const{
        cout << "POOF!";
    }

    /*!
     * WARRIOR METHOD DEFINITIONS
     !*/
    //Constructor. Passed directly to Protector constructor
    Warrior::Warrior(string n, double s): Protector(n, s){};
    // defend() outputs a battle-cry when their lord goes to battle.
    void Warrior::defend() const {
        cout << getName() << " says: Take that in the name of my lord, "
             << getLord().getName();
    }

    /*!
     * ARCHER METHOD DEFINITIONS
     !*/
    //Constructor. Passed directly to Warrior constructor
    Archer::Archer(string n, double s): Warrior(n, s){};
    // defend() outputs a battle-cry when their lord goes to battle.
    void Archer::defend() const {
        cout << "TWANG! ";
        Warrior::defend();
    }

    /*!
     * SWORDSMAN METHOD DEFINITIONS
     !*/
    //Constructor. Passed directly to Warrior constructor
    Swordsman::Swordsman(string n, double s): Warrior(n, s){};
    // defend() outputs a battle-cry when their lord goes to battle.
    void Swordsman::defend() const {
        cout << "CLANG! ";
        Warrior::defend();
    }


}
