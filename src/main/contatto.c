#include "contatto.h"

void searchButton() {
    mvprintw(13, 1, "%s", getKey("Search", getLanguage()));
}

void addButton() {
    mvprintw(13, 1, "%s", getKey("Add", getLanguage()));
}

void drawChangeModeButton() {
    mvprintw(17, 1, "%s", getKey("Change mode", getLanguage()));
}

void drawExitButton() {
    mvprintw(19, 1, "%s", getKey("Exit", getLanguage()));
}

void drawContent(int select, char *nome, char *cognome, char *eta, char *numero, char *citta)
{
    // mvprintw(y, x, format, ...);
    char *lang=getLanguage();

    clear();
    mvprintw((select+1)*2+1, 0, "%c", '*');

    mvprintw(1, 1, "%s", getKey("Contact", lang));

    mvprintw(2, 1, "%s:", getKey("Name", lang));
    mvprintw(3, 1, "%s", nome);

    mvprintw(4, 1, "%s:", getKey("Surname", lang));
    mvprintw(5, 1, "%s", cognome);

    mvprintw(6, 1, "%s:", getKey("Age", lang));
    mvprintw(7, 1, "%s", eta);

    mvprintw(8, 1, "%s:", getKey("Phone", lang));
    mvprintw(9, 1, "%s", numero);

    mvprintw(10, 1, "%s:", getKey("City", lang));
    mvprintw(11, 1, "%s", citta);

    mvprintw(15, 1, "%s", getKey("Home", lang));
}
