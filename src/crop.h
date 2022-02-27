// Copyright Sindrilaru Catalina-Maria 312CA

#ifndef CROP_H_
#define CROP_H_

#include "struct.h"

void crop_image(double ***image, color * **rgb_image, int *x1, int *x2, int *y1,
				int *y2, int *lines, int *cols);
void crop_rgb_image(color ***rgb_image, int *x1, int *x2, int *y1, int *y2,
					int *lines, int *cols);

#endif
