//
// Created by booke on 3/24/2023.
//

#ifndef REC08_RATIONAL_H
#define REC08_RATIONAL_H

using namespace std;



class Rational{
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
    Rational operator++(int dummy);



    explicit operator bool() const;

private:
    int num, den;
    Rational& normalize();

};


#endif //REC08_RATIONAL_H
