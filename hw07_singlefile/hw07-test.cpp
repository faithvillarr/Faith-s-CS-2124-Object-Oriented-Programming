/*
  CS2124 hw07-test.cpp
  -jbs
 */

#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <iostream>

using namespace std;


class Noble{
private:
    string name;
    bool alive = true;
public:
    //constructor
    Noble(string n) : name(n){};

    //helper method i made
    bool isAlive() const { return alive; }

    //bool removeSoldier(Protector *);
    const string& getName() const {return name;}

    //method i had to make
    virtual void battle(Noble & enemy){
        //to be called, they both have to exist
        double my_strength = this->getStrength();
        double enemy_strength = enemy.getStrength();
        //are they dead?
        if(this->alive && enemy.alive){
            //continue the battle
            //will change variables now
            battlecry();
            enemy.battlecry();
            if(my_strength == enemy_strength){
                //tie
                this->die();
                enemy.die();
                cout << "Mutual annihalation!\n";
            }else if(my_strength > enemy_strength){
                //i win
                enemy.die();
                cout << name << " defeat " << enemy.name << endl;
            }else {
                //they win
                die();
                cout << enemy.name << " defeat " << name << endl;
            }
        }else if(!(this->alive || enemy.alive)){
            cout << "Oh, NO!  They're both dead!  Yuck!\n";
        }else if (alive){
            cout << name << " is dead\n!";
        }else
            cout << enemy.name << "is dead!\n";
    }

    friend ostream& operator<<(ostream&, const Noble&);

    virtual const ostream & print(ostream&) const;
    virtual void die(){ alive = false; }
    virtual double getStrength() = 0;
    virtual void battlecry() = 0;
};

ostream& operator<<(ostream& os, const Noble& n){
    /*
     * Sam has an army of size: 1
	Samantha has strength 200
     */
    os << n.name;
    n.print(os);
    return os;
}

class Protector;
class Lord : public Noble{
private:
    vector<Protector*> army;
public:
    Lord(string n) : Noble(n){};
    double getStrength();
    void battlecry();
    void die();

    void hires(Protector &);
    void fires(Protector &);

    void battle(Noble& enemy){ Noble::battle(enemy); };
    const ostream & print(ostream&) const;
    bool removeWarr(Protector& p){
        for (size_t i = 0; i < army.size()-1; ++i) {
            if(army[i] == &p){
                army[i] = army[i+1];
                army[i+1] = &p;
            }
        }
        if(army[-1] == &p){
            army.pop_back();
            return true;
        }
        return false;
    }

};

class Lord;
class Protector{
private:
    string name;
    int strength;
    Lord * myNoble = nullptr;

public:
    Protector(string n, int s) : name(n), strength(s){};
    int getStrength(){ return strength; }
    void setStrength(int newStrength) { strength = newStrength; }
    virtual ostream& battlecry(ostream &) = 0; //all defined ;)

    Lord * getNoble() {return myNoble; }
    void setNoble(Lord * n){ myNoble = n;}

    const string& getName() const { return name; }

    bool isHired(){ return myNoble != nullptr; }

    friend ostream& operator<<(ostream& os, const Protector& p){
        os << p.name << " has strength " << p.strength << endl;
        return os;
    }
    void runaway(){
        if(myNoble == nullptr && strength > 0){
            myNoble->removeWarr(*this);
        }else if(strength ==0){
            cout << name << "you're dead. You cant runaway."<<endl;
        }else
            cout << name << ", you're unemployed. Calm down."<<endl;
    }

};
class Wizard : public Protector{
public:
    Wizard(string n, double s): Protector(n,s) {};
    ostream& battlecry(ostream& os){
        os << "POOF\n";
        return os;
    }
};
class Warrior : public Protector{
public:
    Warrior(string n, double s) : Protector(n, s){};
    virtual ostream& battlecry(ostream& os){
        os << Protector::getName() << "says: Take that in the name "
           << "of my lord, " << Protector::getNoble()->getName() << endl;
        return os;
    }

};
class Archer : public Warrior{
public:
    Archer(string n, double s): Warrior(n,s) {};
    ostream& battlecry(ostream& os){
        os << "TWANG! ";
        Warrior::battlecry(os);
        return os;
    }
};
class Swordsman : public Warrior{
public:
    Swordsman(string n, double s): Warrior(n,s) {};
    ostream& battlecry(ostream& os){
        os << "CLANG! ";
        Warrior::battlecry(os);
        return os;
    }
};


const ostream& Lord::print(ostream& os) const{
    os << " has an army of size: " << army.size()<<endl;
    for(const Protector * p : army){
        os << p;
    }
    return os;
}

double Lord::getStrength() {
    double res = 0.0;
    for (Protector * p : army){
        res += p->getStrength();
    }
    return res;
}
void Lord::die(){
    for(Protector* p : army){
        p->setStrength(0);
    }
    Noble::die();
}
void Lord::battlecry(){
    for(Protector* p : army){
        p->battlecry(cout);
    }
}
void Lord::fires(Protector & protector){
    if(protector.getNoble() == this && isAlive()){
        //proceed to fire
        removeWarr(protector);
        protector.setNoble(nullptr);
    }else if(protector.getNoble() != this){
        cout << "Ummm " << Noble::getName()
             << " you can't fire someone you haven't hired.";
    }else{
        cout << Noble::getName() << ", you're dead. You cannot fire bitches no more.";
    }
}
void Lord::hires(Protector & protector){
    //if they aint dead or already hired
    if(!protector.isHired() && protector.getStrength() != 0){
        //proceed with hiring
        army.push_back(&protector);
        protector.setNoble(this);
    }else if (protector.getStrength() == 0){
        cout << "That protector is dead dude";
    }
}

class PersonWithStrengthToFight : public Noble{
private:
    double strength;
public:
    PersonWithStrengthToFight(string n, double s) : Noble(n), strength(s){};
    double getStrength(){ return strength; }
    void die(){
        strength = 0;
        Noble::die();
    }
    void battlecry(){ cout << "UGH!\n"; }
    void battle(Noble & enemy) {
        Noble::battle(enemy);
    }
    const ostream& print(ostream& os) const {
        os << " has strength: " << strength << endl;
        return os;
    }
};


//
// Test Code
//
int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "==========\n";
} // main

