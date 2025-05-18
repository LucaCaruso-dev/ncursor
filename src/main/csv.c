#include "csv.h"

char *csv_read_format(char *line, int ncols) {
    char*token;
    for (token = strtok(line, ";\n"); token != NULL; token = strtok(NULL, ";\n")) {
        if (!ncols--)
            return token;
    }
    return NULL;
}

char *csv_write_format(char *format, ...){
    va_list args;
    va_start(args, format);
    char *result = malloc(CSV_MAX_LINE);
    if (result == NULL)
        return NULL;
    vsnprintf(result, CSV_MAX_LINE, format, args);
    va_end(args);
    return result;
}

void csv_save_contatto(char *nome, char *cognome, char *eta, char *numero, char *citta) {
    char *str = csv_write_format("%s;%s;%s;%s;%s\n", nome, cognome, eta, numero, citta);
    FILE*file = fopen(CSV_FILE, "a");
    if (!file) return;
    fputs(str, file);
    fclose(file);
}

bool csv_find_contatto(char *nome, char *cognome, char *eta, char *numero, char *citta) {
    FILE *file = fopen(CSV_FILE, "r");
    if (!file) return false;

    char buffer[CSV_MAX_LINE] = "";
    char buffer_temp[CSV_MAX_LINE] = "";
    
    while (fgets(buffer, CSV_MAX_LINE, file)) {
        strcpy(buffer_temp, buffer);
        char *nome_csv = csv_read_format(buffer_temp, 0);

        strcpy(buffer_temp, buffer);
        char *cognome_csv = csv_read_format(buffer_temp, 1);

        if (nome_csv && cognome_csv && 
            !strcmp(nome, nome_csv) && 
            !strcmp(cognome, cognome_csv)) {
            
            // Copia per età
            strcpy(buffer_temp, buffer);
            strcpy(eta, csv_read_format(buffer_temp, 2));

            // Copia per numero
            strcpy(buffer_temp, buffer);
            strcpy(numero, csv_read_format(buffer_temp, 3));

            // Copia per città
            strcpy(buffer_temp, buffer);
            strcpy(citta, csv_read_format(buffer_temp, 4));

            fclose(file);
            return true;
        }
    }
    
    fclose(file);
    return false;
}