/*  Author: Faith Villarreal
 *  File Purpose: Implementation of all methods of Warrior class.
 */

#include "Warrior.h"

namespace WarriorCraft{

    //WARRIOR METHODS
    //standard getters for all private fields
    const string& Warrior::getName() const { return name; }
    const double Warrior::getStrength() const { return strength; }
    bool Warrior::isHired(){ return !employable; }

    //Purpose: Inverts employment status. Returns nothing.
    void Warrior::changeEmployment(){ employable = !employable; }

    //Purpose: Sets to new given strength. Returns nothing.
    void Warrior::setStrength(double new_strength){ strength = new_strength; }

    //Sets a new noble/lord to the warrior
    void Warrior::setNewNoble(Noble * noble) { myNoble = noble; }

    //the infamous new runaway function
    //allows warriors to runaway from nobles, removing them from the nobles army
    bool Warrior::runaway() {
        //need to be employed and not dead
        if(isHired() && strength != 0){

            if(myNoble->removeWarr(this)) {
                this->changeEmployment();
                cout << name << " flees in terror, abandoning his lord, ";
                cout << myNoble->getName() << endl;
                myNoble = nullptr; //last step bc removes access
                return true;
            }else
                cout << name << " was not hired by " << myNoble->getName() << endl;
        }else if(!isHired()){ cout << name << " has not been hired!\n";
        }else{ cout << name << " is dead! They run away too late. ;-; \n"; }
        return false;
    }

    //Output operator overloading.
    ostream& operator<<(ostream& os, const Warrior& warrior){
        os << "\t" << warrior.name << ": " << warrior.strength <<endl;
        return os;
    }

}