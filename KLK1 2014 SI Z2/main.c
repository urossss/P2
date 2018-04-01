/*	
	Napisati program na programskom jeziku C koji sa standardnog ulaza učitava ceo broj tipa
	unsigned int(pretpostaviti da je za smeštanje jednog podatka tog tipa potrebno 16 bita), a
	potom proverava da li je bitska reprezentacija tog broja, posmatrana od bita najveće težine ka bitu
	najmanje težine, komplementarna u odnosu na bitsku reprezentaciju posmatranu od bita namanje
	težine ka bitu najveće težine.U slučaju da jeste, na standardnom izlazu treba ispisati poruku “DA“, u
	suprotnom poruku “NE“.Pimer: binarna reprezentacija broja 48322 je 1011110011000010, pa se
	ispisuje poruka “DA“.
	(1. kolokvijum 2014, SI, 2. zadatak)
 */

#include <stdio.h>

int main() {
	unsigned int a, lmask = 0x8000, dmask = 0x0001;
	int i;

	scanf("%u", &a);

	for (i = 0; i < 8; i++) {
		if (((a & lmask) && (a & dmask)) || (!(a & lmask) && !(a & dmask))) break;	// ne smeju biti oba bita 0 ili oba bita 1
		lmask >>= 1;
		dmask <<= 1;
	}

	if (i == 8) printf("DA\n");
	else printf("NE\n");
}