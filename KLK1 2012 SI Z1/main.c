/*
	Vrednost broja PI se može statistički odrediti uz pomoć generatora
	pseudoslučajnih brojeva uniformne raspodele. Potrebno je generisati tačke
	u ravni sa obema koordinatama u realnom opsegu [0, 1]. Vrednost broja
	PI se tada može odrediti na osnovu odnosa broja tačaka koje se nalaze u
	delu kruga poluprečnika 1 sa centrom u koordinatnom početku (Tc) i broja
	tačaka koje pripadaju kvadratu stranice 1 koji obuhvata sve generisane
	tačke (Tu) pomoću sledeće formule:
		pi = 4 * Tc / Tu
	Napisati program na programskom jeziku C koji izračunava vrednost broja PI. Program treba da učita
	ukupan broj tačaka koji treba da budu generisan, izračuna vrednost broja PI i ispiše rezultat.
	Program treba da ponavlja opisane korake sve dok se za broj tačaka unosi pozitivna vrednost
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
	int n, i, Tc = 0;
	double x, y, pi;

	srand(time(NULL));

	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		x = 1.0 * rand() / RAND_MAX;
		y = 1.0 * rand() / RAND_MAX;

		if (sqrt(x * x + y * y) <= 1) {
			Tc++;
		}
	}

	pi = 4.0 * Tc / n;

	printf("PI = %lf\n", pi);
}