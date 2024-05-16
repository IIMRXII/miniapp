#include "Database.h"
#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Task.h"

void Database::addEmployeeToDatabaseFile() {
    std::ofstream file("employees.txt", std::ios_base::app);
    if (file.is_open()) {
        std::string employee;
        int hoursPerDay;

        std::cout << "Введите имя сотрудника: ";
        std::getline(std::cin >> std::ws, employee); 
        std::cout << "Введите количество рабочих часов в день: ";
        std::cin >> hoursPerDay;

        file << employee << " " << hoursPerDay << std::endl;
        file.close();
        std::cout << "Сотрудник \"" << employee << "\" успешно добавлен в файл." << std::endl;
    }
    else {
        std::cerr << "Невозможно открыть файл для записи." << std::endl;
    }
}


void Database::addTaskToDatabaseFile() {
    std::ofstream file("task.txt", std::ios_base::app);
    if (file.is_open()) {
        std::string description;
        int hours;
        int deadline;

        std::cout << "Введите описание задачи: ";
        std::getline(std::cin >> std::ws, description);
        std::cout << "Введите срок выполнения задачи: ";
        std::cin >> deadline;
        std::cout << "Введите сколько часов потребуется на задачу";
        std::cin >> hours;

        file << description << " " << deadline << " " << hours << std::endl;
        file.close();
        std::cout << "Задача \"" << description << "\" успешно добавлен в файл." << std::endl;
    }
    else {
        std::cerr << "Невозможно открыть файл для записи." << std::endl;
    }
}

void Database::removeEmployeeFromFile(const std::string& name) {
    std::ifstream inFile("employees.txt"); 
    if (inFile.is_open()) {
        std::string line;
        std::vector<std::string> fileData;

        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string employeeName;
            std::string employeeFullName;
            iss >> employeeFullName; 
            int hoursPerDay;
            iss >> hoursPerDay;

            if (employeeName != name && employeeFullName != name) {
                fileData.push_back(line);
            }
        }
        inFile.close();

        std::ofstream outFile("employees.txt");
        if (outFile.is_open()) {
            for (const std::string& data : fileData) {
                outFile << data << std::endl;
            }
            outFile.close();
            std::cout << "Сотрудник с именем \"" << name << "\" успешно удален из файла." << std::endl;
        }
        else {
            std::cerr << "Невозможно открыть файл для записи." << std::endl;
        }
    }
    else {
        std::cerr << "Невозможно открыть файл для чтения." << std::endl;
    }
}

void Database::removeTaskFromFile(const std::string& taskName) {
    std::ifstream inFile("task.txt");
    if (inFile.is_open()) {
        std::string line;
        std::vector<std::string> fileData;

        while (std::getline(inFile, line)) {
            if (!line.empty() && line.find(taskName) == std::string::npos) {
                fileData.push_back(line);
            }
        }
        inFile.close();

        std::ofstream outFile("task.txt");
        if (outFile.is_open()) {
            for (const std::string& data : fileData) {
                outFile << data << std::endl;
            }
            outFile.close();
            std::cout << "Задача с именем \"" << taskName << "\" успешно удалена из файла." << std::endl;
        }
        else {
            std::cerr << "Невозможно открыть файл для записи." << std::endl;
        }
    }
    else {
        std::cerr << "Невозможно открыть файл для чтения." << std::endl;
    }
}

void Database::displayEmployeesFromFile() {
    std::ifstream inFile("employees.txt");
    if (inFile.is_open()) {
        std::string line;

        std::cout << "Список сотрудников:" << std::endl;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    }
    else {
        std::cerr << "Невозможно открыть файл для чтения." << std::endl;
    }
}

void Database::displayTasksFromFile() {
    std::ifstream inFile("task.txt");
    if (inFile.is_open()) {
        std::string line;

        std::cout << "Список задач:" << std::endl;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    }
    else {
        std::cerr << "Невозможно открыть файл для чтения." << std::endl;
    }
}

