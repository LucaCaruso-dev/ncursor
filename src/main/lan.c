#include "lan.h" // Inclusione del file header per la gestione delle lingue

// Funzione per ottenere la lingua locale dall'ambiente
char *getLocaleLanguage()
{
    return getenv("LANG"); // Restituisce la variabile d'ambiente LANG
}

// Funzione per testare se un file di lingua esiste
bool testLanguage(char *lang)
{
    char nomefile[100]; // Buffer per il nome del file
    sprintf(nomefile, "%s%s.properties", LANG_FILE_DIR, lang); // Crea il nome del file
    FILE *file = fopen(nomefile, "r"); // Apre il file in lettura
    if (file) // Se il file esiste
        return true; // Restituisce true
    return false; // Altrimenti restituisce false
}

// Funzione per ottenere la lingua da utilizzare
char *getLanguage()
{
    char *lang = getLocaleLanguage(); // Ottiene la lingua locale
    if (lang != NULL) // Se la lingua non è nulla
    {
        lang[2] = '\0'; // Limita la lingua ai primi 2 caratteri
        if (testLanguage(lang)) // Testa se il file di lingua esiste
            return lang; // Restituisce la lingua
    }
    return DEFAULT_LANG; // Restituisce la lingua di default
}

// Funzione per ottenere il valore di una chiave da un file di lingua
char *getKey(char*key, char*lang) {
    char nomefile[100]; // Buffer per il nome del file
    sprintf(nomefile, "%s%s.properties", LANG_FILE_DIR, lang); // Crea il nome del file
    FILE *file = fopen(nomefile, "r"); // Apre il file in lettura
    if (!file) return key; // Se il file non esiste, restituisce la chiave

    char buffer[1024]; // Buffer per la lettura delle righe
    while (fgets(buffer, 1024, file)) // Legge il file riga per riga
    {
        if (buffer[0] == '#') // Se la riga è un commento
            continue; // Salta il commento

        // Se la chiave corrisponde, restituisce il valore associato
        if (!strcmp(strtok(buffer, "="), key)) {
            fclose(file); // Chiude il file
            return strtok(NULL, "\n"); // Restituisce il valore
        }
    }
    fclose(file); // Chiude il file
    return key; // Restituisce la chiave se non trovata
}
