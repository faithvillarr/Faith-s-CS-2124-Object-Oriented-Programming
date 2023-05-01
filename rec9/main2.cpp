//
// Created by booke on 3/31/2023.
//
# include <iostream>
using namespace std;

class A {
public:
    void x(){
        this->y();
        this->z();
    }
    void y(){
        cout << "A::y()" << endl;
    }
    virtual void z(){
        cout << "A::z()" << endl;
    }
};

class B: public A{
public:
    void y(){
        cout << "B::y()"
    }
};