// Copyright Sindrilaru Catalina-Maria 312CA

#ifndef ROTATE_H_
#define ROTATE_H_

#include "struct.h"

void rotate_all_image_left(double ***image, int *x1, int *x2, int *y1, int *y2,
						   int *lines, int *cols);
void rotate_all_image_right(double ***image, int *x1, int *x2, int *y1, int *y2,
							int *lines, int *cols);
void rotate_section_left(double ***image, int *x1, int *x2, int *y1, int *y2);
void rotate_section_right(double ***image, int *x1, int *x2, int *y1, int *y2);
int verif_angle(int angle);
void rotate_image(double ***image, color ***rgb_image, char *angle_string,
				  int *x1, int *x2, int *y1, int *y2, int *lines, int *cols);
void rotate_all_rgb_image_left(color ***rgb_image, int *x1, int *x2, int *y1,
							   int *y2, int *lines, int *cols);
void rotate_all_rgb_image_right(color ***rgb_image, int *x1, int *x2, int *y1,
								int *y2, int *lines, int *cols);
void rotate_rgb_section_left(color ***rgb_image, int *x1, int *x2, int *y1,
							 int *y2);
void rotate_rgb_section_right(color ***rgb_image, int *x1, int *x2, int *y1,
							  int *y2);
void rotate_rgb_image(color ***rgb_image, char *angle_string, int *x1, int *x2,
					  int *y1, int *y2, int *lines, int *cols);

#endif
