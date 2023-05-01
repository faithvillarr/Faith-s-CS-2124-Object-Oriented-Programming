//
// Created by booke on 3/10/2023.
//

#ifndef REC07_COURSE_H
#define REC07_COURSE_H


#include <iostream>
#include <string>
#include <vector>
#include "student.h"
namespace BrooklynPoly {
    class Student;

    class Course {
        friend std::ostream &operator<<(std::ostream &os, const Course &rhs);

    public:
        // Course methods needed by Registrar
        Course(const std::string &courseName);

        const std::string &getName() const;

        bool addStudent(Student *);

        void removeStudentsFromCourse();

    private:
        std::string name;
        std::vector<Student *> students;
    };
}
#endif //REC07_COURSE_H
