/*  Author: Faith Villarreal
 *  File Purpose: Implementation of all methods of Noble class.
 */

#include "Noble.h"

namespace WarriorCraft{
    // NOBLE METHODS
    //Overloading output operator for Noble class. Uses const noble pointer.
    ostream& operator<<(ostream& os, const Noble & noble) {
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for(const Warrior * const w : noble.army){ os << * w; }
        return os;
    }
    //Gets the name
    const string& Noble::getName() const { return name; }

    // Purpose: get army's total strength for battle method.
    // Returns: total army's strength as double.
    double Noble::getArmyStrength() const {
        double res = 0;
        for(const Warrior * const w :army){
            res += w->getStrength();
        }
        return res;
    }

    /* * Purpose: To deplete the strength of every soldier in the army to zero.
    *          Mark the Noble as dead.
    *          Supports the battle function.
    *          Returns and uses nothing */
    void Noble::die(){
        for (Warrior * w : army){
            w->setStrength(0);
        }
        this->isAlive = false;
    }

    // Purpose: To have two nobles battle.
    //          Determining who wins or if no one wins.
    // Parameter: (Noble)(ptr) The enemy noble to be considered.
    // Returns nothing.
    void Noble::battle(Noble & enemy) {
        cout << name << " battles " << enemy.name << endl;

        //if someone is dead
        if (!this->isAlive && !enemy.isAlive) {//both dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!this->isAlive) {
            cout << "He's dead, " << enemy.name << endl;
        } else if (!enemy.isAlive) {
            cout << "He's dead, " << name << endl;

            //this noble wins
        } else if (this->getArmyStrength() > enemy.getArmyStrength()) {
            //first augment winner's army
            double change = 1 - (enemy.getArmyStrength()
                                 / this->getArmyStrength());
            for (Warrior * w: army) {
                w->setStrength(w->getStrength() * change);
            }

            //kill loser
            enemy.die();

            cout << this->name << " defeats " << enemy.name << endl;

            //You win
        } else if (enemy.getArmyStrength() > this->getArmyStrength()) {
            // 1 - (getArmyStrength() / enemy->getArmyStrength())
            double change = 1 - (getArmyStrength() / enemy.getArmyStrength());
            for (Warrior * w: enemy.army) {
                w->setStrength(w->getStrength() * change);
            }

            //kill loser
            this->die();

            cout << enemy.name << " defeats " << this->name << endl;

        } else {//Mutual annihilation
            this->die();
            enemy.die();

            cout << "Mutual Annihilation: " << this->name << " and ";
            cout << enemy.name << " die at each other's hands" << endl;
        }
    }

    /* Purpose: Hire a warrior via pointer.
    * Parameter: The pointer to that warrior.
    * Returns true if successfully hired. */
    bool Noble::hire(Warrior & warrior){
        //already checked if exists
        //if noble is alive and if noble is not dead and alr hired?
        if(isAlive && !warrior.isHired()){
            army.push_back(&warrior);
            warrior.changeEmployment();
            warrior.setNewNoble(this);
            return true;
        }
        cout << name << " failed to hire " << warrior.getName() << endl;
        return false;
    }

    /* Purpose: Fire a warrior via pointer.
    * Parameter: The pointer to that warrior.
    * Returns true if successfully fired. */
    bool Noble::fire(Warrior & warrior){
        //already checked if exists
        //if warrior is alive and if noble is not dead and alr hired?
        for(Warrior * w : army){
            if(w == &warrior && isAlive) {
                //pushes that warrrior to the back
                if (removeWarr(w)) {
                    cout << warrior.getName() << ", you dont work for";
                    cout << " me any more! -- " << this->name << endl;
                    warrior.changeEmployment();
                    warrior.setNewNoble(nullptr);
                    return true;
                }
            }

        }
        return false;
    }

    //returns true if successfully removes warrior from the army
    bool Noble::removeWarr(Warrior * warrior){
        for (size_t i = 0; i < army.size() - 1; i++) {
            if (army[i] == warrior) {
                army[i] = army[i + 1];
                army[i + 1] = warrior;
            }
        }
        if (army[army.size() - 1] == warrior) {
            army.pop_back();
            return true;
        }
        return false;
    }
}
