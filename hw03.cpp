/* Author: Faith Villarreal, fmv8970
 * Class: Object-Oriented Programming
 * Assignment: hw03: Data hiding, encapsulation, delegation, overloading the output operator
 * Purpose: Read a file of warriors and battles. Displays commentary on the warriors' statuses and battles.
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//Warrior Class
class Warrior{
private:
    class Weapon{
    public:
        //Weapon Constructor
        Weapon(const string& name, int strength): wpn_name(name), wpn_strength(strength){}

        //Weapon Methods
        /* Purpose: Get weapon strength.
         * Parameter: N/A
         * Return: (int) Returns weapon strength
         */
        int getWeaponStrength(){
            return wpn_strength;
        }
        /* Purpose: Subtract value from weapon's strength.
         *          If removes too much, makes 0.
         * Parameter: (int) Value to subtract.
         * Return: N/A
         */
        void minusStrength(int change){
            wpn_strength -= change;
            if(wpn_strength < 0){ wpn_strength =0; }
        }

        /* Purpose: Overload output operator for Weapon class
         * Parameter: (ostream)(ref) Designated output stream.
         * Parameter: (const)(Weapon)(ref) Current weapon.
         * Return: (int) Returns weapon strength
         */
        friend ostream& operator<<(ostream& os, const Weapon& wpn){
            os << ", weapon: " << wpn.wpn_name << ", ";
            os << wpn.wpn_strength;
            return os;
        }
    private:
        //Weapon Variables
        string wpn_name;
        int wpn_strength;
    };

    //Warrior Variables
    string wrr_name;
    Weapon wrr_weapon;

public:
    //Warrior Methods
    Warrior(const string& name, const string& wpn_name, int wpn_str) :
    wrr_name(name), wrr_weapon(Weapon(wpn_name, wpn_str)){};

    /* Purpose: Get warrior name.
     * Parameter: N/A
     * Return: (const)(string)(ref) Returns warrior name.
     */
    const string& getWrrName(){
        return wrr_name;
    }
    /* Purpose: Get weapon strength.
     * Parameter: N/A
     * Return: (int) Returns weapon strength.
     */
    int getWpnStrength(){
        return wrr_weapon.getWeaponStrength();
    }

    // Setters
    /* Purpose: Change weapon strength from battle.
     * Parameter: (int) Value to be subtracted from base strength.
     * Return: N/A
     */
    void minusWpnStrength(int change){
        wrr_weapon.minusStrength(change);
    }

    /* Purpose: Overload output operator for Warrior class
     * Parameter: (ostream)(ref) Designated output stream.
     * Parameter: (const)(Weapon)(ref) Current weapon.
     * Return: (int) Returns output stream.
     */
    friend ostream& operator<<(ostream& os, const Warrior& w){
        os << "Warrior: " << w.wrr_name << w.wrr_weapon;
        return os;
    }

};

//Function Prototypes
int getWarrior(vector<Warrior>&, const string&);
void command_switch(ifstream&, vector<Warrior>&);
void status(const vector<Warrior>&);
void battle(const string&, const string&, vector<Warrior>&);
void make_Warrior(ifstream&, vector<Warrior>&);

/*
 * HELPER FUNCTIONS - Help functions in command switch
 */

/* Purpose: Grabs index of warrior if present.
 *          Returns -1 if not. Used to check if present.
 * Parameter: (vector)(Warrior)(ref) Reference to vector of all warriors.
 * Parameter: (const)(string)(ref) Reference to a proposed warrior's name.
 * Return: (int) Returns index if warrior is present.
 *                Returns -1 if not.
 */
int getWarrior(vector<Warrior>& warrior_vec, const string& w_name){
    for(size_t i = 0; i < warrior_vec.size(); i++){
        if(warrior_vec[i].getWrrName() == w_name){
            return i;
        }
    }
    return -1;
}

/*
 * MAIN FUNCTIONS - Is and In command switch
 */

/* Purpose: Traverses the main file, recognizing the
 *          command type and routes to correct function.
 * Parameter: (ifstream)(ref) Ref to main file
 * Parameter: (vector)(Warrior)(ref) Ref to vector containing all warriors defined.
 * Return: N/A
 */
void command_switch(ifstream& is, vector<Warrior>& warrior_list){
    string command_type;
    while(is >> command_type){
        if(command_type == "Warrior"){
            make_Warrior(is, warrior_list);
        }else if(command_type == "Battle"){
            string warrior1, warrior2;
            is >> warrior1 >> warrior2;
            battle(warrior1, warrior2, warrior_list);
        }else{  //"Status"
            status(warrior_list);
        }
    }
}

