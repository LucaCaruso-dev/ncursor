/*
 * Compile with: gcc main.c -o ncurses -lncurses
 * Run with: ./ncurses
 */

/*
 * Press 'q' to quit
 */

#include <curses.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256

int x, y;
FILE *LanFile;

struct Data
{
    char *label1;
    char *label2;
    char *label3;
    char *label4;
    char *label5;
    char *label6;
    char *email;
    char *pwd;
};
typedef struct Data Data;

/*
 * for printing string in specified coordinates
 * x: x coordinate
 * y: y coordinate
 * string: str (with format specifiers)
 * ...: variable arguments
 *
 * mvprintw(y, x, str, ...);       print
 * refresh();                       refresh the screen
 */

bool readProperties(FILE *File, const char *Key, char *Value)
{
    /*
     * Read the file line by line
     * If the line contains the key, extract the value and store it in data
     * Return true if the key is found, false not found
     * The file format is: %key% = %value%
     *
     * Please don't use char '=' in value
     */
    char Line[MAX_STR_LEN];
    const char *Token = "=";
    char *KeyFound;
    while (fgets(Line, MAX_STR_LEN, File))
    {
        KeyFound = strtok(Line, Token);
        if (strcmp(Line, Key) == 0)
        {
            Value = strtok(NULL, Token);
            return true; // Key found
        }
    }
    return false; // Key not found
}

bool setUpLan(Data *data)
{
    /*
     * Open the file lan/%lan%.properties in read mode
     * If the file is not found, print an error message and return false
     */
    char *lan = getenv("LANG");
    char filepath[100];

    int line = 0;

    snprintf(filepath, sizeof(filepath), "lan/%.2s.properties", lan);
    mvprintw(line++, 0, "Opening file %s", filepath);
    refresh();

    LanFile = fopen(filepath, "r");
    if (LanFile == NULL)
    {
        mvprintw(line++, 0, "Error: File %s not found", filepath);
        LanFile = fopen("lan/it.properties", "r");
        mvprintw(line++, 0, "Opening file lan/it.properties");
        refresh();
        if (LanFile == NULL)
        {
            mvprintw(line++, 0, "Error: File %s not found", filepath);
            refresh();
            napms(1000); // Pausa di 1 secondo
            return false;
        }
    }

    napms(1000); // Pausa di 1 secondo

    /*
     * Data data;
     * data.label1 = %InsertEmail%;
     * data.label2 = %Email%;
     * data.label3 = %InsertPassword%;
     * data.label4 = %Password%;
     * data.label5 = %PasswordConfirmation%;
     * data.label6 = %Login%;
     *
     * data.email => userInput
     * data.pwd => userInput
     */

    if (!readProperties(LanFile, "InsertEmail", data->label1))
    {
        return false;
    }
    if (!readProperties(LanFile, "Email", data->label2))
    {
        return false;
    }
    if (!readProperties(LanFile, "InsertPassword", data->label3))
    {
        return false;
    }
    if (!readProperties(LanFile, "Password", data->label4))
    {
        return false;
    }
    if (!readProperties(LanFile, "PasswordConfirmation", data->label5))
    {
        return false;
    }
    if (!readProperties(LanFile, "Login", data->label6))
    {
        return false;
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

    Data data;
    if (!setUpLan(&data))
    {
        endwin();
        return 1;
    }

    clear();

    bool quit = false;

    while (!quit)
    {
        int ch = getch();
        switch (ch)
        {
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