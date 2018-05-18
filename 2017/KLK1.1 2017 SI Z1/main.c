/*
	Napisati program na programskom jeziku C koji međusobno zamenjuje grupu bitova od pozicije X
	do pozicije Y u svakom paru susednih elemenata niza, sa parnim indeksom k i neparnim indeksom
	k+1. Brojevi čiji se bitovi zamenjuju se učitavaju sa standardnog ulaza u niz tipa unsigned int
	(veličina tipa je 32 bita). Broj elemenata niza je paran i iznosi maksimalno 100, a unosi se pre samog
	niza sa standardnog ulaza. Program treba da na pseudoslučajan način odabere brojeve X i Y, čije
	vrednosti mogu biti od 0 do 31 (Y≥X). Za manipulaciju sa bitovima je potrebno koristiti bitske
	operatore, a nije dozvoljeno koristiti aritmetičke operacije (%, /, stepenovanje, itd...) i dodatne
	nizove. Nakon obrade na standardnom izlazu potrebno je ispisati X i Y i sve elemente niza nakon
	izvršene obrade.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int main() {
	unsigned int arr[MAX], m1 = 0xffffffff, m2, ma, mb;
	int n, i, x, y;

	scanf("%d", &n);
	if (n <= 0 || n > MAX || (n & 1)) return 1;

	for (i = 0; i < n; i++) scanf("%x", &arr[i]);	// ucitavamo u hexa obliku jer je lakse ispratiti sta se desava

	srand(time(NULL));
	x = rand() / (RAND_MAX + 1.) * 32;
	y = rand() / (RAND_MAX + 1.) * 32;
	if (x > y) {
		int t = x;
		x = y;
		y = t;
	}

	m1 >>= 31 - y + x;
	m1 <<= x;		// m1 ima '1' na pozicijama od x do y (ovim koje treba zameniti)
	m2 = ~m1;		// m2 ima '0' na tim pozicijama, a '1' na ostalim

	for (i = 0; i < n; i += 2) {
		ma = arr[i] & m1;		// izdvajamo bitove koje treba zameniti, iz prvog broja
		mb = arr[i + 1] & m1;	// i iz drugog

		arr[i] &= m2;			// postavljamo te bitove na '0'
		arr[i + 1] &= m2;

		arr[i] |= mb;			// i tu ubacujemo izdvojene bitove iz drugog broja
		arr[i + 1] |= ma;
	}

	printf("x y = %d %d\n", x, y);

	for (i = 0; i < n; printf("%#x ", arr[i++]));	// ispis takodje u hexa formatu
	putchar('\n');
}