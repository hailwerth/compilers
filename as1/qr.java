import java.util.Scanner;


class ArrayObj extends Object {

	public int x;
	public ArrayObj next;

	public ArrayObj() {
		return;
	}

	public ArrayObj(int x) {

		this.x = x;
	}

	public ArrayObj push_back(int num) {

		this.next = new ArrayObj();
		this.next.x = num;
		return this.next;
	}

	public ArrayObj queue(int num) {

		this.x = num;
		this.next = new ArrayObj(0);
		return this.next;
	}
}

class Divide extends Object {
	
	Divide() {
		return;
	}

	int rem;

	public int divide(int x, int y) {

		int num = 0;
		
		while( !(!(y < x) && !(y == x)) ) {
			num = num + 1;
			x = x - y;
		}

		this.rem = x;
		return num;
	}
}

public class qr {

	public qr() {
		return;
	}

	public static void printNat(int x) {

		System.out.println(x);
	}

	public static int readNat() {

		int num;
		Scanner scanner;

		scanner = new Scanner(System.in);
		System.out.format("Enter number: ");
		num = scanner.nextInt();
		return num;
	}

	public static void main(String[] args) {

		int i, j, num, max, count;
		Boolean ifound, jfound;
		ArrayObj start, current;
		Divide div;

		max = 10000;
		count = 0;
		num = 1;
		start = new ArrayObj(0);
		current = start;
		while(0 < num && count < max) {

			// System.out.format("Enter number: ");
			num = readNat();
			current = current.queue(num);
			count = count + 1;
		}
		count = count - 1;

		i = readNat();
		j = readNat();

		if( !((i < count) && (j < count)) ) {
			printNat(0);
			printNat(0);
		}
		else {
			current = start;
			num = 0;
			ifound = jfound = false;
			while(!(ifound && jfound) ) {

				if(num == i) {
					i = current.x;
					ifound = true;
				}
				else {
					ifound = ifound;
				}

				if(num == j) {
					j = current.x;
					jfound = true;
				}
				else {
					jfound = jfound;
				}

				current = current.next;
				num = num + 1;
			}

			//
			div = new Divide();
			printNat(div.divide(i,j));
			printNat(div.rem);
		}
	}
}
