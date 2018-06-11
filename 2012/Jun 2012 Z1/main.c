/*
	1) Napisati program na programskom jeziku C koji treba da učita kvadratnu matricu dimenzije N, prepiše deo
	matrice u niz i ispiše sadržaj dobijenog niza na standardni izlaz. Program prvo čita dimenziju matrice, a zatim i
	elemente matrice. Potom od elemenata učitane matrice formira niz koji sadrži samo one vrednosti koje se u
	učitanoj matrici pojavljuju manje od 3 puta. Vrednosti u rezultujućem nizu ne smeju da se ponavljaju.
	Redosled vrednosti u nizu treba da odgovara redosledu kojim se nailazi na vrednosti u matrici kada se matrica
	obilazi po vrstama. Prepisivanje elemenata iz matrice u niz realizovati u potprogramu koji sa glavnim
	programom komunicira isključivo pomoću argumenata i povratne vrednosti. Vrednost N nije veća od 20.
*/

#include <stdio.h>
#include <stdlib.h>

void error() {
	fprintf(stderr, "Error in allocaton!\n");
	exit(1);
}

void printMatrix(int **m, int n) {
	putchar('\n');
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			printf("%d%c", m[i][j], j == n - 1 ? '\n' : ' ');
	putchar('\n');
}

void printArray(int *arr, int n) {
	for (int i = 0; i < n; i++)
		printf("%d%c", arr[i], i == n - 1 ? '\n' : ' ');
}
int *formArray(int **mat, int n, int *len) {
	int i, j, i1, j1, cnt;
	int *arr = malloc(n * n * sizeof(*arr));
	*len = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			for (cnt = i1 = 0; i1 < *len; i1++)
				if (arr[i1] == mat[i][j]) {
					cnt = 3;
					break;
				}
			for (i1 = 0; i1 < n; i1++) {
				for (j1 = 0; j1 < n; j1++) {
					if (mat[i1][j1] == mat[i][j])
						if (++cnt == 3) break;
				}
				if (cnt == 3) break;
			}
			if (cnt < 3) arr[(*len)++] = mat[i][j];
		}
	return arr;
}

int main() {
	int **mat, n, i, j, i1, j1, *arr, len;
	scanf("%d", &n);

	mat = malloc(n * sizeof(*mat));
	if (!mat) error();

	for (i = 0; i < n; i++) {
		mat[i] = malloc(n * sizeof(**mat));
		if (!mat[i]) error();

		for (j = 0; j < n; j++)
			scanf("%d", &mat[i][j]);
	}
	//printMatrix(mat, n);

	arr = formArray(mat, n, &len);
	printArray(arr, len);
}