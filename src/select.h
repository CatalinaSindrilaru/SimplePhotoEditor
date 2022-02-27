// Copyright Sindrilaru Catalina-Maria 312CA

#ifndef SELECT_H_
#define SELECT_H_

#include "struct.h"

void select_coordinates(double **image, color * *rgb_image, char *expression,
						int *x1, int *x2, int *y1, int *y2, int new_x1,
						int new_x2, int new_y1, int new_y2, int lines,
						int cols);
void select_all(double **image, color **rgb_image, int *x1, int *x2, int *y1,
				int *y2, int lines, int cols);

#endif
