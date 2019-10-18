/* -----------------------------------------------------------------------
   GNUitarra
   Copyright (c) 2002, Kronoman - All rights reserved
   In loving memory of my father
   -----------------------------------------------------------------------
   Simple program for powerful scale/chord construction for guitars.
   Works fine with guitars.
   Theorically it must work with any cord instrument.
   Made by Kronoman.
   In loving Memory of my father.
   Made in Argentina. (Suck this IMF!)
   Started in August 2002.
   -----------------------------------------------------------------------
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
   -----------------------------------------------------------------------
   mainfile.h
   This has some usefult things...
*/


#ifndef MAINFILE_H
#define MAINFILE_H

/* Titulo de la aplicacion */
#define GUITARRA_TITULO  "GNUitarra beta"

/* Version: max.min.rev */
#define GUITARRA_VER_MAX 0
#define GUITARRA_VER_MIN 1
#define GUITARRA_VER_REV 1

/* string de la version
   usar asi: printf(GUITARRA_STR_VERSION); */
#define GUITARRA_STR_VERSION "%s %d.%d.%d", GUITARRA_TITULO, GUITARRA_VER_MAX, GUITARRA_VER_MIN, GUITARRA_VER_REV

/* www of gnuitarra */
#define GUITARRA_HOME_PAGE "http://gnuitarra.sourceforge.net/"

/* Un par de pavadas para tener convencionalismos en C */
#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE -1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#endif