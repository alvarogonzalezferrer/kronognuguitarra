/*
   --------------------------------------------------------------------
   GNUitarra
   Copyright (c) 2002, Kronoman - All rights reserved
   In loving memory of my father.
   -----------------------------------------------------------------------
   guitdir.h
   This have the default location of the data 
   from where read the chords and the default name of the two files.
   Pretty ugly!
*/

#ifndef GUITARRA_DIR_H
#define GUITARRA_DIR_H

/* dir location of the data files 
   if this fails, will try with ./ and then die... 
   REMEMBER TO PUT THE LAST / */
#define GNUITARRA_DATA_DIR "/usr/local/share/gnuitarra/"

/* file name of the chord file */
#define GNUITARRA_CHORD_FILE "acordes.dat"

/* file name of the scales file */
#define GNUITARRA_SCALE_FILE "escalas.dat"

/* file name of the afination file */
#define GNUITARRA_AFINA_FILE "afinacio.dat"

#endif