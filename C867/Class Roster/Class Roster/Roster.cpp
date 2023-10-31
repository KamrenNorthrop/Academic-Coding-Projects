#include <iostream>
#include "Degree.h"
#include "Roster.h"
#include "Student.h"
void Roster::add(std::string studentID, std::string firstName, std::string lastName, std::string emailAddress, int age, int days1, int days2, int days3, DegreeProgram program) {
    //array to hold all 3 days
    int days[3] = { days1, days2, days3 };

    //create new student object, increment
    classRosterArray[classRosterArrayPos] = new Student(studentID, firstName, lastName, emailAddress, age, days, program);
    classRosterArrayPos++;
}
void Roster::remove(std::string studentID) {
    for (int i = 0; i < 5; i++) {
        if (removed[i] == studentID) {  //has ID been removed previously?
            std::cout << "Removing " << studentID << " again" << std::endl;
            std::cout << std::endl;

            if (removed[i] == studentID && classRosterArray[i] == nullptr) { //if it's been removed before and doesn't exist again
                std::cout << "The student with the ID: " << studentID << " was not found." << std::endl;
                std::cout << "DONE." << std::endl;
            }
        }
        else if (classRosterArray[i] == nullptr) { //does ID exist in table?
            std::cout << "The student with the ID: " << studentID << " was not found." << std::endl;
            std::cout << "DONE." << std::endl;
            break;
        }
        else if (classRosterArray[i]->Student::GetStudentID() == studentID) { //remove ID if exists.
            std::cout << "Removing " << studentID << std::endl;
            removed[i] = classRosterArray[i]->GetStudentID();
            classRosterArray[i] = nullptr;
        }
    }
}
void Roster::printAll() {
    for (int i = 0; i < 5; i++) {
        if (classRosterArray[i] != nullptr) {
            classRosterArray[i]->Student::Print();
        }
    }
}
void Roster::printAverageDaysInCourse(std::string studentID) {
    int averageDays;
    int* daysInClass;

    for (int i = 0; i < 5; i++) { //loop through students
        if (studentID == classRosterArray[i]->GetStudentID()) { //find ID
            daysInClass = classRosterArray[i]->GetDaysToComplete(); //Point to days array 
            averageDays = (daysInClass[0] + daysInClass[1] + daysInClass[2]) / 3; //calc average

            std::cout << "Student ID: " << studentID << ", average days in course is: " << averageDays << std::endl;
        }
    }
}
void Roster::printInvalidEmails() {
    int foundAt = -1;
    int foundPeriod = -1;
    int foundSpace = -1;
    std::string email;

    //valid emails contains an @ and a . but no spaces.
    //can change -1 with index place of found @ . or ' ' if occurs.
    std::cout << std::endl;

    for (int i = 0; i < 5; i++) {
        email = classRosterArray[i]->Student::GetStudentEmail();

        if (email.find('@')) {
            foundAt = email.find('@');
        }

        if (email.find('.')) {
            foundPeriod = email.find('.');
        }

        if (email.find(' ')) {
            foundSpace = email.find(' ');
        }

        if (foundAt != -1 && foundPeriod != -1 && foundSpace == -1) { //found an @ and a . but no space
            continue;
        }
        else {
            std::cout << email << " - is invalid." << std::endl;
        }
    }
}

std::string degreeToString(DegreeProgram degree) { //using to easily convert DegreeProgram to a string.
    switch (degree) {
    case DegreeProgram::SECURITY:
        return "SECURITY";
    case DegreeProgram::NETWORK:
        return "NETWORK";
    case DegreeProgram::SOFTWARE:
        return "SOFTWARE";
    default:
        std::cout << "Program not found" << std::endl;
    }
}
void Roster::printByDegreeProgram(DegreeProgram degree) {
    std::string program = degreeToString(degree); //convert degree to a string
    std::cout << "Showing students in degree program: " << program << std::endl;
    std::cout << std::endl;

    //printing students in degree program that was passed in
    for (int i = 0; i < 5; i++) {
        if (degree == classRosterArray[i]->Student::GetDegree()) {
            classRosterArray[i]->Student::Print();
        }
    }
}

//Desctruction
Roster::~Roster() {}