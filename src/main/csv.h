#ifndef CSV_H
#define CSV_H

#include <string.h>   // strtok()
#include <stdarg.h>   // va_list, va_start(), va_end()
#include <stdio.h>    // vsnprintf()
#include <stdlib.h>   // malloc()
#include <stdbool.h>

#define CSV_MAX_LINE 1024

#define CSV_FILE_NAME "saves.csv"
#define CSV_FILE_DIR "resources/"
#define CSV_FILE "resources/saves.csv"

char *csv_read_format(char *line, int ncols);
char *csv_write_format(char *format, ...);
bool csv_find_contatto(char*nome, char*cognome, char *eta, char *numero, char *citta);
void csv_save_contatto(char *nome, char *cognome, char *eta, char *numero, char *citta);

#endif