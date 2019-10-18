/*
   -----------------------------------------------------------------------
   GNUitarra
   Copyright (c) 2002, Kronoman - All rights reserved
   In loving memory of my father
   -----------------------------------------------------------------------
   loaddata.h
   This loads/unloads the datafiles from disk into RAM memory
   using the scheme of brute force arrays using malloc -:^(
*/

#ifndef  GUITARRA_LOADDATA_H
#define  GUITARRA_LOADDATA_H

#include "myincs.h"
#include "chordram.h"

/* prototypes */
int load_guitar_data(const char *dir, const char *file,
					  MI_MENU_ARRAY **list,
					  ARRAY_DOCE_NOTAS **notes,
					  int *itemsize);

void free_all_data(void);

void load_all_data(void);
#endif