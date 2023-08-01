//Name: Kamren Northrop
//Class: CSE223 - Data Sturcutres & OOP
//Assignment: PA3 - Vector class
/*Synopsis: The following code is an implementation of a vector class in java. This class creates vectors by accepting arguments such as v1 = new Vector (x,y,z) at which point those components are passed to the classes constructor setting them as the vector components. After a vector has been implemented, there are various methods that preform vector arithmetic. .add will accept another vector and return the vector outcome of adding both vectors together. .mul is able to accept another vector or a scalar and will perform the multiplication accordingly returning the solution. .length() calculate the magnitude of the vector it is called with. .normalize will normalize the vector it is called with and return it to the user. There are also getters for the x, y, z components to access those outside of the class as these variables within the class are set to private.*/ 

class Vector{ //start of class
//------Private x, y, z-------
	private	double x; //x component, private
	private double y; //y component, private
	private double z; //z component, private
//------End of private variables------

//------Constructor------
/*Constuctor: The constructor takes the values of xComp, yComp, and zComp passed in by the user when creating a new vector and saves them to the private x,y,z variables in  the class.*/
	public Vector(double xComp, double yComp, double zComp){ //constructor for making vector
		x = xComp; //setting x = to the xComp passed in by user
		y = yComp; //setting y = to the yComp passed in by user
		z = zComp; //seting z = to the zComp passed in by user
	}
//------End of Constructor-----

//------Start of Add------
/*Add method: the add method is called with an object and takes in an argument of another vector. From there, it adds the corresponding x,y,z components of both vectors     together, saves the sum into the variable newXYZComp. After the addition is done, this method creates a new vector with the new components saved and returns it to           the user*/	
	public Vector add(Vector a){ //adding vectors
		double newXComp = this.x + a.x; //adding the current object's x with the passed in vectors x to create the new vectors newXComp
		double newYComp = this.y + a.y; //adding the current object's y with the passed in vectors y to create the new vectors newYComp
		double newZComp = this.z + a.z; //adding the current object's z with the passed in vectors z to create the new vectors newZComp
		
		return new Vector(newXComp, newYComp, newZComp); //creating and returning new vector with the new components 
	}
//------END OF ADD------

//------Start of Subtraction------
/*Subtraction method: the subtraction method is called with an object and takes in an argument of another vector. From there, it subtracts the corresponding x,y,z componentsv1-v2 from eachother, saves the difference into the variables newXYZComp. After the subtraction is done, this methode creates a new vector with the new components           saved and returns it to the user*/
	public Vector sub(Vector a){ //subtracting vectors
		double newXComp = this.x - a.x; //subtracting the current object's x with the passed in vectors x to create the new vectors newXComp
		double newYComp = this.y - a.y; //subtracting the current object's y with the passed in vectors y to create the new vectors newYComp
		double newZComp = this.z - a.z; //subtracting the current object's z with the passed in vectors z to create the new vectors newZComp

		return new Vector(newXComp, newYComp, newZComp); //creating and returning new vector with the new components
	}
//------End of Subtraction------

//------Start of Multiplication by scalar------
/*Multiplication by scalar method: the multiplication by scalar method is called with an objects and takes in an argument of a single scalar. From there, it multiplies the  x,y,z components of the current object by the scalar given and saves the outcome into the variables newXYZComp. After the multiplication has taken place, this method        creates a new vector with the new components saved and returns it to the user.*/
	public Vector multiply(double s){ //multiplying vector by scalar
		double newXComp = this.x*s; //mulitplying the current object's x component by the scalar s to create the new vectors newXComp
		double newYComp = this.y*s; //multiplying the current object's y component by the scalar s to create the new vectors newYComp
		double newZComp = this.z*s; //multiplying the current object's z component by the scalar s to create the new vectors newZComp

		return new Vector(newXComp, newYComp, newZComp); //creating and returning new vector with the new components
	}
//------End of Multiplication by scalar------

//------Start of Multiplication of Vectors------
/*Multiplying dot product of two vectors method: the multiplication method to get the dot product is called with an object and takes in an argument of another Vector.       from there, it begins by multiplying the corresponding values of each vector together v1*v2 and saving them into the variables newXYZComp. After the multiplication          takes place, it takes the values saved in the variables newXYZComp and adds them together and saves the sum into the variable dotProduct. Once that has taken place          this method will return the variable dotProduct to the user.*/
	public double multiply(Vector a){ //multiplying vector by another vector aka dot product of two vectors
		double newXComp = this.x*a.x; //multiplying the current objects x with the passed in vectors x to create value for newXComp
		double newYComp = this.y*a.y; //multiplying the current objects y with the passed in vectors y to create value for newYComp
		double newZComp = this.z*a.z; //multiplying the current objects z with the passed in vectors z to create value for newZComp
		double dotProduct = newXComp+newYComp+newZComp; //adding together all values of above multiplication and saving to variable dotProduct
 
		return dotProduct; //returning dotProduct to the user
	}
//------End of Mulitplication of vectors------

//------Start of Length------
//Length method: the length method is called with an object, once called it will start by raising the x,y,z components of the current object to the power of two and save    the outcome of the arithmatic to the variables newXYZComp. Once the multiplication is done, this method will then add together newXYZComp, take the square root, and return  the value to the user.*/
	public double length(){ //magnitude of vector
		double newXComp = Math.pow(this.x, 2); //squaring the current objects x component to create value for newXComp
		double newYComp = Math.pow(this.y, 2); //squaring the current objects y component to create value for newYComp
		double newZComp = Math.pow(this.z, 2); //squaring the current objects z component to create value for newZComp

		return Math.sqrt(newXComp+newYComp+newZComp); //adding the squared values saved in newXComp, newYComp, newZComp together, then taking the square root and 
	}						      //returning the value to the user.
//------End of Length------

//------Start of Normalize------
/*Normalize method: the normalize method is called with an obnject, once called it will start by calculating the length of the vector by using the length method. Once the   length is found, if the length is greater then 0 it will create a unit vector by setting up the fraction 1.0 / length. From there it will then multiply the x,y,z components of the vector with the unit vector and save the outcome to the variables newXYZComp. After that has taken place this method will create a new vector with the saved values innewXYZComp and return it to the user. However, if the length is 0, this method will create a zero vector and return the zero vector to the user.*/
	public Vector normalize(){ //normalizing vector - Note: all components raised to power 2, after length takes place, all values will be greater then 0!!!
		double length = length(); //finding the length of the current vector object

		if (length > 0){ //if the length is greater then 0
			double normalized = 1.0 / length; //creating unit vector 

			double newXComp = this.x*normalized; //multiplying the current objects x component by unit vector to create newXComp
			double newYComp = this.y*normalized; //multiplying the current objects y component by unit vector to create newYComp
			double newZComp = this.z*normalized; //multiplying the current objects z component by unit vector to create newZcomp

			return new Vector(newXComp, newYComp, newZComp); //creating and returning new vector with the new components
		}
		else{ //if the length is 0
			return new Vector(0, 0, 0); //creating and returning zero vector
		}
	}
//------End of Normalize------

//------Start toString------
/*toString method: this toString method ensures that the string returned from concatination is in the format of (x, y, z) and returns it to the user*/
	public String toString(){ //new toString format
		return "("+x+", "+y+", "+z+")"; //returning vector format when .toString is inherently called to get (x, y, z) string format.
	} 
//------End toString------

//------Start of Getters------	
/*Getters x, y, z methods: the x(), y(), z() methods are used to be able to have access to the private variables x, y, z outside of the vector class. Each method returns    the corresponding component to the user. Ex: v1.x() returns v1's x component, etc.*/
	public double x(){ //access to private variable x
		return x; //returning value of x to user
	}
	public double y(){ //access to private variable y
		return y; //returning value of y to user
	}
	public double z(){ //access to private variable z
		return z; //returning value of z to user
	}
//------End of Getters------
}//End of Class
