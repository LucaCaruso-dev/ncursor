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

struct Data
{
    char label1[MAX_STR_LEN];
    char label2[MAX_STR_LEN];
    char label3[MAX_STR_LEN];
    char label4[MAX_STR_LEN];
    char label5[MAX_STR_LEN];
    char label6[MAX_STR_LEN];
    char email[MAX_STR_LEN];
    char pwd[MAX_STR_LEN];
};
typedef struct Data Data;

int x, y;
FILE *LanFile;
int temp = 0;

Data data;

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

void printContent(int x, int y, const char *str)
{
    mvprintw(y, x, "%s", str);
    refresh();
}

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
            // Value = strtok(NULL, Token);
            strcpy(Value, strtok(NULL, Token));
            // printContent(0, temp++, Value);
            return true; // Key found
        }
    }
    return false; // Key not found
}

bool setUpLan()
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

    /*char label1[MAX_STR_LEN] = "";
    char label2[MAX_STR_LEN] = "";
    char label3[MAX_STR_LEN] = "";
    char label4[MAX_STR_LEN] = "";
    char label5[MAX_STR_LEN] = "";
    char label6[MAX_STR_LEN] = "";*/

    if (!readProperties(LanFile, "InsertEmail", data.label1) ||
        !readProperties(LanFile, "Email", data.label2) ||
        !readProperties(LanFile, "InsertPassword", data.label3) ||
        !readProperties(LanFile, "Password", data.label4) ||
        !readProperties(LanFile, "PasswordConfirmation", data.label5) ||
        !readProperties(LanFile, "Login", data.label6))
    {
        fclose(LanFile);
        return false;
    }

    fclose(LanFile);
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

    data.label1[0] = '\0';
    data.label2[0] = '\0';
    data.label3[0] = '\0';
    data.label4[0] = '\0';
    data.label5[0] = '\0';
    data.label6[0] = '\0';
    data.email[0] = '\0';
    data.pwd[0] = '\0';

    if (!setUpLan())
    {
        endwin();
        return 1;
    }

    clear();

    bool quit = false;
    int select = 0;
    int max_select = 3;

    printContent(2, 0, data.label1);
    printContent(2, 1, data.label2);
    printContent(2, 2, data.label3);
    printContent(2, 3, data.label4);
    printContent(2, 4, data.label5);
    printContent(2, 5, data.label6);
    printContent(2, 6, "Press CTR+C to quit");

    while (!quit)
    {

        int ch = getch();
        switch (select)
        {
        case 0:
            
            break;
        }
        switch (ch)
        {
        case KEY_DOWN:
            if (select < max_select)
                select++;
            else
                select = 0;
            break;
        case KEY_UP:
            if (select > 0)
                select--;
            else
                select = max_select;
            break;
        }
    }

end:
    clear();
    endwin();
    return 0;
}