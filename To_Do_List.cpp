#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const string FILENAME = "tasks.txt";

void showMenu() {
    cout << "-------- To-Do List --------" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Update Task" << endl;
    cout << "4. Delete Task" << endl;
    cout << "5. Exit" << endl;
    cout << "-----------------------------" << endl;
    cout << "Enter your choice: ";
}

void loadTasks(vector<string> &tasks) {
    ifstream file;
    try {
        file.open(FILENAME);
        if (!file) {
            throw runtime_error("Unable to open file for reading.");
        }
        string task;
        while (getline(file, task)) {
            tasks.push_back(task);
        }
        file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void saveTasks(const vector<string> &tasks) {
    ofstream file;
    try {
        file.open(FILENAME);
        if (!file) {
            throw runtime_error("Unable to open file for writing.");
        }
        for (const string &task : tasks) {
            file << task << endl;
        }
        file.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void addTask(vector<string> &tasks) {
    cout << "Enter the task: ";
    string task;
    cin.ignore();
    getline(cin, task);
    tasks.push_back(task);
    cout << "Task added successfully!" << endl;
    saveTasks(tasks);
}

void viewTasks(const vector<string> &tasks) {
    if (tasks.empty()) {
        cout << "No tasks to show." << endl;
    } else {
        cout << "Your To-Do List:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i] << endl;
        }
    }
}

void updateTask(vector<string> &tasks) {
    if (tasks.empty()) {
        cout << "No tasks to update." << endl;
        return;
    }

    viewTasks(tasks);

    int taskNumber;
    cout << "Enter the task number to update: ";
    cin >> taskNumber;

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!" << endl;
    } else {
        cout << "Enter the new task: ";
        string newTask;
        cin.ignore();
        getline(cin, newTask);
        tasks[taskNumber - 1] = newTask;
        cout << "Task updated successfully!" << endl;
        saveTasks(tasks);
    }
}

void deleteTask(vector<string> &tasks) {
    if (tasks.empty()) {
        cout << "No tasks to delete." << endl;
        return;
    }

    viewTasks(tasks);

    int taskNumber;
    cout << "Enter the task number to delete: ";
    cin >> taskNumber;

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number!" << endl;
    } else {
        tasks.erase(tasks.begin() + taskNumber - 1);
        cout << "Task deleted successfully!" << endl;
        saveTasks(tasks);
    }
}

int main() {
    vector<string> tasks;
    loadTasks(tasks);
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                updateTask(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        cout << endl;
    }

    return 0;
}
