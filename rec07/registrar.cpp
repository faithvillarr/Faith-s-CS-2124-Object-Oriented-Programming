//
// Created by booke on 3/10/2023.
//

#include <iostream>
#include <string>
#include <vector>
#include "registrar.h"
#include "student.h"
#include "course.h"
using namespace std;
namespace BrooklynPoly {
    Registrar ::Registrar() {};

    size_t Registrar::findStudent(const string &name) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i]->getName() == name) {
                return i;
            }
        }
        return students.size();
    };

    size_t Registrar::findCourse(const string &name) const {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i]->getName() == name) {
                return i;
            }
        }
        return courses.size();
    };

    bool Registrar::addCourse(const string &name) {
        for (const Course *c: courses) {
            if (c->getName() == name) {
                return false;
            }
        }
        Course *new_course = new Course(name);
        courses.push_back(new_course);
        return true;
    };

    bool Registrar::addStudent(const string &name) {
        for (const Student *s: students) {
            if (s->getName() == name) {
                return false;
            }
        }
        Student *new_student = new Student(name);
        students.push_back(new_student);
        return true;
    };

    bool Registrar::enrollStudentInCourse(const string &studentName, const string &courseName) {
        int ind_s = findStudent(studentName);
        int ind_c = findCourse(courseName);
        if (ind_c != courses.size() && ind_s != students.size()) {
            Student *student = students[findStudent(studentName)];
            Course *course = courses[findCourse(courseName)];
            if (course->addStudent(student) && student->addCourse(course))
                return true;
        }
        return false;

    };

    bool Registrar::cancelCourse(const string &courseName) {
        size_t courseIndex = findCourse(courseName);
        if (courseIndex == courses.size()) return false;
        Course *course = courses[courseIndex];

        // Remove course from registrar's record
        courses[courseIndex] = courses[courses.size() - 1];
        courses.pop_back();

        // Remove course from each student's record
        course->removeStudentsFromCourse();

        delete course;

        return true;
    };

    void Registrar::purge() {
        for (Student *s: students) {
            delete s;
        }
        students.clear();
        for (Course *c: courses) {
            delete c;
        }
        courses.clear();
    };

    ostream &operator<<(ostream &os, const Registrar &rhs) {
        os << "Registrar's Report\nCourses: \n";

        //os << "Size of courses is " << rhs.courses.size() << endl;
        //os << rhs.courses[0]->getName() << "hi";
        for (const Course *c: rhs.courses) {
            os << *c << endl;
        }
        os << "Students:\n";
        for (const Student *s: rhs.students) {
            os << *s << endl;
        }
        return os;
    };
}
