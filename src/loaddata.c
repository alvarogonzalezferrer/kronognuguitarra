/*
   -----------------------------------------------------------------------
   GNUitarra
   Copyright (c) 2002, Kronoman - All rights reserved
   In loving memory of my father
   -----------------------------------------------------------------------
   loaddata.c
   This loads/unloads the datafiles from disk into RAM memory
   using the scheme of brute force arrays using malloc -:^(
*/


/* NOTA: este modulo fue una puta, me dio un trabajo barbaro.
   Si no les gusta, vayanse a lavar las tetas */

/* define this to debug this module */
/* define KRONO_QUIERE_DEBUG */  /* DEBUG: definir esto 'crashea' la aplicacion... que pasa? */
			         /* DEBUG: I SUSPECT THAT USING THIS #define core dumps the app.. why? */
#include <string.h>
#include <ctype.h>
#include "guitdir.h"
#include "myincs.h"
#include "chordram.h"
#include "loaddata.h"
#include "krstring.h"
/*-------------------------------------------------
   This loads the datafiles from disk

   const char *dir is the dir where the file is; *MUST* contain the last /
   const char *file is the file having the data
   MI_MENU_ARRAY **name is the &structure that will have
   the names of each chord/whatever
   ARRAY_DOCE_NOTAS **notes is the &structure that will have
   the twelve notes matrix for each data
   int *itemsize will be modified to contain the number of items readed

   If each pointer to struct are not NULL, the data will be appended to it,
   if are NULL, will be first malloc, and then realloc...
   If fails, returns TRUE; if sucefull, FALSE
   Free the memory of the structs before calling this and set the itemsize to 0
   -------------------------------------------------*/
int load_guitar_data(const char *dir, const char *file,
					  MI_MENU_ARRAY **list,
					  ARRAY_DOCE_NOTAS **notes,
					  int *itemsize)
{
	FILE *fp = NULL;
	char *str1 = NULL;	 /* temporal string to store paths and whatever */
	char str2[128]; /* file I/O reading buffer */
    char str3[128], str4[128]; /* buffer string for trim trailing spaces, filter extrange chars, etc */
	int i = 0, i1 = 0, i2 = 0; /* fors, etc */
	int validline = FALSE; /* flag for validating format of the input line... */
	int notaidx = 0; /* index of note readed 0..11 */



	str1 = (char *)malloc(sizeof(char) * (strlen(dir)+strlen(file)+1)); /* enough space to store full path */
    if (str1 == NULL)
	{
	/* ugly computer! not enough RAM! */
	/* DEBUG: usar GETTEXT! */
	printf("FATAL ERROR:\nload_guitar_data:\nFailed to alloc RAM to init the path... sorry\n");
	return -1;
	}
	
	/* make the path */
	sprintf(str1,"%s%s",dir, file); /* chord file */
#ifdef KRONO_QUIERE_DEBUG
   printf("Path: %s\n", str1);
#endif
	/* open the dir/file and read it as plain text */
	fp = fopen(str1,"rt");
	if (fp == NULL ) return TRUE; /* error! */

	if (str1 != NULL) { free(str1); str1 = NULL; }	 /* free RAM */

	/* read line to line, parse it and send it to RAM... */
	while (fgets(str2, 80, fp) != NULL)
	{
		validline = FALSE; /* still not a valid line */

		/* filter text */
		for (i = 0; str2[i] != '\0'; i++)
			{
			if (str2[i] < ' ') str2[i] = ' '; /* erases al control caracteres below the space... */
			if (str2[i] == '|') validline = TRUE; /* has the special separator, is valid - DEBUG: DO A BETTER CHECK! */
			}
		/* trim trailing spaces */
		krtrim(str3, str2);
		sprintf(str2, "%s", str3);

		if (strlen(str2) > 1 && validline) /* add only if not blank line or invalid one */
		{
			(*itemsize)++; /* other more! */

			/* allocate RAM */
			if ( *list == NULL)
					*list = (MI_MENU_ARRAY *)malloc(sizeof(MI_MENU_ARRAY));
				else
					*list = (MI_MENU_ARRAY *)realloc(*list, sizeof(MI_MENU_ARRAY) * ((*itemsize)+1));

				if (*list == NULL) /* not enough RAM, die... */
					{
					printf("FATAL ERROR:\nload_guitar_data:\nFailed to alloc RAM to add item to *list\n");
					return -1;
					}

			if ( *notes == NULL)
					*notes = (ARRAY_DOCE_NOTAS *)malloc(sizeof(ARRAY_DOCE_NOTAS));
				else
					*notes  = (ARRAY_DOCE_NOTAS *)realloc(*notes , sizeof(ARRAY_DOCE_NOTAS) * ((*itemsize)+1));

				if (*notes  == NULL) /* not enough RAM, die... */
					{
					printf("FATAL ERROR:\nload_guitar_data:\nFailed to alloc RAM to add item to *notes\n");
					return -1;
					}
			/* reset flag status of each note */
			for (i=0; i<12; i++) (*notes)[(*itemsize)-1].nota[i] = -1;

			/* pick the name, is all before the first '|' */
			for (i=0; str2[i] != '|' && i < MAX_MENUSTR_LEN - 1; i++)
				(*list)[(*itemsize)-1].menuitemstr[i] = str2[i];

				(*list)[(*itemsize)-1].menuitemstr[i] = '\0'; /* finish the string... */
			/* now, pick the remaining in other string - important; 'i' must have the value returned from the previous for! */
			i1 = 0;
			for (i=i; str2[i] != '\0' && i < 128; i++)
					{
					/* copy only digits and , */
					if (str2[i] == ',' || isdigit(str2[i]))
						{
							str3[i1] = str2[i]; i1 ++;
						}
					}
			str3[i1] = '\0'; /* finish string */

			/* now, I interpret each value separated by , like a number an set that value
			   in the notes array */
			i = i1 =  0;
			str4[0]='\0';
			notaidx = 0;
			while (str3[i] != '\0' && notaidx < 12)
			{
				if (str3[i] != ',')
				{
					str4[i1] = str3[i]; /* add digit */
					i1++;
				}
				if (str3[i] == ',' || str3[i+1] == '\0')
				{
					str4[i1] = '\0';
					/* found end of a number */
					i2 = atoi(str4);


#ifdef KRONO_QUIERE_DEBUG
				/* DEBUG INFO */
				printf("%s = %d\n", str4, i2);
#endif
					if (i2 >= 0  && i2 <= 11)
							(*notes)[(*itemsize)-1].nota[notaidx] = i2;

					notaidx++;
					str4[0] = '\0';
					i1 = 0;
				}
				i++;
			}

#ifdef KRONO_QUIERE_DEBUG
			/* DEBUG... */
			printf("[%d] %s = %s - %s \n", *itemsize,  str2, (*list)[(*itemsize)-1].menuitemstr, str3);
			for (i=0; i < 12; i++)
				printf("%d\t", (*notes)[(*itemsize)-1].nota[i]); 
			printf("\n");
#endif

		}
	}

	fclose(fp);

	
	
	return FALSE;
};


