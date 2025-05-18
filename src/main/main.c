#include <curses.h>
#include <ctype.h>
#include <string.h>

#include "contatto.h"
#include "csv.h"

#define MAX_STRLEN 100
int x, y;

typedef struct Contatto
{
    char nome[MAX_STRLEN];
    char cognome[MAX_STRLEN];
    char eta[MAX_STRLEN];
    char numero[MAX_STRLEN];
    char citta[MAX_STRLEN];
} Contatto;

int main()
{
    initscr();              // Initialize the window
    getmaxyx(stdscr, x, y); // Get the maximum x & y coordinates
    keypad(stdscr, TRUE);   // Abilita la lettura dei tasti speciali (come le frecce)
    noecho();               // Disabilita l'echo dei caratteri
    nodelay(stdscr, TRUE);  // Rende getch() non bloccante
    curs_set(0);            // Nasconde il cursore
    // start_color();

    bool search = true;
    bool change = true;
    bool home = true;
    bool enter_down = false;
    int select = 0;
    bool quit = false;

    Contatto contatto;

    while (!quit)
    {
        char ch = getch();
        if (home)
        {
            clear();
            change = true;
            select = 0;
            contatto.nome[0] = '\0';
            contatto.cognome[0] = '\0';
            contatto.eta[0] = '\0';
            contatto.numero[0] = '\0';
            contatto.citta[0] = '\0';
            home = false;
        }

        if (change)
        {
            drawContent(select, contatto.nome, contatto.cognome, contatto.eta, contatto.numero, contatto.citta);
            if (search)
                searchButton();
            else
                addButton();
            drawChangeModeButton();
            drawExitButton();

            change = false;
        }

        if (ch == ERR)
            continue;

        // gestione tasti per movimento
        switch (ch)
        {
        case KEY_DOWN:
        case 2:
            if (search)
            {
                switch (select)
                {
                case 0:
                    select = 1;
                    break;
                case 1:
                    select = 5;
                    break;
                case 5:
                    select = 6;
                    break;
                case 6:
                    select = 7;
                    break;
                case 7:
                    select = 8;
                    break;
                default:
                    select = 0;
                    break;
                }
            }
            else
            {
                if (select < 8)
                    select++;
            }
            change = true;
            break;
        case 10:
            enter_down = true;
            break;
        case KEY_UP:
        case 3:
            if (search)
            {
                switch (select)
                {
                case 5:
                    select = 1;
                    break;
                case 6:
                    select = 5;
                    break;
                case 7:
                    select = 6;
                    break;
                case 8:
                    select = 7;
                    break;
                default:
                    select = 0;
                    break;
                }
            }
            else
            {
                if (select)
                    select--;
            }
            change = true;
            break;
        }

        if (search)
        { // cercare un contatto

            if (ch == 7)
            {
                if (select == 0 && strlen(contatto.nome) > 0)
                    contatto.nome[strlen(contatto.nome) - 1] = '\0';
                if (select == 1 && strlen(contatto.cognome) > 0)
                    contatto.cognome[strlen(contatto.cognome) - 1] = '\0';
                change = true;
            }
            else if (isprint(ch))
            {
                char temp[2] = {ch, '\0'};
                if (select == 0 && strlen(contatto.nome) < MAX_STRLEN - 1)
                    strcat(contatto.nome, temp);
                if (select == 1 && strlen(contatto.cognome) < MAX_STRLEN - 1)
                    strcat(contatto.cognome, temp);
                change = true;
            }

            if (enter_down)
            {
                if (select == 5)
                {
                    if (!csv_find_contatto(
                            contatto.nome,
                            contatto.cognome,
                            contatto.eta,
                            contatto.numero,
                            contatto.citta))
                    {
                        // contatto non trovato
                        contatto.eta[0] = '\0';
                        contatto.numero[0] = '\0';
                        contatto.citta[0] = '\0';
                    }
                    refresh();
                    napms(100);
                    change = true;
                }
                else if (select == 6)
                {
                    home = true;
                }
                else if (select == 7)
                {
                    home = true;
                    search = false;
                }
                else if (select == 8)
                {
                    quit = true;
                }

                enter_down = false;
            }
        }
        else
        { // aggiungere un contatto

            if (ch == 7)
            {
                if (select == 0 && strlen(contatto.nome) > 0)
                    contatto.nome[strlen(contatto.nome) - 1] = '\0';
                if (select == 1 && strlen(contatto.cognome) > 0)
                    contatto.cognome[strlen(contatto.cognome) - 1] = '\0';
                if (select == 2 && strlen(contatto.eta) > 0)
                    contatto.eta[strlen(contatto.eta) - 1] = '\0';
                if (select == 3 && strlen(contatto.numero) > 0)
                    contatto.numero[strlen(contatto.numero) - 1] = '\0';
                if (select == 4 && strlen(contatto.citta) > 0)
                    contatto.citta[strlen(contatto.citta) - 1] = '\0';
                change = true;
            }
            else if (isprint(ch))
            {
                char temp[2] = {ch, '\0'};
                if (select == 0 && strlen(contatto.nome) < MAX_STRLEN - 1)
                    strcat(contatto.nome, temp);
                if (select == 1 && strlen(contatto.cognome) < MAX_STRLEN - 1)
                    strcat(contatto.cognome, temp);
                if (select == 2 && strlen(contatto.eta) < MAX_STRLEN - 1)
                    strcat(contatto.eta, temp);
                if (select == 3 && strlen(contatto.numero) < MAX_STRLEN - 1)
                    strcat(contatto.numero, temp);
                if (select == 4 && strlen(contatto.citta) < MAX_STRLEN - 1)
                    strcat(contatto.citta, temp);
                change = true;
            }

            if (enter_down)
            {
                if (select == 5)
                {
                    csv_save_contatto(contatto.nome,
                                      contatto.cognome,
                                      contatto.eta,
                                      contatto.numero,
                                      contatto.citta);
                    home = true;
                }
                else if (select == 6)
                {
                    home = true;
                }
                else if (select == 7)
                {
                    home = true;
                    search = true;
                }
                else if (select == 8)
                {
                    quit = true;
                }
                enter_down = false;
            }
        }
    }

    endwin();
    return 0;
}