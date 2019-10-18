/*
   -----------------------------------------------------------------------
   GNUitarra
   Copyright (c) 2002, Kronoman - All rights reserved
   In loving memory of my father
   -----------------------------------------------------------------------
   ** In loving memory of my father **
   Distributed under the terms of the GNU GPL license.
   Made in Argentina
   -----------------------------------------------------------------------
   ui.c
   This has the user interface (select chord, select scale, etc...)
*/



#ifndef UI_H
#define UI_H

/* prototypes */
void start_user_interface(void);

void interactive_fret(MI_MENU_ARRAY *list,
					  ARRAY_DOCE_NOTAS *notes,
					  const int itemsize,
					  int idx,
					  int afina);


#endif