#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include "Task.h"

class Employee {
public:
    Employee(const std::string& name, int hoursPerDay) : name(name), hoursPerDay(hoursPerDay), assignedTask(nullptr) {}

    std::string getName() const {
        return name;
    }

    bool hasTaskAssigned() const {
        return (assignedTask != nullptr);
    }

    void assignTask(Task* task) {
        assignedTask = task;
    }

    Task* getAssignedTask() {
        return assignedTask;
    }
    int getHoursPerDay() const {
        return hoursPerDay;
    }

private:
    std::string name;
    int hoursPerDay;
    Task* assignedTask;
};

#endif // EMPLOYEE_H