#ifndef CONTATTO_H // Prevenzione della doppia inclusione
#define CONTATTO_H

#include <curses.h> // Inclusione per la gestione dell'interfaccia utente in modalità testo
#include "lan.h" // Inclusione del file header per la gestione delle lingue

#define SelColor 10 // Colore per la selezione
#define NotSelColor 1 // Colore per la non selezione

// Dichiarazione delle funzioni per la gestione dei contatti
void drawContent(int select, char*nome, char*cognome, char*eta, char*numero, char*citta);
void searchButton();
void addButton();
void drawChangeModeButton();
void drawExitButton();

#endif // Fine della protezione
