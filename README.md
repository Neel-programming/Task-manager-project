# Task Manager (C++)

A simple command-line app for tracking tasks: add them, mark them
done, search them, and delete them. Data is saved to a file so your
list is still there next time you run it.

Built in C++ to practice core fundamentals: classes, vectors, file
I/O, and basic input validation.

## What it does

- Add a task with a title and priority (LOW, MEDIUM, HIGH)
- View all tasks, with a checkbox showing what's done
- Mark a task completed by its id
- Delete a task by its id
- Search tasks by keyword in the title
- Saves automatically to a file when you exit

## How to run it

**1. Make sure you have a C++ compiler installed.**

Open a terminal and type:

g++ --version

If you see a version number, you're set. If not:
- **Mac:** install Xcode Command Line Tools (`xcode-select --install`)
- **Windows:** install [MinGW](https://www.mingw-w64.org/) or use WSL
- **Linux:** `sudo apt install g++`

**2. Download this project** (or clone it if using Git):

git clone <this-repo-url>


**3. Open a terminal in the project's `src` folder and compile:**

cd src
g++ -std=c++17 -o task_manager Task.cpp TaskManager.cpp main.cpp


**4. Run it:**

./task_manager

(On Windows, run `task_manager.exe` instead.)

**5. Use the menu:**
Add task
View all tasks
Mark task completed
Delete task
Search tasks
Save and exit

Your tasks are saved to `tasks.txt` in the same folder, and reload
automatically the next time you run the program.

## Example

Choose an option: 1
Title: Push code to GitHub
Priority (LOW, MEDIUM, HIGH): HIGH
Added as task #1


## Project structure

| File | What it does |
|---|---|
| `Task.h` / `Task.cpp` | Defines a single task and how it's saved to/read from a file |
| `TaskManager.h` / `TaskManager.cpp` | Manages the full list: add, complete, delete, search, save, load |
| `main.cpp` | The menu loop the user interacts with |

## Built by

Neel Patel — [github.com/Neel-programming](https://github.com/Neel-programming)
