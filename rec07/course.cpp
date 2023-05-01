//
// Created by booke on 3/10/2023.
//
#include <iostream>
#include <string>
#include "student.h"
#include "course.h"
using namespace std;

namespace BrooklynPoly {
    Course::Course(const string &courseName) : name(courseName) {};

    const string &Course::getName() const { return name; };

    bool Course::addStudent(Student *new_s) {
        for (const Student *s: students) {
            if (s == new_s) return false;
        }
        students.push_back(new_s);
        return true;
    };

    void Course::removeStudentsFromCourse() {
        for (size_t i = 0; i < students.size(); ++i) {
            students[i]->removedFromCourse(this);
        }
        students.clear();
    };

    ostream &operator<<(ostream &os, const Course &rhs) {

        os << rhs.getName() << ": ";
        if (rhs.students.size() == 0)
            os << "No Students";
        else {
            for (const Student *s: rhs.students) {
                os << s->getName() << "  ";
            }
        }
        return os;
    }
}