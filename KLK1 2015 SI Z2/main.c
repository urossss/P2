/*
	Napisati program na programskom jeziku C koji vrši simulaciju igre na sreću Loto. Svaki od M loto
	listića sadrži N različitih brojeva koje je igrač odabrao iz intervala celih brojeva [1, 50]. Program prvo
	sa standardnog ulaza učita broj loto listića (M) i broj odabranih brojeva na svakom od listića (N), a
	zatim učita kombinacije sa zadatog broja loto listića (broj listića nije veći od 100). Smatrati da će
	uneti brojevi za svaki od listića sigurno biti različiti, pa provera učitanih podataka nije potrebna. Posle
	unosa kombinacija, program "pokreće bubanj". Bubanj generiše dobitnu kombinaciju od N različitih
	pseudoslučajnih celih brojeva iz intervala [1, 50], tako što izvlači jedan po jedan broj i ukoliko se
	izvuče broj koji je već izvučen, izvlačenje se ponavlja. Na kraju, program treba da ispiše na
	standardnom izlazu koliko listića je bilo sa N, a koliko sa N-1 pogodaka.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_M 100
#define MAX_N 50

int main() {
	int m, n, i, j, x, count_n = 0, count_n1 = 0;
	int loto[MAX_M + 1][MAX_N + 1] = { 0 };

	scanf("%d%d", &m, &n);

	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++) {
			scanf("%d", &x);
			loto[i][x]++;
		}

	srand(time(NULL));
	for (i = 1; i <= n; i++) {
		while (1) {
			x = rand() / (RAND_MAX + 1.) * 50 + 1;
			if (!loto[0][x]) {
				loto[0][x]++;
				break;
			}
		}
	}

	for (i = 1; i <= m; i++)
		for (j = 1; j <= MAX_N; j++)
			if (loto[0][j] && loto[i][j]) loto[i][0]++;

	for (i = 1; i <= m; i++) {
		if (loto[i][0] == n) count_n++;
		else if (loto[i][0] == n - 1) count_n1++;
	}

	/*for (i = 0; i <= m; i++) {
		for (j = 0; j <= MAX_N; j++) {
			printf("%d ", loto[i][j]);
		}
		printf("\n");
	}*/

	printf("Sa n pogodaka: %d\n", count_n);
	printf("Sa n-1 pogodaka: %d\n", count_n1);
}