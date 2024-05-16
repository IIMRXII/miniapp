#include "Database.h"
#include "Menu.h"

int main() {
    Database db;
    Menu menu(db);
    menu.showMenu();

    return 0;
}