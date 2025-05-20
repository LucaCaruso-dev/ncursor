#include "csv.h" // Inclusione del file header per la gestione dei file CSV

// Funzione per leggere un formato CSV
char *csv_read_format(char *line, int ncols) {
    char*token; // Variabile per il token
    for (token = strtok(line, ";\n"); token != NULL; token = strtok(NULL, ";\n")) {
        if (!ncols--) // Se sono stati letti tutti i token richiesti
            return token; // Restituisce il token corrente
    }
    return NULL; // Restituisce NULL se non ci sono più token
}

// Funzione per scrivere un formato CSV
char *csv_write_format(char *format, ...){
    va_list args; // Lista di argomenti variabili
    va_start(args, format); // Inizializza la lista
    char *result = malloc(CSV_MAX_LINE); // Alloca memoria per il risultato
    if (result == NULL)
        return NULL; // Restituisce NULL se l'allocazione fallisce
    vsnprintf(result, CSV_MAX_LINE, format, args); // Scrive il formato nella stringa
    va_end(args); // Termina l'uso della lista
    return result; // Restituisce il risultato
}

// Funzione per salvare un contatto nel file CSV
void csv_save_contatto(char *nome, char *cognome, char *eta, char *numero, char *citta) {
    char *str = csv_write_format("%s;%s;%s;%s;%s\n", nome, cognome, eta, numero, citta); // Crea la stringa da salvare
    FILE*file = fopen(CSV_FILE, "a"); // Apre il file in modalità append
    if (!file) return; // Se il file non può essere aperto, esce dalla funzione
    fputs(str, file); // Scrive la stringa nel file
    fclose(file); // Chiude il file
}

// Funzione per cercare un contatto nel file CSV
bool csv_find_contatto(char *nome, char *cognome, char *eta, char *numero, char *citta) {
    FILE *file = fopen(CSV_FILE, "r"); // Apre il file in lettura
    if (!file) return false; // Se il file non può essere aperto, restituisce false

    char buffer[CSV_MAX_LINE] = ""; // Buffer per la lettura delle righe
    char buffer_temp[CSV_MAX_LINE] = ""; // Buffer temporaneo per la manipolazione

    while (fgets(buffer, CSV_MAX_LINE, file)) { // Legge il file riga per riga
        strcpy(buffer_temp, buffer); // Copia la riga nel buffer temporaneo
        char *nome_csv = csv_read_format(buffer_temp, 0); // Estrae il nome

        strcpy(buffer_temp, buffer); // Ripristina il buffer temporaneo
        char *cognome_csv = csv_read_format(buffer_temp, 1); // Estrae il cognome

        // Se il nome e il cognome corrispondono
        if (nome_csv && cognome_csv && 
            !strcmp(nome, nome_csv) && 
            !strcmp(cognome, cognome_csv)) {
            
            // Copia per età
            strcpy(buffer_temp, buffer); // Ripristina il buffer temporaneo
            strcpy(eta, csv_read_format(buffer_temp, 2)); // Estrae l'età

            // Copia per numero
            strcpy(buffer_temp, buffer); // Ripristina il buffer temporaneo
            strcpy(numero, csv_read_format(buffer_temp, 3)); // Estrae il numero

            // Copia per città
            strcpy(buffer_temp, buffer); // Ripristina il buffer temporaneo
            strcpy(citta, csv_read_format(buffer_temp, 4)); // Estrae la città

            fclose(file); // Chiude il file
            return true; // Restituisce true se il contatto è stato trovato
        }
    }
    
    fclose(file); // Chiude il file
    return false; // Restituisce false se il contatto non è stato trovato
}
