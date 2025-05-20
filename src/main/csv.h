#ifndef CSV_H // Prevenzione della doppia inclusione
#define CSV_H

#include <string.h>   // Inclusione per strtok()
#include <stdarg.h>   // Inclusione per va_list, va_start(), va_end()
#include <stdio.h>    // Inclusione per vsnprintf()
#include <stdlib.h>   // Inclusione per malloc()
#include <stdbool.h>  // Inclusione per il tipo booleano

#define CSV_MAX_LINE 1024 // Definizione della lunghezza massima di una riga CSV

#define CSV_FILE_NAME "saves.csv" // Nome del file CSV
#define CSV_FILE_DIR "resources/" // Directory dei file CSV
#define CSV_FILE "resources/saves.csv" // Percorso completo del file CSV

// Dichiarazione delle funzioni
char *csv_read_format(char *line, int ncols);
char *csv_write_format(char *format, ...);
bool csv_find_contatto(char*nome, char*cognome, char *eta, char *numero, char *citta);
void csv_save_contatto(char *nome, char *cognome, char *eta, char *numero, char *citta);

#endif // Fine della protezione
