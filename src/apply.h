// Copyright Sindrilaru Catalina-Maria 312CA

#ifndef APPLY_H_
#define APPLY_H_

#include "struct.h"

double clamp(double aux);
void apply_edge_filter(color ***rgb_image, int x1, int x2, int y1, int y2,
					   int lines, int cols);
void apply_sharpen_filter(color ***rgb_image, int x1, int x2, int y1, int y2,
						  int lines, int cols);
void apply_blur_filter(color ***rgb_image, int x1, int x2, int y1, int y2,
					   int lines, int cols);
void apply_gaussian_filter(color ***rgb_image, int x1, int x2, int y1, int y2,
						   int lines, int cols);
int check_filter(char *filter);
void apply_filter(double ***image, color ***rgb_image, char *filter,
				  char *p_type, int x1, int x2, int y1, int y2, int lines,
				  int cols);

#endif
