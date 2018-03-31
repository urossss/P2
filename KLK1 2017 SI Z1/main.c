/*
	Napisati program na programskom jeziku C koji vrši konverziju realnog broja iz binarnog u decimalni oblik.
	Realan broj u binarnom brojnom sistemu se zadaje kao niz znakova koji može sadržati samo cifre 0, 1 i
	eventualnu decimalnu tačku. Program treba da učita niz znakova sa standardnog ulaza do kraja tekućeg reda,
	izvrši konverziju zadatog broja u odgovarajući realni tip programskog jezika C i ispiše rezultat u decimalnom
	brojnom sistemu. Prlikom učitavanja, obezbediti da korisnik unosi samo dozvoljene znakove, a u slučaju
	unošenja nedozvoljenog znaka zahtevati ponovni unos. Smatrati da niz znakova nije duži od 50 elemenata i
	obezbediti prekid unosa, ukoliko korisnik pokuša da unese više znakova.
*/

#include <stdio.h>

#define MAX 50

int main() {
	char broj[MAX], c;
	int i, n, err;
	double ceo_deo, realan_deo, rez;

	while (1) {
		err = 0;
		ceo_deo = realan_deo = 0;

		printf("Realan broj u binarnom obliku: ");

		n = 0;
		while ((c = getchar()) != '\n' && n < MAX) {
			if (c != '0' && c != '1' && c != '.') {
				err = 1;
				while (getchar() != '\n');		// kada se naidje na pogresan karakter, odmah se pamti greska, ali treba procitati sva 
												// slova do kraja reda da ih ne bismo u narednim iteracijama ucitavali
				break;
			}
			broj[n++] = c;
		}
		if (err) continue;
		if (n >= MAX) break;

		i = 0;
		if (broj[i] != '.') {
			ceo_deo = broj[i] - '0';
			while (++i < n && broj[i] != '.') {
				ceo_deo = ceo_deo * 2 + broj[i] - '0';
			}
		}
		if (i < n) {
			while (i < --n) {
				realan_deo = (realan_deo + broj[n] - '0') / 2;
			}
		}

		rez = ceo_deo + realan_deo;
		printf("%.10lg\n", rez);
	}
}