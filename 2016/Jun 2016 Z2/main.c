/*
	2)U svakom redu datoteke korisnici.txt zapisani su podaci o jednom korisniku u formatu: korisničko ime i e-
	mail adresa, razdvojeni jednim blanko znakom. Korisničko ime, kao i e-mail adresa su jedinstveni podaci i 
	pojavljuju se u najviše jednom redu. U svakom redu datoteke log.txt nalaze se podaci o istoriji prijavljivanja i 
	odjavljivanja korisnika na sistem u formatu: e-mail, akcija, vreme. Akcija može imati oznaku „p“ ili „o“ (p –
	prijava, o – odjava), dok je vreme ceo broj i predstavlja trenutak u kome se akcija izvršila. Jedan korisnik se 
	može više puta prijaviti i odjaviti sa sistema. Napisati potprogram koji formira listu korisnika tako što u listu 
	dodaje svakog pročitanog korisnika iz datoteke korisnici.txt. Zatim napisati potprogram za učitavanje 
	podataka iz datoteke log.txt i ažuriranje liste na osnovu e-mail adrese, tako da na kraju rada potprograma za 
	svakog korisnika bude izračunato ukupno vreme koje je proveo prijavljen na sistem (za potrebe računanja u 
	listi je dozvoljeno čuvati i druge podatke). Smatrati da je datoteka log.txt ispravna i da su svi korisnici 
	odjavljeni sa sistema. Koristeći implementirane potprograme napisati program koji ispisuje ime korisnika koji 
	je bio najviše vremena prijavljen na sistem. Ukoliko ima više takvih korisnika, dovoljno je ispisati jednog od 
	njih. Voditi računa o korektnoj upotrebi resursa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 10

typedef struct {
	char *username, *email;
	int time;
} User;

typedef struct elem {
	User *user;
	struct elem *next;
} Elem;

void error(int e) {
	switch (e) {
	case 1:
		fprintf(stderr, "Error opening files!\n");
		break;
	case 2:
		fprintf(stderr, "Error in allocation!\n");
		break;
	}
	exit(e);
}

char *readWord(FILE *in) {
	char *s = malloc(CHUNK), c;
	if (!s) error(2);
	int len = 0, n = 0;
	while ((c = fgetc(in)) != EOF) {
		if (c == ' ' || c == '\n') break;
		if (n == CHUNK) {
			s = realloc(s, (len + CHUNK));
			if (!s) error(2);
			n = 0;
		}
		s[len] = c;
		len++;
		n++;
	}
	if (!len) return NULL;
	if (n == CHUNK) {
		s = realloc(s, (len + 1));
		if (!s) error(2);
		n = 0;
	}
	s[len++] = '\0';
	if (len % CHUNK) {
		s = realloc(s, (len + 1));
		if (!s) error(2);
	}
	return s;
}

Elem *loadList(FILE *in) {
	Elem *lst = NULL, *newElem;
	// dinamicko ucitavanje svih stringova
	char *s;
	while (1) {
		if (!(s = readWord(in))) break;
		newElem = malloc(sizeof(Elem));
		if (!newElem) error(2);
		newElem->user = malloc(sizeof(User));
		if (!newElem->user) error(2);
		newElem->user->username = s;
		newElem->user->email = readWord(in);
		newElem->user->time = 0;
		newElem->next = lst;
		lst = newElem;
	}
	/*// staticko ucitavanje pa onda samo krajnja realokacija
	char username[256], email[256];
	while (fscanf(in, "%s %s\n", username, email) != EOF) {
		newElem = malloc(sizeof(Elem));
		if (!newElem) error(2);
		newElem->user = malloc(sizeof(User));
		if (!newElem->user) error(2);
		newElem->user->username = malloc((strlen(username) + 1) * sizeof(char));
		strcpy(newElem->user->username, username);
		newElem->user->email = malloc((strlen(email) + 1) * sizeof(char));
		strcpy(newElem->user->email, email);
		newElem->user->time = 0;
		newElem->next = lst;
		lst = newElem;
	}*/
	return lst;
}

void printList(Elem *lst) {
	while (lst) {
		printf("%s %s %d\n", lst->user->username, lst->user->email, lst->user->time);
		lst = lst->next;
	}
}

void deleteList(Elem *lst) {
	Elem *old;
	while (lst) {
		old = lst;
		lst = lst->next;
		free(old->user->username);
		free(old->user->email);
		free(old);
	}
}

void readLog(FILE *log, Elem *lst) {
	Elem *curr;
	int time;
	// dinamicko citanje
	char *s, action;
	while (1) {
		if (!(s = readWord(log))) break;
		fscanf(log, "%c %d\n", &action, &time);
		curr = lst;
		while (curr) {
			if (!strcmp(curr->user->email, s)) {
				curr->user->time += action == 'p' ? -time : time;
				break;
			}
			curr = curr->next;
		}
	}
	/*// staticko citanje
	char email[256], action;
	while (fscanf(log, "%s %c %d\n", email, &action, &time) != EOF) {
		curr = lst;
		while (curr) {
			if (!strcmp(curr->user->email, email)) {
				curr->user->time += action == 'p' ? -time : time;
				break;
			}
			curr = curr->next;
		}
	}*/
}

void printMax(Elem *lst) {
	Elem *max = lst;
	while (lst) {
		if (lst->user->time > max->user->time)
			max = lst;
		lst = lst->next;
	}
	if (max) puts(max->user->username);
}

int main() {
	FILE *users = fopen("korisnici.txt", "r");
	FILE *log = fopen("log.txt", "r");
	if (!users || !log) error(1);

	Elem *lst = loadList(users);
	//printList(lst);
	readLog(log, lst);
	//printList(lst);
	printMax(lst);

	deleteList(lst);

	fclose(users);
	fclose(log);
}