// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "struct.h"
#include "exit.h"

// Functie ce elibereaza memoria la sfarsitul programului
void exit_command(double ***image, color ***rgb_image, int lines)
{
	if (!(*image) && !(*rgb_image)) {
		printf("No image loaded\n");
		return;
	}

	if (*image) {
		for (int i = 0; i < lines; i++)
			free((*image)[i]);
		free(*image);
	}

	if (*rgb_image) {
		for (int i = 0; i < lines; i++)
			free((*rgb_image)[i]);
		free(*rgb_image);
	}
}