/* Purpose: Create a warrior and adds it to vector of all warriors.
 *          Tells main if it worked or not so error message can be printed.
 * Parameter: (ifstream)(ref) Ref to main file
 * Parameter: (vector)(Warrior)(ref) Ref to vector of all warriors.
 * Return: N/A
 */
void make_Warrior(ifstream& is, vector<Warrior>& warrior_list){
    string w_name, wpn_name;
    int wpn_str;
    is >> w_name >> wpn_name >> wpn_str;
    Warrior new_warrior = Warrior(w_name, wpn_name, wpn_str);
    if(getWarrior(warrior_list, w_name) < 0){       // checks if warrior exists
        warrior_list.push_back(new_warrior);            // if !exist
    }else
        cerr << w_name << " already exist!" << endl;    // if exists
}

/* Purpose: Makes two warriors fight.
 * Parameter: (const)(string)(ref) First warrior's name
 * Parameter: (const)(string)(ref) Second warrior's name
 * Parameter: (vector)(Warrior)(ref) Ref to vector of all warriors.
 * Return: N/A
 */
void battle(const string& w_name1, const string& w_name2, vector<Warrior>& warrior_list){
    cout << w_name1 << " battles " << w_name2 << endl;

    //If statement checks if they both exist
    if((getWarrior(warrior_list, w_name1) > -1) && (getWarrior(warrior_list, w_name2) > -1)){
        //check warriors exist
        int w_ind1 = getWarrior(warrior_list, w_name1);
        int w_ind2 = getWarrior(warrior_list, w_name2);

        Warrior& warrior1 = warrior_list[w_ind1];
        Warrior& warrior2 = warrior_list[w_ind2];

        //check what type of battle to take place
        //(1) dead
            // (a) both dead
            // (b) one dead
        //(2) actual fight
            // (a) mutual annihilation
            // (b) first wins
            // (c) second wins

            //BOTH DEAD
            if(warrior1.getWpnStrength() == 0 && warrior2.getWpnStrength() == 0){
                cout << "Oh, NO! They're both dead! Yuck!" << endl;

            //FIRST DEAD
            }else if (warrior1.getWpnStrength() == 0 ){
                cout << "He's dead, " << warrior2.getWrrName() << endl;

            //SECOND DEAD
            }else if (warrior2.getWpnStrength() == 0 ){
                cout << "He's dead, " << warrior1.getWrrName() << endl;

            //EQUAL STRENGTH
            }else if (warrior1.getWpnStrength() == warrior2.getWpnStrength()){
                // Text Portion
                cout << "Mutual Annihilation: ";
                cout << warrior1.getWrrName() << " and ";
                cout << warrior2.getWrrName() << " die at each other's hands" << endl;

                // Set to new weapon strength
                warrior1.minusWpnStrength(warrior1.getWpnStrength());
                warrior2.minusWpnStrength(warrior2.getWpnStrength());

            //WARRIOR 2 WINS
            }else if (warrior1.getWpnStrength() < warrior2.getWpnStrength()){
                cout << warrior2.getWrrName() << " defeats ";
                cout << warrior1.getWrrName() << endl;

                //sets new strength
                //once the winner has been adjusted
                warrior2.minusWpnStrength(warrior1.getWpnStrength());
                //then lower is adjusted
                warrior1.minusWpnStrength(warrior1.getWpnStrength());

            }else{ //WARRIOR 1 WINS
                cout << warrior1.getWrrName() << " defeats ";
                cout << warrior2.getWrrName() << endl;

                //sets new strength
                warrior1.minusWpnStrength(warrior2.getWpnStrength());
                warrior2.minusWpnStrength(warrior2.getWpnStrength());

            }
    }else
        cerr << "One or both warrior do not exist!" << endl;
}

/* Purpose: Outputs the current # and list of warriors,
 *          with their names and strength.
 * Parameter: (vector)(Warrior)(ref) Ref to vector of all warriors.
 * Return: N/A
 */
void status(const vector<Warrior>& warrior_vec){
    cout << "There are: " << warrior_vec.size() << " warriors" << endl;
    for(const Warrior& w: warrior_vec){
        cout << w << endl;
    }
}



int main() {
    //gets and checks file
    ifstream file("warriors.txt");
    if(!file){
        cerr << "file not found.";
        exit(1);
    }

    vector<Warrior> all_warriors;
    command_switch(file, all_warriors);
}
