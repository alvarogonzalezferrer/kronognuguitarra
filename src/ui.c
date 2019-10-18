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
   I mean, this is the UI, all the menus, about, stuff comes from here
   The engine for the menus is in mimenu.*
*/

#include "myincs.h"
#include "chordram.h"
#include "mimenu.h" 
#include "textbox.h"
#include "ui.h"
#include "drawfret.h"

/*-------------------------------------------------
   This starts the show of the user interface
   and starts the main menu 
   -------------------------------------------------*/
void start_user_interface(void)
{
    MI_MENU_ARRAY ui_menu[10]; /* generic container for a menu */
	int salir = FALSE; /* salir? */
	int ret = 0; /* menu choose */
	int afinacion_actual = 0; /* afinacion actual en uso 0..afina_size-1 */
	
	/* set main menu - DEBUG - usar GETTEXT! */
	sprintf(ui_menu[0].menuitemstr, "Escalas   / Scales");
	sprintf(ui_menu[1].menuitemstr, "Acordes   / Chords");
	sprintf(ui_menu[2].menuitemstr, "Afinacion / Tune");
	sprintf(ui_menu[3].menuitemstr, "Buscar    / Search ");
	sprintf(ui_menu[4].menuitemstr, "Acerca de / About");
	sprintf(ui_menu[5].menuitemstr, "Salir     / Exit");
	
clear();
	
/* inner loop */
while (!salir)
{
   move(0,0);
   printw(GUITARRA_STR_VERSION);
   printw("\nBienvenido! - Welcome!\n");
	/* el refresh lo hace el mismo menu... */
	
	/* show little help on bottom screen */
	if (COLS>75)
		my_menu_help(0, LINES-2, 2 );
	else if (COLS > 40)
			my_menu_help(0, LINES-2, 1 );
		 else
			my_menu_help(0, LINES-2, 0 );
	
	/* do the menu */
	move(3, 1);
	printw("[ ] Menu principal / Main menu   ");
	/* do whatever choose the user */
	ret = do_my_menu(1, 4, 30, 6, ui_menu, 6);
	switch (ret)
	{
	case 0: /* scales */
		move(3, 1);
		printw("[ ] Escalas / Scales (%d loaded)   ", scale_size);
		ret = do_my_menu(1, 4, MAX_MENUSTR_LEN + 5,15, scale_list, scale_size);
		
		/* mostrar la escala seleccionada! */
		if (ret >= 0)  interactive_fret(scale_list,  scale_note, scale_size, ret, afinacion_actual);

		clear();
		refresh();
	break;		
	
	case 1: /* chords */
		move(3, 1);
		printw("[ ] Acordes / Chords (%d loaded)   ", chord_size);
		ret = do_my_menu(1, 4, MAX_MENUSTR_LEN + 5, 15, chord_list, chord_size);
	    /* mostrar el acorde seleccionado! */
		if (ret >= 0)  interactive_fret(chord_list,  chord_note, chord_size, ret, afinacion_actual);
		
		clear();
		refresh();
	break;	
	
	case 2: /* tune / afination / afinacion */
		move(3, 1);
		printw("[ ] Afinacion  - Tune (%d loaded)  ", afina_size);
		ret = do_my_menu(1, 4, MAX_MENUSTR_LEN + 5, 15, afination_list, afina_size);
		/* changes the afination - cambia la afinacion */
		if (ret >= 0 && ret < afina_size) afinacion_actual = ret;
		
		clear();
		refresh();
	break;	
	
	case 3: /* search */
		clear();
		printw("This function is not finished. Sorry...!\n\rui.c, line 103\n\n\rPress a key");
	    refresh();
	    getch();
		clear();
	break;	
	
	case 4: /* about */
		/* DEBUG: USAR GETTEXT! */
		draw_box(5,5,40,11,-1);
		move(6,6);printw(GUITARRA_STR_VERSION);
		move(8,6); printw("Copyright (c) 2002, Kronoman");
		move(9,6); printw("In loving memory of my father");
		move(10,6); printw("Under GNU GPL License.");
		move(11,6); printw("NO WARRANTY OF ANY KIND!");
		move(12,6); printw("Get updates at:");
		move(13,6); printw("%s", GUITARRA_HOME_PAGE);
		move(15,6); printw("-- Press a key to continue --");
		refresh();
		ret = getch();
		clear();
		refresh();
	break;		
	
	case 5: /* quit */
		salir = TRUE;
	break;	
		
	}	
	
}    /* end main loop */

clear();
refresh();

};



/* This function presents the interactive fretboard
   using the family of scale/chord/whatever passed in the parameters,
   and starting with the selected one.
   This is interactive!

   *list is the list of names of the chords/scales/whatever
   *notes the list of notes of the chords/scales/whatever
   itemsize the quantity of chords/scales/whatever
   idx the starting chord selected 
   afina is the starting afination selected

	NOTE: for the afination list/names, I use the global vars...
*/
void interactive_fret(MI_MENU_ARRAY *list,
					  ARRAY_DOCE_NOTAS *notes,
					  const int itemsize,
					  int idx,
					  int afina)

