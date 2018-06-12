/*
	1) Napisati program na programskom jeziku C koji obrađuje tekst učitan sa standardnog ulaza. Tekst se čita iz
	proizvoljnog broja redova sve dok se ne dođe do praznog reda. Svakim učitani red se potom ispisuje na
	standardni izlaz uz prelamanje (ako ima više od N reči). Redove teksta koji imaju više od N reči potrebno je
	prelomiti u više manjih redova, tako da svaki manji red ima tačno N reči, osim poslednjeg u kojem može biti
	najviše N reči. Maksimalne dužine reči i reda nisu unapred poznate. Poznato je da se u ulaznom tekstu
	pojavljuju samo slova i blanko znakovi. Reči su razdvojene sa jednim ili više blanko znakova. Parametar N se
	učitava sa standardnog ulaza na početku programa. Voditi računa o korektnoj upotrebi resursa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 10
#define PCHUNK 10

int main() {
	char **text;
	char *s;
	int n = 0, i = 0, j, size, N, cnt;

	scanf("%d\n", &N);	// broj reci za ispis u jednom redu

	text = malloc(PCHUNK * sizeof(char*));
	if (!text) exit(1);

	/* 
		Alokacija se vrsi sa inkrementima, i za pojedinacne stringove (blokovi velicine CHUNK) i za niz stringova (blokovi velicine PCHUNK).
		Nakon svake ucitane reci odseca se bespotreban alociran prostor ako postoji, slicno i nakon sto se svi stringovi ucitaju.
	*/
	while (1) {
		s = malloc((CHUNK + 1) * sizeof(char));
		if (!s) exit(1);
		fgets(s, CHUNK + 1, stdin);
		if (!strcmp(s, "\n")) {	// unos se prekida kad se unese prazan red
			free(s);
			break;
		}
		while (s[strlen(s) - 1] != '\n') {	// oslobadjamo svaki put po jos malo prostora dok se ne ucita ceo red
			size = strlen(s);
			s = realloc(s, (size + CHUNK + 1) * sizeof(char));
			if (!s) exit(1);
			fgets(s + size, CHUNK + 1, stdin);
		}
		s[strlen(s) - 1] = '\0';	// posto fgets pokupi i '\n' a ne treba nam
		if (strlen(s) % CHUNK) {	// ako je alocirano vise mesta nego sto string zaista zauzima
			s = realloc(s, strlen(s) + 1);
			if (!s) exit(1);
		}

		if (n == PCHUNK) {	// ako je vec uneto onoliko stringova za koliko smo alocirali prostora, treba alocirati jos
			n = 0;
			text = realloc(text, (i + PCHUNK) * sizeof(char*));
			if (!text) exit(1);
		}

		text[i++] = s;
		n++;
	}
	n = i;	// broj ucitanih linija
	if (n % PCHUNK) {	// ako je alocirano prostora za vise stringova nego sto je uneto
		text = realloc(text, n * sizeof(char*));
		if (!text) exit(1);
	}

	for (i = 0; i < n; i++) {
		cnt = 0;
		for (j = 0; j < strlen(text[i]); j++) {
			if (text[i][j] == ' ') {
				cnt++;
				while (text[i][j] == ' ') j++;
				putchar(' ');
			}
			if (cnt == N) {
				cnt = 0;
				// j++;
				putchar('\n');
			}
			putchar(text[i][j]);
		}
		putchar('\n');
	}
}