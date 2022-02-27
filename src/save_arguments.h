// Copyright Sindrilaru Catalina-Maria 312CA

#ifndef SAVE_ARGUMENTS_H_
#define SAVE_ARGUMENTS_H_

void save_output_filename_and_ascii(char *output_filename, int *ascii);
void save_name(char *filter);
int is_number(char *word);
void save_arguments_select(char *expression, int *new_x1, int *new_y1,
						   int *new_x2, int *new_y2, int *ok);

#endif
