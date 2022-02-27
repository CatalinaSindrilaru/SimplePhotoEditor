// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "select.h"
#include "struct.h"
#include "swap.h"

// Stochez selectia citita, daca aceasta este valida
void select_coordinates(double **image, color **rgb_image, char *expression,
						int *x1, int *x2, int *y1, int *y2, int new_x1,
						int new_x2, int new_y1, int new_y2, int lines, int cols)
{
	if (!image && !rgb_image) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(expression, "nothing") == 0) {
		printf("Invalid command\n");
		return;
	}

	if (new_x2 == new_x1 && new_y1 == new_x1 && new_y2 == new_x1) {
		printf("Invalid set of coordinates\n");
		return;
	}

	if (new_x1 == new_x2 || new_y1 == new_y2) {
		printf("Invalid set of coordinates\n");
		return;
	}

	if (new_x1 < 0 || new_x2 < 0 || new_y1 < 0 || new_y2 < 0) {
		printf("Invalid set of coordinates\n");
		return;
	}

	if (new_x1 > cols || new_x2 > cols || new_y1 > lines || new_y2 > lines) {
		printf("Invalid set of coordinates\n");
		return;
	}

	if (new_x1 > new_x2)
		swap(&new_x1, &new_x2);
	if (new_y1 > new_y2)
		swap(&new_y1, &new_y2);

	printf("Selected %d %d %d %d\n", new_x1, new_y1, new_x2, new_y2);

	*x1 = new_x1;
	*x2 = new_x2;
	*y1 = new_y1;
	*y2 = new_y2;
}

// Functie ce selecteaza toata imaginea in cazul in care argumentul citit
// a fost "ALL"
void select_all(double **image, color **rgb_image, int *x1, int *x2, int *y1,
				int *y2, int lines, int cols)
{
	if (!image && !rgb_image) {
		printf("No image loaded\n");
		return;
	}

	*x1 = 0;
	*x2 = cols;
	*y1 = 0;
	*y2 = lines;

	printf("Selected ALL\n");
}
