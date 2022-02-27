// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "struct.h"
#include "apply.h"

// Functie ce rastrange o valoare la intervalul 0-255
double clamp(double aux)
{
	if (aux > 255)
		aux = 255;
	if (aux < 0)
		aux = 0;
	return aux;
}

// Filtrele se aplica in mod similar

// Functie ce aplica pe o anumita selectie filtrul EDGE
void apply_edge_filter(color ***rgb_image, int x1, int x2, int y1, int y2,
					   int lines, int cols)
{
	// Aloc memorie pentru o matrice auxiliara
	color **aux = (color **)malloc(lines * sizeof(color *));
	if (!aux) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < lines; i++) {
		aux[i] = (color *)malloc(cols * sizeof(color));
		if (!aux[i]) {
			for (int j = 0; j < i; j++)
				free(aux[j]);
			free(aux);
			exit(-1);
		}
	}

	// Copiez matricea initiala
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			aux[i][j].r = (*rgb_image)[i][j].r;
			aux[i][j].g = (*rgb_image)[i][j].g;
			aux[i][j].b = (*rgb_image)[i][j].b;
		}

	// Aplic filtrul in cadrul selectiei, dar nu pe marginile unei imagini
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++) {
			if (i != 0 && i != lines - 1 && j != 0 && j != cols - 1) {
				// Inmultesc fiecare pixel din vecinatatea pixelului pe care il
				// voi modifica, cu pixelul de pe acea pozitie din kernel
				double aux1;
				aux1 = (-1) * aux[i - 1][j - 1].r + (-1) * aux[i - 1][j].r
					+ (-1) * aux[i - 1][j + 1].r	+ (-1) * aux[i][j - 1].r
					+ 8 * aux[i][j].r + (-1) * aux[i][j + 1].r
					+ (-1) * aux[i + 1][j - 1].r + (-1) * aux[i + 1][j].r
					+ (-1) * aux[i + 1][j + 1].r;
				aux1 = clamp(aux1);
				(*rgb_image)[i][j].r = aux1; // schimb valoarea in matrice

				aux1 = (-1) * aux[i - 1][j - 1].g + (-1) * aux[i - 1][j].g
					+ (-1) * aux[i - 1][j + 1].g + (-1) * aux[i][j - 1].g
					+ 8 * aux[i][j].g + (-1) * aux[i][j + 1].g
					+ (-1) * aux[i + 1][j - 1].g + (-1) * aux[i + 1][j].g
					+ (-1) * aux[i + 1][j + 1].g;
				aux1 = clamp(aux1);
				(*rgb_image)[i][j].g = aux1;

				aux1 = (-1) * aux[i - 1][j - 1].b + (-1) * aux[i - 1][j].b
					+ (-1) * aux[i - 1][j + 1].b	+ (-1) * aux[i][j - 1].b
					+ 8 * aux[i][j].b + (-1) * aux[i][j + 1].b
					+ (-1) * aux[i + 1][j - 1].b + (-1) * aux[i + 1][j].b
					+ (-1) * aux[i + 1][j + 1].b;
				aux1 = clamp(aux1);
				(*rgb_image)[i][j].b = aux1;
			}
		}

	for (int i = 0; i < lines; i++)
		free(aux[i]);
	free(aux);
}

