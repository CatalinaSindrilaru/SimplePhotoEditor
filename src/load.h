// Copyright Sindrilaru Catalina-Maria 312CA

#ifndef LOAD_H_
#define LOAD_H_

void skip_comments(FILE *image_file);
int function_type_image(char *p_type);
void alloc_matrix(double ***image, int cols, int lines);
void read_matrix(double ***image, int cols, int lines, FILE *image_file);
void read_matrix_binary(double ***image, int cols, int lines, FILE *image_file);
void alloc_rgb_matrix(color ***rgb_image, int cols, int lines);
void read_rgb_matrix(color ***rgb_image, int cols, int lines, FILE *image_file);
void read_rgb_matrix_binary(color ***rgb_image, int cols, int lines,
							FILE *image_file);
void load_type_p2(double ***image, int *cols, int *lines, int *maxvalue,
				  FILE *image_file);
void load_type_p3(color ***rgb_image, int *cols, int *lines, int *maxvalue,
				  FILE *image_file);
void load_type_p5(double ***image, int *cols, int *lines, int *maxvalue,
				  FILE **image_file, char *filename);
void load_type_p6(color ***rgb_image, int *cols, int *lines, int *maxvalue,
				  FILE **image_file, char *filename);
void load_image(char *filename, double ***image, color ***rgb_image,
				char *p_type, int *cols, int *lines, int *maxvalue, int *x1,
				int *x2, int *y1, int *y2);

#endif
