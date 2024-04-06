#include <iostream>
using namespace std;
template<typename T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;
    Node() : prev(nullptr), next(nullptr) {}
    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};
template<typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int size;
public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
        size++;
    }
    T dequeue() {
        if (isEmpty()) {
            cerr << "Queue is empty" << endl;
            exit(EXIT_FAILURE);
        }
        T data = front->data;
        Node<T>* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        else {
            front->prev = nullptr;
        }
        delete temp;
        size--;
        return data;
    }
    bool isEmpty() const {
        return size == 0;
    }
    int getSize() const {
        return size;
    }
    Queue clone() const {
        Queue clonedQueue;
        Node<T>* current = front;
        while (current != nullptr) {
            clonedQueue.enqueue(current->data);
            current = current->next;
        }
        return clonedQueue;
    }
    Queue operator+(const Queue& other) const {
        Queue result = *this;
        Node<T>* current = other.front;
        while (current != nullptr) {
            result.enqueue(current->data);
            current = current->next;
        }
        return result;
    }
    Queue operator*(const Queue& other) const {
        Queue result;
        Node<T>* current = front;
        while (current != nullptr) {
            Node<T>* otherCurrent = other.front;
            while (otherCurrent != nullptr) {
                if (current->data == otherCurrent->data) {
                    result.enqueue(current->data);
                    break;
                }
                otherCurrent = otherCurrent->next;
            }
            current = current->next;
        }
        return result;
    }
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        Node<T>* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};
int main() {
    Queue<int> queue1;
    queue1.enqueue(1);
    queue1.enqueue(2);
    queue1.enqueue(3);
    Queue<int> queue2;
    queue2.enqueue(2);
    queue2.enqueue(3);
    queue2.enqueue(4);
    Queue<int> clonedQueue = queue1.clone();
    Queue<int> concatenatedQueue = queue1 + queue2;
    Queue<int> commonElementsQueue = queue1 * queue2;
    cout << "Original Queue 1: ";
    queue1.display();
    cout << "Cloned Queue: ";
    clonedQueue.display();
    cout << "Concatenated Queue: ";
    concatenatedQueue.display();
    cout << "Common Elements Queue: ";
    commonElementsQueue.display();
    return 0;
}
