/*
	Napisati program na programskom jeziku C koji vrši određenu obradu nad dva niza celih brojeva
	jednake dužine (najviše 100 elemenata). Program treba da utvrdi i ispiše da li je prvi učitani niz
	moguće dobiti rotacijom drugog učitanog niza za odgovarajući broj mesta udesno, kao i broj mesta
	za koji ga je potrebno rotirati. Program najpre treba da učita dimenziju nizova, zatim i same nizove.
	Na kraju, program treba da ispiše na standardnom izlazu ulazne nizove i rezultat provere. Postupak
	ponavljati sve dok se za dužinu nizova ne unese nedozvoljena vrednost.
	(Kolokvijum 2012, ER)
*/

#include <stdio.h>
#define MAX 100

int main() {
	int a[MAX], b[MAX], pom[MAX], n, i, j, rot, jednaki, tmp;
	while (1) {
		printf("n = ");
		scanf("%d", &n);
		if (n <= 0 || n > MAX) exit(1);
		printf("Niz A: ");
		for (i = 0; i < n; i++) scanf("%d", &a[i]);
		printf("Niz B: ");
		for (i = 0; i < n; i++) {
			scanf("%d", &b[i]);
			pom[i] = b[i];
		}

		rot = 0;
		for (i = 0; i < n; i++) {
			jednaki = 1;
			for (j = 0; j < n; j++)
				if (a[j] != pom[j]) {
					jednaki = 0;
					break;
				}
			if (jednaki) break;
			rot++;
			tmp = pom[n - 1];
			for (j = n - 1; j > 0; j--)
				pom[j] = pom[j - 1];
			pom[0] = tmp;
		}

		printf("Niz A: ");
		for (i = 0; i < n; i++) printf("%d ", a[i]);
		printf("\nNiz B: ");
		for (i = 0; i < n; i++) printf("%d ", b[i]);
		if (jednaki)
			printf("\nNiz A se dobija rotacijom niza B za %d mesta udesno!\n", rot);
		else
			printf("\nNiz A se ne moze dobiti rotacijom niza B!\n");
	}
}