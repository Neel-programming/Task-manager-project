#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "Task.h"
#include <vector>
#include <string>

// Owns the full list of tasks and handles everything that touches
// more than one task at a time: adding, searching, saving, loading.
class TaskManager {
public:
    explicit TaskManager(std::string filePath);

    // Adds a task and returns the id it was assigned.
    int addTask(const std::string& title, Priority priority);

    bool markCompleted(int id);
    bool removeTask(int id);

    // Simple case-insensitive substring search on the title.
    std::vector<Task> search(const std::string& keyword) const;

    const std::vector<Task>& getAllTasks() const;

    void save() const;
    void load();

private:
    std::string filePath;
    std::vector<Task> tasks;
    int nextId;
};

#endif
