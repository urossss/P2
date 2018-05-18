#include <stdio.h>
#define MAX 100

int main() {
	int a[MAX], n = 0, i, j, x;
	while (n < MAX) {
		scanf("%d", &x);
		if (x <= 0) break;

		for (i = 0; i < n; i++) if (a[i] == x) break;
		if (i != n) continue;

		for (i = n - 1; i >= 0 && a[i] < x; i--) a[i + 1] = a[i];
		a[i + 1] = x;

		n++;
	}
	for (i = 0; i < n; i++) printf("%d ", a[i]);
	putchar('\n');
}