//
// Created by booke on 3/10/2023.
//

#ifndef REC07_REGISTRAR_H
#define REC07_REGISTRAR_H


#include <iostream>
#include <string>
#include <vector>
#include "course.h"
#include "student.h"

namespace BrooklynPoly {


    class Registrar {
        friend std::ostream &operator<<(std::ostream &os, const Registrar &rhs);

    public:
        Registrar();

        bool addCourse(const std::string &);

        bool addStudent(const std::string &);

        bool enrollStudentInCourse(const std::string &studentName,
                                   const std::string &courseName);

        bool cancelCourse(const std::string &courseName);

        void purge();

    private:
        size_t findStudent(const std::string &) const;

        size_t findCourse(const std::string &) const;

        std::vector<Course *> courses;
        std::vector<Student *> students;
    };
}
#endif //REC07_REGISTRAR_H
