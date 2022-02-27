// Copyright Sindrilaru Catalina-Maria 312CA

#ifndef SAVE_H_
#define SAVE_H_

#include "struct.h"

void save_image_in_ascii(char *output_filename, double **image, char *p_type,
						 int lines, int cols, int maxvalue);
void save_rgb_image_in_ascii(char *output_filename, color **rgb_image,
							 char *p_type, int lines, int cols,
							 int maxvalue);
void save_image_in_binary(char *output_filename, double **image, char *p_type,
						  int lines, int cols, int maxvalue);
void save_rgb_image_in_binary(char *output_filename, color **rgb_image,
							  char *p_type, int lines, int cols,
							  int maxvalue);
void save(double **image, color **rgb_image, char *output_filename, int ascii,
		  char *p_type, int lines, int cols, int maxvalue);

#endif
