// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct.h"
#include "load.h"

// Functie ce sare peste liniile ce contin comentarii
void skip_comments(FILE *image_file)
{
	char character;
	fscanf(image_file, "%c", &character);
	if (character == '\n')
		fscanf(image_file, "%c", &character);
	if (character != '#') {
		fseek(image_file, -1, SEEK_CUR);
	} else {
		while (character != '\n')
			fscanf(image_file, "%c", &character);
	}
}

// Functie ce returneaza numarul corespunzator tipului imaginii
int function_type_image(char *p_type)
{
	if (strcmp(p_type, "P2") == 0)
		return 2;
	else if (strcmp(p_type, "P3") == 0)
		return 3;
	else if (strcmp(p_type, "P5") == 0)
		return 5;
	else if (strcmp(p_type, "P6") == 0)
		return 6;

	return 0;
}

// Functie ce aloca dinamic o matrice pentru o imagine in tonuri de gri
void alloc_matrix(double ***image, int cols, int lines)
{
	(*image) =  (double **)malloc(lines * sizeof(double *));
	if (!(*image)) {
		fprintf(stderr, "Error\n");
		free(*image);
		exit(-1);
	}
	for (int i = 0; i < lines; i++) {
		(*image)[i] = (double *)malloc(cols * sizeof(double));
		if (!(*image)[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free((*image)[j]);
			free(*image);
			exit(-1);
		}
	}
}

// Functie care citeste matricea corespunzatoare unei imagini in tonuri de gri
// din format ASCII
void read_matrix(double ***image, int cols, int lines, FILE *image_file)
{
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			int aux;
			fscanf(image_file, "%d", &aux);
			(*image)[i][j] = (double)aux;
		}
}

// Functie care citeste matricea corespunzatoare unei imagini in tonuri de gri
// din format BINAR
void read_matrix_binary(double ***image, int cols, int lines, FILE *image_file)
{
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			unsigned char aux1;
			fread(&aux1, sizeof(unsigned char), 1, image_file);
			int aux2 = (int)aux1;
			(*image)[i][j] = (double)aux2;
		}
}

// Functie ce aloca dinamic o matrice pentru o imagine color
void alloc_rgb_matrix(color ***rgb_image, int cols, int lines)
{
	(*rgb_image) = (color **)malloc(lines * sizeof(color *));
	if (!(*rgb_image)) {
		fprintf(stderr, "Error\n");
		free(*rgb_image);
		exit(-1);
	}
	for (int i = 0; i < lines; i++) {
		(*rgb_image)[i] = (color *)malloc(cols * sizeof(color));
		if (!(*rgb_image)[i]) {
			fprintf(stderr, "Error\n");
			for (int j = 0; j < i; j++)
				free((*rgb_image)[j]);
			free(*rgb_image);
			exit(-1);
		}
	}
}

// Functie care citeste matricea corespunzatoare unei imagini color
// din format ASCII
void read_rgb_matrix(color ***rgb_image, int cols, int lines, FILE *image_file)
{
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			int aux;
			fscanf(image_file, "%d", &aux);
			(*rgb_image)[i][j].r = (double)aux;

			fscanf(image_file, "%d", &aux);
			(*rgb_image)[i][j].g = (double)aux;

			fscanf(image_file, "%d", &aux);
			(*rgb_image)[i][j].b = (double)aux;
		}
}

// Functie care citeste matricea corespunzatoare unei imagini color
// din format BINAR
void read_rgb_matrix_binary(color ***rgb_image, int cols, int lines,
							FILE *image_file)
{
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			unsigned char aux1;
			fread(&aux1, sizeof(unsigned char), 1, image_file);
			int aux2 = (int)aux1;
			(*rgb_image)[i][j].r = (double)aux2;

			fread(&aux1, sizeof(unsigned char), 1, image_file);
			aux2 = (int)aux1;
			(*rgb_image)[i][j].g = (double)aux2;

			fread(&aux1, sizeof(unsigned char), 1, image_file);
			aux2 = (int)aux1;
			(*rgb_image)[i][j].b = (double)aux2;
		}
}

// Functie care salveaza o imagine de tip P2(in tonuri de gri din format ascii)
void load_type_p2(double ***image, int *cols, int *lines, int *maxvalue,
				  FILE *image_file)
{
	skip_comments(image_file);
	// Citesc dimensiunile imaginii
	fscanf(image_file, "%d%d", cols, lines);
	skip_comments(image_file);
	// Citesc valoarea maxima pe care o poate avea un pixel
	fscanf(image_file, "%d", maxvalue);
	skip_comments(image_file);
	// Aloc memorie pentru matrice si apoi o stochez
	alloc_matrix(image, *cols, *lines);
	read_matrix(image, *cols, *lines, image_file);
	fclose(image_file);
}

