import java.util.Scanner;

public class inout_ext {

	public inout_ext() {
		System.out.println("Constructor of qr class.");
	}

	public static void main(String[] args) {

		int answer;
		Test div = new Test(4,2);

		answer = div.divide();
		System.out.println("\nAnswer 1 = " + answer);
		//System.out.format("\nAnswer = %d\n", answer);

		GetTest gtest = new GetTest(100,5);
		answer = gtest.divide();
		System.out.format("\nAnswer 2 = %d\n", answer);
	}
}

class Test {

	public int x, y;

	public Test(int x, int y) {
		this.x = x;
		this.y = y;
	}

	public int divide() {

		return this.x / this.y;
	}
}

class GetTest extends Test{

	public Scanner scanner;
	public String username;
	public int age;

	public GetTest(int x, int y) {
		
		//pass x and y to super class constructor
		super(x,y);

		// create a scanner so we can read the command-line input
	    scanner = new Scanner(System.in);

	    //  prompt for the user's name
	    System.out.print("Enter your name: ");

	    // get their input as a String
	    username = scanner.next();

	    // prompt for their age
	    System.out.print("Enter your age: ");

	    // get the age as an int
	    age = scanner.nextInt();

	    System.out.println(String.format("%s, your age is %d", username, age));
	}
}