#ifndef LAN_H // Prevenzione della doppia inclusione
#define LAN_H

#include <stdlib.h> // Inclusione per funzioni di gestione della memoria
#include <stdbool.h> // Inclusione per il tipo booleano
#include <stdio.h> // Inclusione per funzioni di input/output
#include <string.h> // Inclusione per funzioni di manipolazione delle stringhe

#define DEFAULT_LANG "it" // Lingua di default
#define LANG_FILE_DIR "resources/lan/" // Directory dei file di lingua

// Dichiarazione delle funzioni
char *getLanguage();
char *getKey(char*key, char*lang);

#endif // Fine della protezione
