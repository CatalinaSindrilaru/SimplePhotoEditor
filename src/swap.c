// Copyright Sindrilaru Catalina-Maria 312CA

#include <stdio.h>
#include "swap.h"

// Interschimbarea a doua valori
void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}