// Functie ce aplica pe o anumita selectie filtrul SHARPEN
void apply_sharpen_filter(color ***rgb_image, int x1, int x2, int y1, int y2,
						  int lines, int cols)
{
	color **aux = (color **)malloc(lines * sizeof(color *));
	if (!aux) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < lines; i++) {
		aux[i] = (color *)malloc(cols * sizeof(color));
		if (!aux[i]) {
			for (int j = 0; j < i; j++)
				free(aux[j]);
			free(aux);
			exit(-1);
		}
	}

	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			aux[i][j].r = (*rgb_image)[i][j].r;
			aux[i][j].g = (*rgb_image)[i][j].g;
			aux[i][j].b = (*rgb_image)[i][j].b;
		}

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++) {
			if (i != 0 && i != lines - 1 && j != 0 && j != cols - 1) {
				double aux1;
				aux1 = 0 * aux[i - 1][j - 1].r + (-1) * aux[i - 1][j].r
				   + 0 * aux[i - 1][j + 1].r	+ (-1) * aux[i][j - 1].r
				   + 5 * aux[i][j].r + (-1) * aux[i][j + 1].r
				   + 0 * aux[i + 1][j - 1].r + (-1) * aux[i + 1][j].r
				   + 0 * aux[i + 1][j + 1].r;
				aux1 = clamp(aux1);
				(*rgb_image)[i][j].r = aux1;

				aux1 = 0 * aux[i - 1][j - 1].g + (-1) * aux[i - 1][j].g
				   + 0 * aux[i - 1][j + 1].g + (-1) * aux[i][j - 1].g
				   + 5 * aux[i][j].g + (-1) * aux[i][j + 1].g
				   + 0 * aux[i + 1][j - 1].g + (-1) * aux[i + 1][j].g
				   + 0 * aux[i + 1][j + 1].g;
				aux1 = clamp(aux1);
				(*rgb_image)[i][j].g = aux1;

				aux1 = 0 * aux[i - 1][j - 1].b + (-1) * aux[i - 1][j].b
				   + 0 * aux[i - 1][j + 1].b + (-1) * aux[i][j - 1].b
				   + 5 * aux[i][j].b + (-1) * aux[i][j + 1].b
				   + 0 * aux[i + 1][j - 1].b + (-1) * aux[i + 1][j].b
				   + 0 * aux[i + 1][j + 1].b;
				aux1 = clamp(aux1);
				(*rgb_image)[i][j].b = aux1;
			}
		}

	for (int i = 0; i < lines; i++)
		free(aux[i]);
	free(aux);
}

// Functie ce aplica pe o anumita selectie filtrul BLUR
void apply_blur_filter(color ***rgb_image, int x1, int x2, int y1, int y2,
					   int lines, int cols)
{
	color **aux = (color **)malloc(lines * sizeof(color *));
	if (!aux) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < lines; i++) {
		aux[i] = (color *)malloc(cols * sizeof(color));
		if (!aux[i]) {
			for (int j = 0; j < i; j++)
				free(aux[j]);
			free(aux);
			exit(-1);
		}
	}

	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			aux[i][j].r = (*rgb_image)[i][j].r;
			aux[i][j].g = (*rgb_image)[i][j].g;
			aux[i][j].b = (*rgb_image)[i][j].b;
		}

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++) {
			if (i != 0 && i != lines - 1 && j != 0 && j != cols - 1) {
				double aux1;
				aux1 = aux[i - 1][j - 1].r + aux[i - 1][j].r
					+ aux[i - 1][j + 1].r + aux[i][j - 1].r
					+ aux[i][j].r + aux[i][j + 1].r
					+ aux[i + 1][j - 1].r + aux[i + 1][j].r
					+ aux[i + 1][j + 1].r;
				aux1 = aux1 / 9;
				(*rgb_image)[i][j].r = aux1;

				aux1 = aux[i - 1][j - 1].g + aux[i - 1][j].g
					+ aux[i - 1][j + 1].g + aux[i][j - 1].g
					+ aux[i][j].g + aux[i][j + 1].g
					+ aux[i + 1][j - 1].g + aux[i + 1][j].g
					+ aux[i + 1][j + 1].g;
				aux1 = aux1 / 9;
				(*rgb_image)[i][j].g = aux1;

				aux1 = aux[i - 1][j - 1].b + aux[i - 1][j].b
					+ aux[i - 1][j + 1].b + aux[i][j - 1].b
					+ aux[i][j].b + aux[i][j + 1].b
					+ aux[i + 1][j - 1].b + aux[i + 1][j].b
					+ aux[i + 1][j + 1].b;
				aux1 = aux1 / 9;
				(*rgb_image)[i][j].b = aux1;
			}
		}

	for (int i = 0; i < lines; i++)
		free(aux[i]);
	free(aux);
}

