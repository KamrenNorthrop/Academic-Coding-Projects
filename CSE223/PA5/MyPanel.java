/*
Names: Lodhi Ahmad, Kamren Northrop
Class: CSE223 - Data Structures & OOP
Date: 5/22/2023
Assignment: PA5
Summary: This class holds the methods that are used to calculate all where the user clicked, which line they intended to draw, who owns what boxes,
etc. It also handles painting the board every time a new event takes place and houses all of the important information used to track the game status.
*/
import java.awt.Graphics;
import javax.swing.JPanel;

public class MyPanel extends JPanel {
	Dots parent; // the Dots board
	int numRows = 8; int numCols=8; int boxSideLength=50; // the number of rows, columns, and the size of the box length
	int playerOneScore = 0; int playerTwoScore = 0; // the scores of both players
	Box[][] boxes = new Box[numRows][numCols]; // the 8x8 uninitialized 2d box array
	
	// method to allow access to Dots
	public void saveDots(Dots par) {
		parent=par;
	}
	
	// paint method that draws the dots and lines
	public void paint(Graphics g) {
		super.paint(g);
		
		for(int row = 0; row < 450; row=row+50) { // draw a grid of 9x9 dots
			for(int col = 0; col < 450; col=col+50) {
				drawDot(row,col,g);
			}
		}
		
		if (parent.gameStatus==1) { // if the game has started, then check which lines to draw
	        int x = 0; int y = 0;			
			for (int row=0; row<numRows; row++) { // go through each box and check whether to draw lines for each side
				for (int col=0; col<numCols; col++) {
					x = (row * 50); y = (col * 50); 
					if( boxes[row][col].getTop()==true) g.drawLine(x, y, x+boxSideLength+5, y);
					if( boxes[row][col].getBot()==true) g.drawLine(x, y+boxSideLength+5, x+boxSideLength+5, y+boxSideLength+5);
					if( boxes[row][col].getLeft()==true) g.drawLine(x, y, x, y+boxSideLength+5);
					if( boxes[row][col].getRight()==true) g.drawLine(x+boxSideLength+5, y, x+boxSideLength+5, y+boxSideLength+5);
					if( boxes[row][col].isComplete()==true) g.drawString(boxes[row][col].getOwner(), x+20, y+30);
				}
			}		
		}	
	}
	
	// method used to draw a dot
	void drawDot(int x, int y, Graphics g) {
		g.fillOval(x, y, 5, 5);
	}
	
	// method that initializes the boxes
	public void initializeBoxes()
	{
		for (int row=0; row<numRows; row++) { // go through each box and initialize it
			for (int col=0; col<numCols; col++) {
				boxes[row][col] = new Box();
			}
		}
	}
	
	// method that resets the values of all boxes to false and sets the owner to blank
	public void resetBoxes(Box[][] boxes) {
		for (int row=0; row<numRows; row++) { 
			for (int col=0; col<numCols; col++) {
				boxes[row][col].setTop(false);
				boxes[row][col].setBot(false);
				boxes[row][col].setLeft(false);
				boxes[row][col].setRight(false);
				boxes[row][col].setOwner(" ");
			}
		}		
	}
	
	// method that resets values of the game
	public void resetGame() {
		playerOneScore=0;
		playerTwoScore=0;
		resetBoxes(boxes);
	}
	
	// method that checks if the game is over
	public boolean isGameOver() {
		if ( anyBoxes()==false && (playerOneScore+playerTwoScore>=64) ){ return true; } // if there's no unclaimed boxes and player score is 64, all boxes are claimed, game is over
		else
			return false;
	}
	
	// method that checks which player won the game
	public int winner() {
		if (playerOneScore>playerTwoScore) { return 1; } // player one has won
		else if (playerOneScore<playerTwoScore) { return 2; } // player two has won
		else
			return 3; // game is a tie
	}
	
	// method that returns player 1 score as string
	public String getPlayerOneScore() { return String.valueOf(playerOneScore); }
	
	// method that returns player 2 score as string
	public String getPlayerTwoScore() { return String.valueOf(playerTwoScore); }
	
	// method that returns the first initial of the player whose turn it currently is
	public String currentPlayer() {
		if(parent.playerTurn==false) return parent.firstName.substring(0,1);
		else if(parent.playerTurn==true) return parent.secondName.substring(0,1);
		else
			return " ";
	}
	
