/*
Names: Lodhi Ahmad, Kamren Northrop
Class: CSE223
Date: 6/5/2023
Assignment: PA6
Summary: This class constructs a box that will be used in our Dots game. Each box has
four sides that are boolean values, along with an owner of the box which is a string.
When all 4 sides of the box are true, the game will assign an owner to the box, which
is the player that completed the box. There are methods to set and get the values of 
each side as well as the owner.
*/

class NetBox {
	private boolean top, bot, left, right;
	private String owner; // we default the owner to blank

	// constructor for box
	public NetBox() {
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
