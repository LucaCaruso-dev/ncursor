#include "lan.h"

char *getLocaleLanguage()
{
    return getenv("LANG");
}

bool testLanguage(char *lang)
{
    char nomefile[100];
    sprintf(nomefile, "%s%s.properties", LANG_FILE_DIR, lang);
    FILE *file = fopen(nomefile, "r");
    if (file)
        return true;
    return false;
}

char *getLanguage()
{
    char *lang = getLocaleLanguage();
    if (lang != NULL)
    {
        lang[2] = '\0';
        if (testLanguage(lang))
            return lang;
    }
    return DEFAULT_LANG;
}

char *getKey(char*key, char*lang) {
    char nomefile[100];
    sprintf(nomefile, "%s%s.properties", LANG_FILE_DIR, lang);
    FILE *file = fopen(nomefile, "r");
    if (!file) return key;
    char buffer[1024];
    while (fgets(buffer, 1024, file))
    {
        if (buffer[0] == '#') // commento
            continue;

        if (!strcmp(strtok(buffer, "="), key)) {
            fclose(file);
            return strtok(NULL, "\n");
        }
    }
    fclose(file);
    return key;
}