#include <curses.h> // Libreria per la gestione dell'interfaccia utente in modalità testo
#include <ctype.h>  // Libreria per funzioni di carattere
#include <string.h> // Libreria per funzioni di manipolazione delle stringhe

#include "contatto.h" // Inclusione del file header per la gestione dei contatti
#include "csv.h"      // Inclusione del file header per la gestione dei file CSV

#define MAX_STRLEN 100 // Definizione della lunghezza massima delle stringhe
int x, y; // Variabili per le dimensioni della finestra

// Struttura per rappresentare un contatto
typedef struct Contatto
{
    char nome[MAX_STRLEN];    // Nome del contatto
    char cognome[MAX_STRLEN]; // Cognome del contatto
    char eta[MAX_STRLEN];     // Età del contatto
    char numero[MAX_STRLEN];  // Numero di telefono del contatto
    char citta[MAX_STRLEN];   // Città del contatto
} Contatto;

int main()
{
    initscr();              // Inizializza la finestra
    getmaxyx(stdscr, x, y); // Ottiene le dimensioni massime della finestra
    keypad(stdscr, TRUE);   // Abilita la lettura dei tasti speciali (come le frecce)
    noecho();               // Disabilita l'eco dei caratteri
    nodelay(stdscr, TRUE);  // Rende getch() non bloccante
    curs_set(0);            // Nasconde il cursore

    // Variabili di stato per la gestione dell'interfaccia
    bool search = true;     // Modalità di ricerca
    bool change = true;     // Indica se è necessario ridisegnare l'interfaccia
    bool home = true;       // Indica se si è nella schermata principale
    bool enter_down = false; // Indica se il tasto Enter è stato premuto
    int select = 0;         // Indice per la selezione degli elementi
    bool quit = false;      // Indica se si deve uscire dal programma

    Contatto contatto;      // Dichiarazione di una variabile di tipo Contatto

    while (!quit) // Ciclo principale del programma
    {
        char ch = getch(); // Ottiene il carattere premuto dall'utente
        if (home) // Se ci si trova nella schermata principale
        {
            clear(); // Pulisce la finestra
            change = true; // Indica che è necessario ridisegnare
            select = 0; // Resetta la selezione
            // Inizializza i campi del contatto
            contatto.nome[0] = '\0';
            contatto.cognome[0] = '\0';
            contatto.eta[0] = '\0';
            contatto.numero[0] = '\0';
            contatto.citta[0] = '\0';
            home = false; // Cambia lo stato della schermata
        }

        if (change) // Se è necessario ridisegnare l'interfaccia
        {
            drawContent(select, contatto.nome, contatto.cognome, contatto.eta, contatto.numero, contatto.citta);
            if (search)
                searchButton(); // Disegna il pulsante di ricerca
            else
                addButton(); // Disegna il pulsante di aggiunta
            drawChangeModeButton(); // Disegna il pulsante per cambiare modalità
            drawExitButton(); // Disegna il pulsante di uscita

            change = false; // Resetta il flag di cambiamento
        }

        if (ch == ERR) // Se non ci sono tasti premuti
            continue;

        // Gestione dei tasti per il movimento
        switch (ch)
        {
        case KEY_DOWN: // Tasto giù
        case 2: // Codice per il tasto giù
            if (search) // Se si è in modalità ricerca
            {
                switch (select) // Gestione della selezione
                {
                case 0:
                    select = 1; // Passa alla selezione successiva
                    break;
                case 1:
                    select = 5; // Salta a un'altra selezione
                    break;
                case 5:
                    select = 6; // Passa alla selezione successiva
                    break;
                case 6:
                    select = 7; // Passa alla selezione successiva
                    break;
                case 7:
                    select = 8; // Passa alla selezione successiva
                    break;
                default:
                    select = 0; // Torna all'inizio
                    break;
                }
            }
            else // Se si è in modalità aggiunta
            {
                if (select < 8) // Se non si è già all'ultima selezione
                    select++; // Passa alla selezione successiva
            }
            change = true; // Indica che è necessario ridisegnare
            break;
        case 10: // Tasto Enter
            enter_down = true; // Imposta il flag di Enter
            break;
        case KEY_UP: // Tasto su
        case 3: // Codice per il tasto su
            if (search) // Se si è in modalità ricerca
            {
                switch (select) // Gestione della selezione
                {
                case 5:
                    select = 1; // Torna indietro
                    break;
                case 6:
                    select = 5; // Torna indietro
                    break;
                case 7:
                    select = 6; // Torna indietro
                    break;
                case 8:
                    select = 7; // Torna indietro
                    break;
                default:
                    select = 0; // Torna all'inizio
                    break;
                }
            }
            else // Se si è in modalità aggiunta
            {
                if (select) // Se non si è già all'inizio
                    select--; // Torna alla selezione precedente
            }
            change = true; // Indica che è necessario ridisegnare
            break;
        }

        if (search) // Se si è in modalità ricerca
        { 
            if (ch == 7) // Se il tasto 7 è premuto (cancellazione)
            {
                if (select == 0 && strlen(contatto.nome) > 0) // Se si sta modificando il nome
                    contatto.nome[strlen(contatto.nome) - 1] = '\0'; // Rimuove l'ultimo carattere
                if (select == 1 && strlen(contatto.cognome) > 0) // Se si sta modificando il cognome
                    contatto.cognome[strlen(contatto.cognome) - 1] = '\0'; // Rimuove l'ultimo carattere
                change = true; // Indica che è necessario ridisegnare
            }
            else if (isprint(ch)) // Se il carattere è stampabile
            {
                char temp[2] = {ch, '\0'}; // Crea una stringa temporanea
                if (select == 0 && strlen(contatto.nome) < MAX_STRLEN - 1) // Se si sta modificando il nome
                    strcat(contatto.nome, temp); // Aggiunge il carattere al nome
                if (select == 1 && strlen(contatto.cognome) < MAX_STRLEN - 1) // Se si sta modificando il cognome
                    strcat(contatto.cognome, temp); // Aggiunge il carattere al cognome
                change = true; // Indica che è necessario ridisegnare
            }

            if (enter_down) // Se il tasto Enter è stato premuto
            {
                if (select == 5) // Se si è selezionato il pulsante di ricerca
                {
                    if (!csv_find_contatto( // Cerca il contatto nel file CSV
                            contatto.nome,
                            contatto.cognome,
                            contatto.eta,
                            contatto.numero,
                            contatto.citta))
                    {
                        // Se il contatto non è stato trovato
                        contatto.eta[0] = '\0'; // Resetta l'età
                        contatto.numero[0] = '\0'; // Resetta il numero
                        contatto.citta[0] = '\0'; // Resetta la città
                    }
                    refresh(); // Aggiorna la finestra
                    napms(100); // Attende 100 millisecondi
                    change = true; // Indica che è necessario ridisegnare
                }
                else if (select == 6) // Se si è selezionato il pulsante di reset
                {
                    home = true; // Torna alla schermata principale
                }
                else if (select == 7) // Se si è selezionato il pulsante di cambio modalità
                {
                    home = true; // Torna alla schermata principale
                    search = false; // Cambia modalità
                }
                else if (select == 8) // Se si è selezionato il pulsante di uscita
                {
                    quit = true; // Imposta il flag di uscita
                }

                enter_down = false; // Resetta il flag di Enter
            }
        }
        else // Se si è in modalità aggiunta
        { 
            if (ch == 7) // Se il tasto 7 è premuto (cancellazione)
            {
                if (select == 0 && strlen(contatto.nome) > 0) // Se si sta modificando il nome
                    contatto.nome[strlen(contatto.nome) - 1] = '\0'; // Rimuove l'ultimo carattere
                if (select == 1 && strlen(contatto.cognome) > 0) // Se si sta modificando il cognome
                    contatto.cognome[strlen(contatto.cognome) - 1] = '\0'; // Rimuove l'ultimo carattere
                if (select == 2 && strlen(contatto.eta) > 0) // Se si sta modificando l'età
                    contatto.eta[strlen(contatto.eta) - 1] = '\0'; // Rimuove l'ultimo carattere
                if (select == 3 && strlen(contatto.numero) > 0) // Se si sta modificando il numero
                    contatto.numero[strlen(contatto.numero) - 1] = '\0'; // Rimuove l'ultimo carattere
                if (select == 4 && strlen(contatto.citta) > 0) // Se si sta modificando la città
                    contatto.citta[strlen(contatto.citta) - 1] = '\0'; // Rimuove l'ultimo carattere
                change = true; // Indica che è necessario ridisegnare
            }
            else if (isprint(ch)) // Se il carattere è stampabile
            {
                char temp[2] = {ch, '\0'}; // Crea una stringa temporanea
                if (select == 0 && strlen(contatto.nome) < MAX_STRLEN - 1) // Se si sta modificando il nome
                    strcat(contatto.nome, temp); // Aggiunge il carattere al nome
                if (select == 1 && strlen(contatto.cognome) < MAX_STRLEN - 1) // Se si sta modificando il cognome
                    strcat(contatto.cognome, temp); // Aggiunge il carattere al cognome
                if (select == 2 && strlen(contatto.eta) < MAX_STRLEN - 1) // Se si sta modificando l'età
                    strcat(contatto.eta, temp); // Aggiunge il carattere all'età
                if (select == 3 && strlen(contatto.numero) < MAX_STRLEN - 1) // Se si sta modificando il numero
                    strcat(contatto.numero, temp); // Aggiunge il carattere al numero
                if (select == 4 && strlen(contatto.citta) < MAX_STRLEN - 1) // Se si sta modificando la città
                    strcat(contatto.citta, temp); // Aggiunge il carattere alla città
                change = true; // Indica che è necessario ridisegnare
            }

            if (enter_down) // Se il tasto Enter è stato premuto
            {
                if (select == 5) // Se si è selezionato il pulsante di salvataggio
                {
                    csv_save_contatto(contatto.nome, // Salva il contatto nel file CSV
                                      contatto.cognome,
                                      contatto.eta,
                                      contatto.numero,
                                      contatto.citta);
                    home = true; // Torna alla schermata principale
                }
                else if (select == 6) // Se si è selezionato il pulsante di reset
                {
                    home = true; // Torna alla schermata principale
                }
                else if (select == 7) // Se si è selezionato il pulsante di cambio modalità
                {
                    home = true; // Torna alla schermata principale
                    search = true; // Cambia modalità
                }
                else if (select == 8) // Se si è selezionato il pulsante di uscita
                {
                    quit = true; // Imposta il flag di uscita
                }
                enter_down = false; // Resetta il flag di Enter
            }
        }
    }

    endwin(); // Termina la finestra
    return 0; // Restituisce 0 per indicare che il programma è terminato con successo
}
