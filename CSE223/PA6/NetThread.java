/*
Names: Lodhi Ahmad, Kamren Northrop
Class: CSE223
Date: 6/5/2023
Assignment: PA6
Summary: This class is the thread used to create the server and client sockets and allow the two players to interact with each other. The
class also contains methods to send the (x,y) coordinates of mouse clicks to each others game.
*/

import javax.swing.*;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class NetThread extends Thread {

    ServerSocket ss;
    Socket sock;
    NetDot parent;

    // constructor that accepts NetDot as a parent
    public NetThread(NetDot par){
        parent = par;
    }

    // run method for the thread
    public void run(){
        if (parent.serverClientSelection==0){
            // create a server socket
            try{
                ss = new ServerSocket(12345);
            } catch (IOException e) {
                e.printStackTrace(); return;
            }

            // accept connections to the server socket
            try {
                sock = ss.accept();
            } catch (IOException e) {
                e.printStackTrace(); return;
            }
            System.out.println("Got a connection: sock= " + sock);

            // declare a scanner to read from sock
            Scanner sc;
            try {
                sc = new Scanner(sock.getInputStream());
            } catch (IOException e) {
                e.printStackTrace(); return;
            }

            // open a PrintWriter to send to the client
            PrintWriter pw;
            try {
                pw = new PrintWriter(sock.getOutputStream());
            } catch (IOException e) {
                e.printStackTrace(); return;
            }

            // read from scanner and print
            while (sc.hasNextLine()) {
                String receivedName = sc.nextLine();
                parent.secondName = receivedName; parent.playerTwoName.setText(receivedName);
                System.out.println("received the string: " + receivedName);
                pw.println(parent.firstName); pw.flush();
            }
        }

        // if this is the client
        else if(parent.serverClientSelection==1){
            // create a socket so the client can join the server
            Socket sock;
            try {
                sock = new Socket(parent.ip, 12345);
            } catch (IOException e) {
                e.printStackTrace(); return;
            }
            System.out.println("Established a connection: sock=" + sock);

            // send the client name to the server
            Scanner sc;
            try {
                sc = new Scanner(sock.getInputStream());
            } catch (IOException e) {
                e.printStackTrace(); return;
            }

            // Open printWriter to send to server
            PrintWriter pw;
            try {
                pw = new PrintWriter(sock.getOutputStream());
            } catch (IOException e) {
                e.printStackTrace(); return;
            }

            // read from scanner and print
            pw.println(parent.secondName); pw.flush();
            String receivedName = sc.nextLine();
            parent.firstName = receivedName; parent.playerOneName.setText(receivedName);
            System.out.println("received name: " + receivedName);
            parent.isConnected=true;
        }
    }

    // sends the x and y coordinates
    public void sendXY(int x, int y){
        PrintWriter pw;
        try {
            pw = new PrintWriter(sock.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace(); return;
        }
        pw.println("c " + x + " " + y);
        pw.flush();
    }
}

