//Name: Kamren Northrop
//Class: CSE223 - Data Structures & OOP
//Assignment: PA2


class PA2{
	public static void main(String[] args){
		double number = 0;
		double argNumber;
//------ERROR HANDLING------
		if (args.length == 0){ //No arguments
			System.out.println("Usage: PA2 add/mul n1 n2 n3....");
			return;
		}

		if (!args[0].equals("add") && !args[0].equals("mul")){ //if argument 0 doesn't equal add or mul
                                System.out.println("Usage: java PA2 add/mul n1 n2 n3....");
                                return;
                        }


		if (args.length < 2){ //if there are less then 2 arguments
				System.out.println("Usage: java PA2 add/mul n1 n2 n3...."); //otherwise, no arguments are given
				return;
		}
//------END OF ERROR HANDLING------

//------START OF ADD------
		if (args[0].equals("add")){
			for (int i = 1; i < args.length; i++){
				try{
					argNumber=Double.parseDouble(args[i]);
				}
				catch(NumberFormatException e){
					System.out.println("Usage: java PA2 add/mul n1 n2 n3....");
					return;
				}
				number = number+argNumber;
			}
			System.out.println("The sum of your numbers is = " + number);
		}
//------END OF ADD------

//------START OF MUL------
		if (args[0].equals("mul")){
			number = 1; //initializing variable to 1 so not multiplying by 0.
			for (int i = 1; i < args.length; i++){
				try{
					argNumber = Double.parseDouble(args[i]);
				}
				catch(NumberFormatException e){
					System.out.println("Usage: java PA2 add/mul n1 n2 n3....");
					return;
				}
				number = number*argNumber;
			}
			System.out.println("The product of your numbers is = " + number);
		}
//------END OF MUL------
	}//end of main
}//end of class
