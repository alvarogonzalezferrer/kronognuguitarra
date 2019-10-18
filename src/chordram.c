/*
   -----------------------------------------------------------------------
   GNUitarra
   Copyright (c) 2002, Kronoman - All rights reserved
   In loving memory of my father.
   -----------------------------------------------------------------------
   chordram.c
   This have some simple GLOBAL arrays that I use to keep the stuff
   into RAM... pretty ugly, but damn simple...
*/

#include "chordram.h"
#include "mimenu.h" /* this module uses typedef defined here... */
#include "mainfile.h" /* NULL definition uh? */

/* here I will store all the chord and scale names used to show in the menus
   on this I do malloc/realloc/etc */
MI_MENU_ARRAY *chord_list = NULL;
MI_MENU_ARRAY *scale_list = NULL;
MI_MENU_ARRAY *afination_list = NULL; /* afinations of the guitar... */

/* here I will store all the chord and scale notes
   this will be malloced/etc */
ARRAY_DOCE_NOTAS *chord_note = NULL;
ARRAY_DOCE_NOTAS *scale_note = NULL;
ARRAY_DOCE_NOTAS *afination_note = NULL;

/* items on each structure */
int chord_size = 0;
int scale_size = 0;
int afina_size = 0;