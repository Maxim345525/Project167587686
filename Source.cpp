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
class Array {
private:
    Node<T>* head;
    int size;
    int capacity;
    int grow;
    void expandCapacity(int newSize) {
        while (capacity < newSize) {
            capacity += grow;
        }
    }
public:
    Array() : head(nullptr), size(0), capacity(0), grow(1) {}
    int GetSize() const {
        return size;
    }
    void SetSize(int newSize, int newGrow = 1) {
        if (newSize > capacity) {
            expandCapacity(newSize);
        }
        size = newSize;
        grow = newGrow;
    }
    int GetUpperBound() const {
        return size - 1;
    }
    bool IsEmpty() const {
        return size == 0;
    }
    void FreeExtra() {
        SetSize(size);
    }
    void RemoveAll() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        size = 0;
    }
    T GetAt(int index) const {
        if (index < 0 || index >= size) {
            cerr << "Index out of bounds" << endl;
            exit(EXIT_FAILURE);
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    void SetAt(int index, T value) {
        if (index < 0 || index >= size) {
            cerr << "Index out of bounds" << endl;
            exit(EXIT_FAILURE);
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->data = value;
    }
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            cerr << "Index out of bounds" << endl;
            exit(EXIT_FAILURE);
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    void Add(T value) {
        if (size >= capacity) {
            expandCapacity(size + grow);
        }
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
        size++;
    }
    Array operator+(const Array& other) const {
        Array result = *this;
        Node<T>* current = other.head;
        while (current != nullptr) {
            result.Add(current->data);
            current = current->next;
        }
        return result;
    }
    Array& operator=(const Array& other) {
        if (this == &other) {
            return *this;
        }
        RemoveAll();
        Node<T>* current = other.head;
        while (current != nullptr) {
            Add(current->data);
            current = current->next;
        }
        return *this;
    }
    T* GetData() const {
        T* data = new T[size];
        Node<T>* current = head;
        for (int i = 0; i < size; ++i) {
            data[i] = current->data;
            current = current->next;
        }
        return data;
    }
    void InsertAt(int index, T value) {
        if (index < 0 || index > size) {
            std::cerr << "Index out of bounds" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (index == size) {
            Add(value);
            return;
        }
        Node<T>* newNode = new Node<T>(value);
        if (index == 0) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        else {
            Node<T>* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next->prev = newNode;
            current->next = newNode;
            newNode->prev = current;
        }
        size++;
    }
    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            cerr << "Index out of bounds" << endl;
            exit(EXIT_FAILURE);
        }
        Node<T>* current = head;
        if (index == 0) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete current;
        }
        else {
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            Node<T>* temp = current->next;
            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            delete temp;
        }
        size--;
    }
    void Display() const {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    ~Array() {
        RemoveAll();
    }
};
int main() {
    Array<int> arr1;
    arr1.Add(1);
    arr1.Add(2);
    arr1.Add(3);
    Array<int> arr2;
    arr2.Add(4);
    arr2.Add(5);
    arr2.Add(6);
    cout << "Array 1: ";
    arr1.Display();
    cout << "Array 2: ";
    arr2.Display();
    arr1 = arr1 + arr2;
    cout << "Concatenated Array: ";
    arr1.Display();
    return 0;
}
