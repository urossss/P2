/*
	Napisati program na programskom jeziku C koji na slučajan način generiše dva niza realnih brojeva
	X i Y zadate dužine koji predstavljaju koordinate tačaka u ravni. Prvo se unese dužina nizova, a zatim
	se generišu koordinate tačaka u opsegu [0.0, 1.0]. Nakon generisanja tačaka, iz nizova treba
	ukloniti sve one tačke koje ne pripadaju krugu jediničnog poluprečnika čiji se centar nalazi u
	koordinatnom početku. Na kraju programa ispisati rezultujuće nizove, tačku po tačku. Postupak
	ponavljati sve dok se za dužinu nizova ne unese nedozvoljena vrednost.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 100

int main() {
	double x[MAX], y[MAX];
	int n, i, j;

	srand(time(NULL));

	while (1) {
		scanf("%d", &n);

		if (n <= 0 || n > MAX) break;

		for (i = 0; i < n; i++) {
			x[i] = (double) rand() / RAND_MAX;
			y[i] = (double) rand() / RAND_MAX;

			printf("[%lf, %lf]\n", x[i], y[i]);
		}

		printf("\n");

		for (i = j = 0; i < n; i++) {
			if (sqrt(x[i] * x[i] + y[i] * y[i]) <= 1) {
				x[j] = x[i];
				y[j++] = y[i];
			}
		}
		n = j;

		printf("%d\n", n);
		for (i = 0; i < n; i++) printf("[%lf, %lf]\n", x[i], y[i]);

		printf("\n*******************\n\n");
	}
}