void Database::advanceTime(int hours) {
    std::ifstream tasksFile("task.txt");
    std::ifstream assignedTasksFile("assigned_tasks.txt");

    if (tasksFile.is_open() && assignedTasksFile.is_open()) {
        std::string line;
        while (std::getline(tasksFile, line)) {
            std::istringstream iss(line);
            std::string taskDescription;
            int deadline;
            int duration;
            iss >> taskDescription >> deadline >> duration;

            deadline -= hours;
            duration -= hours;

            std::ofstream tasksFile("task.txt");
            if (tasksFile.is_open()) {
                tasksFile << taskDescription << " " << deadline << " " << duration << std::endl;
                tasksFile.close();
            }
            while (std::getline(assignedTasksFile, line)) {
                std::istringstream iss(line);
                std::string employeeName;
                std::string taskDescription;
                std::string status;
                iss >> employeeName >> taskDescription >> status;


                if (duration == 0) {
                    status = "Выполнена";
                }
                else if (deadline == 0 && duration > 0) {
                    status = "Невыполнена";
                }
                else {
                    status = "Выполняется";
                }


                tasksFile.close();



                std::ofstream assignedTasksFile("assigned_tasks.txt");
                if (assignedTasksFile.is_open()) {
                    assignedTasksFile << employeeName << " " << taskDescription << " " << status << std::endl;
                    assignedTasksFile.close();
                }
            }

            assignedTasksFile.close();
        }
    }
}



bool Database::employeeHasAssignedTask(const std::string& employeeName) {
    std::ifstream assignedTasksFile("assigned_tasks.txt");

    if (assignedTasksFile.is_open()) {
        std::string line;
        while (std::getline(assignedTasksFile, line)) {
            std::istringstream iss(line);
            std::string name;
            iss >> name;
            if (name == employeeName) {
                assignedTasksFile.close();
                return true;
            }
        }

        assignedTasksFile.close();
    }

    return false;
}


void Database::assignTask(const std::string& employeeName, const std::string& taskDescription) {
    std::ifstream employeeFile("employees.txt");
    std::ifstream taskFile("task.txt");

    if (employeeFile.is_open() && taskFile.is_open()) {
        bool employeeFound = false;
        bool taskFound = false;
        std::string line;

        while (std::getline(employeeFile, line)) {
            std::istringstream iss(line);
            std::string name;
            iss >> name;
            if (name == employeeName) {
                employeeFound = true;
                break;
            }
        }

        while (std::getline(taskFile, line)) {
            std::istringstream iss(line);
            std::string description;
            iss >> description;
            if (description == taskDescription) {
                taskFound = true;
                break;
            }
        }

        employeeFile.close();
        taskFile.close();
        if (employeeFound && taskFound) {
            if (employeeHasAssignedTask(employeeName)) {
                std::ofstream taskFile("task.txt", std::ios::app);
                if (taskFile.is_open()) {
                    taskFile << taskDescription << " " << "Not Assigned" << std::endl;
                    taskFile.close();
                }
            }


            std::ofstream assignedTasksFile("assigned_tasks.txt", std::ios::app);
            if (assignedTasksFile.is_open()) {
                assignedTasksFile << employeeName << " " << taskDescription << " " << "Выполняется" << std::endl;
                assignedTasksFile.close();
            }



            /*std::ofstream employeeFile("employees.txt");
            if (employeeFile.is_open()) {
                for (const Employee& emp : employees) {
                    employeeFile << emp.getName() << " " << emp.getHoursPerDay() << std::endl;
                }
                employeeFile.close();
            }*/

            std::cout << "Задача успешно назначена сотруднику." << std::endl;
        }
        else {
            std::cerr << "Сотрудник или задача не найдены." << std::endl;
        }
    }
}
void Database::getTaskStatus(const std::string& taskDescription) {
    std::ifstream assignedTasksFile("assigned_tasks.txt");

    if (assignedTasksFile.is_open()) {
        std::string line;
        while (std::getline(assignedTasksFile, line)) {
            std::istringstream iss(line);
            std::string employeeName;
            std::string description;
            std::string status;
            iss >> employeeName >> description >> status;

            if (description == taskDescription) {
                std::cout << status << std::endl;
                assignedTasksFile.close();
                return;
            }
        }

        assignedTasksFile.close();
    }

    std::cout << "Задача не найдена" << std::endl;
}