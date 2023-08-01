//Names: Lodhi Ahmad, Kamren Northrop
//Class: CSE223 - Data Structures & OOP
//Date: 5/22/2023
//Assignment: PA5 
// This class is used to construct a box, which will set all the variables top, bot, left, right boolean variables to false indicating that the board does not have any lines
class Box {
	private boolean top, bot, left, right;
	private String owner; // we default the owner to blank
	
	// constructor for box
	public Box () {
		top=false; bot=false; left=false; right=false;
		owner = " " ; // we default the owner to blank
	}
	
	// setter for box owner
	public void setOwner (String newOwner) {
		this.owner = newOwner;
	}
	
	// setter for top boolean
	public void setTop (boolean t) {
		top=t;
	}
	
	// setter for bottom boolean
	public void setBot (boolean b) {
		bot=b;
	}
	
	// setter for left boolean
	public void setLeft (boolean l) {
		left=l;
	}
	
	// setter for right boolean
	public void setRight (boolean r) {
		right=r;
	}
	
	// getter for box owner
	public String getOwner() {
		return owner;
	}
	
	// getter for top boolean
	public boolean getTop () {
		return top;
	}
	
	// getter for bottom boolean
	public boolean getBot() {
		return bot;
	}
	
	// getter for left boolean
	public boolean getLeft() {
		return left;
	}
	
	// getter for right boolean
	public boolean getRight() {
		return right;
	}
	
	// method to determine if box is complete
	public boolean isComplete() {
		if (getTop()==true && getBot()==true && getLeft() == true && getRight()==true) {
			return true;
		}
		else
			return false;
	}
}
