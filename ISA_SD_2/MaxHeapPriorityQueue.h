#pragma once

class MaxHeapPriorityQueue {
private:
    // Struktura elementu schowana w sekcji prywatnej
    struct QueueItem {
        int value;
        int priority;
        unsigned long long id;
    };

    // Wewnętrzna minitablica dynamiczna wbudowana bezpośrednio w klasę
    QueueItem* arr;
    size_t size;
    size_t capacity;
    unsigned long long sequenceCounter;

    void resize(size_t newCapacity);

    // Metody nawigacji i przesiewania kopca
    size_t parent(size_t index) const { return (index - 1) / 2; }
    size_t leftChild(size_t index) const { return 2 * index + 1; }
    size_t rightChild(size_t index) const { return 2 * index + 2; }

    bool hasHigherPriority(const QueueItem& item1, const QueueItem& item2) const;
    void siftUp(size_t index);
    void siftDown(size_t index);

public:
    MaxHeapPriorityQueue();
    MaxHeapPriorityQueue(size_t initialCapacity);
    ~MaxHeapPriorityQueue();

    void insert(int e, int p);          // O(log n)
    int extractMax();                   // O(log n)
    int peek() const;                   // O(1)
    void modifyKey(int e, int newP);    // O(n)
    size_t returnSize() const;          // O(1)

    void printQueue();
};