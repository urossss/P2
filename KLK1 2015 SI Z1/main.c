/*
	Napisati program na programskom jeziku C koji pretražuje binarnu predstavu broja radi pronalaženja
	svih pojava zadate binarne sekvence. Program treba sa standardnog ulaza da učita dva broja tipa
	unsigned int (pretpostaviti da je veličina tipa 16 bita). Prvo se učitava broj koji se pretražuje.
	Iz binarne predstave drugog učitanog broja izdvaja se deo između binarnih jedinica najmanje i najveće
	težine (uključujući i njih), pa to predstavlja sekvencu koja se traži. Pretraživanje se vrši počevši
	od cifre najveće težine. Program treba da ispiše sve početne pozicije u prvom broju gde je nađen
	zadati sadržaj (pozicija najveće težine je 15). Na primer neka je prvi broj 0x5B5A, a drugi broj 0x0168.
	Pozicije koje treba ispisati su: 14, 11 i 6.
	(1. kolokvijum 2015, SI, 1. zadatak)
*/

#include <stdio.h>

#define SIZE 16

int main() {
	unsigned int a, b;
	int n = 0, i, j, m1, m2;

	scanf("%x %x", &a, &b);

	if (b == 0) return 1;

	while (!(b & 1)) b >>= 1;			// pomeramo b tako da je '1' najnize tezine na 0. poziciji
	while (!((b << n) & 0x8000)) n++;	// brojimo koliko ima cifara u broju b izmedju prve i poslednje '1', ukljucujuci i njih
	n = 16 - n;							// n je broj bitova iz broju b koje trazimo u broju a

	for (i = 0; i <= SIZE - n; i++) {
		m1 = 1 << i;					// maska za izdvajanje bita iz broja a
		m2 = 1;							// maska za izdvajanje bita iz broja b
		for (j = 0; j < n; j++) {
			if (((a & m1) != 0) != ((b & m2) != 0)) break;
			m1 <<= 1;
			m2 <<= 1;
		}
		if (j == n) printf("%d\n", i + n - 1);
	}
}