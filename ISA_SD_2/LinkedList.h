#pragma once

#include "PQ.h"
#include "Element.h"

class LinkedList : public PQ {
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

    void insert(int e, int p) override;
    int extract_max() override;
    int find_max() const override;
    void modify_key(int e, int p) override;
    int return_size() const override;
};