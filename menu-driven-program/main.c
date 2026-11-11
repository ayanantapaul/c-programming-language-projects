#include <stdio.h>
#include <stdbool.h>

/* factorial */
int factorial(int number) {
	int result = 1;
	for (int i = 1; i <= number; i++) {
		result *= i;
	}
	return result;
}

/* prime */
bool prime(int number) {
    if (number < 2) return false;              // 0, 1, negatives → not prime
    if (number == 2) return true;              // 2 IS prime
    if (number % 2 == 0) return false;         // other evens → not prime
    for (int i = 3; i * i <= number; i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}   

/* main */
int main(void) {

	int input, output;
	int choice = 0;
	
	while (1) {
		printf("[1] Find the factorial of a given numbers\n");
		printf("[2] Find if a given number is prime\n");
		printf("[3] Check if a given number is odd or even\n");
		printf("[4] Exit\n");
		printf(":: Enter an option to continue: ");
		scanf("%d", &choice);
		
		switch (choice) {

			/* factorial */
			case 1:
				printf(":: Enter a numbner: ");
				scanf("%d", &input);
				printf("=> The factorial of %d is %d\n\n",
						input, factorial(input));
				continue;

			/* check if numnber is prime */
			case 2:
				printf(":: Enter a numbner: ");
				scanf("%d", &input);
				printf("=> %s\n\n", (prime(input)? "PRIME" : "NOT PRIME"));
				continue;

			/* check is a given number is even or odd */
			case 3:
				printf(":: Enter a number: ");
				scanf("%d", &input);
				printf("=> %s\n\n", ((input % 2 == 0)?"EVEN" : "ODD"));
				continue;

			/* in case the user wants to exit */
			case 4:
				printf("=> Execution terminated.\n");
				return 0;

			/* default case */
			default:
				printf("Please enter a valid option\n");
				continue;
		}
	}
}
