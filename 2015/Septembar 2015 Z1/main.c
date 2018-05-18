/*
	Napisati program na programskom jeziku C koji filtrira nazive datoteka na osnovu zadate ekstenzije. Naziv
	datoteke je niz znakova (string) koji se sastoji od imena i ekstenzije. Ekstenzija je podstring iza poslednje
	tačke u nazivu. Program na početku sa standardnog ulaza učitava nazive datoteka (dinamički alocirane) i
	smešta njihove adrese u statički niz pokazivača (maks. dužine 100), sve dok se ne unese prazan red. Zatim sa
	standardnog ulaza učitava ekstenziju datoteka za izbacivanje. Na osnovu učitane ekstenzije, izbacuje iz
	postojećeg niza sve nazive fajlova koji imaju zadatu ekstenziju i ispisuje ih redom na standardnom izlazu. Na
	kraju program treba da ispiše i sve preostale nazive u nizu.
	Napomene: Naziv datoteke se zadaje u jednom redu, ima ispravan format, ne sadrži bele znakove, i može da
	ima maksimalno 256 ASCII znakova. Svaki učitani naziv mora da zauzme tačno onoliko prostora koliko je
	potrebno za smeštanje znakova. Dozvoljeno je koristiti bibliotečke funkcije za obradu stringova iz C zaglavlja
	<string.h>. Voditi računa o pravilnom korišćenju dinamičke memorije.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

void error() {
	printf("Error in allocation!\n");
	exit(1);
}

char* readLine() {
	char *s = NULL, c;
	int n = 1;
	while ((c = getchar()) != '\n') {
		s = realloc(s, (++n) * sizeof(*s));
		if (s == NULL) error();
		*(s + n - 2) = c;
	}
	if (s == NULL) return s;
	*(s + n - 1) = '\0';
	return s;
}

int main() {
	char *str[100], *s, *ext, *p;
	int n = 0, i, j;

	while (1) {
		s = readLine();
		if (s == NULL) break;
		n++;
		if (n >= MAX_LEN) break;
		*(str + n - 1) = s;
	}
	ext = readLine();

	for (i = j = 0; i < n; i++) {
		p = strrchr(str[i], '.') + 1;
		if (strcmp(p, ext)) {
			str[j++] = str[i];
		}
		else {
			puts(str[i]);
			free(str[i]);
		}
	}
	n = j;

	for (i = 0; i < n; i++)
		puts(str[i]);

	for (i = 0; i < n; i++) 
		free(str[i]);
}