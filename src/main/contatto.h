#ifndef CONTATTO_H
#define CONTATTO_H

#include <curses.h>
#include "lan.h"

#define SelColor 10
#define NotSelColor 1

void drawContent(int select, char*nome, char*cognome, char*eta, char*numero, char*citta);
void searchButton();
void addButton();
void drawChangeModeButton();
void drawExitButton();

#endif