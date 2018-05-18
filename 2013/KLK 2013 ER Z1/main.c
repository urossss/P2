/*
	Napisati program na programskom jeziku C koji vrši određenu obradu nad nizom celih brojeva. Niz
	može sadržati najviše 100 elemenata. Program najpre treba da učita dužinu niza i same elemente
	niza, a zatim na standardnom izlazu ispiše svaki element niza kao zbir stepena dvojke od kojih se on
	sastoji. Obezbediti da se u niz mogu uneti samo pozitivni celi brojevi. Ukoliko korisnik unese
	negativan broj ili nulu ponovo zatražiti unos. Prilikom ispisa usvojiti format izlaza kao što je u
	primeru. Postupak ponavljati sve dok se za dužinu niza ne unese nekorektna vrednost.
*/

#include <stdio.h>
#define MAX 100

int main() {
	int a[MAX], n, i, j, prvi, err;
	while (1) {
		printf("n = ");
		scanf("%d", &n);
		if (n <= 0 || n > MAX) break;
		printf("Niz: ");
		err = 0;
		for (i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			if (a[i] <= 0) err = 1;
		}
		if (err) continue;
		for (i = 0; i < n; i++) {
			printf("%d = ", a[i]);
			prvi = 1;
			for (j = 8 * sizeof(a[0]) - 1; j >= 0; j--) {
				if (a[i] & (1 << j)) {
					if (!prvi)
						printf(" + ");
					else
						prvi = 0;
					printf("2^%d", j);
				}
			}
			printf("\n");
		}
	}
}