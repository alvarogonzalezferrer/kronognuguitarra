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
 
/* drawfret.c - Fretboard routines
   By Kronoman
   In loving memory of my father
   AC/DC rocks!!!!
   Shake a leg baby...
*/

#include "drawfret.h"
#include "chordram.h"
#include "myincs.h"
#include <stdio.h>

/* global, note names... used by other modules (ui.c, etc) */
char *note_name[12] =  { "C ", "C#", "D ", "D#", "E ", "F ", "F#", "G " ,"G#", "A " , "A#", "B " };


/* helper to determine if the note belongs to the *chord in the tonica specified
	   returns -1 or the note */
int check_note_in_chord(const int note,
						const int tonica,
						const ARRAY_DOCE_NOTAS *chord)
{
	int x;
	for (x=0; x<12; x++)
	{
		if (chord->nota[x] > -1) /* the note is used? */
			if (((chord->nota[x])+tonica)%12 == note) return note; /* translates the note to tonic and test */
		}
	
	return -1; /* not found */	
}
	


/* this helper function fills a int[12][12] matrix
   with -1 or 0..11 numbers, representing notes
   Is useful for search patterns in a fretboard or to draw the fretboard with a full scale or chord note cloud
   int *matrix is a [12][12] matrix to contain the output
   the first index is the string, the 2nd the fret: matrix[string][fret]
   const ARRAY_DOCE_NOTAS *chord -> chord to represent
   const ARRAY_DOCE_NOTAS *afination -> afination to use
   const int tonica -> tonica a usar (C,D,etc)
 */
void do_fret_matrix (int matrix[][12],
					const ARRAY_DOCE_NOTAS *chord,
					const ARRAY_DOCE_NOTAS *afination,
					const int tonica)
{
int x = 0, y = 0, note = 0;
	
	
	/* scan the chords and fill the matrix with notes... */
	for (y=0; y<12; y++)	
	{	
		for (x=0; x<12; x++)
		{
			if (afination->nota[y] < 0) /* string not used... */
			{ matrix[y][x] = -1; } /* all the string is not used */
			else
			{
				if (x == 0) /* put the afination and start the note */
				{
					note = afination->nota[y];
				}
				else 
				{
					note++;
					note %= 12; /* keep into 0..11 range */
				}
				matrix[y][x] = check_note_in_chord(note, tonica, chord); /* put the filtered result into matrix */
			}
		}
	}
	
}

/* This is a helper that draws a matrix of char
   previously maded that has the representation of the fretboard
   This draws it on screen or a file previously opened
   Pass it:
   xp, yp = screen coordinates to draw the fretboard
   fp = pointer to a file, or NULL for screen
   char fretb[12][81] = the matrix with the PREVIOUSLY drawed fretboard!
*/
void help_draw_fretboard(const int xp, const int yp, char fretb[12][81], FILE *fp)
{
	int y;
    /* print guide numbers */
	if (fp == NULL)
	{
		move(yp,xp);
		printw("   0    1    2    3    4    5    6    7    8    9     10   11");
	}
	else
		fprintf((FILE *)fp, "   0    1    2    3    4    5    6    7    8    9     10   11\n");	
	
	/* print the fret */
	for (y=0; y < 12; y++)
	{
		if (fretb[y][0] != '\0') /* print only non empty strings... */
		{	
			if (fp == NULL)
			{
				move(y+yp+1, xp);
				printw("%2d %s", y+1 , fretb[y]);
			}
			else
			{
				fprintf((FILE *)fp, "%2d %s\n", y+1, fretb[y]);
			}
		}
	}
	
	if (fp != NULL ) refresh();
}


/* This fills the notes and then calls the helper to draw a fretboard 
   xp,yp coordinates of the top,left corner of the fretboard.
   *chord is a pointer to a "SINGLE" ARRAY_DOCE_NOTAS struct
   that has the list of notes to represent
   *afination is a pointer to a "SINGLE", ARRAY_DOCE_NOTAS struct
   that has the afination (and number of strings) of the instrument
   const int tonica -> tonica a usar (C,D,etc)
   FILE *fp is a pointer to a open file, for screen using
   ncurses put this to NULL, else put it to a fopen archive
   in text mode; and the output will be redirected there.

   NOTE: this routine represents only the first 12 frets
	of the instrument (all the octave, 0..11).
	The instrument has a maximum of 12 strings, and a minimum of 1

*/
void draw_fretboard(const int xp,
				    const int yp,
				 	const ARRAY_DOCE_NOTAS *chord,
					const ARRAY_DOCE_NOTAS *afination,
					const int tonica,
					const FILE *fp)
{
	/* fretboard, as will be seen in the screen,
	   with a maximum of 80 chars width, and 12 height 	   */
	char fretb[12][81];
	/* matrix with the arranged notes */
	int matrix[12][12];				
	int x,y, x1;
	
	/* fill the matrix */
	do_fret_matrix (matrix,	chord, afination, tonica);
	
	
	/* fill the fretb */
	for (y=0; y<12; y++)	
	{	
		if (afination->nota[y] > -1) /* is the string used? */
		{
			x1 = 0; /* pos in fretb */
			for (x=0; x<12; x++)
			{
				if (x == 0)
				{
					if (matrix[y][x] < 0)
						sprintf(&(fretb[y][0]), "  ||");
					else
						sprintf(&(fretb[y][0]), "%2s||", note_name[matrix[y][x]]);
								
					x1 += 4;
				}
				else
				{
					/* this prints: -[note]-| */
					sprintf(&(fretb[y][x1]), "-%2s-|",
							(matrix[y][x] >= 0) ? note_name[matrix[y][x]] : "--");
					x1 += 5;
				}
			}
			fretb[y][x1] = '\0';
		}
		else
		{	fretb[y][0] = '\0';}
	}
		
	/* throw it to screen / file */
    help_draw_fretboard(xp, yp, fretb, (FILE *)fp);
}