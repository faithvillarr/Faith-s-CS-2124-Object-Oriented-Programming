/* Author: Faith Villarreal, fmv8970
 * Class: Object-Oriented Programming
 * Assignment: hw01: Vectors, strings and functions
 * Purpose: Read a file of warriors and battles. Displays commentary on the warriors' statuses and battles.
 */

#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <fstream>
using namespace std;

struct Warrior{
    int strength;
    string name;
};

//Function Prototypes
void getFile(ifstream&);
void readMedivalTimes(istream&, vector<Warrior>&);
bool warriorPresent(const string&, const vector<Warrior>&);
bool makeWarrior(string&, int, vector<Warrior>&);
void reportStatus(vector<Warrior>&);
Warrior& getWarrior(string, vector<Warrior>&);
void goToBattle(Warrior&, Warrior&);


int main() {
    ifstream myFile;
    getFile(myFile);

    vector<Warrior> allWarriors;
    readMedivalTimes(myFile, allWarriors);
    myFile.close();
}

/* Purpose: Retrieves the main file and assigns it to ref location.
 * Parameter: (ifstream)(ref) Main file
 * Return: N/A
 */
void getFile(ifstream& file_spot){
    file_spot.open("warriors.txt");
    if (!file_spot) {
        cerr << "file failed to open";
        exit(1);
    }
}

/* Purpose: Traverses the main file, recognizing the command type and routes to correct function
 * Parameter: (ifstream)(ref) Ref to main file
 * Parameter: (vector)(Warrior)(ref) Ref to vector containing all warriors defined.
 * Return: N/A
 */
void readMedivalTimes(istream& i_stream, vector<Warrior>& warrior_list){
    string command_type;

    while(i_stream >> command_type){

        if (command_type == "Battle"){
            string warrior1, warrior2;
            i_stream >> warrior1 >> warrior2;
            //checks if the warriors exist
            if(warriorPresent(warrior1, warrior_list) && warriorPresent(warrior2, warrior_list)){
                goToBattle(getWarrior(warrior1, warrior_list),  getWarrior(warrior2, warrior_list));
            }else{
                cerr << "error: one or both warriors do not exist yet!";
            }

        }else if (command_type == "Warrior"){
            string name;
            int strength;
            i_stream >> name >> strength;
            if(!makeWarrior(name, strength, warrior_list)){
                cerr << 'warrior already exists!';
            }

        }else if (command_type == "Status"){
            reportStatus(warrior_list);
        }
    }
}

/* Purpose: Check if the warrior by some name exists in the list of all warrior.
 * Parameter: (const)(string)(ref) Reference to a purposed warrior's name.
 * Parameter: (const)(vector)(Warrior)(ref) Reference to vector of all warriors.
 * Return: (bool) Returns true if warrior is present. Returns false if not.
 */
bool warriorPresent(const string& w_name, const vector<Warrior>& warrior_list){
    //checks entire vector if warrior is present by checking name
    for(Warrior w : warrior_list){
        if(w.name == w_name){
            return true;
        }
    }
    return false;
}

/* Purpose: Create a warrior and adds it to vector of all warriors.
 *          Tells main if it worked or not so error message can be printed.
 * Parameter: (string)(ref) Reference to a new warrior's name.
 * Parameter: (int) Strength to be assigned to new warrior
 * Parameter: (const)(vector)(Warrior)(ref) Reference to vector of all warriors.
 * Return: (bool) Returns true if warrior was added. Returns false if not.
 */
bool makeWarrior(string& name, int strength, vector<Warrior>& warrior_list){
    // passes if warrior doesn't already exist
    if(!warriorPresent(name, warrior_list)){
        Warrior new_Warrior;
        new_Warrior.name = name;
        new_Warrior.strength = strength;
        warrior_list.push_back(new_Warrior);
        return true;
    }
    return false;
}

/* Purpose: Outputs the current # and list of warriors, with thier name and strength
 * Parameter: (vector)(Warrior)(ref) Ref to vector containing all warriors defined.
 * Return: N/A
 */
void reportStatus(vector<Warrior>& warrior_list){
    cout << "There are: " << warrior_list.size() << " warriors" << endl;
    for(Warrior w: warrior_list){
        cout << "Warrior: " << w.name << ", strength: " << w.strength << endl;
    }
}

/* Purpose: Retrieves a warrior from vector using the warrior's name. Assumes they exist.
 * Parameter: (const)(string) String of warrior's name.
 * Parameter: (vector)(Warrior)(ref) Ref to vector containing all warriors defined.
 * Return: (Warrior)(ref) Reference to Warrior in the warrior vector.
 */
Warrior& getWarrior(const string w_name, vector<Warrior>& warrior_list){
    for(int i =0; i < warrior_list.size(); i++){
        if (warrior_list[i].name == w_name){
            return warrior_list[i];
        }
    }
}

/* Purpose: Makes two warriors fight.
 * Parameter: (Warrior)(ref) Reference to first warrior
 * Parameter: (Warrior)(ref) Reference to second warrior
 * Return: N/A
 */
void goToBattle(Warrior& warrior1, Warrior& warrior2) {
    cout << warrior1.name << " battles " << warrior2.name << endl;
    /* Possibilities:
     * (1) everything is perfect. both alive and well. one beats the other.
     * (2) one is dead
     * (3) same health
     * (4) one or both are undefined. checked both routing here.
     */
    // if dead. no changes to strength
    if(warrior1.strength == 0 && warrior2.strength == 0){
        cout << "OH NO! They're both dead! Yuck!" << endl;
    }else if(warrior1.strength == 0) {
        cout << "He's dead, " << warrior2.name << endl;
    }else if(warrior2.strength == 0){
        cout << "He's dead, " << warrior1.name << endl;
    // actually fight. need to change strength of both
    }else if(warrior1.strength > warrior2.strength){
        cout << warrior1.name << " defeats " << warrior2.name << endl;
        warrior1.strength -= warrior2.strength;
        warrior2.strength = 0;
    }else if(warrior2.strength > warrior1.strength){
        cout << warrior2.name << " defeats " << warrior1.name << endl;
        warrior2.strength -= warrior1.strength;
        warrior1.strength = 0;
    }else if(warrior1.strength = warrior2.strength){
        cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name << " die at each other's hands." << endl;
        warrior2.strength = 0;
        warrior1.strength = 0;
    }
}