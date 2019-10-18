/*
   -----------------------------------------------------------------------
   GNUitarra
   Copyright (c) 2002, Kronoman - All rights reserved
   In loving memory of my father.
   -----------------------------------------------------------------------
   chordram.h
   This have a simple struct to keep the note structure in RAM
   and exports some GLOBALs
*/

#ifndef GUITARRA_CHORDRAM_H
#define GUITARRA_CHORDRAM_H

#include "mimenu.h" 



/* structure used to store the notes that form each scale
   a note not used has a -1 value
   a note in use has a a value between 0..11 (C..B)
   they are put here in the way they are ordered in the file readed */
typedef struct ARRAY_DOCE_NOTAS
{
	int nota[12];
} ARRAY_DOCE_NOTAS;

/* globals used by the program */
extern MI_MENU_ARRAY *chord_list;
extern MI_MENU_ARRAY *scale_list;
extern MI_MENU_ARRAY *afination_list;

extern ARRAY_DOCE_NOTAS *chord_note;
extern ARRAY_DOCE_NOTAS *scale_note;
extern ARRAY_DOCE_NOTAS *afination_note;

extern int chord_size;
extern int scale_size;
extern int afina_size;
#endif