#include "contatto.h" // Inclusione del file header per la gestione dei contatti

// Funzione per disegnare il pulsante di ricerca
void searchButton() {
    mvprintw(13, 1, "%s", getKey("Search", getLanguage())); // Stampa il testo del pulsante di ricerca
}

// Funzione per disegnare il pulsante di aggiunta
void addButton() {
    mvprintw(13, 1, "%s", getKey("Add", getLanguage())); // Stampa il testo del pulsante di aggiunta
}

// Funzione per disegnare il pulsante di cambio modalità
void drawChangeModeButton() {
    mvprintw(17, 1, "%s", getKey("Change mode", getLanguage())); // Stampa il testo del pulsante di cambio modalità
}

// Funzione per disegnare il pulsante di uscita
void drawExitButton() {
    mvprintw(19, 1, "%s", getKey("Exit", getLanguage())); // Stampa il testo del pulsante di uscita
}

// Funzione per disegnare il contenuto dell'interfaccia
void drawContent(int select, char *nome, char *cognome, char *eta, char *numero, char *citta)
{
    // mvprintw(y, x, format, ...);
    char *lang=getLanguage(); // Ottiene la lingua corrente

    clear(); // Pulisce la finestra
    mvprintw((select+1)*2+1, 0, "%c", '*'); // Segna la selezione corrente

    mvprintw(1, 1, "%s", getKey("Contact", lang)); // Stampa l'etichetta "Contatto"

    mvprintw(2, 1, "%s:", getKey("Name", lang)); // Stampa l'etichetta "Nome"
    mvprintw(3, 1, "%s", nome); // Stampa il nome del contatto

    mvprintw(4, 1, "%s:", getKey("Surname", lang)); // Stampa l'etichetta "Cognome"
    mvprintw(5, 1, "%s", cognome); // Stampa il cognome del contatto

    mvprintw(6, 1, "%s:", getKey("Age", lang)); // Stampa l'etichetta "Età"
    mvprintw(7, 1, "%s", eta); // Stampa l'età del contatto

    mvprintw(8, 1, "%s:", getKey("Phone", lang)); // Stampa l'etichetta "Telefono"
    mvprintw(9, 1, "%s", numero); // Stampa il numero di telefono del contatto

    mvprintw(10, 1, "%s:", getKey("City", lang)); // Stampa l'etichetta "Città"
    mvprintw(11, 1, "%s", citta); // Stampa la città del contatto

    mvprintw(15, 1, "%s", getKey("Home", lang)); // Stampa il pulsante di reset
}
