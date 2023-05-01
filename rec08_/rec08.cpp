#include <iostream>
#include "gcd.cpp"
//#include "Rational.h"

using namespace std;
/*
        << and >> (i.e., input and output).
            Rational numbers are read and written as an integer, followed by a slash, followed by an integer.
            Either (or both) of the numerator and the denominator may be input as negative integers. The following are all possible inputs: 1/2, -1/-2, -1/2 and 1/-2.
            It's a design decision as to when to "normalize" a rational number. Should it always be normalized? Or is that only a choice to be made when we dispaly it?
                We will maintain the numbers in their normalized form at all times.
                Thus when they are first created, they must be stored as normalized and any operation that might change a number must also normalize it.
                What does "normalize" mean? The numerator and denominator will be in "lowest terms" and only the numerator may be negative. For example, if we were given as input 4/-8, we would store and display it as -1/2. Similarly -8/-6 would turn into 4/3.
        += Implement as a member function, aka method.
        + Implement (i.e., addition) as a non-member function that calls the += operator. Do not make + a friend. (There is no reason to.)
*/
/*
        == and <: Implement as non-member and as friend.
        ++ and --
            Both pre- and post-.
            Member for ++
            Non-member, non-friend for --
                Yes, normally we would do this as a member.
                We are just asking you to implement the decrement operator as a non-member for you to see how it would look different.
        !=, <=, > and >= Implement as non-member and non-friend.
    Make it possible to write if (r) {}, where r is a Rational number. The test will evaluate to false if the numerator is zero and true otherwise.
    We provide two files
        testRational.cpp to test your class. Can you think of additional tests to write?
        gcd.cpp: to compute the greatest common divisor of two non-negative integers, that should be useful for writing the normalize function. If you're clever, try to write this function yourself before looking at ours.
    Put all method and function implementations after main.
    Your class definition should only have prototypes and the member variable definitions.

Arithmetic Reminder
    Adding fractions:
    == and <
        For equality, since we are maintaining everything normalized,
        then the only thing is to check that the numerators and
        denominators are the same.
        If the Rationals were not kept normalized, then we would use
        “cross multiplying”
                a/b=c/d  if and only if a*d = b*c
        For less than, the cross multiplying is similar:
            a/b < c/d if and only if a*d < b*c  if b and d are positive.
            So, keep the negatives out of the denominators!

 Operators to Overload:
 <<, >>, +=, +, =, <, ++a, a++, --a, a--, !=, <=, >, >=, bool()
 To-Do:
 +, =, <
 */

class Rational{
    ~Rational(){ }
    Rational(const Rational rhs);
    friend ostream& operator<<(ostream&, const Rational&);
    friend istream& operator>>(istream&, Rational &);
    friend bool operator==(const Rational&, const Rational&);
    //= and <: Implement as non-member and as friend.
    friend bool operator<(const Rational&, const Rational&);

public:
    Rational(int num = 0, int den = 1) : num(num), den(den){ this->normalize(); };
    //+= Implement as a member function, aka method.
    Rational& operator+=(const Rational&);
    Rational& operator=(const Rational&);

    Rational& operator++();
    Rational& operator++(int dummy);

    explicit operator bool() const;

private:
    int num, den;
    Rational& normalize();

};

//non-member non-friends
//!=, <=, > and >= Implement as non-member and non-friend.
bool operator!=(const Rational& lhs, const Rational& rhs){
    return !(lhs==rhs);
}
bool operator<=(const Rational& lhs, const Rational& rhs){
    return lhs < rhs || lhs == rhs;
}
bool operator>(const Rational& lhs, const Rational& rhs){
    return !(rhs < lhs) && rhs !=lhs;
}
bool operator >=(const Rational& rhs, const Rational& lhs){
    return !(rhs<lhs);
}

Rational& operator--(Rational& rat){
    rat += -1;
    return rat;
}
Rational operator--(Rational& rat, int dummy){
    Rational res = rat;
    rat += -1;
    return res;
}

//+ Implement (i.e., addition) as a non-member function that calls the += operator. Do not make + a friend. (There is no reason to.)
Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational temp = lhs;
    temp += rhs;
    return temp;
}


//friends
ostream& operator<<(ostream& os, const Rational& rat){
    os << rat.num << "/" << rat.den;
    return os;
}
istream& operator>>(istream& is, Rational& rat){
    char slash;
    is >> rat.num >> slash >> rat.den;
    rat.normalize();
    return is;
}
bool operator==(const Rational& r1, const Rational& r2){
    return r1.num * r2.den == r2.num * r1.den;
}
bool operator<(const Rational& rhs, const Rational& lhs) {
    return (rhs.num * lhs.den) < (lhs.num * rhs.den);
}

//member functions
Rational& Rational::normalize() {
    //simplifying
    int x = greatestCommonDivisor(num, den);
    while(x != 1){
        num /= x;
        den /= x;
        x = greatestCommonDivisor(num, den);
        //if not both pos or both neg
    }
    //fixing pos/neg
    if (den < 0){
        num = -1 * num;
        cout << num;
        den = -1 * den;
    }
    return *this;
}

//+= Implement as a member function, aka method.
Rational& Rational::operator+=(const Rational& rat){
    num = num * rat.den + rat.num * den;
    den *= rat.den;
    normalize();
    return *this;
}
Rational& Rational::operator=(const Rational& rs){
    num = rs.num;
    den = rs.den;
    return *this;
}
Rational::operator bool() const { return this->num; }

Rational& Rational::operator++() { //pre
    num += den;
    normalize();
    return *this;
}
Rational& Rational::operator++(int dummy) { //post
    Rational res(num, den);
    num += den;
    normalize();
    return res;
}




