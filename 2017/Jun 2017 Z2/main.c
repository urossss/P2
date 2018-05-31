/*
	2)Napisati program na programskom jeziku C koji razvrstava đake osnovnih škola u željene srednje škole. U
	svakom redu datoteke skole.txt se nalaze informacije o srednjoj školi u sledećem formatu: broj slobodnih
	mesta (ceo broj), naziv skole (niz znakova, koji može sadržati blanko znake, od najviše 30 karaktera). Svakoj
	školi se dodeljuje redni broj koji odgovara rednom broju linije teksta u kojem se škola nalazi. Redni brojevi
	škola počinju od 0. U datoteci ima podataka o najviše 400 škola. U binarnoj datoteci zelje.pod svaki zapis
	sadrži: prijavni broj đaka (ceo broj), ime i prezime đaka (dužine tačno 30 karaktera), prosečnu ocenu (realan
	broj) i redni broj srednje škole koju đak želi da upiše. Prijavni brojevi đaka su jedinstveni. Program treba da
	učita podatke o školama i đacima, zatim da formira tekstualnu datoteku upisi.txt koja će za svakog đaka
	sadržati podatke o dodeljenoj srednjoj školi. Jedan red datoteke treba da ima sledeći format: prijavni broj
	đaka, me i prezime đaka, prosečna ocena, naziv škole. Ako nema mesta u školi koju je đak naveo kao želju,
	umesto upisane škole upisati NEUPISAN. Đaci sa višom prosečnom ocenom imaju veći prioritet pri
	raspoređivanju. Prednost prilikom upisa đaka sa istim prosekom imaju oni sa nižim prijavnim brojem. Voditi
	računa o ispravnoj upotrebi resursa.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int prijava;
	char ime[31];
	double prosek;
	int skola;
} Student;

typedef struct elem {
	Student *s;
	struct elem *sled;
} Elem;

typedef struct {
	int mesta;
	char ime[31];
} School;

int readSchools(FILE *in, School skole[400]) {
	School s;
	int i = 0;
	while (fscanf(in, "%d %[^\n]\n", &s.mesta, s.ime) != EOF)
		skole[i++] = s;
	return i;
}

void printSchools(School skole[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d %s\n", skole[i].mesta, skole[i].ime);
	}
}

Elem *readStudents(FILE *in) {
	Elem *lst = NULL, *novi, *tek, *pret;
	Student *s = malloc(sizeof(Student));
	if (!s) exit(2);
	while (fread(s, sizeof(Student), 1, in) == 1) {
		//printf("%d %s %lf %d\n", s->prijava, s->ime, s->prosek, s->skola);
		tek = lst;
		pret = NULL;
		while (tek && tek->s->prosek > s->prosek) {
			pret = tek;
			tek = tek->sled;
		}
		if (tek && tek->s->prosek == s->prosek) {
			while (tek && tek->s->prosek == s->prosek && tek->s->prijava < s->prijava) {
				pret = tek;
				tek = tek->sled;
			}
		}
		novi = malloc(sizeof(Elem));
		if (!novi) exit(2);
		novi->s = s;
		novi->sled = tek;
		if (!pret) lst = novi;
		else pret->sled = novi;

		s = malloc(sizeof(Student));
		if (!s) exit(2);
	}
	return lst;
}

void printStudents(Elem *lst) {
	while (lst) {
		printf("%d %s %lf %d\n", lst->s->prijava, lst->s->ime, lst->s->prosek, lst->s->skola);
		lst = lst->sled;
	}
}

void deleteStudents(Elem *lst) {
	Elem *stari;
	while (lst) {
		stari = lst;
		lst = lst->sled;
		free(stari);
	}
}

void assignSchools(FILE *out, Elem *lst, School skole[]) {
	while (lst) {
		if (skole[lst->s->skola].mesta > 0) {
			fprintf(out, "%d %s %lf %s\n", lst->s->prijava, lst->s->ime, lst->s->prosek, skole[lst->s->skola].ime);
			skole[lst->s->skola].mesta--;
		} else
			fprintf(out, "%d %s %lf %s\n", lst->s->prijava, lst->s->ime, lst->s->prosek, "NEUPISAN");
		lst = lst->sled;
	}
}

int main() {
	FILE *skole_ulaz = fopen("skole.txt", "r");
	FILE *zelje = fopen("zelje.pod", "r");
	FILE *upisi = fopen("upisi.txt", "w");
	if (!skole_ulaz || !zelje || !upisi) exit(1);

	School skole[400];
	int n;
	n = readSchools(skole_ulaz, skole);
	//printSchools(skole, n);

	Elem *lst = readStudents(zelje);
	//printStudents(lst);

	assignSchools(upisi, lst, skole);

	deleteStudents(lst);

	fclose(skole_ulaz);
	fclose(zelje);
	fclose(upisi);
}