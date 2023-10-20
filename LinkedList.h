#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class LinkedList {

public:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node() {
            data = {};
            next = prev = nullptr;
        }
    };

    // Behaviors 
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;


    // Accessors
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;


    // Insertion
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);


    // Removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();


    // Operators
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    bool operator==(const LinkedList<T>& rhs) const;


    // Construction / Destruction
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();




private:
    Node* head;
    Node* tail;
    unsigned int nodeCount;
};


template <typename T>
LinkedList<T>::LinkedList() {
    head = tail = nullptr;
    nodeCount = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node* current = head;

    while (current) {
        head = head->next;
        delete current;
        current = head;
    }

    nodeCount = 0;
    head = tail = nullptr;
}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = head;

    if (head != nullptr) {
        head->prev = newNode;
    }

    head = newNode;

    if (tail == nullptr) {
        tail = head;
    }

    nodeCount += 1;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->prev = tail;

    if (tail != nullptr) {
        tail->next = newNode;
    }

    tail = newNode;

    if (head == nullptr) {
        head = tail;
    }

    nodeCount += 1;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {

    for (unsigned int i = count; i > 0; --i) {
        AddHead(data[i - 1]);
    }

}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {

    for (unsigned int i = 0; i < count; ++i) {
        AddTail(data[i]);
    }

}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodeCount;
}

template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* current = head;

    while (current) {
        cout << current->data << endl;
        current = current->next;
    }

}

template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node* current = tail;

    while (current) {
        cout << current->data << endl;
        current = current->prev;
    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {

    if (index >= nodeCount) {
        throw out_of_range("Error! Index out of range!");
    }

    Node* curr = head;

    for (unsigned int i = 0; i < index; ++i) {
        curr = curr->next;
    }

    return curr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {

    if (index >= nodeCount) {
        throw out_of_range("Error! Index out of range!");
    }

    Node* curr = head;

    for (unsigned int i = 0; i < index; ++i) {
        curr = curr->next;
    }

    return curr;
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {

    if (index >= nodeCount) {
        throw out_of_range("Error! Index out of range!");
    }
    Node* curr = head;

    for (unsigned int i = 0; i < index; ++i) {
        curr = curr->next;
    }
    return curr->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {

    if (index >= nodeCount) {
        throw out_of_range("Error! Index out of range!");
    }

    Node* curr = head;

    for (unsigned int i = 0; i < index; ++i) {
        curr = curr->next;
    }

    return curr->data;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
    Node* current = head;

    while (current) {

        if (current->data == value) {
            outData.push_back(current);
        }

        current = current->next;
    }
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
    Node* curr = head;

    while (curr) {

        if (curr->data == data) {
            return curr;
        }

        curr = curr->next;
    }
    return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
    Node* curr = head;

    while (curr) {

        if (curr->data == data) {
            return curr;
        }

        curr = curr->next;
    }
    return nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    nodeCount = 0;
    head = tail = nullptr;

    Node* currentNode = list.head;

    while (currentNode != nullptr) {
        AddTail(currentNode->data);
        currentNode = currentNode->next;
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    Node* curr = head;

    while (curr != nullptr) {
        head = head->next;
        delete curr;
        curr = head;
    }

    nodeCount = 0;
    head = tail = nullptr;

    Node* currentNode = rhs.head;

    while (currentNode != nullptr) {
        AddTail(currentNode->data);
        currentNode = currentNode->next;
    }

}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {

    if (index < 0 || index > nodeCount) {
        throw out_of_range("Error! Index out of range!");
    }

    if (index == 0) {
        AddHead(data);
        return;
    }

    else if (index == nodeCount) {
        AddTail(data);
        return;
    }

    Node* current = head;
    Node* previous = nullptr;

    for (unsigned int i = 0; i < index; ++i) {
        previous = current;
        current = current->next;
    }

    Node* newNode = new Node;
    newNode->data = data;

    previous->next = newNode;
    current->prev = newNode;

    newNode->next = current;
    newNode->prev = previous;
    nodeCount += 1;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {

    if (node == head) {
        AddHead(data);
        return;
    }

    Node* curr = head;

    while (curr) {

        if (curr == node) {
            Node* newNode = new Node;
            newNode->data = data;
            newNode->next = curr;
            newNode->prev = curr->prev;
            curr->prev->next = newNode;
            curr->prev = newNode;
            return;
        }

        curr = curr->next;
    }
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {

    if (node == tail) {
        AddTail(data);
        return;
    }

    Node* curr = head;

    while (curr) {

        if (curr == node) {
            Node* newNode = new Node;
            newNode->data = data;
            newNode->prev = curr;
            newNode->next = curr->next;

            curr->next->prev = newNode;
            curr->next = newNode;
            return;
        }

        curr = curr->next;
    }
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {

    if (nodeCount != rhs.nodeCount) {
        return false;
    }

    Node* myCurr = head;
    Node* rhsCurr = rhs.head;

    while (myCurr && rhsCurr) {

        if (myCurr->data != rhsCurr->data) {
            return false;
        }

        myCurr = myCurr->next;
        rhsCurr = rhsCurr->next;
    }
    return true;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {

    if (head != nullptr) {
        Node* deleteMe = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        }

        delete deleteMe;
        nodeCount -= 1;

        if (nodeCount == 0) {
            head = tail = nullptr;
        }

        return true;
    }
    return false;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {

    if (tail != nullptr) {
        Node* deleteMe = tail;
        tail = tail->prev;

        if (tail != nullptr) {
            tail->next = nullptr;
        }

        delete deleteMe;
        nodeCount -= 1;

        if (nodeCount == 0) {
            head = tail = nullptr;
        }

        return true;
    }
    return false;
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {

    unsigned int removed = 0;
    Node* current = head;
    Node* previous = nullptr;

    while (current) {

        if (current->data == data) {
            removed += 1;

            if (current == head) {
                current = current->next;
                RemoveHead();
                continue;
            }

            else if (current == tail) {
                current = nullptr;
                RemoveTail();
                continue;
            }

            else {
                Node* deleteMe = current;
                previous->next = current->next;

                if (current->next != nullptr) {
                    current->next->prev = previous;
                }

                current = current->next;
                delete deleteMe;
                nodeCount -= 1;

                if (nodeCount == 0) {
                    head = tail = nullptr;
                }

                continue;
            }
        }
        previous = current;
        current = current->next;
    }
    return removed;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
    if (index >= nodeCount) {
        return false;
    }

    if (index == 0) {
        RemoveHead();
        return true;
    }

    else if (index == nodeCount - 1) {
        RemoveTail();
        return true;
    }

    Node* current = head;
    Node* previous = nullptr;

    for (unsigned int i = 0; i < index; ++i) {
        previous = current;
        current = current->next;
    }

    previous->next = current->next;

    if (current->next != nullptr) {
        current->next->prev = previous;
    }

    delete current;
    nodeCount -= 1;

    if (nodeCount == 0) {
        head = tail = nullptr;
    }

    return true;
}

template <typename T>
void LinkedList<T>::Clear() {

    Node* current = head;

    while (current) {

        head = head->next;
        delete current;
        current = head;
    }

    nodeCount = 0;
    head = tail = nullptr;
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {

    if (node != nullptr) {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }

}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {

    if (node != nullptr) {
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }

}
