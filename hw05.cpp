/* Author: Faith Villarreal
 * Assignment: hw05: dynamic memory
 * Purpose: Create a program to simulate battle between nobles w/ their armies
INSTRUCTIONS:
 * Each time a warrior or a noble is defined, we will create it on the heap.
 *  We will keep track of the nobles in a vector of pointers to nobles.
 *  We will keep track of all warriors using a vector of pointers to warriors
 */


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


class Warrior{
private:
    string name;
    double strength;
    bool employable = true; //if not hired, true. if employed, false.

    //Output operator overloading.
    friend ostream& operator<<(ostream& os, const Warrior& warrior){
        os << "\t" << warrior.name << ": " << warrior.strength << endl;
        return os;
    }

public:
    //constructor
    Warrior(const string& name, double str): name(name), strength(str){};

    //getter for each private variable field
    const string& getName() const { return name; }
    double getStrength() const { return strength; }
    bool isEmployable() const { return employable; }

    //setters for employability and strength

    //Purpose: Inverts employment status. Returns nothing.
    void changeEmployment(){ employable = !employable; }

    //Purpose: Sets to new given strength. Returns nothing.
    void setStrength(double new_strength ){ strength = new_strength; }

};


class Noble{
private:
    string name;
    vector<Warrior*> army;
    bool isAlive = true;

    //Overloading output operator for Noble class. Uses const noble pointer.
    friend ostream& operator<<(ostream& os, const Noble & noble) {

        os << noble.name << " has an army of " << noble.army.size() << endl;
        for(const Warrior * w : noble.army){
            os << *w;
        }
        return os;
    }
public:
    //getters for private variables
    const string& getName() const { return name; }

    /* Purpose: get army's total strength for battle method.
     * Returns: total army's strength as double.    */
    double getArmyStrength() const {
        double res = 0;
        for(const Warrior * const w :army){
            res += w->getStrength();
        }
        return res;
    }

    Noble(const string& name) : name(name){};

    /* Purpose: Hire a warrior via pointer.
     * Parameter: The pointer to that warrior.
     * Returns true if successfully hired. */
    bool hire(Warrior * warrior){
        //already checked if exists
        //if noble is alive and if noble is not dead and alr hired?
        if(isAlive && warrior->isEmployable()){
            army.push_back(warrior);
            warrior->changeEmployment();
            return true;
        }
        return false;
    }
    /* Purpose: Fire a warrior via pointer.
     * Parameter: The pointer to that warrior.
     * Returns true if successfully fired. */
    bool fire(Warrior* warrior){
        //already checked if exists
        //if warrior is alive and if noble is not dead and alr hired?
        for(Warrior * w : army){
            if(w == warrior && isAlive) {
                //pushes that warrrior to the back
                for (size_t i = 0; i < army.size() - 1; i++) {
                    if (army[i] == warrior) {
                        army[i] = army[i + 1];
                        army[i + 1] = warrior;
                    }
                }
                if (army[army.size() - 1] == warrior) {
                    army.pop_back();
                    cout << warrior->getName() << ", you dont work for";
                    cout << " me any more! -- " << this->name << endl;
                    warrior->changeEmployment();
                    return true;
                }
            }

        }
        return false;
    }


     /* * Purpose: To deplete the strength of every soldier in the army to zero.
     *          Mark the Noble as dead.
     *          Supports the battle function.
     *          Returns and uses nothing */
    void die(){
        for (Warrior * w : army){
            w->setStrength(0);
        }
        this->isAlive = false;
    }

    // Purpose: To have two nobles battle.
    //          Determining who wins or if no one wins.
    // Parameter: (Noble)(ptr) The enemy noble to be considered.
    // Returns nothing.

    void battle(Noble* enemy) {
        cout << name << " battles " << enemy->name << endl;

        //if someone is dead
        if (!this->isAlive && !enemy->isAlive) {//both dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!this->isAlive) {
            cout << "He's dead, " << enemy->name << endl;
        } else if (!enemy->isAlive) {
            cout << "He's dead, " << name << endl;

            //this noble wins
        } else if (this->getArmyStrength() > enemy->getArmyStrength()) {
            //first augment winner's army
            double change = 1 - (enemy->getArmyStrength()
                                 / this->getArmyStrength());
            for (Warrior * w: army) {
                w->setStrength(w->getStrength() * change);
            }

            //kill loser
            enemy->die();

            cout << this->name << " defeats " << enemy->name << endl;

            //You win
        } else if (enemy->getArmyStrength() > this->getArmyStrength()) {
            // 1 - (getArmyStrength() / enemy->getArmyStrength())
            double change = 1 - (getArmyStrength() / enemy->getArmyStrength());
            for (Warrior * w: enemy->army) {
                w->setStrength(w->getStrength() * change);
            }

            //kill loser
            this->die();

            cout << enemy->name << " defeats " << this->name << endl;

        } else {//Mutual annihilation
            this->die();
            enemy->die();

            cout << "Mutual Annihilation: " << this->name << " and ";
            cout << enemy->name << " die at each other's hands" << endl;
        }
    }

};


//fuction prototypes
void open_file(ifstream&);
void play_medival_times(ifstream&);
Noble* getNoblePtr(const vector<Noble*>&, const string&);
Warrior* getWrPtr(const vector<Warrior*>&, const string&);
void status(const vector<Noble*>&, const vector<Warrior*>&);

int main() {
    //get file
    ifstream noble_warrior_file;

    //open file
    open_file(noble_warrior_file);

    //read and use file
    play_medival_times(noble_warrior_file);

    //close file
    noble_warrior_file.close();
}

