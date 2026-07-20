#include "Task.h"
#include <sstream>
#include <stdexcept>
#include <vector>

std::string priorityToString(Priority p) {
    switch (p) {
        case Priority::LOW: return "LOW";
        case Priority::MEDIUM: return "MEDIUM";
        case Priority::HIGH: return "HIGH";
    }
    return "MEDIUM"; // unreachable, keeps the compiler happy
}

Priority priorityFromString(const std::string& text) {
    if (text == "LOW") return Priority::LOW;
    if (text == "HIGH") return Priority::HIGH;
    return Priority::MEDIUM; // safe default if input doesn't match
}

Task::Task(int id, std::string title, Priority priority, bool completed)
    : id(id), title(std::move(title)), priority(priority), completed(completed) {}

std::string Task::toFileLine() const {
    // Fields separated by '|' since titles may contain commas.
    std::ostringstream out;
    out << id << "|"
        << title << "|"
        << priorityToString(priority) << "|"
        << (completed ? "1" : "0");
    return out.str();
}

Task Task::fromFileLine(const std::string& line) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, '|')) {
        parts.push_back(field);
    }
    if (parts.size() != 4) {
        throw std::runtime_error("Malformed task line: " + line);
    }
    int id = std::stoi(parts[0]);
    std::string title = parts[1];
    Priority priority = priorityFromString(parts[2]);
    bool completed = (parts[3] == "1");
    return Task(id, title, priority, completed);
}