// Functie care salveaza o imagine de tip P3(color din format ascii)
void load_type_p3(color ***rgb_image, int *cols, int *lines, int *maxvalue,
				  FILE *image_file)
{
	skip_comments(image_file);
	// Citesc dimensiunile imaginii
	fscanf(image_file, "%d%d", cols, lines);
	skip_comments(image_file);
	// Citesc valoarea maxima pe care o poate avea un pixel
	fscanf(image_file, "%d", maxvalue);
	skip_comments(image_file);
	// Aloc memorie pentru matrice si apoi o stochez
	alloc_rgb_matrix(rgb_image, *cols, *lines);
	read_rgb_matrix(rgb_image, *cols, *lines, image_file);
	fclose(image_file);
}

// Functie care salveaza o imagine de tip P5 (in tonuri de gri din format binar)
void load_type_p5(double ***image, int *cols, int *lines, int *maxvalue,
				  FILE **image_file, char *filename)
{
	skip_comments(*image_file);
	// Citesc dimensiunile imaginii
	fscanf(*image_file, "%d%d", cols, lines);
	skip_comments(*image_file);
	// Citesc valoarea maxima pe care o poate avea un pixel
	fscanf(*image_file, "%d", maxvalue);
	// Retin pozitia la care m-am oprit din citit din fisier
	int current_pos =  ftell(*image_file) + 1;
	fclose(*image_file);
	// Deschid fisierul pentru citire din format binar
	*image_file = fopen(filename, "rb");
	if (!(*image_file)) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	// Ma situez la pozitia la care am ramas inainte
	fseek(*image_file, current_pos, SEEK_SET);
	// Aloc memorie pentru matrice si apoi o stochez
	alloc_matrix(image, *cols, *lines);
	read_matrix_binary(image, *cols, *lines, *image_file);
	fclose(*image_file);
}

// Functie care salveaza o imagine de tip P6 (color din format binar)
void load_type_p6(color ***rgb_image, int *cols, int *lines, int *maxvalue,
				  FILE **image_file, char *filename)
{
	skip_comments(*image_file);
	// Citesc dimensiunile imaginii
	fscanf(*image_file, "%d%d", cols, lines);
	skip_comments(*image_file);
	// Citesc valoarea maxima pe care o poate avea un pixel
	fscanf(*image_file, "%d", maxvalue);
	skip_comments(*image_file);
	// Retin pozitia la care m-am oprit din citit din fisier
	int current_pos =  ftell(*image_file);
	fclose(*image_file);
	// Deschid fisierul pentru citire din format binar
	*image_file = fopen(filename, "rb");
	if (!(*image_file)) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}
	// Ma situez la pozitia la care am ramas inainte
	fseek(*image_file, current_pos, SEEK_SET);
	// Aloc memorie pentru matrice si apoi o stochez
	alloc_rgb_matrix(rgb_image, *cols, *lines);
	read_rgb_matrix_binary(rgb_image, *cols, *lines, *image_file);
	fclose(*image_file);
}

// Functie care verifica tipul imaginii si apeleaza functia pentru
// formatul potrivit
void load_image(char *filename, double ***image, color ***rgb_image,
				char *p_type, int *cols, int *lines, int *maxvalue, int *x1,
				int *x2, int *y1, int *y2)
{
	// Daca exista deja o imagine salvata, ii elibereaza memoria
	if (*image) {
		for (int i = 0; i < *lines; i++)
			free((*image)[i]);
		free(*image);
		*image = NULL;
	}

	if (*rgb_image) {
		for (int i = 0; i < *lines; i++)
			free((*rgb_image)[i]);
		free(*rgb_image);
		*rgb_image = NULL;
	}

	// In cazul in care comanda LOAD nu a fost urmata de numele unui fisier
	if (strcmp(filename, "nothing") == 0) {
		printf("Invalid command\n");
		return;
	}

	// Se deschide fisierul pentru citire din format text
	FILE *image_file = fopen(filename, "rt");

	if (!image_file) {
		fprintf(stderr, "Error\n");
		printf("Failed to load %s\n", filename);
		return;
	}

	skip_comments(image_file);

	//Citesc tipul imaginii
	fscanf(image_file, "%s", p_type);

	int image_type;
	image_type = function_type_image(p_type);

	if (image_type == 2)
		load_type_p2(image, cols, lines, maxvalue, image_file);
	else if (image_type == 3)
		load_type_p3(rgb_image, cols, lines, maxvalue, image_file);
	else if (image_type == 5)
		load_type_p5(image, cols, lines, maxvalue, &image_file, filename);
	else if (image_type == 6)
		load_type_p6(rgb_image, cols, lines, maxvalue, &image_file, filename);

	printf("Loaded %s\n", filename);

	// Selectez intreaga imagine
	*x1 = 0;
	*x2 = *cols;
	*y1 = 0;
	*y2 = *lines;
}