	/* method that checks all boxes to see if any are unclaimed by a player.
	 * then it will claim all boxes for the current player and increase their score accordingly
	 */
	public void claimBoxes() {
		int bonusScore=1; // the player has to have gotten at least one completed box for this method to be called in the first place
		for (int row=0; row<numRows; row++) {
			for (int col=0; col<numCols; col++) {
				if (boxes[row][col].isComplete()==true) { // if the box is complete
					if (boxes[row][col].getOwner().equals(" ")) { // and the owner is empty
						boxes[row][col].setOwner(currentPlayer()); // claim that box for the current player
						bonusScore=bonusScore+1; // increment their score for any double box claims
					}
				}
			}
		}
		if(parent.playerTurn==false) playerOneScore=playerOneScore+bonusScore; // determine who gets the points 
		if(parent.playerTurn==true) playerTwoScore=playerTwoScore+bonusScore;  // for the claimed boxes
	}
	
	// method that checks for unclaimed boxes and returns true if there are, false if not
	public boolean anyBoxes() {
		for (int row=0; row<numRows; row++) {
			for (int col=0; col<numCols; col++) {
				if (boxes[row][col].isComplete()==true) {
					if (boxes[row][col].getOwner().equals(" ")) {
						boxes[row][col].setOwner(currentPlayer());
						return true;
					}
				}
			}
		}
		return false;
	}
	
	// big method that checks user mouse clicks 
	public boolean commitMove(int x, int y) {
		int row = x/50; int col = y/50;
		int lineChoice = determineLine(x,y);
		
		if (lineChoice==0) { // if chosen line was top line
			if (boxes[row][col].getTop()==false) {
				boxes[row][col].setTop(true);
				
				if (col-1>=0) boxes[row][col-1].setBot(true); // if there's a box above this one, set its bottom to true
				
				if(anyBoxes()==true) { // if this move completed a box
					claimBoxes(); // claim them for the current player
					return true; // do not switch player turn
				}
				else // this turn did not complete a box, switch player turn
				{
					parent.playerTurn=!parent.playerTurn;
					return true;
				}
			}
			else
				return false;
		}
		
		if (lineChoice==1) { // if chosen line was bottom line
			if (boxes[row][col].getBot()==false) {
				boxes[row][col].setBot(true);
				
				if (col+1<=7) boxes[row][col+1].setTop(true); // if there's a box below this one, set its top to true
				
				if(anyBoxes()==true) { // if there are any unclaimed, yet completed boxes
					claimBoxes(); // claim them for the current player
					return true; // do not switch player turn
				}
				else // this turn did not complete a box, switch player turn
				{
					parent.playerTurn=!parent.playerTurn;
					return true;
				}
			}
			else
				return false;
		}
		
		if (lineChoice==2) { // if chosen line was left line
			if (boxes[row][col].getLeft()==false) {
				boxes[row][col].setLeft(true);
				
				if(row-1>=0) boxes[row-1][col].setRight(true); // if there's a box to the left of this one, set its right to true

				if(anyBoxes()==true) { // if there are any unclaimed, yet completed boxes
					claimBoxes();
					return true; // do not switch player turn
				}
				else // this turn did not complete a box, switch player turn
				{
					parent.playerTurn=!parent.playerTurn;
					return true;
				}
			}
			else
				return false; 			
		}
		
		if (lineChoice==3) { // if chosen line was right line
			if (boxes[row][col].getRight()==false) { // if the line has not been made yet
				boxes[row][col].setRight(true); // set the right side of the box to true
				
				if(row+1<=7) boxes[row+1][col].setLeft(true); // if there's a box to the right of this one, set its left to true
				
				if(anyBoxes()==true) { // if there are any unclaimed, yet completed boxes
					claimBoxes(); // claim them for the current player
					return true; // do not switch player turn
				}
				else // this turn did not complete a box, switch player turn
				{
					parent.playerTurn=!parent.playerTurn; // switch the player turn
					return true;
				}
			}
			else // this line was already here
				return false;			 		    
		}		
		return false;    
	}
	
	// method that determines which line the player was trying to click
	public int determineLine(int xCord, int yCord) {
		int row = xCord/50; int col = yCord/50;

		int ULX=(row*50); int ULY=(col*50); int URX=(row*50)+50; int URY=(col*50); // upper cords of box
		int LLX=(row*50); int LLY=(col*50)+50; int LRX=(row*50)+50; int LRY=(col*50)+50; // lower cords of box
		int dt = Math.abs(yCord-URY); int db = Math.abs(LRY - yCord); // distance from top and bottom sides
		int dl = Math.abs(xCord-LLX); int dr = Math.abs(LRX-xCord); // distance from left and right sides
		
		if (dt < db && dt < dl && dt < dr) {
            return 0; // top line is the closest           
        }
        if (db < dt && db < dl && db < dr) {
            return 1; // bottom line is the closest 
        }
        if (dl < dt && dl < db && dl < dr) {
            return 2; // left line is the closest
        }
        if (dr < dt && dr < db && dr < dl) {
            return 3; // right line is the closest
        }
        else
        	return -1;
	}	
}
