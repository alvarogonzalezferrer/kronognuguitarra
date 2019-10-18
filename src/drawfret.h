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

/* This is how the fretboard should look  :^D
  0    1    2    3    4    5    6    7    8    9   10   11  
1 E||----|----|----|----|----|----|----|----|----|----|----|
2 B||----|----|----|----|----|----|----|----|----|----|----|
3 G||----|----|----|----|----|----|----|----|----|----|----|
4 D||----|----|----|----|----|----|----|----|----|----|----|
5 A||----|----|----|----|----|----|----|----|----|----|----|
6 E||----|----|----|----|----|----|----|----|----|----|----|
etc... for more strings... :^P
*/

/* drawfret.c - Fretboard routines
   By Kronoman
   In loving memory of my father
   AC/DC rocks!!!!
   Chase the Ace!
*/


#ifndef DRAWFRET_H
#define DRAWFRET_H

#include "chordram.h"
#include "myincs.h"
/* names of the notes 0..11:
[C ][C#][D ][D#][E ][F ][F#][G ][G#][A ][A#][B ]
[0 ][ 1][2 ][3 ][4 ][5 ][6 ][7 ][8 ][9 ][10][11]
 */
extern char *note_name[12];
		

/* prototypes */
		
int check_note_in_chord(const int note,
						const int tonica,
						const ARRAY_DOCE_NOTAS *chord);


void do_fret_matrix (int matrix[][12],
					const ARRAY_DOCE_NOTAS *chord,
					const ARRAY_DOCE_NOTAS *afination,
					const int tonica);

void help_draw_fretboard(const int xp, const int yp, char fretb[12][81], FILE *fp);

void draw_fretboard(const int xp,
					const int yp,
					const ARRAY_DOCE_NOTAS *chord,
					const ARRAY_DOCE_NOTAS *afination,
					const int tonica,
					const FILE *fp);

#endif