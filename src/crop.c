// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "struct.h"
#include "crop.h"

// Functie ce taie o imagine in tonuri de gri
void crop_image(double ***image, color ***rgb_image, int *x1, int *x2, int *y1,
				int *y2, int *lines, int *cols)
{
	if (!(*image) && !(*rgb_image)) {
		printf("No image loaded\n");
		return;
	}

	int aux_lines, aux_cols; // dimensiunile noii matrice
	aux_lines = *y2 - *y1;
	aux_cols = *x2 - *x1;

	// Aloc memorie pentru o matrice auxiliara in care stochez pixelii
	// imaginii taiate
	double **aux_mat;
	aux_mat = (double **)malloc(aux_lines * sizeof(double *));
	if (!aux_mat) {
		fprintf(stderr, "Error\n");
		free(aux_mat);
		exit(-1);
	}
	for (int i = 0; i < aux_lines; i++) {
		aux_mat[i] = (double *)malloc(aux_cols * sizeof(double));
		if (!aux_mat[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(aux_mat[j]);
			free(aux_mat);
			exit(-1);
		}
	}

	int l = 0, c = 0;
	for (int i = *y1; i < *y2; i++)
		for (int j = *x1; j < *x2; j++) {
			aux_mat[l][c] = (*image)[i][j];
			c++;
			if (c == aux_cols) {
				l++;
				c = 0;
			}
		}

	// Eliberez memoria pentru matricea initiala
	for (int i = 0; i < *lines; i++)
		free((*image)[i]);
	free((*image));

	// Copiez matricea pentru poza taiata
	(*image) = aux_mat;

	// Modific dimensiunile matricei initiale cu dimensiunile celei taiate
	*lines = aux_lines;
	*cols = aux_cols;

	// Modific selectia conform noilor dimensiuni
	*x1 = 0;
	*x2 = aux_cols;
	*y1 = 0;
	*y2 = aux_lines;

	printf("Image cropped\n");
}

// Functie ce taie o imagine color
void crop_rgb_image(color ***rgb_image, int *x1, int *x2, int *y1, int *y2,
					int *lines, int *cols)
{
	if (!(*rgb_image)) {
		printf("No image loaded\n");
		return;
	}

	int aux_lines, aux_cols; // dimensiunile noii matrice
	aux_lines = *y2 - *y1;
	aux_cols = *x2 - *x1;

	// Aloc memorie pentru o matrice auxiliara in care stochez pixelii
	// imaginii taiate
	color **aux_rgb_mat;
	aux_rgb_mat = (color **)malloc(aux_lines * sizeof(color *));
	if (!aux_rgb_mat) {
		fprintf(stderr, "Error\n");
		free(aux_rgb_mat);
		exit(-1);
	}
	for (int i = 0; i < aux_lines; i++) {
		aux_rgb_mat[i] = (color *)malloc(aux_cols * sizeof(color));
		if (!aux_rgb_mat[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free(aux_rgb_mat[j]);
			free(aux_rgb_mat);
			exit(-1);
		}
	}

	int l = 0, c = 0;
	for (int i = *y1; i < *y2; i++)
		for (int j = *x1; j < *x2; j++) {
			aux_rgb_mat[l][c].r = (*rgb_image)[i][j].r;
			aux_rgb_mat[l][c].g = (*rgb_image)[i][j].g;
			aux_rgb_mat[l][c].b = (*rgb_image)[i][j].b;
			c++;
			if (c == aux_cols) {
				l++;
				c = 0;
			}
		}

	// Eliberez memoria pentru matricea initiala
	for (int i = 0; i < *lines; i++)
		free((*rgb_image)[i]);
	free((*rgb_image));

	// Copiez matricea taiata
	(*rgb_image) = aux_rgb_mat;

	// Modific dimensiunile matricei initiale cu dimensiunile celei taiate
	*lines = aux_lines;
	*cols = aux_cols;

	// Modific selectia conform noilor dimensiuni
	*x1 = 0;
	*x2 = aux_cols;
	*y1 = 0;
	*y2 = aux_lines;

	printf("Image cropped\n");
}
