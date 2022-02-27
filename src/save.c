// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "struct.h"
#include "save.h"

// Functie ce salveaza o imagine in tonuri de gri in format ASCII
void save_image_in_ascii(char *output_filename, double **image, char *p_type,
						 int lines, int cols, int maxvalue)
{
	FILE *filename = fopen(output_filename, "wt");
	if (!filename) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}

	strcpy(p_type, "P2");
	fprintf(filename, "%s\n", p_type);
	fprintf(filename, "%d %d\n", cols, lines);
	fprintf(filename, "%d\n", maxvalue);

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < cols; j++) {
			int aux = (int)round(image[i][j]);
			fprintf(filename, "%d ",  aux);
		}
		fprintf(filename, "\n");
	}

	fclose(filename);
}

// Functie ce salveaza o imagine color in format ASCII
void save_rgb_image_in_ascii(char *output_filename, color **rgb_image,
							 char *p_type, int lines, int cols,
							 int maxvalue)
{
	FILE *filename = fopen(output_filename, "wt");
	if (!filename) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}

	strcpy(p_type, "P3");
	fprintf(filename, "%s\n", p_type);
	fprintf(filename, "%d %d\n", cols, lines);
	fprintf(filename, "%d\n", maxvalue);

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < cols; j++) {
			int aux;
			aux = (int)round(rgb_image[i][j].r);
			fprintf(filename, "%d ", aux);

			aux = (int)round(rgb_image[i][j].g);
			fprintf(filename, "%d ", aux);

			aux = (int)round(rgb_image[i][j].b);
			fprintf(filename, "%d ", aux);
		}
		fprintf(filename, "\n");
	}
	fclose(filename);
}

// Functie ce salveaza o imagine in tonuri de gri in format BINAR
void save_image_in_binary(char *output_filename, double **image, char *p_type,
						  int lines, int cols, int maxvalue)
{
	FILE *filename = fopen(output_filename, "wt");
	if (!filename) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}

	strcpy(p_type, "P5");
	fprintf(filename, "%s\n", p_type);
	fprintf(filename, "%d %d\n", cols, lines);
	fprintf(filename, "%d\n", maxvalue);
	fclose(filename);

	// Se deschide fisierul in format binar pentru a se scrie matricea
	filename = fopen(output_filename, "ab");
	if (!filename) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}

	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			int aux1 = (int)round(image[i][j]);
			unsigned char aux2 = (unsigned char)aux1;
			fwrite(&aux2, sizeof(unsigned char), 1, filename);
		}
	fclose(filename);
}

// Functie ce salveaza o imagine color in format BINAR
void save_rgb_image_in_binary(char *output_filename, color **rgb_image,
							  char *p_type, int lines, int cols,
							  int maxvalue)
{
	FILE *filename = fopen(output_filename, "wt");
	if (!filename) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}

	strcpy(p_type, "P6");
	fprintf(filename, "%s\n", p_type);
	fprintf(filename, "%d %d\n", cols, lines);
	fprintf(filename, "%d\n", maxvalue);
	fclose(filename);

	// Se deschide fisierul in format binar pentru a se scrie matricea
	filename = fopen(output_filename, "ab");
	if (!filename) {
		fprintf(stderr, "Error\n");
		exit(-1);
	}

	for (int i = 0; i < lines; i++)
		for (int j = 0; j < cols; j++) {
			int aux1;
			unsigned char aux2;
			aux1 = (int)round(rgb_image[i][j].r);
			aux2 = (unsigned char)aux1;
			fwrite(&aux2, sizeof(unsigned char), 1, filename);

			aux1 = (int)round(rgb_image[i][j].g);
			aux2 = (unsigned char)aux1;
			fwrite(&aux2, sizeof(unsigned char), 1, filename);

			aux1 = (int)round(rgb_image[i][j].b);
			aux2 = (unsigned char)aux1;
			fwrite(&aux2, sizeof(unsigned char), 1, filename);
		}

	fclose(filename);
}

// Functie ce salveaza o imagine intr-un fisier dat in format ASCII/BINAR
void save(double **image, color **rgb_image, char *output_filename, int ascii,
		  char *p_type, int lines, int cols, int maxvalue)
{
	if (!image && !rgb_image) {
		printf("No image loaded\n");
		return;
	}

	// Daca SAVE nu are argument
	if (strcmp(output_filename, "nothing") == 0) {
		printf("Invalid command\n");
		return;
	}

	if (ascii == 1) { // salvare in format ascii
		if (strcmp(p_type, "P2") == 0 || strcmp(p_type, "P5") == 0)
			save_image_in_ascii(output_filename, image, p_type, lines, cols,
								maxvalue);
		else if (strcmp(p_type, "P3") == 0 || strcmp(p_type, "P6") == 0)
			save_rgb_image_in_ascii(output_filename, rgb_image, p_type, lines,
									cols, maxvalue);
	} else { // salvare in format binar
		if (strcmp(p_type, "P2") == 0 || strcmp(p_type, "P5") == 0)
			save_image_in_binary(output_filename, image, p_type, lines,
								 cols, maxvalue);
		else if (strcmp(p_type, "P3") == 0 || strcmp(p_type, "P6") == 0)
			save_rgb_image_in_binary(output_filename, rgb_image, p_type, lines,
									 cols, maxvalue);
	}

	printf("Saved %s\n", output_filename);
}
