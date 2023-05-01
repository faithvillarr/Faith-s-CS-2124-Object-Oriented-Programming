/*
  rec10.cpp
  Author: Faith Villarreal
  Purpose: Simulate a music loan service and orchestra
 */

#include <iostream>
#include <vector>
using namespace std;

//
// Musician class as provided to the students. Requires an Instrument class.
//

class Instrument{
public:
    virtual void makeSound() const= 0;
    friend ostream& operator<<(ostream&, const Instrument&);
    virtual ostream& printInstrument(ostream&) const = 0;
    virtual void play() const = 0;
};

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
        else cout << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};


void Instrument::makeSound() const{
        cout << "To make a sound...";
}
ostream& operator<<(ostream& os, const Instrument& i){
    return i.printInstrument(os);
}


class Brass : public Instrument{
private:
    unsigned mp_size;
public:
    Brass(unsigned mp = 3): mp_size(mp) {};
    void makeSound() const{
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size "<< mp_size << endl;
    }
    ostream& printInstrument(ostream &os) const{
        os << mp_size << endl;
        return os;
    }
};
class Trumpet : public Brass{
public:
    Trumpet(unsigned mp) : Brass(mp){};
    void makeSound() const{
        Brass::makeSound();
    }
    ostream & printInstrument(ostream &os) const{
        os << "Trumpet: ";
        Brass::printInstrument(os);
        return os;
    }
    void play() const{
        cout << "Toot";
    }
};
class Trombone : public Brass{
public:
    Trombone(unsigned mp) : Brass(mp){};
    void makeSound() const{
        Brass::makeSound();
    }
    ostream & printInstrument(ostream &os) const{
        os << "Trombone: ";
        Brass::printInstrument(os);
        return os;
    }
    void play() const{
        cout << "Blat";
    }
};

class String : public Instrument{
private:
    unsigned string_pitch;
public:
    String(unsigned sp) : string_pitch(sp){};
    void makeSound() const{
        Instrument::makeSound();
        cout << " bow a string with pitch " << string_pitch << endl;
    }
    ostream & printInstrument(ostream &os) const{
        os << string_pitch << endl;
        return os;
    }
};
class Violin : public String{
public:
    Violin(unsigned sp) : String(sp){};
    void makeSound() const{
        String::makeSound();
    }
    ostream & printInstrument(ostream &os) const{
        os << "Violin: ";
        String::printInstrument(os);
        return os;
    }
    void play() const{
        cout << "Screech";
    }
};
class Cello : public String{
public:
    Cello(unsigned sp) : String(sp){};
    void makeSound() const{
        String::makeSound();
    }
    ostream & printInstrument(ostream &os) const{
        os << "Cello: ";
        String::printInstrument(os);
        return os;
    }
    void play() const{
        cout << "Sqwuak";
    }
};

class Percussion : public Instrument{
public:
    Percussion(){};
    void makeSound() const{
        cout << "To make a sound... hit me!\n";
    }
    ostream & printInstrument(ostream &os) const{
       os << endl;
       return os;
    }
};
class Drum : public Percussion{
public:
    Drum(){};
    void makeSound() const{
        Percussion::makeSound();
    }
    ostream & printInstrument(ostream &os) const{
        os << "Drum";
        Percussion::printInstrument(os);
    }
    void play() const{
        cout << "Boom";
    }
};
class Cymbal : public Percussion{
public:
    Cymbal(){};
    void makeSound() const{
        Percussion::makeSound();
    }
    ostream & printInstrument(ostream &os) const{
        os << "Cymbal";
        Percussion::printInstrument(os);
    }
    void play() const{
        cout << "Crash";
    }
};

class MILL{
private:
    vector<Instrument*> library;
    int num_Inst = 0;
public:
    void receiveInstr(Instrument& new_Inst){
//        bool added = false;
//        if(num_Inst != library.size()){
        new_Inst.makeSound();
        num_Inst += 1;

        for (size_t i = 0; i < library.size(); ++i) {
            if(library[i] == nullptr){
                library[i] = &new_Inst;

                return;
            }
        }
//        }else{
        library.push_back(&new_Inst);
//        }

    };
    void dailyTestPlay(){
        for(Instrument *i: library){
            if(i != nullptr)
                i->makeSound();
        }
    };
    Instrument* loanOut(){
        if(num_Inst != 0){
            for (size_t i = 0; i < library.size(); ++i) {
                if(library[i] != nullptr){
                    Instrument* res = library[i];
                    library[i] = nullptr;
                    num_Inst -= 1;
                    return res;
                }
            }
        }else{
            cout << "There are no instruments to loan.\n";
        }
    }

    friend ostream& operator<<(ostream& os, const MILL& mill){
        os << "The MILL has the following instruments: ";
        if(mill.num_Inst ==0){
            os << "None\n";
            return os;
        }
        cout << endl;
        for(Instrument* i : mill.library){
            if(i!= nullptr)
                cout << *i;
            //else cout << "[EMPTY]\n";
        }
        return os;
    }
};

class Orch{
private:
    vector<Musician*> players;
public:
    void play(){
        for(Musician* p : players){
            p->play();
        }
        cout << endl;
    }
    bool addPlayer(Musician& m){
        for(Musician * p : players){
            if (p == &m)
                return false;
        }
        players.push_back(&m);
        return true;
    }
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
         << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()1" << endl;
    mill.dailyTestPlay();
    cout << endl;

    groucho.testPlay();
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()2" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());


    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;


    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";

    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;

}

