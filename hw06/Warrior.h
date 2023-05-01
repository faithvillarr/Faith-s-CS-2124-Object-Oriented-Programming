/*  Author: Faith Villarreal
 *  File Purpose: Definition of Warrior class.
 */

#ifndef HW06_WARRIOR_H
#define HW06_WARRIOR_H

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"

using namespace std;

namespace WarriorCraft{
    class Noble;

    class Warrior {
        //Output operator overloading.
        friend ostream &operator<<(ostream &, const Warrior &);

    private:
        string name;
        double strength;
        bool employable = true; //if not hired, true. if employed, false.
        Noble *myNoble = nullptr;
    public:
        Warrior(const string &name, double str) : name(name), strength(str) {};

        //getters for all private members
        const string &getName() const;

        const double getStrength() const;

        bool isEmployable() const;

        //sets myNoble to a new noble if possible
        void setNewNoble(Noble *noble);

        // returns isEmployable
        bool isHired();

        //setters
        //inverts employments status
        void changeEmployment();

        //sets to a new strength
        void setStrength(double new_strength);

        //runs away from myNoble's army
        bool runaway();
    };

}
#endif //HW06_WARRIOR_H
