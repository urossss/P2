#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* readLine() {
	char *s = NULL, c;
	int n = 1;
	while ((c = getchar()) != '\n') {
		s = realloc(s, (++n) * sizeof(*s));
		*(s + n - 2) = c;
	}
	if (s == NULL) return s;
	*(s + n - 1) = '\0';
	return s;
}



int main() {
	char **str, *s;

	s = readLine();
	puts(s);

	free(s);
}