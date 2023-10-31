#pragma once
#ifndef roster_h
#define roster_h
//top level - array of student object -- storage for all student objects
#include <iostream>
#include "Degree.h"
#include "Student.h"
class Roster {
private:
    //use this index for classRosterArray independently from i
    int classRosterArrayPos = 0;
public:
    //ClassRosterArray -- Initialize to nothing
    Student* classRosterArray[5] = { nullptr, nullptr, nullptr, nullptr, nullptr }; //Class Roster
    std::string removed[5] = { "", "", "", "", "" }; //catch removed ID's, used in remove function

    void add(std::string studentID, std::string firstName, std::string lastName, std::string emailAddress, int age, int daysInCourse1, int daysInCourse2, int daysInCourse3, DegreeProgram degree);
    void remove(std::string studentID);
    void printAll();
    void printAverageDaysInCourse(std::string studentID);
    void printByDegreeProgram(DegreeProgram degree);
    void printInvalidEmails();

    //destruction
    ~Roster();
};
#endif