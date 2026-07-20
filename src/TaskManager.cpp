#include "TaskManager.h"
#include <fstream>
#include <algorithm>
#include <cctype>

TaskManager::TaskManager(std::string filePath)
    : filePath(std::move(filePath)), nextId(1) {
    load();
}

int TaskManager::addTask(const std::string& title, Priority priority) {
    int id = nextId++;
    tasks.emplace_back(id, title, priority);
    return id;
}

bool TaskManager::markCompleted(int id) {
    for (auto& t : tasks) {
        if (t.id == id) {
            t.completed = true;
            return true;
        }
    }
    return false; // no task with that id
}

bool TaskManager::removeTask(int id) {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
                              [id](const Task& t) { return t.id == id; });
    if (it == tasks.end()) {
        return false; // nothing matched
    }
    tasks.erase(it, tasks.end());
    return true;
}

namespace {
    std::string toLower(const std::string& s) {
        std::string result = s;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }
}

std::vector<Task> TaskManager::search(const std::string& keyword) const {
    std::vector<Task> matches;
    std::string lowerKeyword = toLower(keyword);
    for (const auto& t : tasks) {
        if (toLower(t.title).find(lowerKeyword) != std::string::npos) {
            matches.push_back(t);
        }
    }
    return matches;
}

const std::vector<Task>& TaskManager::getAllTasks() const {
    return tasks;
}

void TaskManager::save() const {
    std::ofstream out(filePath);
    for (const auto& t : tasks) {
        out << t.toFileLine() << "\n";
    }
}

void TaskManager::load() {
    std::ifstream in(filePath);
    if (!in.is_open()) {
        return; // no file yet, that's fine on first run
    }
    std::string line;
    int highestId = 0;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        Task t = Task::fromFileLine(line);
        tasks.push_back(t);
        highestId = std::max(highestId, t.id);
    }
    nextId = highestId + 1;
}
