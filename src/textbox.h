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


#ifndef GNUITARRA_TEXTBOX_H
#define GNUITARRA_TEXTBOX_H

#ifdef __cplusplus
extern "C"
{
#endif

	

/* prototypes */	
void clear_box(const int x, const int y, const int w, const int h);
void draw_box(const int x, const int y, const int w, const int h, const int fill);
	
	
	
#ifdef __cplusplus
}
#endif

#endif /* GNUITARRA_TEXTBOX_H */