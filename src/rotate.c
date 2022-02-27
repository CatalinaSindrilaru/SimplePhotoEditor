// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "struct.h"
#include "swap.h"
#include "rotate.h"

// Functie ce roteste intreaga imagine cu 90 de grade la stanga
void rotate_all_image_left(double ***image, int *x1, int *x2, int *y1, int *y2,
						   int *lines, int *cols)
{
	// Aloc memorie pentru o matrice auxiliara
	double **rotated_image;
	rotated_image = (double **)malloc(*cols * sizeof(double *));
	if (!rotated_image) {
		fprintf(stderr, "Error\n");
		free(rotated_image);
		exit(-1);
	}
	for (int i = 0; i < *cols; i++) {
		rotated_image[i] = (double *)malloc(*lines * sizeof(double));
		if (!rotated_image[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(rotated_image[j]);
			free(rotated_image);
			exit(-1);
		}
	}

	// Retin matricea rotita la stanga in matricea auxiliara
	for (int i = 0; i < *cols; i++)
		for (int j = 0; j < *lines; j++)
			rotated_image[i][j] = (*image)[j][*cols - i - 1];

	// Eliberez memoria pentru matricea initiala
	for (int i = 0; i < *lines; i++)
		free((*image)[i]);
	free((*image));

	// Copiez noua matrice
	(*image) = rotated_image;

	// Inversez numarul de linii si de coloane
	swap(lines, cols);

	// Modific selectia pentru dimensiunile noii imagini
	*x1 = 0;
	*x2 = *cols;
	*y1 = 0;
	*y2 = *lines;
}

// Functie ce roteste intreaga imagine cu 90 de grade la dreapta
void rotate_all_image_right(double ***image, int *x1, int *x2, int *y1, int *y2,
							int *lines, int *cols)
{
	// Aloc memorie pentru o matrice auxiliara
	double **rotated_image;
	rotated_image = (double **)malloc(*cols * sizeof(double *));
	if (!rotated_image) {
		fprintf(stderr, "Error\n");
		free(rotated_image);
		exit(-1);
	}
	for (int i = 0; i < *cols; i++) {
		rotated_image[i] = (double *)malloc(*lines * sizeof(double));
		if (!rotated_image[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(rotated_image[j]);
			free(rotated_image);
			exit(-1);
		}
	}

	// Retin matricea rotita la dreapta in matricea auxiliara
	for (int i = 0; i < *cols; i++)
		for (int j = 0; j < *lines; j++)
			rotated_image[i][j] = (*image)[*lines - j - 1][i];

	// Eliberez memoria pentru matricea initiala
	for (int i = 0; i < *lines; i++)
		free((*image)[i]);
	free((*image));

	// Copiez noua matrice
	(*image) = rotated_image;

	// Inversez numarul de linii si de coloane
	swap(lines, cols);

	// Modific selectia pentru dimensiunile noii imagini
	*x1 = 0;
	*x2 = *cols;
	*y1 = 0;
	*y2 = *lines;
}

// Functie ce roteste la stanga cu 90 de grade selectia curenta
void rotate_section_left(double ***image, int *x1, int *x2, int *y1, int *y2)
{
	int number = *x2 - *x1; // numarul de linii/coloane al selectiei
	int l = 0, c = 0;
	// Aloc o matrice auxiliara in care stochez selectia curenta
	double **square;
	square = (double **)malloc(number * sizeof(double *));
	if (!square) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < number; i++) {
		square[i] = (double *)malloc(number * sizeof(double));
		if (!square[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(square[j]);
			free(square);
			exit(-1);
		}
	}

	for (int i = *y1; i < *y2; i++) {
		for (int j = *x1; j < *x2; j++) {
			square[l][c] = (*image)[i][j];
			c++;
		}
		l++;
		c = 0;
	}

	// Realizez rotirea la stanga a selectiei folosind matricea auxiliara
	l = 0;
	c = number - 1;
	for (int i = *y1; i < *y2; i++) {
		for (int j = *x1; j < *x2; j++) {
			(*image)[i][j] = square[l][c];
			l++;
		}
		l = 0;
		c--;
	}

	for (int i = 0; i < number; i++)
		free(square[i]);
	free(square);
}

// Functie ce roteste la dreapta cu 90 de grade selectia curenta
void rotate_section_right(double ***image, int *x1, int *x2, int *y1, int *y2)
{
	int number = *x2 - *x1; // numarul de linii/coloane al selectiei
	int l = 0, c = 0;
	// Aloc o matrice auxiliara in care stochez selectia curenta
	double **square;
	square = (double **)malloc(number * sizeof(double *));
	if (!square) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < number; i++) {
		square[i] = (double *)malloc(number * sizeof(double));
		if (!square[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(square[j]);
			free(square);
			exit(-1);
		}
	}

	for (int i = *y1; i < *y2; i++) {
		for (int j = *x1; j < *x2; j++) {
			square[l][c] = (*image)[i][j];
			c++;
		}
		l++;
		c = 0;
	}

	// Realizez rotirea la dreapta a selectiei folosind matricea auxiliara
	l = number - 1;
	c = 0;
	for (int i = *y1; i < *y2; i++) {
		for (int j = *x1; j < *x2; j++) {
			(*image)[i][j] = square[l][c];
			l--;
		}
		l = number - 1;
		c++;
	}
	for (int i = 0; i < number; i++)
		free(square[i]);
	free(square);
}

// Functie ce verifica daca un unghi se gaseste printre variantele permise
int verif_angle(int angle)
{
	if (angle == 0)
		return 1;
	if (abs(angle) == 90)
		return 1;
	if (abs(angle) == 180)
		return 1;
	if (abs(angle) == 270)
		return 1;
	if (abs(angle) == 360)
		return 1;
	return 0;
}

// Functie ce roteste o imagine in tonuri de gri/selectie dintr-o imagine in
// tonuri de gri cu un anumit grad la stanga sau la dreapta
void rotate_image(double ***image, color ***rgb_image, char *angle_string,
				  int *x1, int *x2, int *y1, int *y2, int *lines, int *cols)
{
	int angle;
	if (!(*image) && !(*rgb_image)) {
		printf("No image loaded\n");
		return;
	}
	//In cazul in care comanda ROTATE nu este insotita de un unghi
	if (strcmp(angle_string, "nothing") == 0) {
		printf("Invalid command\n");
		return;
	}

	angle = atoi(angle_string);

	if (verif_angle(angle) == 0) { // Daca unghiul nu are o valoare permisa
		printf("Unsupported rotation angle\n");
		return;
	}

	// Selectia curenta nu reprezinta intreaga imagine si nu este patratica
	if (*x1 != 0 || *y1 != 0 || *x2 != *cols || *y2 != *lines) {
		if (*x2 - *x1 != *y2 - *y1) {
			printf("The selection bust be square\n");
			return;
		}
	}

	//Pentru intreaga imagine
	if (*x1 == 0 && *y1 == 0 && *x2 == *cols && *y2 == *lines) {
		if (angle == -90)
			rotate_all_image_left(image, x1, x2, y1, y2, lines, cols);
		if (angle == -180) {
			rotate_all_image_left(image, x1, x2, y1, y2, lines, cols);
			rotate_all_image_left(image, x1, x2, y1, y2, lines, cols);
		}
		if (angle == -270) {
			rotate_all_image_left(image, x1, x2, y1, y2, lines, cols);
			rotate_all_image_left(image, x1, x2, y1, y2, lines, cols);
			rotate_all_image_left(image, x1, x2, y1, y2, lines, cols);
		}
		if (angle == 90)
			rotate_all_image_right(image, x1, x2, y1, y2, lines, cols);
		if (angle == 180) {
			rotate_all_image_right(image, x1, x2, y1, y2, lines, cols);
			rotate_all_image_right(image, x1, x2, y1, y2, lines, cols);
		}
		if (angle == 270) {
			rotate_all_image_right(image, x1, x2, y1, y2, lines, cols);
			rotate_all_image_right(image, x1, x2, y1, y2, lines, cols);
			rotate_all_image_right(image, x1, x2, y1, y2, lines, cols);
		}
	} else { // Pentru o anumita selectie patratica
		if (angle == -90)
			rotate_section_left(image, x1, x2, y1, y2);
		if (angle == -180) {
			rotate_section_left(image, x1, x2, y1, y2);
			rotate_section_left(image, x1, x2, y1, y2);
		}
		if (angle == -270) {
			rotate_section_left(image, x1, x2, y1, y2);
			rotate_section_left(image, x1, x2, y1, y2);
			rotate_section_left(image, x1, x2, y1, y2);
		}
		if (angle == 90)
			rotate_section_right(image, x1, x2, y1, y2);
		if (angle == 180) {
			rotate_section_right(image, x1, x2, y1, y2);
			rotate_section_right(image, x1, x2, y1, y2);
		}
		if (angle == 270) {
			rotate_section_right(image, x1, x2, y1, y2);
			rotate_section_right(image, x1, x2, y1, y2);
			rotate_section_right(image, x1, x2, y1, y2);
		}
	}

	printf("Rotated %d\n", angle);
}

// Functie ce roteste la stanga cu 90 de grade intreaga imagine color
void rotate_all_rgb_image_left(color ***rgb_image, int *x1, int *x2, int *y1,
							   int *y2, int *lines, int *cols)
{
	// Aloc memorie pentru o matrice auxiliara
	color **rotated_rgb_image;
	rotated_rgb_image = (color **)malloc(*cols * sizeof(color *));
	if (!rotated_rgb_image) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < *cols; i++) {
		rotated_rgb_image[i] = (color *)malloc(*lines * sizeof(color));
		if (!rotated_rgb_image[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(rotated_rgb_image[j]);
			free(rotated_rgb_image);
			exit(-1);
		}
	}

	// Stochez in matricea auxiliara matricea rotita la stanga
	for (int i = 0; i < *cols; i++)
		for (int j = 0; j < *lines; j++) {
			rotated_rgb_image[i][j].r = (*rgb_image)[j][*cols - i - 1].r;
			rotated_rgb_image[i][j].g = (*rgb_image)[j][*cols - i - 1].g;
			rotated_rgb_image[i][j].b = (*rgb_image)[j][*cols - i - 1].b;
		}

	// Eliberez memoria pentru matricea initiala
	for (int i = 0; i < *lines; i++)
		free((*rgb_image)[i]);
	free(*rgb_image);

	// Copiez matricea rotita
	(*rgb_image) = rotated_rgb_image;

	// Invers numarul de linii si de coloane
	swap(lines, cols);

	// Modific selectia pentru dimensiunile noii imagini
	*x1 = 0;
	*x2 = *cols;
	*y1 = 0;
	*y2 = *lines;
}

// Functie ce roteste la dreapta cu 90 de grade intreaga imagine color
void rotate_all_rgb_image_right(color ***rgb_image, int *x1, int *x2, int *y1,
								int *y2, int *lines, int *cols)
{
	// Aloc memorie pentru o matrice auxiliara
	color **rotated_rgb_image;
	rotated_rgb_image = (color **)malloc(*cols * sizeof(color *));
	if (!rotated_rgb_image) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < *cols; i++) {
		rotated_rgb_image[i] = (color *)malloc(*lines * sizeof(color));
		if (!rotated_rgb_image[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(rotated_rgb_image[j]);
			free(rotated_rgb_image);
			exit(-1);
		}
	}

	// Stochez in matricea auxiliara matricea rotita la dreapta
	for (int i = 0; i < *cols; i++)
		for (int j = 0; j < *lines; j++) {
			rotated_rgb_image[i][j].r = (*rgb_image)[*lines - j - 1][i].r;
			rotated_rgb_image[i][j].g = (*rgb_image)[*lines - j - 1][i].g;
			rotated_rgb_image[i][j].b = (*rgb_image)[*lines - j - 1][i].b;
		}

	// Eliberez memoria pentru matricea initiala
	for (int i = 0; i < *lines; i++)
		free((*rgb_image)[i]);
	free(*rgb_image);

	// Copiez matricea rotita
	(*rgb_image) = rotated_rgb_image;

	// Invers numarul de linii si de coloane
	swap(lines, cols);

	// Modific selectia pentru dimensiunile noii imagini
	*x1 = 0;
	*x2 = *cols;
	*y1 = 0;
	*y2 = *lines;
}

// Functie ce roteste la stanga cu 90 de grade selectia curenta dintr-o
// imagine color
void rotate_rgb_section_left(color ***rgb_image, int *x1, int *x2, int *y1,
							 int *y2)
{
	int number = *x2 - *x1; // numarul de linii/coloane al selectiei
	int l = 0, c = 0;

	// Aloc o matrice auxiliara in care stochez selectia curenta
	color **square;
	square = (color **)malloc(number * sizeof(color *));
	if (!square) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < number; i++) {
		square[i] = (color *)malloc(number * sizeof(color));
		if (!square[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(square[j]);
			free(square);
			exit(-1);
		}
	}

	for (int i = *y1; i < *y2; i++) {
		for (int j = *x1; j < *x2; j++) {
			square[l][c].r = (*rgb_image)[i][j].r;
			square[l][c].g = (*rgb_image)[i][j].g;
			square[l][c].b = (*rgb_image)[i][j].b;
			c++;
		}
		l++;
		c = 0;
	}

	// Realizez rotirea la stanga a selectiei folosind matricea auxiliara
	l = 0;
	c = number - 1;
	for (int i = *y1; i < *y2; i++) {
		for (int j = *x1; j < *x2; j++) {
			(*rgb_image)[i][j].r = square[l][c].r;
			(*rgb_image)[i][j].g = square[l][c].g;
			(*rgb_image)[i][j].b = square[l][c].b;
			l++;
		}
		l = 0;
		c--;
	}

	for (int i = 0; i < number; i++)
		free(square[i]);
	free(square);
}

// Functie ce roteste la dreapta cu 90 de grade selectia curenta dintr-o
// imagine color
void rotate_rgb_section_right(color ***rgb_image, int *x1, int *x2, int *y1,
							  int *y2)
{
	int number = *x2 - *x1; //numarul de linii/coloane al selectiei
	int l = 0, c = 0;
	// Aloc o matrice auxiliara in care stochez selectia curenta
	color **square;
	square = (color **)malloc(number * sizeof(color *));
	if (!square) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < number; i++) {
		square[i] = (color *)malloc(number * sizeof(color));
		if (!square[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(square[j]);
			free(square);
			exit(-1);
		}
	}

	for (int i = *y1; i < *y2; i++) {
		for (int j = *x1; j < *x2; j++) {
			square[l][c].r = (*rgb_image)[i][j].r;
			square[l][c].g = (*rgb_image)[i][j].g;
			square[l][c].b = (*rgb_image)[i][j].b;
			c++;
		}
		l++;
		c = 0;
	}

	// Realizez rotirea la dreapta a selectiei folosind matricea auxiliara
	l = number - 1;
	c = 0;
	for (int i = *y1; i < *y2; i++) {
		for (int j = *x1; j < *x2; j++) {
			(*rgb_image)[i][j].r = square[l][c].r;
			(*rgb_image)[i][j].g = square[l][c].g;
			(*rgb_image)[i][j].b = square[l][c].b;
			l--;
		}
		l = number - 1;
		c++;
	}
	for (int i = 0; i < number; i++)
		free(square[i]);
	free(square);
}

// Functie ce roteste o imagine color/selectie dintr-o imagine color cu un
// anumit grad la stanga sau la dreapta
void rotate_rgb_image(color ***rgb_image, char *angle_string, int *x1, int *x2,
					  int *y1, int *y2, int *lines, int *cols)
{
	int angle;
	if (!(*rgb_image)) {
		printf("No image loaded\n");
		return;
	}
	// Daca ROTATE nu are argument
	if (strcmp(angle_string, "nothing") == 0) {
		printf("Invalid command\n");
		return;
	}

	angle = atoi(angle_string);

	if (verif_angle(angle) == 0) { // daca unghiul nu are o valoarea permisa
		printf("Unsupported rotation angle\n");
		return;
	}

	// Selectia curenta nu reprezinta intreaga imagine si nu este patratica
	if (*x1 != 0 || *y1 != 0 || *x2 != *cols || *y2 != *lines) {
		if (*x2 - *x1 != *y2 - *y1) {
			printf("The selection bust be square\n");
			return;
		}
	}

	// Pentru intreaga imagine
	if (*x1 == 0 && *y1 == 0 && *x2 == *cols && *y2 == *lines) {
		if (angle == -90)
			rotate_all_rgb_image_left(rgb_image, x1, x2, y1, y2, lines, cols);
		if (angle == -180) {
			rotate_all_rgb_image_left(rgb_image, x1, x2, y1, y2, lines, cols);
			rotate_all_rgb_image_left(rgb_image, x1, x2, y1, y2, lines, cols);
		}
		if (angle == -270) {
			rotate_all_rgb_image_left(rgb_image, x1, x2, y1, y2, lines, cols);
			rotate_all_rgb_image_left(rgb_image, x1, x2, y1, y2, lines, cols);
			rotate_all_rgb_image_left(rgb_image, x1, x2, y1, y2, lines, cols);
		}
		if (angle == 90)
			rotate_all_rgb_image_right(rgb_image, x1, x2, y1, y2, lines, cols);
		if (angle == 180) {
			rotate_all_rgb_image_right(rgb_image, x1, x2, y1, y2, lines, cols);
			rotate_all_rgb_image_right(rgb_image, x1, x2, y1, y2, lines, cols);
		}
		if (angle == 270) {
			rotate_all_rgb_image_right(rgb_image, x1, x2, y1, y2, lines, cols);
			rotate_all_rgb_image_right(rgb_image, x1, x2, y1, y2, lines, cols);
			rotate_all_rgb_image_right(rgb_image, x1, x2, y1, y2, lines, cols);
		}
	} else { // Pentru o selectie din imagine
		if (angle == -90)
			rotate_rgb_section_left(rgb_image, x1, x2, y1, y2);
		if (angle == -180) {
			rotate_rgb_section_left(rgb_image, x1, x2, y1, y2);
			rotate_rgb_section_left(rgb_image, x1, x2, y1, y2);
		}
		if (angle == -270) {
			rotate_rgb_section_left(rgb_image, x1, x2, y1, y2);
			rotate_rgb_section_left(rgb_image, x1, x2, y1, y2);
			rotate_rgb_section_left(rgb_image, x1, x2, y1, y2);
		}
		if (angle == 90)
			rotate_rgb_section_right(rgb_image, x1, x2, y1, y2);
		if (angle == 180) {
			rotate_rgb_section_right(rgb_image, x1, x2, y1, y2);
			rotate_rgb_section_right(rgb_image, x1, x2, y1, y2);
		}
		if (angle == 270) {
			rotate_rgb_section_right(rgb_image, x1, x2, y1, y2);
			rotate_rgb_section_right(rgb_image, x1, x2, y1, y2);
			rotate_rgb_section_right(rgb_image, x1, x2, y1, y2);
		}
	}
	printf("Rotated %d\n", angle);
}
