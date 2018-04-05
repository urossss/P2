/*
	Napisati program na programskom jeziku C koji pronalazi i ispisuje informacije o duplim sličicama.
	Korisnik preko standardnog ulaza unosi šifre sličica proizvoljnim redosledom (sličice su izmešane pa
	duplirane sličice ne moraju biti jedna za drugom). Program treba da prebroji pojavljivanja za sve
	sličice, a zatim da izbaci iz niza sve one koje nemaju duplikate. Preostale sličice treba ispisati na
	standardnom izlazu, u nerastućem poretku po broju pojavljivanja, tako što se za svaku sličicu u
	posebnom redu ispiše šifra i broj pojavljivanja. Smatrati da broj različitih sličica nije veći od 1000, a
	da je šifra ceo broj tipa int.
*/

#include <stdio.h>

#define MAX 1000

int main() {
	int count[MAX] = { 0 }, id[MAX], n = 0, x, i, j, tmp;

	while (1) {
		scanf("%d", &x);
		if (x < 0) break;	// prekidamo unos ako je sifra negativna??

		for (i = 0; i < n; i++) {
			if (id[i] == x) break;
		}

		if (i == n && n >= MAX) break;

		if (i == n) {
			id[n] = x;
			count[n]++;
			n++;
		}
		else {
			count[i]++;
		}
	}

	for (i = j = 0; i < n; i++) {
		if (count[i] >= 2) {
			count[j] = count[i];
			id[j++] = id[i];
		}
	}
	n = j;

	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
			if (count[j] > count[i]) {
				tmp = count[j];
				count[j] = count[i];
				count[i] = tmp;
				tmp = id[i];
				id[i] = id[j];
				id[j] = tmp;
			}

	for (i = 0; i < n; i++) {
		printf("%10d: %5d\n", id[i], count[i]);
	}
}