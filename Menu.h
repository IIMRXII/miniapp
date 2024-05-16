#ifndef MENU_H
#define MENU_H

#include "Database.h"

class Menu {
public:
    Menu(Database& db);
    void showMenu();

private:
    Database& database;
};

#endif // MENU_H