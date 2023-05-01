/* Author: Faith Villarreal, fmv8970
 * Class: Object-Oriented Programming
 * Assignment: hw04: Classes, pointers and association
 * Purpose: Implement the Noble and Warrior class to simulate battles.
 * Based on the output code.
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//function prototypes

// Your Noble and Warrior classes should go here.
class Warrior{
private:
    double strength;
    const string name;
    //to tell if you can employ a warrior
    bool employed = false;

    /* Purpose: To print information about the warrior
     * Parameter: (ostream)(ref) Ostream to send output to.
     * Parameter: (const)(Warrior)(ptr) Warrior to pull info from
     * Return: (ostream)(ref) Ostream to send output to.
     */
    friend ostream& operator<<(ostream& os, const Warrior*& warrior){
        os << "\n\t" << warrior->name << ": " << warrior->strength;
        return os;
    }

public:

    //Constructor
    Warrior(const string& n, double s) : name(n), strength(s){}

    /* Purpose: To get warrior's name
     * Parameter:N/A
     * Return: (const)(string) Returns warrior's name. Doesn't change.
     */
    const string get_W_Name(){
        return name;
    }
    /* Purpose: To get current warrior's strength
     * Parameter: N/A
     * Return: (const)(double) Returns warrior's strength
     */
    const double getWrStrength(){
        return strength;
    }

    /* Purpose: To see if the warrior is already employed
     * Parameter: N/A
     * Return: (const)(bool) Returns true if Warrior can be employed.
     *                      Returns false if not.
     */
    const bool isEmployable(){
        return employed;
    }
    /* Purpose: To see if the warrior is already employed
     * Parameter: N/A
     * Return: (const) N/A
     */
    const void changeEmployability(){
        employed = !employed;
    }

    /* Purpose: To change warrior's strength after battle.
     * Parameter: (const)(double) Ratio to multiply the warrior's strength by.
     * Return: (const) N/A
     */
    const void multiplyWrStr(const double change){
        this->strength *= change;
    }
};

class Noble{
private:
    //to contain all their warriors in order
    vector<Warrior*> army;
    const string name;
    bool isDead = false;

    /* Purpose: To print information about the warrior
     *  Parameter: (ostream)(ref) Ostream to send output to.
     * Parameter: (const)(Warrior)(ref) Noble to pull info from
     * Return: (ostream)(ref) Ostream to send output to.
     */
    friend ostream& operator<<(ostream& os, const Noble& noble){
        //write what to print here
        os << noble.name << " has an army of " << noble.army.size();
        for (const Warrior* w: noble.army){
            os << w;
        }
        return os;
    }

public:
    //Constructor
    Noble(const string n):name(n){};

    /* Purpose: Get total strength of all warriors in the army
     * Parameter: N/A
     * Return: (const)(double) Returns total strength
     *         of each solider added together.
     */
    const double getArmyStrength(){
        double res = 0;
        for(Warrior *w: army){
            res += w->getWrStrength();
        }
        return res;
    }

    /* Purpose: To hire a warrior. Add them to the nobles army vector.
     *          And prevent from being hired away.
     * Parameter: (Warrior)(ref) Warrior to be hired
     * Return: (const) (bool) True if they were successfully hired.
     *                False if not.
     */
    const bool hire(Warrior& warrior){
        //if warrior isn't employed
        if(!warrior.isEmployable() && !this->isDead){
            army.push_back(&warrior);
            warrior.changeEmployability();
            return true;
        }
        //if already employed gets here
        cout << name << " failed to hire " << warrior.get_W_Name() << endl;
        return false;
    }

    /* Purpose: To fire a specific warrior if they are employed
     *          by this noble. Allow them to be hired by another noble.
     * Parameter: (Warrior) (ref) Warrior to be fired.
     * Return: (const)(bool) True if the warrior was succesfully fired.
     *                False if not.
     */
    const bool fire(Warrior& warrior){
        if(!this->isDead) {
            for (size_t i = 0; i < army.size() - 1; i++) {
                if (army[i] == &warrior) {
                    army[i] = army[i + 1];
                    army[i + 1] = &warrior;
                }
            }
            if (army[army.size() - 1] == &warrior) {
                army.pop_back();
                cout << warrior.get_W_Name() << ", you dont work for";
                cout <<  " me any more! -- " << this->name << endl;
                warrior.changeEmployability();
                return true;
            }
        }
        cout << name << " failed to fire " << warrior.get_W_Name() << endl;
        return false;
    }

    /* Purpose: To deplete the strength of every soldier in the army to zero.
     *          Mark the Noble as dead.
     *          Supports the battle function.
     * Parameter: N/A
     * Return: (const) N/A
     */
    const void die(){
        for (Warrior*& w : army){
            w->multiplyWrStr(0);
        }
        this->isDead = true;
    }

    /* Purpose: To have two nobles battle.
     *          Determining who wins or if no one wins.
     * Parameter: (Noble)(ref) The enemy noble to be considered.
     * Return: (const) N/A
     */
    const void battle(Noble& enemy){
        cout << name << " battles " << enemy.name << endl;

        //if someone is dead
        if(this->isDead && enemy.isDead){//both dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }else if(this->isDead) {
            cout << "He's dead, " << enemy.name << endl;
        }else if(enemy.isDead){
            cout << "He's dead, " << name << endl;

        //this noble wins
        }else if(this->getArmyStrength() > enemy.getArmyStrength()){
            //first augment winner's army
            double change = enemy.getArmyStrength() / this->getArmyStrength();
            for (Warrior*& w : army){
                w->multiplyWrStr(1 - change);
            }

            //kill loser
            enemy.die();

            cout << this->name << " defeats " << enemy.name << endl;

        //You win
        }else if(enemy.getArmyStrength() > this->getArmyStrength()){
            double change = this->getArmyStrength() / enemy.getArmyStrength();
            for (Warrior*& w : enemy.army){
                w->multiplyWrStr(1 - change);
            }

            //kill loser
            this->die();

            cout << enemy.name << " defeats " << this->name << endl;

        }else{//Mutual annihilation
            this->die();
            enemy.die();

            cout << "Mutual Annihilation: " << this->name << " and ";
            cout << enemy.name << " die at each other's hands" << endl;
        }
    }
};





//test code
int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);

    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

}

