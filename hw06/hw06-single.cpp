/* Author: Faith Villarreal
 * Assignment: hw05: dynamic memory
 * Purpose: Create a program to simulate battle between nobles w/ their armies

 PLEASE READ MS/MR GRADER.
 I copied the test code into the main function on this file, so you can just
 compile this file first and check it. Then you can compile the other files.
 Hope that helps!

 */


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior;
class Noble;

class Warrior{
    //Output operator overloading.
    friend ostream& operator<<(ostream&, const Warrior&);
private:
    string name;
    double strength;
    bool employable = true; //if not hired, true. if employed, false.
    Noble * myNoble = nullptr;
public:
    Warrior(const string& name, double str): name(name), strength(str){};

    //getters for all private members except myNoble
    const string& getName() const;
    double getStrength() const;
    bool isEmployable() const;

    //sets myNoble to a new noble if possible
    void setNewNoble(Noble * noble);

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

    //removes a warrior from my army vector
    bool removeWarr(Warrior *);

    //run when a warrior becomes a coward
    //(they ran away because i didnt feed them for a month)
    bool defector(Warrior *);

};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

//WARRIOR METHODS
//standard getters for all private fields
const string& Warrior::getName() const { return name; }
double Warrior::getStrength() const { return strength; }
bool Warrior::isEmployable() const { return employable; }

//Purpose: Inverts employment status. Returns nothing.
void Warrior::changeEmployment(){ employable = !employable; }

//Purpose: Sets to new given strength. Returns nothing.
void Warrior::setStrength(double new_strength){ strength = new_strength; }

//Purpose: Sets noble of warrior
void Warrior::setNewNoble(Noble * noble) { myNoble = noble; }

//the infamous new runaway function
//allows warriors to runaway from nobles, removing them from the nobles army
bool Warrior::runaway() {
    //need to be employed and not dead
    if(!isEmployable() && strength != 0){

        if(myNoble->defector(this)) {
            this->changeEmployment();
            cout << name << " flees in terror, abandoning his lord, ";
            cout << myNoble->getName() << endl;
            myNoble = nullptr; //last step bc removes access
            return true;
        }else
            cout << name << " was not hired by " << myNoble->getName() << endl;
    }else if(!isEmployable()){ cout << name << " has not been hired!\n";
    }else{ cout << name << " is dead! They run away too late. ;-; \n"; }
    return false;
}
bool Warrior::isHired(){ return !isEmployable(); }


//Output operator overloading.
ostream& operator<<(ostream& os, const Warrior& warrior){
    os << "\t" << warrior.name << ": " << warrior.strength <<endl;
    return os;
}

// NOBLE METHODS
//Overloading output operator for Noble class. Uses const noble pointer.
ostream& operator<<(ostream& os, const Noble & noble) {
    os << noble.name << " has an army of " << noble.army.size() << endl;
    for(const Warrior * w : noble.army){ os << * w; }
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
    if(isAlive && warrior.isEmployable()){
        army.push_back(&warrior);
        warrior.changeEmployment();
        warrior.setNewNoble(this);
        return true;
    }
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

//removes a defacting warrior from army vector
bool Noble::defector(Warrior * coward) {
    return removeWarr(coward);
}
