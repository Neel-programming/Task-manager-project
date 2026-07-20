#ifndef TASK_H
#define TASK_H

#include <string>

// Priority as an enum instead of a raw int/string, so a typo like
// priority 7 or "hgih" can't sneak into the data.
enum class Priority {
    LOW,
    MEDIUM,
    HIGH
};

std::string priorityToString(Priority p);
Priority priorityFromString(const std::string& text);

// One task in the list. Kept as a simple struct with a constructor
// since it's just a data holder — the interesting logic lives in
// TaskManager.
struct Task {
    int id;
    std::string title;
    Priority priority;
    bool completed;

    Task(int id, std::string title, Priority priority, bool completed = false);

    // One line of text representing this task, for saving to disk.
    std::string toFileLine() const;

    // Rebuilds a Task from one line read off disk.
    static Task fromFileLine(const std::string& line);
};

#endif
