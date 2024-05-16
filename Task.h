#ifndef TASK_H
#define TASK_H

#include <string>

enum class TaskStatus {
    NOT_STARTED,
    IN_PROGRESS,
    COMPLETED,
    OVERDUE
};

class Task {
public:
    Task(const std::string& description, const std::string& deadline, int timeNeeded)
        : description(description), status("Not Assigned"), deadline(deadline), timeNeeded(timeNeeded) {}

    std::string getStatus() const {
        return status;
    }

    void setStatus(const std::string& newStatus) {
        status = newStatus;
    }

    std::string getDescription() const {
        return description;
    }

    std::string getDeadline() const {
        return deadline;
    }

    int getTimeNeeded() const {
        return timeNeeded;
    }

private:
    std::string description;
    std::string status;
    std::string deadline;
    int timeNeeded;
};

#endif // TASK_H
