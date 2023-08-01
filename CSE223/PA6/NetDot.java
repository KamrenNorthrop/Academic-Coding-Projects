/*
Names: Lodhi Ahmad, Kamren Northrop
Class: CSE223
Date: 6/5/2023
Assignment: PA6
Summary: This program allows two people to play the previously made Dots game over the internet. One player must choose to be the server, in which case they select
the appropriate button choice, enter a name of their choosing, and hit start. Then another player will choose client, enter a name as well as the ip to connect to.
The connection will be made and then the names will be exchanged between the two games.

All features up to this point work fine, but the ability to move onto making
moves in the game was not fully implemented in the NetThread class.

As of now, the swapping of the names, all frontend features are fully developed, working, and the connection is made.
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class NetDot extends JFrame {

	private JPanel contentPane;
	private NetBoard drawingArea;
	public JTextField playerOneName;
	public JTextField playerTwoName;
	private JTextField ipField;
	NetThread network = new NetThread(this); // thread object
	String ip; // the ip the client enters in the text box
	int serverClientSelection=0; // 0 means server, 1 means client
	boolean isConnected=false; // checks if the server and client are connected
	int gameStatus=0; // 0 = game not started, 1 = game started, 2 = game over
	boolean playerTurn=false; // false = player 1 turn, true = player 2 turn
	String firstName; String secondName; // the final names of the first and second player

	// main method to launch jFrame
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					NetDot frame = new NetDot();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	// create the jFrame
	public NetDot() {
		setTitle("Dots");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 540, 650);
		contentPane = new JPanel();
		contentPane.setBackground(new Color(192, 192, 192));
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		// message display
		JTextArea messageDisplay = new JTextArea();
		messageDisplay.setBackground(new Color(192, 192, 192));
		messageDisplay.setFont(new Font("Nirmala UI", Font.PLAIN, 18));
		messageDisplay.setEditable(false);
		messageDisplay.setBounds(40, 553, 450, 36);
		contentPane.add(messageDisplay);

		// player one score
		JTextArea playerOneScore = new JTextArea();
		playerOneScore.setBackground(new Color(192, 192, 192));
		playerOneScore.setEditable(false);
		playerOneScore.setFont(new Font("Mistral", Font.BOLD, 16));
		playerOneScore.setText("0");
		playerOneScore.setToolTipText("Player 1's score");
		playerOneScore.setBounds(136, 12, 20, 20);
		contentPane.add(playerOneScore);

		// player two score
		JTextArea playerTwoScore = new JTextArea();
		playerTwoScore.setBackground(new Color(192, 192, 192));
		playerTwoScore.setEditable(false);
		playerTwoScore.setFont(new Font("Mistral", Font.BOLD, 16));
		playerTwoScore.setText("0");
		playerTwoScore.setToolTipText("Player 2's score");
		playerTwoScore.setBounds(136, 46, 20, 20);
		contentPane.add(playerTwoScore);

		// player one name text field
		playerOneName = new JTextField();
		playerOneName.setBackground(new Color(192, 192, 192));
		playerOneName.setToolTipText("Enter player 1's name");
		playerOneName.setBounds(40, 12, 86, 20);
		contentPane.add(playerOneName);
		playerOneName.setColumns(10);
		firstName=playerOneName.getText();

		// player two name text field
		playerTwoName = new JTextField();
		playerTwoName.setBackground(new Color(192, 192, 192));
		playerTwoName.setToolTipText("Enter player 2's name");
		playerTwoName.setBounds(40, 46, 86, 20);
		contentPane.add(playerTwoName);
		playerTwoName.setColumns(10);
		playerTwoName.setEnabled(false);
		secondName=playerTwoName.getText();

		// ipField for client
		ipField = new JTextField();
		ipField.setBackground(new Color(192, 192, 192));
		ipField.setText("localhost");
		ipField.setToolTipText("Enter IP address to connect to");
		ipField.setBounds(240, 46, 86, 20);
		ipField.setVisible(false);
		contentPane.add(ipField);

		// start or connect button
		JButton start = new JButton("Start");
		start.setBackground(new Color(64, 128, 128));
		start.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				if (gameStatus == 1) { // game is already started, so treat this as quitting the game
					gameStatus = 0; // set game status to off
					drawingArea.resetGame(); // reset values of the game
					playerTurn = false; // set turn back to player 1

					playerOneName.setText("");   //
					playerTwoName.setText("");   // reset the
					playerOneScore.setText("0"); // text
					playerTwoScore.setText("0"); //

					playerOneName.setEditable(true); // set the names
					playerTwoName.setEditable(true); // back to editable
					messageDisplay.setText("Game exited");

				} else if (gameStatus == 0) {
					firstName = playerOneName.getText(); // update name
					secondName = playerTwoName.getText(); // update name
					start.setBackground(new Color(222, 14, 14)); // set start button to red
					start.setText("Quit"); // rename start to quit
					playerOneName.setEditable(false); // set the names to
					playerTwoName.setEditable(false); // not be editable
					drawingArea.initializeBoxes(); // initialize the empty boxes
					gameStatus = 1; // turn game on
					messageDisplay.setText("Game has begun");
					repaint(); // repaint the board

					if (playerOneName.isEnabled()) { // if we are the server
						if (playerOneName.getText().length()==0){ // if the name is blank
							playerOneName.setText("Server");
							firstName = "Server";
						}
						playerOneName.setEnabled(false);
						network.start();
					}

					if (playerTwoName.isEnabled()) { // if we are the client
						ip = ipField.getText();
						if (playerTwoName.getText().length()==0){ // if the name is blank
							playerTwoName.setText("Client");
							secondName = "Client";
						}
						playerTwoName.setEnabled(false);
						network.start();
					}
				}
			}
		});

        start.setToolTipText("Start the game");
        start.setBounds(385, 10, 89, 23);
        contentPane.add(start);

		// button group
		ButtonGroup bg = new ButtonGroup();
		JRadioButton server = new JRadioButton(("Server"));
		JRadioButton client = new JRadioButton("Client");
		bg.add(server); bg.add(client);

		// server radio button
        server.setEnabled(true);
        server.setSelected(true);
        server.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				playerOneName.setEnabled(true);
				playerTwoName.setEnabled(false);
				playerTwoName.setText("");
				ipField.setVisible(false);
				start.setText("Start");
				serverClientSelection=0;
			}
		});
        server.setBackground(new Color(192, 192, 192));
        server.setFont(new Font("Nirmala UI", Font.BOLD, 16));
        server.setBounds(150, 12, 86, 20);
        contentPane.add(server);

		// client radio button
        client.setEnabled(true);
        client.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				playerOneName.setEnabled(false);
				playerTwoName.setEnabled(true);
				playerOneName.setText("");
				ipField.setVisible(true);
				start.setText("Connect");
				serverClientSelection=1;
			}
		});
        client.setBackground(new Color(192, 192, 192));
        client.setFont(new Font("Nirmala UI", Font.BOLD, 16));
        client.setBounds(150, 46, 86, 20);
        contentPane.add(client);

		// the board where the game is played
		drawingArea = new NetBoard();
        drawingArea.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				if(gameStatus==0) {
					messageDisplay.setText("You have to start the game first!");
				}
				else{
					network.sendXY(e.getX(), e.getY());
					boolean valid = drawingArea.commitMove( e.getX(), e.getY() );
					repaint();

					if (valid==false) {messageDisplay.setText("Invalid Move");} // move was invalid

					else{
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
						} else if (playerTurn==false) { // if player 1's turn
							messageDisplay.setText(firstName + "'s turn");
						} else if (playerTurn==true) { // if player 2's turn
							messageDisplay.setText(secondName + "'s turn");
						}
					}
				}
			}
		});
        drawingArea.saveDots(this);
        drawingArea.setBounds(50, 92, 410, 410);
        contentPane.add(drawingArea);
	}
}
