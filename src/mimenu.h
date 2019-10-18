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
   mimenu.h
   This have a simple menu routines to select stuff
   and interact with the user.
   This have the definitions of typedef structures
   for making easy arrays that can be used to the menus.
   They are also used to store the chord names (ugly!)
*/


#ifndef MI_MENU_H
#define MI_MENU_H

/* this defines the maximun length of the string of each menu entry
   *including* the trainling '\0' */
#define MAX_MENUSTR_LEN  41

typedef struct MI_MENU_ARRAY
{
	char menuitemstr[MAX_MENUSTR_LEN];
} MI_MENU_ARRAY;




/* prototypes */

void my_menu_help ( const int x, const int y, const int v );

int do_my_menu( const int x, const int y, const int w, const int h,
	        const MI_MENU_ARRAY *menulist, const int cant);


#endif