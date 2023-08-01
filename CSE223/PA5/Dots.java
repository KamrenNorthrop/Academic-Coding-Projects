/*
Names: Lodhi Ahmad, Kamren Northrop
Class: CSE223 - Data Structures & OOP
Date: 5/22/2023
Assignment: PA5
Summary: This program is allows two people to locally play a dots game using swing. A window will open that lets two players enter
their names and then press the start button, which allows them to take turns drawing lines, with the aim of completing a box, which
puts their initial in the center and grants them a point. There are 9x9 dots, allowing for 8x8 boxes (64 boxes total). Whoever claims
more boxes in the end wins the game.
*/

import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Color;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JTextArea;
import java.awt.Font;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class Dots extends JFrame {
	
	private JPanel contentPane;
	private MyPanel drawingArea;
	private JTextField playerOneName;
	private JTextField playerTwoName;
	int gameStatus=0; // 0 = game not started, 1 = game started, 2 = game over
	boolean playerTurn=false; // false = player 1 turn, true = player 2 turn
	String firstName; String secondName; // the final names of the first and second player
	
	// main method to launch jFrame
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Dots frame = new Dots();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	// create the jFrame
	public Dots() {
		setTitle("Dots");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 540, 650);
		contentPane = new JPanel();
		contentPane.setBackground(new Color(192, 192, 192));
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));

		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JTextArea messageDisplay = new JTextArea();
		messageDisplay.setBackground(new Color(192, 192, 192));
		messageDisplay.setFont(new Font("Nirmala UI", Font.PLAIN, 18));
		messageDisplay.setEditable(false);
		messageDisplay.setBounds(40, 553, 450, 36);
		contentPane.add(messageDisplay);
		
		JTextArea playerOneScore = new JTextArea();
		playerOneScore.setBackground(new Color(192, 192, 192));
		playerOneScore.setEditable(false);
		playerOneScore.setFont(new Font("Mistral", Font.BOLD, 16));
		playerOneScore.setText("0");
		playerOneScore.setToolTipText("Player 1's score");
		playerOneScore.setBounds(136, 12, 20, 20);
		contentPane.add(playerOneScore);
		
		JTextArea playerTwoScore = new JTextArea();
		playerTwoScore.setBackground(new Color(192, 192, 192));
		playerTwoScore.setEditable(false);
		playerTwoScore.setFont(new Font("Mistral", Font.BOLD, 16));
		playerTwoScore.setText("0");
		playerTwoScore.setToolTipText("Player 2's score");
		playerTwoScore.setBounds(136, 46, 20, 20);
		contentPane.add(playerTwoScore);
		
		drawingArea = new MyPanel();
		drawingArea.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if(gameStatus==0) {
					messageDisplay.setText("You have to start the game first!");
				}
				else {
					boolean valid = drawingArea.commitMove( e.getX(), e.getY() );
					repaint();
					
					if (valid==false) {messageDisplay.setText("Invalid Move");} // move was invalid
					
					else {
						playerOneScore.setText(drawingArea.getPlayerOneScore()); // update player one score
						playerTwoScore.setText(drawingArea.getPlayerTwoScore()); // update player two score
						
						if (drawingArea.isGameOver()==true) { // game is over
							int winner=drawingArea.winner();
							gameStatus=0; // set game status to off
							drawingArea.resetGame(); // reset values
							playerTurn=false; // set turn back to player 1
							repaint(); // repaint
							playerOneName.setText("");   //
							playerTwoName.setText("");   // reset the 
							playerOneScore.setText("0"); // text fields
							playerTwoScore.setText("0"); //
							playerOneName.setEditable(true); // set the names
							playerTwoName.setEditable(true); // back to editable
							if(winner==1) messageDisplay.setText(firstName + " has won!");        // determine who
							else if (winner==2) messageDisplay.setText(secondName + " has won!"); // won the game
							else if (winner==3) messageDisplay.setText("The game is a tie!");     // 				
						}
						
						else if (playerTurn==false) { // if player 1's turn
							messageDisplay.setText(firstName + "'s turn");
						}
						
						else if (playerTurn==true) { // if player 2's turn
							messageDisplay.setText(secondName + "'s turn");
						}	
					}				
				}						
			}
		});
		drawingArea.saveDots(this);
		drawingArea.setBounds(50, 92, 410, 410);
		contentPane.add(drawingArea);		
		
		playerOneName = new JTextField();
		playerOneName.setBackground(new Color(192, 192, 192));
		playerOneName.setToolTipText("Enter player 1's name");
		playerOneName.setBounds(40, 12, 86, 20);
		contentPane.add(playerOneName);
		playerOneName.setColumns(10);
		firstName=playerOneName.getText();
		
		playerTwoName = new JTextField();
		playerTwoName.setBackground(new Color(192, 192, 192));
		playerTwoName.setToolTipText("Enter player 2's name");
		playerTwoName.setBounds(40, 46, 86, 20);
		contentPane.add(playerTwoName);
		playerTwoName.setColumns(10);
		secondName=playerTwoName.getText();
		
		JButton start = new JButton("Start");
		start.setBackground(new Color(64, 128, 128));
		start.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if (gameStatus==1) { // game is already started
					messageDisplay.setText("The game has already started!");
				}
				else if (gameStatus==0) {
					try { // catch the error that may occur if name text boxes are empty
						playerOneName.getText().substring(0,1).equals(playerTwoName.getText().substring(0,1));
					} catch (Exception r) {
						messageDisplay.setText("Please enter two valid player names");
					}
					if (playerOneName.getText().substring(0,1).equals(playerTwoName.getText().substring(0,1))) { // if both names have the same first initial, give warning
						messageDisplay.setText("Please enter two valid player names");
					}
					else { // the names are good, so start the game
						playerOneName.setEditable(false); // set the names to
						playerTwoName.setEditable(false); // not be editable
						firstName=playerOneName.getText(); // Grab name for player one
						secondName=playerTwoName.getText(); // Grab name for player two
						messageDisplay.setText(firstName+ "'s turn");
						gameStatus=1; // turn the game on
						drawingArea.initializeBoxes(); // initialize the empty boxes
						repaint(); // repaint the board
					}										
				}
			}
		});
		start.setToolTipText("Start the game");
		start.setBounds(385, 11, 89, 23);
		contentPane.add(start);
		
		JButton restart = new JButton("Restart");
		restart.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if (gameStatus==0) {
					messageDisplay.setText("Game has not started yet!");
				}
				else { 
					gameStatus=0; // set game status to off
					drawingArea.resetGame(); // reset values of the game
					playerTurn=false; // set turn back to player 1
					repaint(); // repaint the board
					
					playerOneName.setText("");   //
					playerTwoName.setText("");   // reset the
					playerOneScore.setText("0"); // text
					playerTwoScore.setText("0"); //
					
					playerOneName.setEditable(true); // set the names
					playerTwoName.setEditable(true); // back to editable
					messageDisplay.setText("Game Reset");
				}
			}
		});
		restart.setBackground(new Color(255, 0, 0));
		restart.setToolTipText("Restart the game");
		restart.setBounds(385, 45, 89, 23);
		contentPane.add(restart);
	}	
}
