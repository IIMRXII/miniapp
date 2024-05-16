#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include "Employee.h"
#include "Task.h"

class Database {
public:
    void addEmployeeToDatabaseFile();
    void addTaskToDatabaseFile();
    void removeEmployeeFromFile(const std::string& name);
    void removeTaskFromFile(const std::string& taskName);
    void displayEmployeesFromFile();
    void displayTasksFromFile();
    void advanceTime(int days);
    bool employeeHasAssignedTask(const std::string& employeeName);
    void assignTask(const std::string& employeeName, const std::string& taskDescription);
    void getTaskStatus(const std::string& taskDescription);


private:
    std::vector<Employee> employees;
    std::vector<Task> tasks;
};

#endif // DATABASE_H