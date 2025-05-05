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
#include <ctype.h>

#define MAX_STR_LEN 256

struct Data
{
    char email[MAX_STR_LEN];
    char pwd[MAX_STR_LEN];
    char pwdConf[MAX_STR_LEN];
};
typedef struct Data Data;

char label1[MAX_STR_LEN];
char label2[MAX_STR_LEN];
char label3[MAX_STR_LEN];
char label4[MAX_STR_LEN];
char label5[MAX_STR_LEN];
char label6[MAX_STR_LEN];

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

    if (!readProperties(LanFile, "InsertEmail", label1) ||
        !readProperties(LanFile, "Email", label2) ||
        !readProperties(LanFile, "InsertPassword", label3) ||
        !readProperties(LanFile, "Password", label4) ||
        !readProperties(LanFile, "PasswordConfirmation", label5) ||
        !readProperties(LanFile, "Save", label6))
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
    curs_set(0);           // Nasconde il cursore

    label1[0] = '\0';
    label2[0] = '\0';
    label3[0] = '\0';
    label4[0] = '\0';
    label5[0] = '\0';
    label6[0] = '\0';
    data.email[0] = '\0';
    data.pwd[0] = '\0';
    data.pwdConf[0] = '\0';

    if (!setUpLan())
    {
        endwin();
        return 1;
    }

    clear();

    bool quit = false;
    int select = 0;
    int max_select = 3;

    bool isUpdated = true;

    while (!quit)
    {
        if (isUpdated)
        {
            // Clear the screen
            clear();
            // Print the labels
            printContent(2, 0, label1);
            printContent(2, 1, data.email);
            printContent(2, 2, label3);
            printContent(2, 3, data.pwd);
            printContent(2, 4, label5);
            printContent(2, 5, data.pwdConf);
            printContent(2, 6, label6);
            printContent(2, 7, "");
            switch (select)
            {
            case 0: // Email
                printContent(0, 1, "*");
                break;
            case 1: // Password
                printContent(0, 3, "*");
                break;
            case 2: // Password Confirmation
                printContent(0, 5, "*");
                break;
            case 3: // Login
                printContent(0, 6, "*");
                break;
            default:
                break;
            }
            isUpdated = false;
        }

        int ch = getch();
        if (ch == ERR)
        {
            isUpdated = false;
            continue; // No input
        }

        switch (ch)
        {
        case KEY_UP:
            if (select > 0)
            {
                select--;
            }
            isUpdated = true;
            break;
        case KEY_DOWN:
        case KEY_ENTER:
        case 10:
            if (select < max_select)
            {
                select++;
            }
            isUpdated = true;
            break;
        case 27: // Escape key
            quit = true;
            break;
        }
        switch (select)
        {
        case 0: // Email
            if (ch == KEY_BACKSPACE)
            {
                if (strlen(data.email) > 0)
                {
                    data.email[strlen(data.email) - 1] = '\0';
                    isUpdated = true;
                }
                break;
            }
            if (!isprint(ch))
            {
                break;
            }
            strcat(data.email, (char *)&ch);
            isUpdated = true;
            break;
        case 1: // Password
            if (ch == KEY_BACKSPACE)
            {
                if (strlen(data.pwd) > 0)
                {
                    data.pwd[strlen(data.pwd) - 1] = '\0';
                    isUpdated = true;
                }
                break;
            }
            if (!isprint(ch))
            {
                break;
            }
            strcat(data.pwd, (char *)&ch);
            isUpdated = true;
            break;
        case 2: // Password Confirmation
            if (ch == KEY_BACKSPACE)
            {
                if (strlen(data.pwdConf) > 0)
                {
                    data.pwdConf[strlen(data.pwdConf) - 1] = '\0';
                    isUpdated = true;
                }
                break;
            }
            if (!isprint(ch))
            {
                break;
            }
            strcat(data.pwdConf, (char *)&ch);
            isUpdated = true;
            break;
        case 3: // save
            if (ch == KEY_ENTER || ch == 10)
            {
                quit = true;
            }
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