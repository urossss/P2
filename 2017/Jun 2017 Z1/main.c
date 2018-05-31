/*
	1) Napisati program na programskom jeziku C koji rešava jedan šahovski problem na tabli
	proizvoljnih dimenzija MxN. Šahovska tabla se predstavlja pomoću dve matrice karaktera (jedna
	za pozicije belih, a druga za pozicije crnih figura) i može sadržati sledeće karaktere: K – kralj, D
	– dama, T – top, L – lovac, S – skakač, P – pešak i O – prazno polje. Dimenzije table nisu
	poznate unapred, pa se mora vršiti dinamička alokacija memorije. Potrebno je odrediti i ispisati
	pozicije svih skakača zadate boje, koji u narednom potezu mogu da „pojedu“ neku drugu figuru, kao i oznake i
	pozicije figura koje mogu da pojedu. Skakač može da se pomera na jedno od polja koje je najbliže polju na
	kome se nalazi, a koje nije u istoj horizontali, vertikali ili dijagonali, kao na slici. Učitavanje table i obradu
	realizovati kao zasebne potprograme koji sa glavnim programom komuniciraju samo putem argumenata i
	povratnih vrednosti. Prilikom učitavanja, obezbediti da se u matricu učitavaju samo dozvoljeni karakteri.
	Ukoliko se unese pogrešan karakter, ponoviti unos. Voditi računa o ispravnom korišćenju dinamičke memorije.
*/

#include <stdio.h>
#include <stdlib.h>


void error() {
	printf("Error in allocation!\n");
	exit(1);
}

char **loadTable(int m, int n) {
	char **t = malloc(m * sizeof(char *)), c;
	if (!t) error();
	for (int i = 0; i < m; i++) {
		*(t + i) = malloc(n * sizeof(char));
		if (!(t + i)) error();
		for (int j = 0; j < n; j++) {
			do {
				c = getche();
			} while (c != 'K' && c != 'D' && c != 'T' && c != 'L' && c != 'S' && c != 'P' && c != 'O');
			t[i][j] = c;
		}
		printf("\n");
	}
	return t;
}

void printTable(char **t, int m, int n) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			printf("%c%c", t[i][j], j == n - 1 ? '\n' : ' ');
}

void deleteTable(char **t, int m, int n) {
	for (int i = 0; i < m; i++)
		free(t[i]);
	free(t);
}

void obrada(char **napad, char **odbrana, int m, int n) {
	static const int pomeraj[][2] = {
		{ 1, -2 }, { 2, -1 }, { 2, 1 }, { 1, 2 },
		{ -1, 2 }, { -2, 1 }, { -2, -1 }, { -1, -2 } };
	int i, j, k;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			if (napad[i][j] == 'S')
				for (k = 0; k < 8; k++) {
					int x = i + pomeraj[k][0];
					int y = j + pomeraj[k][1];
					if (x < 0 || x >= m) continue;
					if (y < 0 || y >= n) continue;
					if (odbrana[x][y] != 'O') {
						printf("Skakac na (%d,%d) moze da pojede %c na (%d, %d).\n", i, j, odbrana[x][y], x, y);
					}
				}
}

int main() {
	char **beli, **crni, boja;
	int m, n;

	printf("Unesite dimenzije table: ");
	scanf("%d %d", &m, &n);

	printf("Ucitavanje table belih figura:\n");
	beli = loadTable(m, n);
	printf("Ucitavanje table crnih figura:\n");
	crni = loadTable(m, n);

	printf("Unesite boju skakaca za obradu (B ili C): ");
	boja = getche();
	printf("\n");

	if (boja == 'B') obrada(beli, crni, m, n);
	else obrada(crni, beli, m, n);

	deleteTable(beli, m, n);
	deleteTable(crni, m, n);
	return 0;
}