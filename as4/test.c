#include <stdio.h>


void printInt(unsigned long int val) {

	if(val == (unsigned long int)NULL)
		printf("\nval = NULL\n");
	else
		printf("\nval = %ld\n", val);
}

int main() {

	char *c = "512";

	int val = atoi(c);

	printInt(val);

	printInt((unsigned long int)NULL);

	printf("\nc = %s\n", c);

	return 0;
}