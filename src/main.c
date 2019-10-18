/*
   -----------------------------------------------------------------------
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
   main.c
   This has the startup code.
*/

#include "loaddata.h"
#include "myincs.h"
#include "ui.h"

/*-------------------------------------------------*/
/* main - Entry point */
int main(int argc, char *argv[])
{
	
/* interpret command-line parameters */
   /* DEBUG - FALTA HACER! */

   /* load datafiles */
   printf(GUITARRA_STR_VERSION);
   /* DEBUG: usar GETTEXT! */
   printf("\nEspere/Wait... loading data files...\n");

	chord_list = NULL;	chord_note = NULL;
	scale_list = NULL;	scale_note = NULL;
	afination_list = NULL;	afination_note = NULL;

	free_all_data();
	load_all_data();
/* DEBUG: usar GETTEXT! */
printf("Data loaded -> starting program...\r");


/* all this stuff inits the ncures library */
   initscr();
   clear();
   cbreak();
   keypad(stdscr, TRUE);
   noecho();


/* enter the main loop */
   start_user_interface();

/* free RAM, for those OS that don't do by itselfs... */
   free_all_data();

/* clean up ncurses */
   endwin();

printf("All OK... bye, bye...             \n");

/* bye message */
/* DEBUG: usar GETTEXT! */
   printf(GUITARRA_STR_VERSION);
   printf("\nCopyright (c) 2002, Kronoman\nDistributed under GNU GPL License\nIn loving memory of my father.\n\n");
   printf("Get updates at:\n%s\n", GUITARRA_HOME_PAGE);
return 0; /* all OK! */
};