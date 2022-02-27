// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "defines.h"
#include "struct.h"
#include "load.h"
#include "select.h"
#include "crop.h"
#include "rotate.h"
#include "apply.h"
#include "save.h"
#include "save_arguments.h"
#include "exit.h"

int main(void)
{
	char command[CMAX], filename[FMAX], p_type[PMAX], output_filename[CMAX];
	char expression[EMAX], filter[FMAX], angle_string[EMAX];
	double **image; // Matricea pentru imaginea in tonuri de gri
	image = NULL;
	color **rgb_image; // Matricea pentru imaginea color
	rgb_image = NULL;
	int lines, cols, maxvalue, x1, x2, y1, y2;
	int new_x1 = 0, new_x2 = 0, new_y1 = 0, new_y2 = 0, ascii;

	while (1) {
		// Identific comanda si apelez functia corespunzatoare
		scanf("%s", command);

		if (strcmp(command, "EXIT") == 0) {
			exit_command(&image, &rgb_image, lines);
			break;
		}

		// Pentru comenzile ce presupun argumente, acestea sunt salvate separat
		// pentru a le putea verifica existenta
		if (strcmp(command, "LOAD") == 0) {
			save_name(filename);
			load_image(filename, &image, &rgb_image, p_type, &cols, &lines,
					   &maxvalue, &x1, &x2, &y1, &y2);

		} else if (strcmp(command, "SELECT") == 0) {
			int ok = 1;
			strcpy(expression, "");
			save_arguments_select(expression, &new_x1, &new_y1, &new_x2,
								  &new_y2, &ok);
			if (strcmp(expression, "ALL") == 0)
				select_all(image, rgb_image, &x1, &x2, &y1, &y2, lines, cols);
			else if (ok == 0)
				printf("Invalid command\n");
			else
				select_coordinates(image, rgb_image, expression, &x1, &x2,
								   &y1, &y2, new_x1, new_x2, new_y1, new_y2,
								   lines, cols);
		} else if (strcmp(command, "ROTATE") == 0) {
			save_name(angle_string);
			int image_type = function_type_image(p_type);
			if (image_type == 3 || image_type == 6)
				rotate_rgb_image(&rgb_image, angle_string, &x1, &x2,
								 &y1, &y2, &lines, &cols);
			else
				rotate_image(&image, &rgb_image, angle_string, &x1, &x2,
							 &y1, &y2, &lines, &cols);

		} else if (strcmp(command, "CROP") == 0) {
			int image_type = function_type_image(p_type);
			if (image_type == 3 || image_type == 6)
				crop_rgb_image(&rgb_image, &x1, &x2, &y1, &y2, &lines,
							   &cols);
			else
				crop_image(&image, &rgb_image, &x1, &x2, &y1, &y2, &lines,
						   &cols);
		} else if (strcmp(command, "APPLY") == 0) {
			save_name(filter);
			apply_filter(&image, &rgb_image, filter, p_type, x1, x2, y1, y2,
						 lines, cols);

		} else if (strcmp(command, "SAVE") == 0) {
			save_output_filename_and_ascii(output_filename, &ascii);
			save(image, rgb_image, output_filename, ascii, p_type, lines, cols,
				 maxvalue);
		} else {
			char character;
			do {
				fscanf(stdin, "%c", &character);
			} while (character != '\n');
			printf("Invalid command\n");
		}
	}

	return 0;
}
