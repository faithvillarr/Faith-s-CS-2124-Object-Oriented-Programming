/* Author: Faith Villarreal
 * Purpose: To learn.
 * Title: rec04.cpp
 */

#include <iostream>
# include <vector>

using namespace std;

struct Complex{
    double real;
    double img;
};



class PlainOldClass {
public:
    PlainOldClass() : x(-72) {}
    int getX() const { return x; }
    void setX( int val )  { x = val; }
private:
    int x;
};

class PlainOldClassV2 {
public:
    PlainOldClassV2() : x(-72) {}
    int getX() const { return x; }
    void setX( int x )  { this->x = x; } // HMMMM???
private:
    int x;
};

class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b)
            : name(name), r(r), g(g), b(b) {}
    void display() const {
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
    }
private:
    string name;      // what we call this colour
    unsigned r, g, b; // red/green/blue values for displaying
};

class SpeakerSystem {
public:
    void vibrateSpeakerCones(unsigned signal) const {

        cout << "Playing: " << signal << "Hz sound..." << endl;
        cout << "Buzz, buzzy, buzzer, bzap!!!\n";
    }
};

class Amplifier {
public:
    void attachSpeakers(const SpeakerSystem& spkrs)
    {
        if (attachedSpeakers)
            cout << "already have speakers attached!\n";
        else {
            *attachedSpeakers = spkrs;
        }
    }

    void detachSpeakers() { // should there be an "error" message if not attached?
        attachedSpeakers = nullptr;
    }

    void playMusic( ) const {
        if (attachedSpeakers)
            attachedSpeakers -> vibrateSpeakerCones(440);
        else
            cout << "No speakers attached\n";
    }
private:
    SpeakerSystem* attachedSpeakers = nullptr;
};

class Person {
public:
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        if(this == &newRoomate){// yourself
            if(this->roomie == nullptr){
                if(newRoomate.roomie == nullptr){
                    roomie = &newRoomate;        // now I have a new roomie
                    newRoomate.roomie = this;    // and now they do too
                }
            }
        }
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie;
    string name;
};

int main() {
    int x;
    x = 10;
    cout << "x = " << x << endl;

    int* p;
    //p = 0x94a99ffc64
    p = &x;
    cout << "p= " << p << endl;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;

    *p = -2763;
    cout << "p points to where " << *p << "is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;

    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout <<"*p now contains " << *p << endl;
    *p = 980;
    cout <<"*p now contains " << *p << endl;
    cout << "y now contains " << y << " is stored\n";

    int* q;
    q =p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "q* contains " << *q << endl;

    double d(33.44);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p = *pD;
    *q = *p;
    //pD = p;
    //p = pD;

    int joe = 24;
    const int sal = 19;
    int*  pI;
    pI = &joe;
    *pI = 234;
    //cannot assign a const int* sal to int* pI
    //pI = &sal;
    *pI = 7623;

    const int* pcI;
    pcI = &joe;
    //cannot change value of a const int*
    //*pcI = 234;
    pcI = &sal; //can change location
    //cannot change value of a const int*
    //*pcI = 7623;

    //have to initialize a const value when initialized.
    //int* const cpI;
    int* const cpI(&joe);
    //cannot initialize const value
    //int* const cpI(&sal);
    //cannot convert int to reference to int
    //  cpI = &joe;
    *cpI = 234;
    //cannot assign new value to const ptr
    //cpI = &sal;
    *cpI = 7623;

    //have to declare and initialize const at same time
    //const int* const cpcI;
    const int* const cpcI(&joe);
    //cannot redeclare const
    //const int* const cpcI(&sal);
    //cannot reassign cpcI, even to same value
    //  cpcI = &joe;
    //cannot reassign value pointed to by cpcI
    // *cpcI = 234;
    //cannot reassign cpcI bc const const
    //  cpcI = &sal;
    //cannot reassign cpcI bc const const
    // *cpcI = 7623;

    //TASK 16
    Complex c = {11.23, 45.67};
    Complex* pC(&c);

    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

    //TASK 17
    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;

    //TASK 19
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;

    cout << "The " << *pDyn
         << " is stored at address " << pDyn
         << " which is in the heap\n";

    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;

    //cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    //cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";


    pDyn = nullptr;

    double* pDouble = nullptr;
    //cout << "Can we dereference nullptr?  " << *pDyn << endl;
    //cout << "Can we dereference nullptr?  " << *pDouble << endl;

    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest; // safe

    short* pShrt = new short(5);
    delete pShrt;
    //delete pShrt;

    long jumper = 12238743;
    //delete jumper;
    long* ptrTolong = &jumper;
    //delete ptrTolong;  // What happens here?
    Complex cmplx;
    //delete cmplx;      // What happens here?

    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        tmpPCmplx = new Complex; // create a new Complex object on the heap
        tmpPCmplx->real = ndx;   // set real and img to be the
        tmpPCmplx->img  = ndx;   // value of the current ndx
        complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
// display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }

// release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx];
    }

// clear the vector
    complV.clear();

    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

// fill vector with Colours from the file
// this could be from an actual file but here we are using the keyboard instead of a file
// (so we don't have to create an actual file)
// Do you remember the keystroke combination to indicate "end of file" at the keyboard?
// somehow the while's test has to fail - from keyboard input

cout << "Input" << endl;
    //while (cin >> inputName >> inputR >> inputG >> inputB) {
    //    colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    //}


// display all the Colours in the vector:
    //for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
    //    colours[ndx]->display();
    //    cout << endl;
    //}

    /*
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete colours[ndx];
    }
     */


// write code to model two people in this world
    Person joeBob("Joe Bob"), billyJane("Billy Jane");

// now model these two becoming roommates
    joeBob.movesInWith(billyJane);

// did this work out?
    //cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    //cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;



}
