// -------------------------------------------------------- 
// krstring.c 
// -------------------------------------------------------- 
// Copyright (c) 2002, Kronoman 
// En memoria de mi querido padre 
// -------------------------------------------------------- 
// Funciones para strings ASCII auxiliares
// -------------------------------------------------------- 

#ifndef KRSTRING_C
#define KRSTRING_C

#include <string.h>

// -------------------------------------------------------- 
// krtrim -
// Funcion equivalente a trim$ de qbasic, elimina
// los espacios adelante y atras de orig, y lo coloca en dest
// devuelve dest.-
// Es algo lenta ya que recorre varias veces la cadena
// dest debe tener espacio suficiente para alojar a orig!!! y un char '0' al final
// --------------------------------------------------------
char *krtrim(char *dest, const char *orig)
{
int ret, x1 = 0, x2 = 0, x3 = 0;

dest[0] = '\0'; // por ahora vacia

x1 = 0; // comienzo cadena

x2 = strlen(orig)-1;

// buscar cadena al final
while ( (orig[x2] == ' ') && (x2 >= 0) )
       {
           x2--;
       }

if (x2 < 0) x2 = 0;

// buscar cadena al principio
while ( (orig[x1] == ' ') && (x1 < x2 ) )
       {
           x1++;
       }

if (x1 > strlen(orig)-1 ) x1 = strlen(orig-1);

// copiar
for (ret = x1; ret < x2+1; ret++)
     {
         dest[x3] = orig[ret];
         x3++;
     }
dest[x3] = '\0';

return dest;
};
#endif