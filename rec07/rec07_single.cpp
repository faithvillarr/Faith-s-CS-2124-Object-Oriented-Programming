/*
  rec07_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Student;
class Course;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar(){};
    bool addCourse(const string& name);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

// Course Methods
Course :: Course(const string& courseName): name(courseName){};
const string& Course :: getName() const { return name; };
bool Course :: addStudent(Student* new_s) {
    for(const Student * s : students){
        if(s == new_s) return false;
    }
    students.push_back(new_s);
    return true;
};
void Course :: removeStudentsFromCourse(){
    for (size_t i = 0; i < students.size(); ++i) {
        students[i]->removedFromCourse(this);
    }
    students.clear();
};



//Student Methods
Student :: Student(const string& name): name(name){};
const string& Student :: getName() const { return name; };
bool Student :: addCourse(Course* new_c) {
    for(const Course * c : courses){
        if(c == new_c){
            return false;
        }
    }
    courses.push_back(new_c);
    return true;
};

void Student :: removedFromCourse(Course* remove_c){
    bool found = false;
    for(size_t i =0 ; i < courses.size() ; i ++){
        if(courses[i] == remove_c || found){
            courses[i] = courses[i+1];
            found = true;

        }
    }

    if(found)
        courses.pop_back();
};




//Registrar Method

size_t Registrar :: findStudent(const string& name) const{
    for(size_t i = 0; i < students.size(); i++){
        if(students[i]->getName() == name){
            return i;
        }
    }
    return students.size();
};
size_t Registrar :: findCourse(const string& name) const{
    for(size_t i = 0; i < courses.size(); i++){
        if(courses[i]->getName() == name){
            return i;
        }
    }
    return courses.size();
};

bool Registrar :: addCourse(const string& name){
    for(const Course * c : courses){
        if(c->getName() == name){
            return false;
        }
    }
    Course  * new_course = new Course(name);
    courses.push_back(new_course);
    return true;
};
bool Registrar :: addStudent(const string& name){
    for(const Student * s : students){
        if(s->getName() == name){
            return false;
        }
    }
    Student * new_student = new Student(name);
    students.push_back(new_student);
    return true;
};
bool Registrar :: enrollStudentInCourse(const string& studentName, const string& courseName){
    int ind_s = findStudent(studentName);
    int ind_c = findCourse(courseName);
    if(ind_c != courses.size() && ind_s != students.size()) {
        Student *student = students[findStudent(studentName)];
        Course *course = courses[findCourse(courseName)];
        if (course->addStudent(student) && student->addCourse(course))
            return true;
    }
    return false;

};
bool Registrar :: cancelCourse(const string& courseName){
    size_t courseIndex = findCourse(courseName);
    if(courseIndex == courses.size()) return false;
    Course* course = courses[courseIndex];

    // Remove course from registrar's record
    courses[courseIndex] = courses[courses.size() - 1];
    courses.pop_back();

    // Remove course from each student's record
    course->removeStudentsFromCourse();

    delete course;

    return true;
};

void Registrar :: purge(){
    for(Student * s : students){
        delete s;
    }
    students.clear();
    for(Course * c : courses){
        delete c;
    }
    courses.clear();
};

ostream& operator<<(ostream& os, const Registrar& rhs){
    os << "Registrar's Report\nCourses: \n";

    //os << "Size of courses is " << rhs.courses.size() << endl;
    //os << rhs.courses[0]->getName() << "hi";
    for(const Course * c: rhs.courses){
        os << *c << endl;
    }
    os << "Students:\n";
    for(const Student * s : rhs.students){
        os << *s << endl;
    }
    return os;
};
ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.name << ": ";
    if(rhs.courses.size() == 0 )
        os << "No courses";
    else{
        for(const Course * c : rhs.courses){

            os << c->getName() << "  ";
        }
    }
    return os;
};
ostream& operator<<(ostream& os, const Course& rhs){

    os << rhs.getName() << ": ";
    if(rhs.students.size() == 0 )
        os << "No Students";
    else{
        for(const Student * s : rhs.students){
            os << s->getName() << "  ";
        }
    }
    return os;
}