/*-------------------------------------------------
  This function frees all the data stuff and
  reset the counters.
  Call this before calling load_all_data
  -------------------------------------------------*/
void free_all_data(void)
{
	
if (chord_list != NULL) free(chord_list);
if (chord_note != NULL) free(chord_note);

if (scale_list != NULL) free(scale_list);
if (scale_note != NULL) free(scale_note);

if (afination_list != NULL) free(afination_list);
if (afination_note != NULL) free(afination_note);

	chord_list = NULL;
	chord_note = NULL;
	chord_size = 0;

	scale_list = NULL;
	scale_note = NULL;
	scale_size = 0;

	afination_list = NULL;
	afination_note = NULL;
	afina_size = 0;

}

/*-------------------------------------------------
  This function loads all the data stuff into 
  memory using the default paths.
  Free the used memory before calling this!
  -------------------------------------------------*/
void load_all_data(void)
{
	/* This goes appending the data files in RAM */
	/* searches in the usr/share/gnuitarra, ~/gnuitarra, and ./  */

	/* load afinations file */
	load_guitar_data(GNUITARRA_DATA_DIR,
					 GNUITARRA_AFINA_FILE,
					 &afination_list,
					 &afination_note,
					 &afina_size );

   load_guitar_data("~/gnuitarra/",
					 GNUITARRA_AFINA_FILE,
					 &afination_list,
					 &afination_note,
					 &afina_size );

   load_guitar_data("./",
					 GNUITARRA_AFINA_FILE,
					 &afination_list,
					 &afination_note,
					 &afina_size );

	/* load chords file */
	load_guitar_data(GNUITARRA_DATA_DIR,
					 GNUITARRA_CHORD_FILE,
					 &chord_list,
					 &chord_note,
					 &chord_size );

   load_guitar_data("~/gnuitarra/",
					 GNUITARRA_CHORD_FILE,
					 &chord_list,
					 &chord_note,
					 &chord_size );

   load_guitar_data("./",
					 GNUITARRA_CHORD_FILE,
					 &chord_list,
					 &chord_note,
					 &chord_size );

	/* load scales file */
  
  load_guitar_data(GNUITARRA_DATA_DIR,
					 GNUITARRA_SCALE_FILE,
					 &scale_list,
					 &scale_note,
					 &scale_size );

   load_guitar_data("~/gnuitarra/",
					 GNUITARRA_SCALE_FILE,
					 &scale_list,
					 &scale_note,
					 &scale_size );

   load_guitar_data("./",
					 GNUITARRA_SCALE_FILE,
					 &scale_list,
					 &scale_note,
					 &scale_size );
					 
/* checks if any data was loaded... else fail... */
	if (afina_size < 1) 
	{
		printf("ERROR! There is not any afination data! I can't continue!\n%s is missing.\n", GNUITARRA_AFINA_FILE);
		exit(-1);
	}
	if (chord_size < 1) 
	{
		printf("ERROR! There is not any chords data! I can't continue!\n%s is missing.\n", GNUITARRA_CHORD_FILE);
		exit(-1);
	}
	if (scale_size < 1) 
	{
		printf("ERROR! There is not any scales data! I can't continue!\n%s is missing.\n", GNUITARRA_SCALE_FILE);
		exit(-1);
	}
						 
};
