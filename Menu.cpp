#include "Menu.h"
#include <iostream>

Menu::Menu(Database& db) : database(db) {}

void Menu::showMenu() {
    Database db;
    int choice;
    bool continueMenu = true;

    while (continueMenu) {
        std::cout << "Main:\n";
        std::cout << "1. displayEmployees\n";
        std::cout << "2. display tasks\n";
        std::cout << "3. add employee\n";
        std::cout << "4. add tasks\n";
        std::cout << "5. remove employ from file\n";
        std::cout << "6. remove task from file\n";
        std::cout << "7. assignTask\n";
        std::cout << "8. advanceTime\n";
        std::cout << "9. check status\n";



        std::cout << "Select an action: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
        {
            db.displayEmployeesFromFile();
            break;
        }
        case 2: {
            db.displayTasksFromFile();
            break;
        }
        case 3: {
            db.addEmployeeToDatabaseFile();
            break;
        }
        case 4: {
            db.addTaskToDatabaseFile();
            break;
        }
        case 5: {
            std::string name;
            std::cout << "Введите имя: ";
            std::getline(std::cin >> std::ws, name);
            db.removeEmployeeFromFile(name);
            break;
        }
        case 6: {
            std::string taskname;
            std::cout << "Введите задачу: ";
            std::getline(std::cin >> std::ws, taskname);
            db.removeTaskFromFile(taskname);
            break;
        }
        case 7: {
            std::string name;
            std::string description;
            std::cout << "Введите имя сотрудника: ";
            std::getline(std::cin >> std::ws, name);
            std::cout << "Введите задачу: ";
            std::getline(std::cin >> std::ws, description);
            db.assignTask(name, description);
            break;
        }
        case 8: {
            int time;
            std::cout << "Сколько должно пройти время (ч)? ";
            std::cin >> time;
            db.advanceTime(time);
            break;
        }
        case 9: {
            std::string description;
            std::cout << "Введите описание задачи: ";
            std::cin >> description;
            db.getTaskStatus(description);
        }
        }
    }
}
