#pragma once
#include "Element.h"

class LinkedList {
private:
    struct Node {
        Element data;
        Node* next;
        Node(Element d) : data(d), next(nullptr) {}
    };

    Node* head;
    int size;
    long long time_counter;

public:
    LinkedList();
    ~LinkedList();

    void insert(int e, int p);
    int extract_max();
    int find_max() const;
    void modify_key(int e, int p);
    int return_size() const;
};