#include <iostream>
#include <sstream>
#include <vector>
#include "Student.h"
#include "Roster.h"
#include "Degree.h"
//Parse function declared
void parseStudentData(const std::string studentData, Roster& classRos);
int main(){
    //Class info
    std::cout << "C867 - Scripting & Programming: Applications" << std::endl;
    std::cout << "Language: C++" << std::endl;
    std::cout << "Student ID: 011338614" << std::endl;
    std::cout << "Name: Kamren Northrop" << std::endl;
    std::cout << std::endl;

    Roster classRoster;

    const std::string studentData[] = {
        "A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",      
        "A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK", 
        "A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE", 
        "A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
        "A5,Kamren,Northrop,nkamren@outlook.com,31,20,40,60,SOFTWARE" //added own info into table 
    };
    //Parsing data, adding into roster -- defined bottom of main.
    for(int i = 0; i < 5; i++){
        parseStudentData(studentData[i], classRoster);
    }

    //Display all students
    std::cout << "Displaying all students:" << std::endl;
    classRoster.printAll();
    std::cout << std::endl;

    //Display invalid emails
    std::cout << "Displaying Invalid Emails: " << std::endl;
    classRoster.printInvalidEmails();
    std::cout << std::endl;

    //loop through student IDs in roster.classRosterArray, index i calls student function Get student ID's
    for(int i = 0; i < 5; i++){ 
        classRoster.printAverageDaysInCourse(classRoster.classRosterArray[i]->Student::GetStudentID());
    }
    std::cout << std::endl;

    //Display by Degree Program
    classRoster.printByDegreeProgram(DegreeProgram::SOFTWARE);
    std::cout << std::endl;

    //remove student
    classRoster.remove("A3"); //Test for Id that does exist
    std::cout << std::endl;

    //Display all students again
    classRoster.printAll();
    std::cout << std::endl;

    //removing same student again
    classRoster.remove("A3"); 
} // end of main

//-----Parse Function-----
void parseStudentData(const std::string studentData, Roster& classRos){
    std::istringstream inSD(studentData); //parsing
    std::vector<std::string> parsedVec; //storing result
    DegreeProgram program;
    int age, days1, days2, days3;
    
    //if issue
    if(inSD.fail()){
        std::cout << "Failed" << std::endl;
    }
 
    //if not issue, parse
    while(inSD.good()){
       std::string subString;
       getline(inSD, subString, ',');
       parsedVec.push_back(subString);
    }

    //Convert string numbers to integers
    age = stoi(parsedVec.at(4));
    days1 = stoi(parsedVec.at(5));
    days2 = stoi(parsedVec.at(6));
    days3 = stoi(parsedVec.at(7));
    
    //convert string program to enum class program
    if(parsedVec.at(8) == "SECURITY"){
        program = DegreeProgram::SECURITY;
    }
    else if(parsedVec.at(8) == "NETWORK"){
        program = DegreeProgram::NETWORK;
    }
    else if(parsedVec.at(8) == "SOFTWARE"){
        program = DegreeProgram::SOFTWARE;
    }
    
    //Load roster with student info
    classRos.add(parsedVec.at(0), parsedVec.at(1), parsedVec.at(2), parsedVec.at(3), age, days1, days2, days3, program);
}