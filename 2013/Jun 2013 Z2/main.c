/*
	2)Napisati program na programskom jeziku C koji vrši određenu obradu nad tekst datotekom koja predstavlja
	plejlistu muzičkih numera. Svaki red ulazne i izlazne datoteke sadrži podatke o jednoj muzičkoj numeri po
	sledećem formatu: naziv numere (najviše 255 znakova i može sadržati blanko znake) i trajanje numere u
	formatu mm:ss, gde su mm minuti, a ss sekunde. Program treba da pročita ulaznu datoteku i formira
	jednostruko ulančanu listu muzičkih numera, a zatim učita jedan ceo broj length koji predstavlja dužinu nove
	plejliste u sekundama. Program treba da na osnovu učitanih podataka formira novu plejlistu čije ukupno
	trajanje neće biti duže od zadate dužine length. Novu plejlistu formirati tako da u nju stane što više numera.
	Imena ulazne i izlazne datoteke se zadaju kao prvi i drugi argument komandne linije. Voditi računa o korektnoj
	upotrebi zauzetih resursa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char title[256];
	int length;
} Song;

typedef struct elem {
	Song *s;
	struct elem *next;
} Elem;

void error(int e) {
	switch (e) {
	case 1:
		printf("Not enough command line arguments!\n");
		break;
	case 2:
		printf("Error opening files!\n");
		break;
	case 3:
		printf("Error in allocation!\n");
		break;
	}
	exit(e);
}

Elem* loadSongs(FILE *in) {
	Elem *lst = NULL, *novi, *tek, *pret;
	Song *s;
	char title[256];
	int min, sec;
	while (fscanf(in, "%[^0-9]%d:%d\n", title, &min, &sec) != EOF) {
		s = malloc(sizeof(Song));
		if (!s) error(3);
		strncpy(s->title, title, strlen(title) - 1);
		s->title[strlen(title) - 1] = '\0';
		s->length = min * 60 + sec;
		novi = malloc(sizeof(Elem));
		if (!novi) error(3);
		novi->s = s;

		tek = lst;
		pret = NULL;
		while (tek && tek->s->length < s->length) {
			pret = tek;
			tek = tek->next;
		}
		if (!pret) lst = novi;
		else pret->next = novi;
		novi->next = tek;
	}
	return lst;
}

void loadNewPlaylist(FILE *out, Elem *lst) {
	int length;
	printf("Unesite duzinu nove plejliste: ");
	scanf("%d", &length);

	while (lst) {
		if (length < lst->s->length) break;
		fprintf(out, "%s %02d:%02d\n", lst->s->title, lst->s->length / 60, lst->s->length % 60);
		length -= lst->s->length;
		lst = lst->next;
	}
}

void deleteList(Elem *lst) {
	Elem *old;
	while (lst) {
		old = lst;
		lst = lst->next;
		free(old->s);
		free(old);
	}
}

int main(int argc, char *argv[]) {

	if (argc < 3) error(1);

	FILE *in, *out;
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (!in || !out) error(2);

	Elem *lst = loadSongs(in);

	loadNewPlaylist(out, lst);

	deleteList(lst);

	fclose(in);
	fclose(out);
}