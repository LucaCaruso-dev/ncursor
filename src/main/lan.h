#ifndef LAN_H
#define LAN_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_LANG "it"
#define LANG_FILE_DIR "resources/lan/"

char *getLanguage();
char *getKey(char*key, char*lang);

#endif