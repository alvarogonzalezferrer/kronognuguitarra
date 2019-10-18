/* This file has some routines to draw boxes 
   and clear boxes on screen
   Is made this way to easy port to windows/dos/etc
   Kronoman
   In loving memory of my father
   */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#include "textbox.h"
#include "myincs.h"

/* clears a box */
void clear_box(const int x, const int y, const int w, const int h)
{
	int x1,y1;
	for (y1 = y; y1 < y+h; y1++)
		for (x1 = x; x1 < x+w; x1++)
		{
			move(y1, x1);
			printw(" ");
		}
}

/* draws a box from x,y width w,h, if fill != 0, clears with ' ' the box */ 
void draw_box(const int x, const int y, const int w, const int h, const int fill)
{
    int x1, y1;
	
	if (fill != 0)
		clear_box(x, y, w, h);
	
	
	for (x1 = x; x1 < x+w; x1++)
		{
			move(y, x1);
			addch(ACS_HLINE);
			move(y+h, x1);
			addch(ACS_HLINE);
		}
	
	for (y1 = y; y1 < y+h; y1++)
		{
			move(y1, x);
			addch(ACS_VLINE);
			move(y1, x+w);
			addch(ACS_VLINE);
		}
	
	/* corners */
	move(y,x);
	addch(ACS_ULCORNER);
	move(y,x+w);
	addch(ACS_URCORNER);

	move(y+h,x);
	addch(ACS_LLCORNER);
	
	move(y+h,x+w);
	addch(ACS_LRCORNER);
	
	refresh();	
};