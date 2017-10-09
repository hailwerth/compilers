import java.util.Scanner;

class LinkedList extends Object {

	public int num;
	public LinkedList next;

	LinkedList() {
		this.num = 0;
	}
}

class DivideXY extends Object {

	public int quotient, remainder;

	DivideXY() {
		this.quotient = this.remainder = 0;
	}

	public void divide(int i, int j) {

		while(!(!(j < i) && !(i == j))) {

			this.quotient = this.quotient + 1;
			i = i - j;
		}
		this.remainder = i;
	}
}

public class skeleton {

	public skeleton() {
		return;
	}
	
	public static int readNat() {
		int num;
		Scanner scanner;

		scanner = new Scanner(System.in);
		System.out.format("Enter number: ");
		num = scanner.nextInt();
		return num;
	}

	public static void printNat(int num) {
		System.out.println(num);
	}

	public static void main(String[] args) {

		//code goes here
		int num = 0;
		LinkedList start, pos;

		start = new LinkedList();
		pos = start;
		num = 100;

		while(0 < num) {

			num = readNat();
			pos.num = num;
			pos.next = new LinkedList();
			pos = pos.next;
		}

		pos = start;
		while(0 < pos.num) {

			printNat(pos.num);
			pos = pos.next;
		}
	}
}