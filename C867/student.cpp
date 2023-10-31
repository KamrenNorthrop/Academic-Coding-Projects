#include <iostream>
#include "student.h"


//CONSTRUCTORS--------------
Student::Student(){
    this->studentID = "";
    this->studentFirstName = "";
    this->studentLastName = "";
    this->studentEmail = "";
    this->studentAge = 0;
    
    for(int i = 0; i < 3; i++){
        this->daysToComplete[i] = 0;
    }
};

Student::Student(std::string id, std::string firstName, std::string lastName, std::string email, int age, int days[], DegreeProgram degree){
    //easy setting student object up calling class setters.
    SetStudentID(id);
    SetStudentFirstName(firstName);
    SetStudentLastName(lastName);
    SetStudentEmail(email);
    SetStudentAge(age);
    SetDaysToComplete(days);
    SetDegree(degree);
};

//SETTERS--------
 void Student::SetStudentID(std::string id){
    this->studentID = id;
 }
 void Student::SetStudentFirstName(std::string firstName){
    this->studentFirstName = firstName;
 }
void Student::SetStudentLastName(std::string lastName){
    this->studentLastName = lastName;
}
void Student::SetStudentEmail(std::string email){
    this->studentEmail = email;
}
void Student::SetStudentAge(int age){
    this->studentAge = age;
}
void Student::SetDaysToComplete(int days[]){
    //allocate daysToComplete pointer to new array for every student object: A1-A5
    this->daysToComplete = new int[3]; 

    for(int i = 0; i < 3; i++){
        this->daysToComplete[i] = days[i];
    }
}
void Student::SetDegree(DegreeProgram degree){
    this->studentDegree = degree;
}
    
//GETTERS----------  
std::string Student::GetStudentID() const{
    return this->studentID;
}
std::string Student::GetFirstName() const{
    return this->studentFirstName;
}
std::string Student::GetLastName() const{
    return this->studentLastName;
}
std::string Student::GetStudentEmail() const{
    return this->studentEmail;
}
int Student::GetStudentAge() const{
    return this->studentAge;
}
int* Student::GetDaysToComplete() const{
    return daysToComplete;
}
DegreeProgram Student::GetDegree() const{
    return this->studentDegree;
}

//PRINTING STUDENT INFO-------------
void Student::Print(){
    std::string degree;
    //ID, first, last, age
    std::cout << GetStudentID();
    std::cout << "\t" << this->GetFirstName();
    std::cout << "\t" << this->GetLastName();
    std::cout << "\t" << this->GetStudentAge();
    
    //point to days to complete array
    int* sDays = GetDaysToComplete();
    std::cout << "\t{";
    for(int i = 0; i < 3; i++){
        std::cout << sDays[i] << ((i == 2) ? "" : " ");
    }
    std::cout << "}";
    
    //Converting enum class program to a string
    if(GetDegree() == DegreeProgram::NETWORK){
        degree = "Network";
    }
    else if(GetDegree() == DegreeProgram::SECURITY){
        degree = "Security";
    }
    else if(GetDegree() == DegreeProgram::SOFTWARE){
        degree = "Software";
    }
    else{
        std::cout << "Degree does not exist" << std::endl;
    }
    std::cout << "\t" << degree << std::endl;
}

//Destruction
Student::~Student(){}