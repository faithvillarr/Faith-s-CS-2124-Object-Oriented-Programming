/*  Author: Faith Villarreal
 *  File Purpose: Definition of Warrior class.
 */

#ifndef HW06_NOBLE_H
#define HW06_NOBLE_H

#include <iostream>
#include <string>
#include <vector>
#include "Warrior.h"

using namespace std;

namespace WarriorCraft {
    class Warrior;

    class Noble {
        friend ostream &operator<<(ostream &os, const Noble &noble);

    private:
        string name;
        vector<Warrior *> army;
        bool isAlive = true;
    public:
        Noble(const string &name) : name(name) {};

        //getters for private data members
        const string &getName() const;
        double getArmyStrength() const;

        //hires a new warrior
        bool hire(Warrior & warrior);

        //fires a warrior if in my army
        bool fire(Warrior & warrior);

        //i lost so my army and i must now perish
        //all of our health is reduced to zero as our souls
        //move to the next plane.
        void die();

        //commence battle against some other warrior
        //resistance is futile
        void battle(Noble &);

        //removes a warrior from my army vector. true if successful.
        bool removeWarr(Warrior *);
    };

}

#endif //HW06_NOBLE_H