// Functie ce aplica pe o anumita selectie filtrul GAUSSIAN-BLUR
void apply_gaussian_filter(color ***rgb_image, int x1, int x2, int y1, int y2,
						   int lines, int cols)
{
	color **aux = (color **)malloc(lines * sizeof(color *));
	if (!aux) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	for (int i = 0; i < lines; i++) {
		aux[i] = (color *)malloc(cols * sizeof(color));
		if (!aux[i]) {
			for (int j = 0; j < i; j++)
				free(aux[j]);
			free(aux);
			exit(-1);
		}
	}

	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			aux[i][j].r = (*rgb_image)[i][j].r;
			aux[i][j].g = (*rgb_image)[i][j].g;
			aux[i][j].b = (*rgb_image)[i][j].b;
		}

	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++) {
			if (i != 0 && i != lines - 1 && j != 0 && j != cols - 1) {
				double aux1;
				aux1 = 1 * aux[i - 1][j - 1].r + 2 * aux[i - 1][j].r
					+ 1 * aux[i - 1][j + 1].r + 2 * aux[i][j - 1].r
					+ 4 * aux[i][j].r + 2 * aux[i][j + 1].r
					+ 1 * aux[i + 1][j - 1].r + 2 * aux[i + 1][j].r
					+ 1 * aux[i + 1][j + 1].r;
				aux1 = aux1 / 16;
				(*rgb_image)[i][j].r = aux1;

				aux1 = 1 * aux[i - 1][j - 1].g + 2 * aux[i - 1][j].g
					+ 1 * aux[i - 1][j + 1].g + 2 * aux[i][j - 1].g
					+ 4 * aux[i][j].g + 2 * aux[i][j + 1].g
					+ 1 * aux[i + 1][j - 1].g + 2 * aux[i + 1][j].g
					+ 1 * aux[i + 1][j + 1].g;
				aux1 = aux1 / 16;
				(*rgb_image)[i][j].g = aux1;

				aux1 = 1 * aux[i - 1][j - 1].b + 2 * aux[i - 1][j].b
					+ 1 * aux[i - 1][j + 1].b + 2 * aux[i][j - 1].b
					+ 4 * aux[i][j].b + 2 * aux[i][j + 1].b
					+ 1 * aux[i + 1][j - 1].b + 2 * aux[i + 1][j].b
					+ 1 * aux[i + 1][j + 1].b;
				aux1 = aux1 / 16;
				(*rgb_image)[i][j].b = aux1;
			}
		}

	for (int i = 0; i < lines; i++)
		free(aux[i]);
	free(aux);
}

// Functie ce verifica daca un filtru se regaseste printre filtrele valide
int check_filter(char *filter)
{
	if (strcmp(filter, "EDGE") == 0)
		return 1;
	if (strcmp(filter, "SHARPEN") == 0)
		return 1;
	if (strcmp(filter, "BLUR") == 0)
		return 1;
	if (strcmp(filter, "GAUSSIAN_BLUR") == 0)
		return 1;
	return 0;
}

// Functie ce verifica daca se poate aplica un filtru, iar in caz afirmativ
// aplica filtrul cerut
void apply_filter(double ***image, color ***rgb_image, char *filter,
				  char *p_type, int x1, int x2, int y1, int y2, int lines,
				  int cols)
{
	if (!(*image) && !(*rgb_image)) {
		printf("No image loaded\n");
		return;
	}

	// Daca APPLY nu are argument
	if (strcmp(filter, "nothing") == 0) {
		printf("Invalid command\n");
		return;
	}

	// Daca argumentul nu este un filtru valid
	if (check_filter(filter) == 0) {
		printf("APPLY parameter invalid\n");
		return;
	}

	// Daca imaginea este in tonuri de gri
	if (strcmp(p_type, "P2") == 0 || strcmp(p_type, "P5") == 0) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	if (strcmp(filter, "EDGE") == 0)
		apply_edge_filter(rgb_image, x1, x2, y1, y2, lines, cols);

	if (strcmp(filter, "SHARPEN") == 0)
		apply_sharpen_filter(rgb_image, x1, x2, y1, y2, lines, cols);

	if (strcmp(filter, "BLUR") == 0)
		apply_blur_filter(rgb_image, x1, x2, y1, y2, lines, cols);

	if (strcmp(filter, "GAUSSIAN_BLUR") == 0)
		apply_gaussian_filter(rgb_image, x1, x2, y1, y2, lines, cols);

	printf("APPLY %s done\n", filter);
}
