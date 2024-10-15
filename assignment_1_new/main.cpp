#include <iostream>
using namespace std;

class JosephusCircle {
private:
    struct Node {
        int id;
        Node *next_node;
        Node(int _id) : id(_id), next_node(nullptr) {}
    };

    Node *head;
    Node *tail; // Add a tail pointer
    int size_of_circle;

public:
    // function to add person to the circle
    void addPerson(int id) {
        Node *new_node = new Node(id);
        if (!head) {
            head = new_node;
            head->next_node = head; // points to itself for the circular behavior
            tail = head; // Set tail to the first person
        } else {
            new_node->next_node = head;
            tail->next_node = new_node;
            tail = new_node; // Update the tail to the newly added person
        }
        size_of_circle++;
    }

    // function to eliminate person
    void eliminateKthPerson(int kth) {
        if(size_of_circle <= 1) {
            return;
        }
        // only if the size_of_circle is larger then one
        Node *previous = head;
        while(size_of_circle > 1) {
            for(int i = 1; i < kth - 1; i++) {
                previous = previous->next_node;
            }
            Node *current = previous->next_node;
            // removing the kth person from the circle
            previous->next_node = current->next_node;
            // free the occupied memory by the eliminated person
            delete current;
            size_of_circle--;

            // moving the next person for the next iteration
            previous = previous->next_node;
        }
    }

    // function to find last remaining person
    int getLastRemainingPerson() {
        if (!head) {
            cout << "The Circle is empty" << endl;
            return -1;
        }
        return head->id;
    }

public:
    // constructor
    JosephusCircle() : head(nullptr), tail(nullptr), size_of_circle(0) {}

    // destructor to clean up memory by eliminating every person one by one
    ~JosephusCircle() {
        while (size_of_circle > 0) {
            // delete one person at time
            eliminateKthPerson(1);
        }
    }
};

int main() {

    // initialize the variables
    JosephusCircle josephus_circle;
    int number_of_people, k;

    cout << "Enter number of people: " << endl;
    cin >> number_of_people;

    // adding the person to the circle
    for(int i = 1; i <= number_of_people; i++) {
        josephus_circle.addPerson(i);
    }

    // take a user input for the value of k
    cout << "Enter the value of k: " << endl;
    cin >> k;

    // simulate elimination process and display the last person's ID
    josephus_circle.eliminateKthPerson(k);
    cout << "The last remaining person's ID: " << josephus_circle.getLastRemainingPerson() << endl;

    return 0;
}
