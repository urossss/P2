/*
	Napisati program na programskom jeziku C koji obađuje niz celih neoznačenih brojeva. Program sa standardnog ulaza
	učita broj elemenata niza i elemente niza, zatim iz niza izbaci sve elemente u čijoj binarnoj reprezentaciji ima više
	parova susednih jedinica od prosečnog broja parova susednih jedinica u reprezentacijama svih unetih brojeva, uredi
	preostale elemente niza po nerastućoj vrednosti elemenata i na kraju ispiše sadržaj rezultujućeg niza. Prilikom
	prebrojavanja parova jedna jedinica može da bude deo dva para (npr. u broju 10011101 postoje 2 para susednih
	jedinica). Smatrati da niz ima najviše 100 elemenata. Za svaki uneti broj dozvoljeno je najviše jednom računati broj
	parova susednih jedinica, pa je izračunatu vrednost potrebno čuvati u pomoćnom nizu. Osim dva pomenuta niza nije
	dozvoljeno koristiti druge pomoćne nizove.
*/

#include <stdio.h>
#define MAX 100

int main() {
	unsigned int brojevi[MAX], parovi[MAX] = { 0 }, n, mask, i, j;
	double sredina = 0;
	scanf("%u", &n);
	if (n <= 0 || n > MAX) exit(1);
	for (i = 0; i < n; i++) scanf("%u", &brojevi[i]);
	for (i = 0; i < n; i++) {
		mask = 3;
		for (j = 0; j < 8 * sizeof(brojevi[i]) - 1; j++) {
			if ((brojevi[i] & mask) == mask) parovi[i]++;
			mask <<= 1;
		}
		sredina += parovi[i];
	}
	sredina /= n;
	for (i = j = 0; i < n; i++) {
		if (parovi[i] <= sredina) {
			brojevi[j] = brojevi[i];
			parovi[j++] = parovi[i];
		}
	}
	n = j;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
			if (brojevi[i] < brojevi[j]) {
				unsigned t = brojevi[i];
				brojevi[i] = brojevi[j];
				brojevi[j] = t;
			}
	for (i = 0; i < n; i++)
		printf("%u ", brojevi[i]);
	putchar('\n');
}