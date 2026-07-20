#include "TaskManager.h"
#include <iostream>
#include <limits>

namespace {
    void printMenu() {
        std::cout << "\n1) Add task\n"
                  << "2) View all tasks\n"
                  << "3) Mark task completed\n"
                  << "4) Delete task\n"
                  << "5) Search tasks\n"
                  << "6) Save and exit\n"
                  << "Choose an option: ";
    }

    void printTask(const Task& t) {
        std::cout << "[" << t.id << "] "
                  << (t.completed ? "[x] " : "[ ] ")
                  << t.title
                  << " (priority: " << priorityToString(t.priority) << ")\n";
    }

    // Clears bad input from the stream so a letter typed where a number
    // is expected doesn't send the program into an infinite loop.
    void clearInputError() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int promptForId() {
        std::cout << "Task id: ";
        int id;
        while (!(std::cin >> id)) {
            std::cout << "That's not a number, try again: ";
            clearInputError();
        }
        std::cin.ignore(); // consume leftover newline before next getline
        return id;
    }
}

int main() {
    TaskManager manager("tasks.txt");
    bool running = true;

    std::cout << "=== Task Manager ===\n";

    while (running) {
        printMenu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Not a valid option, try again.\n";
            clearInputError();
            continue;
        }
        std::cin.ignore(); // consume leftover newline before getline calls

        switch (choice) {
            case 1: {
                std::cout << "Title: ";
                std::string title;
                std::getline(std::cin, title);

                std::cout << "Priority (LOW, MEDIUM, HIGH): ";
                std::string priorityInput;
                std::getline(std::cin, priorityInput);

                int id = manager.addTask(title, priorityFromString(priorityInput));
                std::cout << "Added as task #" << id << "\n";
                break;
            }
            case 2: {
                const auto& tasks = manager.getAllTasks();
                if (tasks.empty()) {
                    std::cout << "No tasks yet.\n";
                } else {
                    for (const auto& t : tasks) {
                        printTask(t);
                    }
                }
                break;
            }
            case 3: {
                int id = promptForId();
                if (manager.markCompleted(id)) {
                    std::cout << "Marked complete.\n";
                } else {
                    std::cout << "No task with that id.\n";
                }
                break;
            }
            case 4: {
                int id = promptForId();
                if (manager.removeTask(id)) {
                    std::cout << "Deleted.\n";
                } else {
                    std::cout << "No task with that id.\n";
                }
                break;
            }
            case 5: {
                std::cout << "Search keyword: ";
                std::string keyword;
                std::getline(std::cin, keyword);
                auto matches = manager.search(keyword);
                if (matches.empty()) {
                    std::cout << "No matches.\n";
                } else {
                    for (const auto& t : matches) {
                        printTask(t);
                    }
                }
                break;
            }
            case 6: {
                manager.save();
                std::cout << "Saved. Goodbye!\n";
                running = false;
                break;
            }
            default:
                std::cout << "Not a valid option, try again.\n";
        }
    }
    return 0;
}
