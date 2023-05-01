/* Author: Faith Villarreal
 * File Name: Noble.cpp
 * Purpose: Outline the methods and data members of the Protector class and
 *          derived classes Wizards and Warrior. Also defines derived classes
 *          of Warrior: Archer and Swordsman.
 */

#ifndef HW07_PROTECTOR_H
#define HW07_PROTECTOR_H

using namespace std;
#include <string>


namespace WarriorCraft {
    class Lord;
    class Protector{
        //Output Operator
        friend ostream& operator<<(ostream&, const Protector&);
    private:
        /* I made these private because a TA told me I would
         *      lose points for using protected keywords.
         * I could have easily made them protected so
         *      that no getters or setter were needed.
         * By making them protected, the derived classes could access these
         *      variables, significantly reducing the number of methods
         *      I had to define for both classes.
         */
        string name;
        double strength;
        Lord * myLord = nullptr;
        /* if I had used the protected keyword, it would've looked like this :)
    protected:
        string name;
        double strength;
        Lord * myLord = nullptr;
         */
    public:
        //Constructor. Called by every derived class.
        Protector(string n, double s);

        /*!GETTERS - Pretty self explanatory!*/
        //getLord() returns the lord a protector serves
        const Lord & getLord() const;
        //getName() returns the name of the protector
        const string& getName() const;
        //getStrength() returns a protector's strength
        const double getStrength() const;

        /*!SETTERS!*/
        //setLord(Lord *) changes myLord to whatever ptr is passed in.
        void setLord(Lord *);
        //changeStrength(double) changes strength to the double passed in
        void changeStrength(double);

        /*!OTHER!*/
        //defend() is a pure virtual method
        virtual void defend() const = 0;
        //runaway() called when protector flees employer
        void runaway();

    };

    class Wizard : public Protector{
    public:
        //Constructor. Passed directly to Protector constructor
        Wizard(string n, double s);
        //Protector makes a battlecry
        void defend() const;
    };
    class Warrior : public Protector{
    public:
        //Constructor. Passed directly to Protector constructor
        Warrior(string n, double s);
        //Protector makes a battlecry
        void defend() const;
    };

    class Archer : public Warrior{
    public:
        //Constructor. Passed directly to Warrior constructor
        Archer(string n, double s);
        //Protector makes a battlecry
        void defend() const;
    };
    class Swordsman : public Warrior{
    public:
        //Constructor. Passed directly to Warrior constructor
        Swordsman(string n, double s);
        //Protector makes a battlecry
        void defend() const;
    };
}

#endif //HW07_PROTECTOR_H
