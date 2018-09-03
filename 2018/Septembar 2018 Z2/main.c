/*
Napisati program na programskom jeziku C koji obrađuje stringove. Program na početku učita string koji sadrži
proizvoljan broj pojava para znakova %s. Zatim program učitava stringove koje ubacuje u prvi string. Za ubacivanje
jednog stringa neophodno je realizovati i koristiti funkciju char* insertString(char *s1, char *s2);. Funkcija
treba da ubaci string s2 u string s1, tako što zameni prvu pojavu para znakova %s u stringu s1 stringom s2. Stringovi za
ubacivanje se učitavaju sa standardnog ulaza, svaki string u zasebnom redu. Učitavanje i ubacivanje stringova se vrši sve
dok postoji bar jedan par znakova %s. Potrebno je napisati i koristiti funkciju koja pronalazi poziciju prvog pojavljivanja
%s u stringu int find(char *s);. Funkcija vraća negativan broj ako ne postoji %s u stringu. Program na kraju treba
da ispiše novoformirani string. Maksimalna dužina svakog stringa je 100, ali je potrebno koristiti samo onoliko
memorijskog prostora koliko je potrebno, drugim rečima prilikom svakog ubacivanja memorijski prostor za string je
potrebno proširiti za tačno onoliko koliko je potrebno da ceo sadržaj stane. Voditi računa o ispravnom korišćenju
dinamičke memorije.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 10

void error() {
	printf("Error in allocation!\n");
	exit(1);
}

char *readLine() {
	int length;
	char *s = malloc((CHUNK + 1) * sizeof(*s));
	if (!s) error();
	fgets(s, CHUNK + 1, stdin);
	while (s[strlen(s) - 1] != '\n') {
		length = strlen(s);
		s = realloc(s, (length + CHUNK + 1) * sizeof(*s));
		if (!s) error();
		fgets(s + length, CHUNK + 1, stdin);
	}
	s[strlen(s) - 1] = '\0';
	if (strlen(s) % CHUNK) {
		s = realloc(s, (strlen(s) + 1) * sizeof(*s));
		if (!s) error();
	}
	return s;
}

int find(char *s) {
	if (!s || *s == '\0') return -1;
	int i = 0;
	while (s[i + 1] != '\0') {
		if (s[i] == '%' && s[i + 1] == 's') return i;
		i++;
	}
	return -1;
}

char* insertString(char *s1, char *s2) {
	int start = find(s1), delta = strlen(s2) - 2, i, len1 = strlen(s1);

	if (delta >= 0) {
		s1 = realloc(s1, (len1 + delta + 1) * sizeof(*s1));
		if (!s1) error();

		for (i = len1 + delta; i >= start + 2 + delta; i--) {
			s1[i] = s1[i - delta];
		}
		//s1[len1 + delta] = '\0';
		//strcpy(s1 + start, s2);
		for (i = 0; i < strlen(s2); i++) {
			s1[start + i] = s2[i];
		}
	}
	else {
		for (i = start + 2 + delta; i <= len1 + delta; i++) {
			s1[i] = s1[i - delta];
		}
		for (i = 0; i < strlen(s2); i++) {
			s1[start + i] = s2[i];
		}

		s1 = realloc(s1, (len1 + delta + 1) * sizeof(*s1));
		if (!s1) error();
	}

	return s1;
}

int main() {
	char *s = readLine(), *s2;
	while (find(s) >= 0) {
		s2 = readLine();
		s = insertString(s, s2);
		free(s2);
	}
	puts(s);
	free(s);
}