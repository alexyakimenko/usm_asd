#include <stdio.h>

double my_sqrt(double radicand) {
	double result = radicand;
	double temp = 0;

	while (result != temp) {
		temp = result;
		result = (result + radicand / result) * .5;
	}
	return result;
}

int main() {
	float number;
	scanf("%f", &number);
	printf("\n%.9f", my_sqrt(number));
	return 0;
}