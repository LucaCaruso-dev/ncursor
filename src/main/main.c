/*
 * Compile with: gcc main.c -o ncurses -lncurses
 * Run with: ./ncurses
 */

#include <curses.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int x, y;
FILE *LanFile;

struct Data
{
    char *label1;
    char *label2;
};
typedef struct Data Data;

/*
 * for printing string in specified coordinates
 * x: x coordinate
 * y: y coordinate
 * string: str (with format specifiers)
 * ...: variable arguments
 *
 * mvprintw(x, y, str, ...);       print
 * refresh();                       refresh the screen
 */

bool setUpLan()
{
    /*
     * Open the file lan/%lan%.properties in read mode
     * If the file is not found, print an error message and return false
     */
    char *lan = getenv("LANG");
    char filepath[100];

    snprintf(filepath, sizeof(filepath), "lan/%.2s.properties", lan);
    mvprintw(0, 0, "Opening file %s", filepath);
    refresh();

    LanFile = fopen(filepath, "r");
    if (LanFile == NULL)
    {
        LanFile = fopen("lan/it.properties", "r");
        if (LanFile == NULL)
        {
            mvprintw(0, 0, "Error: File %s not found", filepath);
            refresh();
            return false;
        }
    }
    return true;
}

int main()
{
start:
    initscr();              // Initialize the window
    getmaxyx(stdscr, x, y); // Get the maximum x & y coordinates

    keypad(stdscr, TRUE);  // Abilita la lettura dei tasti speciali (come le frecce)
    noecho();              // Disabilita l'echo dei caratteri
    nodelay(stdscr, TRUE); // Rende getch() non bloccante

    napms(1000); // Pausa di 1 secondo
    if (!setUpLan())
    {
        endwin();
        return 1;
    }

    clear();

    Data data;

    bool quit = false;

    while (!quit)
    {
        int ch = getch();
        switch (ch) {
            case 'q':
                quit = true;
                break;
            default:
                break;
        }
    }

end:
    clear();
    endwin();
    return 0;
}