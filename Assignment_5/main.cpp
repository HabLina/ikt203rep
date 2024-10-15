#include <iostream>
#include <vector>
#include <limits>
#include <unordered_set>
#include "string"

using namespace std;

// define a structure for tasks in the heap
struct Task {
    string task;
    int priority;

    // constructor to initialize a task with name and priority
    Task(string n, int p) : task(std::move(n)), priority(p) {}
};

// class for the heap (priority queue)
class PriorityQueue {
private:
    // vector to store tasks as a max-heap
    vector<Task> heap;
    // keeps track of the unique names
    unordered_set<string> names;

    // function to maintain the max-heap property by moving the element up
    void heapifyUp() {
        int i = heap.size() - 1;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if(heap[i].priority > heap[parent].priority) {
                swap(heap[i], heap[parent]);
                i = parent;
            }
            else {
                break;
            }
        }
    }

public:
    void insert(Task task) {
        // checking if the input name is unique before inserting
        if (names.find(task.task) == names.end()) {
            heap.push_back(task);
            heapifyUp();
            names.insert(task.task);
        } else {
            cout << "Task with name '" << task.task << "' already exists. Please use a unique name" << endl;
        }
    }

    // function to execute the task with the highest priority
    Task execute() {
        if(heap.empty()) {
            Task emptyTask{"Empty task", -1};
            return emptyTask;
        }
        Task maxTask = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        return maxTask;
    }

    // function to change the priority of a task with a given name
    bool changePriority(const string& name, int new_priority) {
        for(Task& task : heap) {
            if(task.task == name) {
                task.priority = new_priority;
                cout << name << " changed priority to " << task.priority << endl;
                heapifyUp();
                return true;
            }
        }
        return false;
    }

    // function to display the top 'n' tasks with the highest priorities
    void displayTasks(int n) {
        if(heap.empty()) {
            cout << "No tasks to display" << endl;
            return;
        }
        cout << "Tasks with the highest priority: " << endl;
        for(int i = 0; i < n && i < heap.size(); i++) {
            cout << i + 1 << ". " << heap[i].task << " (" << heap[i].priority << ")" << endl;
        }
    }
};

bool hasAlphabeticCharacters(const string& str) {
    for (char c : str) {
        if (std::isalpha(c)) {
            return true;
        }
    }
    return false;
}

int main() {
    PriorityQueue priorityQueue;
    vector<string> tasks;

    while (true) {
        string name;
        int priority = 0;
        cin.clear();

        cout << "Enter task name (or 'exit' to quit):" << endl;
        if (!getline(cin, name) || !hasAlphabeticCharacters(name)) {
            cin.clear();
            cout << "Invalid task name. Please try again." << endl;
            continue;
        }
        for (char &c : name) {
            c = tolower(c);
        }

        if (name == "exit") {
            break;
        }

        cout << "Enter task priority: " << endl;
        if (!(cin >> priority)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid priority. Please enter an integer." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Task task{name, priority};
        priorityQueue.insert(task);
    }


    Task highestPriority = priorityQueue.execute();
    if(highestPriority.priority != -1) {
        cout << "Executing task: " << highestPriority.task << ", Priority: " << highestPriority.priority << endl;
    }
    else {
        cout << "No tasks to execute" << endl;
    }

    int n;
    cout << "Enter number of tasks to display by priority: " << endl;
    if (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer." << endl;
        return 1;
    }
    priorityQueue.displayTasks(n);

    while(true) {
        string changeTask;
        cout << "Enter task name to change priority (or 'exit' to stop): " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (!getline(cin, changeTask) || !hasAlphabeticCharacters(changeTask)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid task name. Please try again." << endl;
            return 1;
        }

        for (char &c : changeTask) {
            c = tolower(c);
        }

        if (changeTask == "exit") {
            break;
        }

        int newPriority = 0;
        cout << "Enter the new priority for task " << changeTask << ": " << endl;
        if (!(cin >> newPriority)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid priority. Please enter an integer" << endl;
            return 1;
        }
        if (!priorityQueue.changePriority(changeTask, newPriority)) {
            cout << "Task not found: " << changeTask << endl;
        }
    }

    return 0;
}