//Name: Kamren Northrop
//Class: CSE223 - Data Structures & OOP
//Assignment: PA4 - Registrar class
/*Synopsis: Registrar is an implementation of a class in Java. This class starts by initializing two hash maps when called: one for students and their SIDS, the other for classes and their SIDS and assigns them both generic data types for reuse using a constructor. It then has a method called Ingest, where the class will create a scanner, read a file line by line, splitting at the commas in the file creating string tokens that are placed into an array called read. It's assuming there are at least 3 sections spacedby ,'s and that each file starts with either an S or an E to indicate which hash map it needs to be stored in. If all is included, it will add the data to the appropriate   place. and then close the scanner. This class can also contains various other methods that give it the ability to get the number of students, get the number of courses, get the student IDs, get student names, and get the number of courses. In total, this class holds all the methods needed to be able to store student names, courses, and SIDs andalso look up the info if needed.*/ 

//------IMPORTS------
import java.io.File; //need to create new file
import java.io.FileNotFoundException; //per java docs - scanner(file source) throws this exception
import java.util.HashMap; //need to create hashmap
import java.util.LinkedList; //need to create linkedlist
import java.util.Scanner; //need to create scanner
//------------------
//------Constructor------
//------Start Of Class------
public class Registrar{
	private HashMap<String, String> students; //declaring private hashmap students of generic type string string
	private HashMap<String, LinkedList<String>> enrollment; //declaring private hashmap enrollment of generic type string linkedlist<string>
	Scanner sc; //declaring scanner sc
//------Start of constructor------
/*the Constructor for Registrar takes the declared hashmaps from above and initializes them to create two emptoy hashmaps when called*/
	public Registrar(){ //Constructor - start hash maps
		students = new HashMap<String, String>(); //initializing students hashmap
		enrollment = new HashMap<String, LinkedList<String>>(); //initializing enrollment hashmap
	}
//------End of constructor------

//------Start of Ingest-----
/*Ingest intializes the scanner that is declared above and takes in the file source given in a try block so that it can catch a FileNotFoundException if it can't find the   source. If expcetion is caught, it will return the boolean value false. If the source is found, it will go into a while loop iterating to the next line as long as one is present, in doing so it will create string tokens by splitting each line at a comma and storing each token into an array of strings called read. Once done, it will check to make sure that read is at least length 3, as the file format is assumed E/S,SID/COURSE,NAME/SID, if one of the sections is missing, it will return an error to the user letting them know info is missing. If read is of length 3, it will then check element 0 to see if it's an S or an E to indicate what hash table to enter into. If it's neither, it   will return an error to the user. If S, it will place element 1 of read to a String variable called sid and element 2 to a string variable called name and then use the      method put to add the sid and name into the students hashmap. If E, it will put element 1 into a String variable called course and element 2 into a string variable called   sid and then check to see if the course is already in the enrollment hashmap. If not, it will then create a new linkedlist<String> called studentIds and it will use the     method put to put the course and the empty linkedlist into the enrollment hashmap. Once the course is present, it will then use the method get to get the values of the course key and then check to see if the student id is in the linked list. If it is not, it will use the linkedlist method add to add the student id to the course. Once it has done this for all the students and the file does not have a next line, it will close the scanner and return the boolean value true.*/
	public boolean ingest(String filename){
		try{  //trying to catch exceptions
			sc = new Scanner(new File(filename)); //initializing scanner as a new file source
		}
		catch(FileNotFoundException e){ //catching FileNotFoundException - according to java docs can throw when scanner(file source) format
			System.out.println("Error: File Not Found"); //informing user
			return false; //exiting, returning false
		}

		while(sc.hasNextLine()){ //while the file has a next line
			String temp = sc.nextLine(); //getting the next line
			String[] read = temp.split(","); //splitting the line at the commas to create string tokens, storing tokens into string array read

			if(read.length != 3){ //if the string array read is noth of length 3
				System.out.println("Error: expected 3 sections in <"+temp+">"); //inform user, error in file, showing error
				return false; //exiting, returning false
			}
			
			if(read[0].equals("S")){ //if element 0 is "S"
				String sid = read[1]; //place element 1 into String variable sid
				String name = read[2]; //place element 2 into string variable name
				students.put(sid, name); //use method put to put the students id and name into the students hashmap
			}
			else if(read[0].equals("E")){ //otherwise, if element 0 is "E"
				String course = read[1]; //place element 1 into String variable course
				String sid = read[2]; //place element 2 into String variable sid

				if (!enrollment.containsKey(course)){ //if the hashmap does not contain the course key
					LinkedList<String> studentIds = new LinkedList<String>(); //create a new empty linkedlist
					enrollment.put(course, studentIds); //use method put to put the course and empty linkedlist into the enrollment hashmap
				}
				
				LinkedList<String> studentIds = enrollment.get(course); //initializing studentIds linkedlist, using method get to get SIDS in a given course

				if(!studentIds.contains(sid)){ //if the student Id is not in the course
					studentIds.add(sid); //use the method add to add the student id into the course
				} 				
			}
			else{ //if element 0 is not either "S" or "E"
				System.out.println("Syntax error in file ingest: <"+temp+">"); //inform user of file syntax error, show line
				return false; //exiting, return false
			}
		}
		sc.close(); //closing scanner
		return true; //exiting, returning true if no errors
	}//end of ingest 

//------Start of numberOfStudents------
/*Number of students is a method that is used to returnt he total number of students. It does so by using the method .size() on the students hashmap which will return an    integer value of the number of key value mappings that are contained within the hashmap. Since we know that this hashmap is only storing student names and SIDS, we know thatthe number returned is going to be true to the total number of students.*/
	public int numberOfStudents(){
		return students.size(); //using method .size() on students hashmap to return total number of students to user
	}//end of numberOfStudents

//------Start of numberOfCourses------
/*Number of courses is a method that is used to return the total number of courses. it does so by using the method .size() on the students hashmap which will return an      integer value of the number of key value mappings that are contained within the hashmap. Since the courses are the key values in this hashmap, we know that the number       returned is going to be true to the total number of courses*/
	public int numberOfCourses(){
		return enrollment.size(); //using method .size() on enrollment hashmap to return total number of courses to user
	}//end of numberOfCourses

//------Start of getStudents------
/*this form of getStudents is a method that doesn't require any arguments, when called it will create a new string array called studentIds and then generate the set of keys within the student hashmap, and then turn the set of keys into a new string array. It will then return an array of strings that contains the SIDs.*/
	public String[] getStudents(){
		String[] studentIds = students.keySet().toArray(new String[0]); //initilizing studenId string array, setting equal to converted key set array
		return studentIds; //returning string array of student ids.
	}//end of getStudents()

//------Start of getStudents(String course)------
/*this form of get students accepts the argument of the course key, once called, it will check to make sure the course key is in the hashmap, if it's not it will return nullIf the course key is in the hashmap, it will create an array of strings called studentIds and set it equal to a new string array created by getting the values of the course and converting them into an array. Once done, it will then return the array of the sids to the user.*/
	public String[] getStudents(String course){
		if(!enrollment.containsKey(course)){ //if the course is not in the enrollment hashmap
			return null; //return null
		}
		
		String[] studentIds = enrollment.get(course).toArray(new String[0]); //initilizing studentId string array and storing converted array of SIDs 
		return studentIds; //returning array of sids			     	
	}//end of getStudents(String course)

//------Start of getStudentName------
/*Get student name accepts the argument of the students id. It will start by checking to see if the students hashmap contains the student id, if it does not, it will return an empty string. If it does, it will use the get method to return the value of the SID key which is the students name.*/
	public String getStudentName(String SID){
		if(!students.containsKey(SID)){ //if the SID is not in the students hashmap
			return ""; //return empty string
		}
		
		return students.get(SID); //otherwise, use .get method to return the students named associated with SID key		
	} //end of getStudentName

//------Start of getCourses------
/*getCourses is a method that doesn't take any arguments and will find all the course key's in the enrollment hashmap and store them into a string array and return that     string array to the user which will contain all the courses available.*/
	public String[] getCourses(){
		String [] courses = enrollment.keySet().toArray(new String[0]); //initilizing course string array and storing converted keySet array that contains courses
		return courses; //returns the string array of courses
	} //end of getCourses
}//end of class
