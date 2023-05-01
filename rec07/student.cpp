//
// Created by booke on 3/10/2023.
//

#include <iostream>
#include <string>
#include "course.h"
#include "student.h"
using namespace std;
//Student Methods
namespace BrooklynPoly {
    ostream &operator<<(ostream &os, const Student &rhs) {
        os << rhs.name << ": ";
        if (rhs.courses.size() == 0)
            os << "No courses";
        else {
            for (const Course *c: rhs.courses) {

                os << c->getName() << "  ";
            }
        }
        return os;
    };

    Student::Student(const string &name) : name(name) {};

    const string &Student::getName() const { return name; };

    bool Student::addCourse(Course *new_c) {
        for (const Course *c: courses) {
            if (c == new_c) {
                return false;
            }
        }
        courses.push_back(new_c);
        return true;
    };

    void Student::removedFromCourse(Course *remove_c) {
        bool found = false;
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i] == remove_c || found) {
                courses[i] = courses[i + 1];
                found = true;
            }
        }
        if (found)
            courses.pop_back();
    };
}
