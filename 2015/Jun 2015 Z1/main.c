/*
	1)Napisati program na programskom jeziku C koji vrši obradu nad poverljivim tekstom. Poverljiv tekst se unosi
	sa standardnog ulaza i završava se praznom linijom. Tekst se sastoji od šifrovanih reči i običnih reči. Reči u
	tekstu su odvojene po jednim blanko znakom. Šifrovana reč ima sledeći format: počinje velikim slovom, zatim
	ide znak @, niz cifara proizvoljne dužine i na kraju se nalazi veliko slovo. Obične reči su sve ostale reči.
	Napisati potprogram koji za zadatu reč proverava da li je šifrovana. Napisati glavni program koji čita poverljiv
	tekst sa standardnog ulaza, koristeći traženi potprogram izbacuje sve šifrovane reči i na standardni izlaz
	ispisuje rezultujući tekst. Na kraju program treba da ispiše i procenat šifrovanih reči u učitanom poverljivom
	tekstu. Maksimalna dužina reči nije poznata. Voditi računa o pravilnom rukovanju korišćenim resursima.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CHUNK 10

typedef struct elem {
	char *s;
	struct elem *next;
} Elem;

char *readWord() {
	int len = 0, n = 1;
	char *s = malloc(CHUNK + 1), c;
	if (!s) exit(1);
	while (1) {
		c = getchar();
		if (c == ' ' || c == '\n') break;
		if (n == CHUNK) {
			s = realloc(s, len + CHUNK + 1);
			if (!s) exit(1);
			n = 0;
		}
		s[len++] = c;
		n++;
	}
	s = realloc(s, len + 1);
	if (!s) exit(1);
	s[len] = '\0';
	return s;
}

int isCoded(char *s) {
	const int len = strlen(s);
	int i = 0;
	for (i = 0; i < len - 1; i++) {
		switch (i) {
		case 0:
			if (!isupper(s[i])) return 0;
			break;
		case 1:
			if (s[i] != '@') return 0;
			break;
		default:
			if (!isdigit(s[i])) return 0;
			break;
		}
	}
	return isupper(s[i]);
}

Elem *removeCoded(Elem *lst, int *n) {
	Elem *curr = lst, *prev = NULL, *old;
	while (curr) {
		if (isCoded(curr->s)) {
			old = curr;
			curr = curr->next;
			if (!prev) lst = curr;
			else prev->next = curr;
			prev = curr;
			free(old->s);
			free(old);
			(*n)--;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
	return lst;
}

void printList(Elem *lst) {
	while (lst) {
		puts(lst->s);
		lst = lst->next;
	}
}

void deleteList(Elem *lst) {
	Elem *old;
	while (lst) {
		old = lst;
		lst = lst->next;
		free(old);
	}
}

int main() {
	char *s;
	int n1 = 0, n2;
	Elem *lst = NULL, *newElem, *last = NULL;

	while (1) {
		s = readWord();
		if (!strcmp(s, "")) break;
		n1++;
		newElem = malloc(sizeof(Elem));
		if (!newElem) exit(1);
		newElem->s = s;
		newElem->next = NULL;
		if (!last) lst = newElem;
		else last->next = newElem;
		last = newElem;
	}

	//printList(lst);
	n2 = n1;
	lst = removeCoded(lst, &n2);

	printList(lst);

	printf("%lg%%\n", 100. * (n1 - n2) / n1);

	deleteList(lst);
}