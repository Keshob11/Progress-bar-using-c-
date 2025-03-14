#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>

const int BAR_LENGTH = 20;
const int MAX_TASKS = 10;

class Task {
public:
    int id;
    int progress;
    int step;

    Task() : id(0), progress(0), step(0) {}
};

void print_bar(Task task);
void clear_screen();

int main() {
    Task tasks[MAX_TASKS];
    srand(time(NULL));

    // Initialization
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % 5 + 1;
    }

    bool tasks_incomplete = true;
    while (tasks_incomplete) {
        tasks_incomplete = false;
        clear_screen();
        for (int i = 0; i < MAX_TASKS; i++) {
            tasks[i].progress += tasks[i].step;
            if (tasks[i].progress > 100) {
                tasks[i].progress = 100;
            } else if (tasks[i].progress < 100) {
                tasks_incomplete = true;
            }
            print_bar(tasks[i]);
        }
        sleep(1); // Sleep for 1 second
    }
    std::cout << "All tasks completed!" << std::endl;
    return 0;
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void print_bar(Task task) {
    int bars_to_show = (task.progress * BAR_LENGTH) / 100;
    std::cout << "Task " << task.id << ": [";
    for (int i = 0; i < BAR_LENGTH; i++) {
        if (i < bars_to_show) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << task.progress << "%" << std::endl;
}
