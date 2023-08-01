// PA4 test code - ingest data and then print stuff

class PA4Test{
  public static void main(String[] args)
  {
    Registrar reg=new Registrar(); // this doesn't do much by itself
                                  // need to ingest data before we can explore
    if (!reg.ingest("PA4data.txt")) return; // returns false on error

// print number of students
    System.out.println("Total # of students: " + reg.numberOfStudents());
// and print list of all students
    String[] students=reg.getStudents(); // array of SIDs
    for (int i=0;i<students.length;i++){
      String SID=students[i];
      System.out.println(reg.getStudentName(SID)); // convert SID to name
    }

// print # of courses
    System.out.println("\nTotal # of courses: " + reg.numberOfCourses());

// get list of courses and print enrollment in each course
    String[] courses=reg.getCourses(); // array of course names

    for (int c=0;c<courses.length;c++){
      String course=courses[c]; // let's examine this course

      System.out.println("\nStudents in " + course);
// get students in this course
      String[] names=reg.getStudents(course); // array of SIDs
      for (int i=0;i<names.length;i++){
        System.out.println(reg.getStudentName(names[i]));
      } // end of student list for this course
    } // end of all courses
  } // end of main
}
