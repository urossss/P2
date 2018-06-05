/*
	1)Napisati potprogram na programskom jeziku C koji pronalazi dve međusobno najudaljenije tačke u prostoru.
	Kao ulazni argument, potprogram dobija niz tačaka koji treba da obradi i njegovu dužinu, a vraća pozicije
	tačaka u nizu koje zadovoljavaju traženi uslov, kao i njihovu razdaljinu. Ukoliko postoji više tačaka koje
	zadovoljavaju traženi uslovi, vratiti prvi par na koji se naiđe. Svaka tačka je predstavljena realnim x, y i z
	koordinatama u Dekartovom koordinatnom sistemu. Napisati program na programskom jeziku C koji učita
	tačke sa standardnog ulaza u dinamički alocirani niz tačaka, pozove realizovani potprogram za računanje
	razdaljine i ispiše dobijene rezultate. Potprogram sa glavnim programom treba da komunicira isključivo
	pomoću argumenata i povratne vrednosti.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	double x, y, z;
} Point;

typedef struct {
	int p1, p2;
	double distance;
} Res;

Point* loadPoints(int *n) {
	printf("Unesite broj tacaka: ");
	scanf("%d", n);
	Point *arr = malloc(*n * sizeof(Point));
	if (!arr) exit(1);
	for (int i = 0; i < *n; i++) {
		scanf("%lf%lf%lf", &(arr + i)->x, &(arr + i)->y, &(arr + i)->z);
	}
	return arr;
}

void printPoints(Point *arr, int n) {
	for (int i = 0; i < n; i++)
		printf("(%lf, %lf, %lf)\n", arr[i].x, arr[i].y, arr[i].z);
}

double distance(Point p1, Point p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

Res furthestPoints(Point *points, int n) {	// O(n^2)
	Res r = { 0, 0, 0 };
	double d;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			d = distance(points[i], points[j]);
			if (d > r.distance) {
				r.p1 = i;
				r.p2 = j;
				r.distance = d;
			}
		}
	return r;
}

int main() {
	int n;
	Point *points = loadPoints(&n);
	printPoints(points, n);
	Res r = furthestPoints(points, n);
	printf("Najudaljenije tacke su (%lg, %lg, %lg) i (%lg, %lg, %lg), sa rastojanjem %lg\n",
		points[r.p1].x, points[r.p1].y, points[r.p1].z,
		points[r.p2].x, points[r.p2].y, points[r.p2].z, r.distance);
}
