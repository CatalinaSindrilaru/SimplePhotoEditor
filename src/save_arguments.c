// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "defines.h"
#include "save_arguments.h"

// Salvez numele fisierului si verific daca trebuie scris in format ASCII
void save_output_filename_and_ascii(char *output_filename, int *ascii)
{
	*ascii = 0;
	char save_line[FMAX];
	fgets(save_line, FMAX, stdin);
	if (save_line[0] == '\n') {
		strcpy(output_filename, "nothing");
		return;
	}
	save_line[strlen(save_line) - 1] = '\0';

	if (strstr(save_line, "ascii") != 0)
		*ascii = 1;

	char *sep = "\n ";
	char *word = strtok(save_line, sep);
	strcpy(output_filename, word);
}

// Salvez argumentul aflat dupa o comanda, daca acesta exista
void save_name(char *filter)
{
	char save_line[FMAX];
	fgets(save_line, FMAX, stdin);
	if (save_line[0] == '\n') {
		strcpy(filter, "nothing");
	} else {
		char *sep = "\n ";
		char *word = strtok(save_line, sep);
		strcpy(filter, word);
	}
}

// Verific daca un cuvant reprezinta un numar
int is_number(char *word)
{
	int ok = 1, i1;
	if (word[0] == '-')
		i1 = 1;
	else
		i1 = 0;
	int l = strlen(word);
	for (int i = i1; i < l; i++)
		if (isdigit(word[i]) == 0)
			ok = 0;

	return ok;
}

// Salvez argumentele pentru comanda SELECT
void save_arguments_select(char *expression, int *new_x1, int *new_y1,
						   int *new_x2, int *new_y2, int *ok)
{
	char *save_line;
	save_line = (char *)malloc(FMAX * sizeof(char));
	fgets(save_line, FMAX, stdin);

	// Verific daca select are vreun argument
	if (save_line[0] == '\n') {
		strcpy(expression, "nothing");
		return;
	}
	save_line[strlen(save_line) - 1] = '\0';

	char *sep = "\n ";
	char *word = strtok(save_line, sep);

	int nr = 0;
	int ok0 = -1, ok1 = -1, ok2 = -1, ok3 = -1;

	while (word) {
		if (nr == 0) {
			// Daca argmentul este ALL
			if (strcmp(word, "ALL") == 0) {
				strcpy(expression, "ALL");
				nr = 4;
				break;
			}
		// Verific daca argumentele <x1> <y1> <x2> <y2>
		// sunt valide
			ok0 = is_number(word);
			if (ok0 == 1)
				*new_x1 = atoi(word);

		} else if (nr == 1) {
			ok1 = is_number(word);
			if (ok1 == 1)
				*new_y1 = atoi(word);
		} else if (nr == 2) {
			ok2 = is_number(word);
			if (ok2 == 1)
				*new_x2 = atoi(word);
		} else if (nr == 3) {
			ok3 = is_number(word);
			if (ok3 == 1)
				*new_y2 = atoi(word);
		}

		nr++;
		word = strtok(NULL, sep);
	}

	// Daca argumentele de tipul <x1> <y1> <x2> <y2> nu sunt valide
	// sau nu s-a atins numarul lor
	if (ok0 == 0 || ok1 == 0 || ok2 == 0 || ok3 == 0 || nr != 4)
		*ok = 0;

	free(save_line);
}
