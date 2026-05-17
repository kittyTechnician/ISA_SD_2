#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList() : head(nullptr), size(0), time_counter(0) {}

LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::insert(int e, int p) {
    Element new_el = { e, p, time_counter++ };
    Node* new_node = new Node(new_el);

    if (!head || new_el > head->data) {
        new_node->next = head;
        head = new_node;
    }
    else {
        Node* current = head;
        while (current->next != nullptr && !(new_el > current->next->data)) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    size++;
}

int LinkedList::extract_max() {
    if (!head) throw std::runtime_error("Kolejka jest pusta!");
    Node* temp = head;
    int max_val = temp->data.value;
    head = head->next;
    delete temp;
    size--;
    return max_val;
}

int LinkedList::find_max() const {
    if (!head) throw std::runtime_error("Kolejka jest pusta!");
    return head->data.value;
}

void LinkedList::modify_key(int e, int p) {
    Node* current = head;
    Node* prev = nullptr;
    long long orig_timestamp = -1;

    while (current != nullptr) {
        if (current->data.value == e) {
            orig_timestamp = current->data.timestamp;
            if (prev == nullptr) {
                head = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            size--;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (orig_timestamp != -1) {
        Element updated_el = { e, p, orig_timestamp };
        Node* new_node = new Node(updated_el);

        if (!head || updated_el > head->data) {
            new_node->next = head;
            head = new_node;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr && !(updated_el > temp->next->data)) {
                temp = temp->next;
            }
            new_node->next = temp->next;
            temp->next = new_node;
        }
        size++;
    }
}

int LinkedList::return_size() const {
    return size;
}