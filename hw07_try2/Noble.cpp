/* Author: Faith Villarreal
 * File Name: Noble.cpp
 * Purpose: utline the methods and data members of the Noble class
 * and derived classes Lord and PersonWithStrengthToFight */

#include "Protector.h"
#include "Noble.h"
#include <iostream>
#include <string>

using namespace std;
namespace WarriorCraft {
    /*!
     * NOBLE STUFF : BASE CLASS
     !*/
    //Constructor
    Noble::Noble(string n): name(n){};

    //Output Operator
    ostream& operator<<(ostream & os, const Noble& n){
        os << n.name;
        n.print(os);
        return os;
    }
    //GETTERS
    // isAlive() returns private data member 'alive';
    bool Noble::isAlive() const{ return alive; }
    // getName() returns ref to private data member 'name'
    const string& Noble::getName() const{ return name; }

    //HELPER METHODS
    // change the strength of the noble depending on the type of noble
    // sets alive to false in Noble class scope
    void Noble::die() { alive = false; }

    //REQUIRED BY ASSIGNMENT AND NOBLE USE IN MAIN
    // simulates battle between this noble and the one passed through
    void Noble::battle(Noble & enemy){
        //announce battle immediately bc dead nobles can declare battle
        cout << name << " battles " << enemy.getName() << endl;

        //grab strength of each noble to efficiency
        double my_strength = this->getStrength();
        double enemy_strength = enemy.getStrength();

        if(!(alive || enemy.alive)){
            //if they're both dead
            cout << "Oh, NO!  They're both dead!  Yuck!\n";
        }else if(alive && enemy.alive){
            //if both nobles are alive
            defend();
            enemy.defend();
            if(my_strength == enemy_strength){
                //tie between both nobles
                //they both die
                this->die();
                enemy.die();
                cout << "Mutual annihalation!\n";
            }else if(my_strength > enemy_strength){
                //this noble wins
                enemy.die();
                win(my_strength, enemy_strength);
                cout << name << " defeat " << enemy.name << endl;
            }else{
                //challenged noble wins
                enemy.win(enemy_strength, my_strength);
                die();
                cout << enemy.name << " defeat " << name << endl;
            }
        }else if (alive){ //only this noble is alive
            defend();
            cout << "He's dead "<< name << endl;
        }else { //only other noble is dead
            enemy.defend();
            cout << "He's dead " << enemy.name << endl;
        }
    }

    /*!
     * PERSON W/STRENGTH STUFF
     !*/
    //Constructor
    PersonWithStrengthToFight::PersonWithStrengthToFight(string n, double s):
            Noble(n), strength(s){};

    //GETTERS
    //getStrength() returns private data member 'strength'
    double PersonWithStrengthToFight::getStrength() const { return strength; }

    //HELPER METHODS
    //print() outputs information on this noble in the format used for
    //      nobles with strength to fight.
    const ostream& PersonWithStrengthToFight::print(ostream& os) const {
        os << " had the strength: " <<
        PersonWithStrengthToFight::strength;
        return os;
    }
    //die() sets private data member 'strength' to 0
    //      also calls Noble::die() so that Noble::alive is set to false,
    void PersonWithStrengthToFight::die(){
        strength = 0;
        Noble::die();
    }
    void PersonWithStrengthToFight::win(double win_str, double loser_str) {
        strength *= 1-(loser_str/win_str);
    }

    //REQUIRED METHOD
    // defend() outputs "Ugh!" the format expected of nobles
    //      with the strength to fight.
    void PersonWithStrengthToFight::defend() const{
        cout << "Ugh!" << endl;
    }


    /*!
     * LORD STUFF
     !*/
    //Constructor. Calls Noble constructor.
    Lord::Lord(string n): Noble(n){};

    //HELPER METHODS
    //print() outputs all of the protectors employed by this lord
    const ostream& Lord::print(ostream& os) const {
        os << " has an army of size: " << army.size();
            for (size_t i = 0; i < army.size(); ++i) {
                os << "   " << *army[i];
                if (i != army.size() - 1) cout << endl;
            }
        return os;
    }
    //die() sets all protector's strength to zero
    //      also calls Noble::die() so that Noble::alive is set to false,
    void Lord::die() {
        for(Protector * p : army){
            p->changeStrength(0);
        }
        Noble::die();
    }
    //getStrength() returns total of all Protector's strength
    double Lord::getStrength() const {
        double res = 0;
        for(const Protector * p : army){
            res += p->getStrength();
        }
        return res;
    }
    // win() reduces strength of all protectors based on the ratio
    //      of total strength between the two nobles
    void Lord::win(double win_str, double loser_str) {
        double ratio = 1 - (loser_str/win_str);
        for (Protector *p: army) {
            p->changeStrength(p->getStrength() * ratio);
        }
    }
    //removeWarr() aids runaway method and fires method
    //Returns true if the protector was employed by this Noble
    //      and the protector is not dead (which implies the Noble
    //      is also not dead).
    bool Lord::removeWarr(Protector & p) {
        for (size_t i = 0; i < army.size()-1; ++i) {
            //this loop moves protector to back of vector if present
            if(army[i] == &p){
                //this process of swapping maintains
                //the order of the army
                army[i] = army[i+1];
                army[i+1] = &p;
            }
        }
        //deletes protector if present and returns true
        if(army[army.size()-1] == &p) {
            army.pop_back();
            p.setLord(nullptr);
            return true;
        }
        //returns false if protector wasn't present
        return false;
    }

    //RE
    //defend() calls the defend() method of all Protectors
    //      employed by this Noble
    void Lord::defend() const{
        for(const Protector * p : army){
            p->defend();
            cout << endl;
        }
    }
    //hires() hires a protector employed by this Noble
    void Lord::hires(Protector & p) {
        /* I took the second output out because it wasn't on the output
            but it seemed necessary based on previous assignments.*/
        if(!p.getStrength()){ //if protector is dead
            cout << "Protector " << p.getName() <<
                 " is already dead!" << endl;
        }else if (&p.getLord()){//if already hired
            //cout << "Protector " << p.getName() << " cannot be hired. They a"
            //        "re already working for " << p.getLord().getName()<< endl;
        }else if (isAlive()){
            // protector is employed by this noble and this noble is alive
            //time to hire!
            p.setLord(this);
            army.push_back(&p);
        }
    }
    void Lord::fires(Protector & p){
        if (!isAlive()) { //noble is dead
            cout << "Lord " << getName() << " is already dead!" << endl;
        }
        if (removeWarr(p)) { // if this noble employs that protector
            cout << p.getName() << ", you don't work for me anymore! -- "
                 << getName() << "." << endl;
        }
    }
}