{
	int salir = FALSE;
	int redibujar = TRUE;
	int tonica = 0; /* tonic, C default */
	int g = 0; /* keys */
	char txt[512]; /* buffer multiuso */
	FILE *fp; /* pointer to save files */
	
	while(!salir)
	{
	if (redibujar)
		{
			redibujar = FALSE;
			clear();
			/* draw the selected one */
			move(0,0);
			printw("Name      -> %s\n\r", list[idx].menuitemstr);
			printw("Afination -> %s\n\r", afination_list[afina].menuitemstr);
			/* Mostrar afinacion */
			printw("Strings   -> ");
			
			for (g = 0; g < 12; g++) /* mostrar notas */
				printw("%2s ", (afination_note[afina].nota[g] > -1) ? note_name[afination_note[afina].nota[g]] : "  ") ;
			
			printw("\n\rTonic     -> %s\n\r", note_name[tonica]); 
			printw("Notes     -> ");
	
			for (g = 0; g < 12; g++) /* mostrar notas */
				printw("%2s ", (check_note_in_chord(g, tonica, &(notes[idx])) > -1) ? note_name[g] : "  ") ;
			
			
			/* The fretboard draw is here! */
			draw_fretboard(0, 6, &(notes[idx]), &(afination_note[afina]), tonica,  NULL);
			
			printw("\n\n\rPress 'b' for help - Presione 'b' para ayuda.");
			
			move(LINES-1, COLS-1); /* keep the cursor on top bottom... */	
			refresh();
		}

		g = getch();
		/* DEBUG: FALTAN MAS FUNCIONES (SALVAR, BUSCAR, ETC!) */
		switch(g)
		{
		case KEY_UP: /* cambia acorde */
		case 'i':
		case 'I':
				idx--;
				redibujar=TRUE;
		break;
		
		case KEY_DOWN: /* cambia acorde */
		case 'k':
		case 'K':
				idx++;
				redibujar=TRUE;		
		break;

		case KEY_LEFT: /* cambia tonica */
		case 'u':
		case 'U':
				tonica--;
				redibujar=TRUE;
		break;
		
		case KEY_RIGHT: /* cambia tonica */
		case 'j':
		case 'J':
				tonica++;
				redibujar=TRUE;
		break;
		
		
		case 's': /* S = salvar */
		case 'S':
			txt[0] = '\0';
			fp = NULL;
			clear_box(0, 0, COLS-5 , 6 );
		    move (0,0);
		
			printw("\n\rSave the diagram (the file will be appended if exists already)\n\rPlease enter the file:\n\r");
			printw("?");
			refresh();
			echo(); /* para que muestre las letras */
			wgetnstr ( stdscr, txt, 511); /* leer la cadena */
			noecho();
			/* abrir y salvar, append at the end */ 
		    fp = fopen(txt, "at");
			if (fp != NULL)
			{
				/* 'draw' to disk aka save it! */
				
				/* Header + fretboard */
				fprintf(fp, "Name      -> %s\n", list[idx].menuitemstr);
				fprintf(fp, "Afination -> %s\n", afination_list[afina].menuitemstr);
				/* Mostrar afinacion */
				fprintf(fp, "Strings   -> ");
				for (g = 0; g < 12; g++) /* mostrar notas */
					fprintf(fp, "%2s ", (afination_note[afina].nota[g] > -1) ? note_name[afination_note[afina].nota[g]] : "  ") ;

				fprintf(fp, "\nTonic     -> %s\n", note_name[tonica]); 
				fprintf(fp, "Notes     -> ");
				for (g = 0; g < 12; g++) /* mostrar notas */
					fprintf(fp, "%2s ", (check_note_in_chord(g, tonica, &(notes[idx])) > -1) ? note_name[g] : "  ") ;
				fprintf(fp, "\n\n");
				draw_fretboard(0, 0, &(notes[idx]), &(afination_note[afina]), tonica,  fp);
				fprintf(fp, "\n\n");
				/* all OK... */
				
				printw("File saved...\n\r");
				fclose(fp);
			}
			else
			{
				printw("ERROR: failed opening the file!\n\r");
			}
			printw("Press a key to continue...");
			getch();
			refresh();
			fp = NULL;
			redibujar=TRUE;
		break;
		
		/* cambiar afinacion */
		case KEY_PPAGE: /* page up en criollo */
		case 'y':
		case 'Y':
			afina--;	
			redibujar=TRUE;
		break;	

		case KEY_NPAGE: 
		case 'h':
		case 'H':
			afina++;	
			redibujar=TRUE;
		break;	
		
		/* debug: faltan teclas para digitaciones, custom, etc */
		
		
		case 'b': /* AYUDA */
		case 'B':
			clear();
			printw("Sorry, help not finished...\n\rui.c, 302\n\rPress a key...");
		    refresh();
			getch();
			redibujar=TRUE;
		break;
		
		case 27:
		case 'q':
		case 'Q':
				salir = TRUE;
		}
		
		/* security checks */
		if (idx < 0) idx = itemsize-1;
		if (idx > itemsize-1) idx = 0;
		if (afina > afina_size-1) afina = 0;
		if (afina < 0) afina = afina_size-1;
		if (tonica > 11) tonica = 0;
	    if (tonica < 0 ) tonica = 11;
	}
}






