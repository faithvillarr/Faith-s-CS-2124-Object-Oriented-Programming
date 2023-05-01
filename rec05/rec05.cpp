/*
  rec05-start.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section{
private:
    class TimeSlot {
    private:
        const string weekday;
        //const string name;
        int time;

        friend ostream &operator<<(ostream &os, const TimeSlot& timeSlot) {
            os << "[Day: " << timeSlot.weekday << " ,";
            os << "Start time: ";
            if (timeSlot.time > 12) {
                os << timeSlot.time - 12 << "pm]";
            } else if (timeSlot.time == 12) {
                os << timeSlot.time << "pm";
            } else
                os << timeSlot.time << "am";
            return os;
        }
    public:
        TimeSlot(const string& weekday, const int time):weekday(weekday), time(time){};
    };

    class StudentRecord{
    private:
        vector<int> gradeRecord;
        const string name;

        //Name: John, Grades: -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
        friend ostream& operator<<(ostream& os, const StudentRecord* studentRecord){
            os << "Name: " << studentRecord->name << ", Grades: ";
            for(int i : studentRecord->gradeRecord){
                os << i << " ";
            }
            return os;
        }
    public:
        StudentRecord(const string& name):name(name), gradeRecord(14, -1){};
        const string& getName() const {
            return name;
        }
        void changeGrade(int grade, size_t ind){
            gradeRecord[ind-1] = grade;
        }

    };


    const string name;
    const TimeSlot timeSlot;
    vector<StudentRecord*> allStudents;

    //Section: A2, Time slot: [Day: Tuesday, Start time: 4pm], Students: None
    friend ostream& operator<<(ostream& os, const Section& labSection){
        os << "Section: " << labSection.name << ", Time slot: " << labSection.timeSlot;
        os << ", Students: " << endl;
        for (const StudentRecord* s : labSection.allStudents){
            cout << s << endl;
        }

        return os;
    }
public:
    //Lab Section Constructor
    Section(const string& name, const string& weekday, int time): name(name), timeSlot(weekday, time){};

    const void addStudent(const string& name){
        StudentRecord* newStud = new StudentRecord(name);
        allStudents.push_back(newStud);
    }

    void addGrade(const string& s_name, int grade, size_t ind){

        for(size_t i = 0; i < allStudents.size(); i++){
            if(allStudents[i]->getName() == s_name){
                allStudents[i]->changeGrade(grade, ind);
            }
        }
    }
    ~Section(){

        reset();
    }
    void reset(){
        cout << "Section " << this->name << " is being deleted." << endl;
        for(StudentRecord* sr : allStudents){
            cout << "Deleting " << sr->getName() << endl;
            delete sr;
        }
        this->allStudents.clear();

    }


    Section(const Section& anotherSection): name(anotherSection.name), timeSlot(anotherSection.timeSlot){
        for(StudentRecord* sr : anotherSection.allStudents){
            this->allStudents.push_back(new StudentRecord(*sr));
        }
    }
};

class LabWorker{
private:
    const string name;
    Section* section = nullptr;
    /*
     * Moe does not have a section
    Test 4: Adding a section to a lab worker.
    Moe has
     */
    friend ostream& operator<<(ostream& os, const LabWorker& labWorker){
        if (labWorker.section == nullptr){
            os << labWorker.name << " does not have a section." << endl;
        }else{
            os << labWorker.name << " has " << *labWorker.section << endl;
        }
    }
public:
    LabWorker(const string& name): name(name){};

    void addSection(Section& sec){
        this->section = &sec;
    }

    // moe.addGrade("John", 17, 1);
    void addGrade(const string& s_name, int grade, size_t ind){
        section->addGrade(s_name, grade, ind);
    }
};


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
     Section secA2("A2", "Tuesday", 16);
     cout << secA2 << endl;


     /*vector<int>* temp = new vector<int>(12,-1);
     for (int i : *temp){
         cout << i << " ";
     }*/
    cout << "\nTest 2: Adding students to a section\n";
     secA2.addStudent("John");
     secA2.addStudent("George");
     secA2.addStudent("Paul");
     secA2.addStudent("Ringo");
     cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
