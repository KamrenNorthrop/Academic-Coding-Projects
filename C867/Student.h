#ifndef student_h
#define student_h
//mid level - student objects to store student info -- object is to be stored in classRosterArray
#include <iostream>
#include "Degree.h"

class Student{
    private:
        std::string studentID;
        std::string studentFirstName;
        std::string studentLastName;
        std::string studentEmail;
        int studentAge;
        int* daysToComplete; 
        DegreeProgram studentDegree;
    public:
    //constructors
    Student();
    Student(std::string id, std::string firstName, std::string lastName, std::string email, int age, int DaysToComplete[], DegreeProgram degree);

    //setters
    void SetStudentID(std::string id);
    void SetStudentFirstName(std::string firstName);
    void SetStudentLastName(std::string lastName);
    void SetStudentEmail(std::string email);
    void SetStudentAge(int age);
    void SetDaysToComplete(int daysToComplete[]);
    void SetDegree(DegreeProgram degree);

    //getters   
    std::string GetStudentID() const;
    std::string GetFirstName() const;
    std::string GetLastName() const;
    std::string GetStudentEmail() const;
    int GetStudentAge() const;
    int* GetDaysToComplete() const;
    DegreeProgram GetDegree() const;
    void Print();

    //destruction
    ~Student();
};
#endif