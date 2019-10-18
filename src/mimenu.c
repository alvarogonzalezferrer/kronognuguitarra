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
   mimenu.c
   This have a simple menu routines to select stuff
   and interact with the user.
*/

#include "myincs.h"
#include "mimenu.h"
#include "textbox.h"


/* This shows a message with the keys (only the letter equivalent) used to select the menu
   The mesagge appears in x, y
   v is the level of verbosity of the message
   <=0 -> basic keys [always showed]
   = 1 -> 
   > 1 -> more keys...
   */
void my_menu_help ( const int x, const int y, const int v )
{
	/* DEBUG: usar GETTEXT! */
	move(y,x);
	printw("|I=up|K=dw|Y=yes|Q=quit|");
	
	if (v >= 1)
		printw("U=pgup|J=pgdw|CR=yes|ESC=quit|");
	
	if (v >= 2)
		printw("1=hom|9=end|");
}


/* This presents a menu in screen
   x, y = top left corner of the menu
   w, h = width, height of the menu
   *note* the selected item is remarked with > ITEM < so leave 2 chars more of width!
   
   MI_MENU_ARRAY *menulist = array with the list of items to show (strings)
   int cant = size in items of the array
	   
   Returns the index 0..cant-1 on MI_MENU_ARRAY or -1 if the user press ESC
   */
int do_my_menu( const int x, const int y, const int w, const int h,
	        const MI_MENU_ARRAY *menulist,
		const int cant)
{
int idx = 0; /* index of the selected item */			   
int c; /* key pressed */		
int i1, i2, i3, i4; /* for draw... */	
int redibujar = TRUE; /* redraw? */			  
			   
while (1) /* shitty loop... */			   
{			 
	if (redibujar)
	{
		redibujar=FALSE;
		draw_box(x, y, w, h, 1);
		
		i1 = idx - ((h-2)/2);
		if (i1<0) i1 = 0;
			
		i2 = i1 + h-2;
		if (i2 > cant-1) i2 = cant-1;
		
		i4=y+1;
		for (i3=i1; i3<i2+1;i3++)
		{
			move(i4,x+1);
			if (idx != i3) 
					printw(" %s", menulist[i3].menuitemstr);
				else
				{
					printw(">%s", menulist[i3].menuitemstr);
					move(i4,x+w-1);
					printw("<");
				}
			i4++;	
		}
		move(LINES-1, COLS-1); /* keep the cursor on top bottom... */
		refresh();
	}

	c = getch();
	
	switch (c)		   
	{
		case KEY_UP:
		case 'i':
		case 'I':
				idx--;
				redibujar=TRUE;
		break;
		
		case KEY_DOWN:
		case 'k':
		case 'K':
				idx++;
				redibujar=TRUE;		
		break;

		case KEY_PPAGE: /* page up en criollo */
		case 'u':
		case 'U':
				idx -= h;
				redibujar=TRUE;
		break;
		
		case KEY_NPAGE: /* page down */
		case 'j':
		case 'J':
				idx += h;
				redibujar=TRUE;		
		break;
		
		
		case KEY_HOME:
		case '1': /* home */
				idx = 0;
				redibujar=TRUE;		
		break;
		
		case KEY_END:
		case '9': /* end */
				idx = cant-1;
				redibujar=TRUE;
		break;
		
		case KEY_ENTER: /* no funciona con esta mierda... por eso lo de 10 y 13 */
		case 10:
		case 13:
		case 'y':
		case 'Y':
			return idx; 
		break;
		
		case KEY_CANCEL: /* esto funciona menos! metanse curses en el orto */
		case 27:	 
		case 'q':
		case 'Q':
			return -1;
		break;
	}		
	
	if (idx < 0) idx = cant-1;
	if (idx > cant-1) idx = 0;	
}			   
   
	   
return -1; /* should never get here... */
};
/* y vayanse a lavar las tetas */