/* Od tekstualne datoteke 'zelje.txt' pravi binarnu 'zelje.dat'. */

#include <stdio.h>
#include <string.h>

typedef struct {
	int prijava;
	char ime[31];
	double prosek;
	int skola;
} Student;

int main() {
	FILE *in = fopen("zelje.txt", "r");
	FILE *out = fopen("..\\Jun 2017 Z2\\zelje.pod", "w");

	Student s;
	while (fscanf(in, "%d %[^0-9]%lf %d\n", &s.prijava, s.ime, &s.prosek, &s.skola) != EOF) {
		s.ime[strlen(s.ime) - 1] = '\0';
		//printf("%d %s %lf %d\n", s.prijava, s.ime, s.prosek, s.skola);
		fwrite(&s, sizeof(Student), 1, out);
	}

	fclose(in);
	fclose(out);
}