/*Purpose: Open file of nobles and warriors
 *Parameter: (ifstream)(ref) Uses main's input file stream to grab file
 * Return: N/A */
void open_file(ifstream& ifs){

    ifs.open("nobleWarriors.txt");
    if(!ifs){
        cerr<<"File not found!"<<endl;
        exit(1);
    }
}

/* Purpose: Read and process file. Use other functions.
 * Parameters: (ifstream)(ref) OG input file stream.
 * Returns nothing.  */
void play_medival_times(ifstream& ifs){
    vector<Noble*> allNobles;
    vector<Warrior*> allWarriors;

    //we'll check if they exist here bc we have access to the arrays
    string command;
    while(ifs >> command){
        if(command == "Noble"){
            string noble_name;
            ifs >> noble_name;

            //check if already exists
            if(getNoblePtr(allNobles, noble_name) == nullptr){

                //make a noble in heap
                Noble* new_noble = new Noble(noble_name);
                allNobles.push_back(new_noble);

            }else
                cout << "That noble already exists!" << endl;

        } else if (command == "Warrior"){
            string warrior_name;
            double w_str;
            ifs >> warrior_name >> w_str;
            //check if already exists
            if(getWrPtr(allWarriors, warrior_name) == nullptr){

                //make a warrior in heap
                Warrior* new_warrior = new Warrior(warrior_name, w_str);
                allWarriors.push_back(new_warrior);

            }else
                cout << "That warrior already exists!" << endl;

        //hire or fire
        //together because they require to check both exist
        } else if (command == "Hire") {

            string noble_name, warrior_name;
            ifs >> noble_name >> warrior_name;

            Noble *noble = getNoblePtr(allNobles, noble_name);
            Warrior *warrior = getWrPtr(allWarriors, warrior_name);

            if (noble != nullptr) {
                if (warrior != nullptr) {
                    //actually hire that warrior to/from noble's army
                    if (!noble->hire(warrior)) {
                        cout << noble_name << " failed to hire ";
                        cout << warrior_name << endl;
                    }
                }else {
                    cout << "Attempting to hire unknown warrior: ";
                    cout << warrior_name << endl;
                }
            }else{
                cout << "Attempting to hire to unknown noble: ";
                cout << noble_name << endl;

            }

        }else if (command == "Fire"){
            string noble_name, warrior_name;
            ifs >> noble_name >> warrior_name;

            Noble *noble = getNoblePtr(allNobles, noble_name);
            Warrior *warrior = getWrPtr(allWarriors, warrior_name);

            if (noble != nullptr){
                if (warrior != nullptr) {
                    //actually fire that warrior to/from noble's army
                    if (!noble->fire(warrior)) {
                        cout << noble_name << " failed to fire ";
                        cout << warrior_name << endl;
                    }
                }else {
                    cout << "Attempting to fire unknown warrior: ";
                    cout << warrior_name << endl;
                }
            }else{
                cout << "Attempting to fire to unknown noble: ";
                cout << noble_name << endl;
            }
        }else if (command == "Battle"){
            string noble1_name, noble2_name;
            ifs >> noble1_name >> noble2_name;

            Noble* noble1 = getNoblePtr(allNobles, noble1_name);
            Noble* noble2 = getNoblePtr(allNobles, noble2_name);

            if(noble1 != nullptr && noble2 != nullptr){
                noble1->battle(noble2);
            }else if (noble1 == nullptr){
                cout << "Attepting to battle unknown noble: ";
                cout << noble1_name << endl;

            }else{
                cout << "Attepting to battle unknown noble: ";
                cout << noble2_name << endl;
            }

        } else if (command == "Status"){
            status(allNobles, allWarriors);

        } else if (command == "Clear"){
            for (Warrior* w : allWarriors){
                delete w;
            }
            for (Noble* n : allNobles){
                delete n;
            }
            allNobles.clear();
            allWarriors.clear();
        }
    }

}

/* Purpose: Grabs noble ptr if it exists from array.
 * Parameters: (const)(vector)(Noble*)(ref) ref to main vector of nobles
 * Parameters: (const)(string)(ref) ref to name string from file
 * Return: (Noble*) Returns ptr to desired noble if found
 *          Returns nullptr if not found. */
Noble* getNoblePtr(const vector<Noble*>& allNobles, const string& name){
    for(Noble * const n : allNobles){
        if(n->getName() == name)
            return n;
    }
    return nullptr;
}

/* Purpose: Grabs warrior ptr if it exists from array.
 * Parameters: (const)(vector)(Warrior*)(ref) ref to main vector of warriors
 * Parameters: (const)(string)(ref) ref to name string from file
 * Return: (Warrior*) Returns ptr to desired warrior if found
 *          Returns nullptr if not found. */
Warrior* getWrPtr(const vector<Warrior*>& allWarrior, const string& name){
    for(Warrior * const w : allWarrior){
        if(w->getName() == name)
            return w;
    }
    return nullptr;
}

/* Purpose: Print all nobles' info to terminal.
 * Parameters: Refs to vectors of ptrs to all nobles and warriors.
 * Returns nothing. */
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors){
    cout << "Status\n" << "======\n" << "Nobles \n";

    for(const Noble * n: nobles){
        cout << *n;
    }
    if(nobles.size() == 0) { cout << "NONE\n"; }

    cout << "\nUnemployed Warriors:\n";
    bool found = false;
    for(const Warrior * w: warriors){
        if(w->isEmployable()){
            cout << *w;
            found = true;
        }
    }
    if(!found){ cout << "NONE\n";}
}
