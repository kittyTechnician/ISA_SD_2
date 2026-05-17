#include "MaxHeapPriorityQueue.h"
#include <stdexcept>
#include <iostream>

using namespace std;

// Konstruktor domyślny z początkową pojemnością 2
MaxHeapPriorityQueue::MaxHeapPriorityQueue() : arr(new QueueItem[2]), size(0), capacity(2), sequenceCounter(0) {}

MaxHeapPriorityQueue::MaxHeapPriorityQueue(size_t initialCapacity) : size(0), capacity(initialCapacity < 1 ? 1 : initialCapacity), sequenceCounter(0) {
    arr = new QueueItem[capacity];
}

MaxHeapPriorityQueue::~MaxHeapPriorityQueue() {
    delete[] arr;
}

// Metoda do zmiany rozmiaru wewnętrznej tablicy
void MaxHeapPriorityQueue::resize(size_t newCapacity) {
    QueueItem* newArr = new QueueItem[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
}

// Porównanie priorytetów dwóch elementów, uwzględniając FIFO dla równych priorytetów
bool MaxHeapPriorityQueue::hasHigherPriority(const QueueItem& item1, const QueueItem& item2) const {
    if (item1.priority > item2.priority) return true;
    if (item1.priority == item2.priority) return item1.id < item2.id;
    return false;
}

// Przesiewanie w górę (shift up) po dodaniu nowego elementu
void MaxHeapPriorityQueue::siftUp(size_t index) {
    while (index > 0) {
        size_t pIndex = parent(index);
        if (hasHigherPriority(arr[index], arr[pIndex])) {
            swap(arr[index], arr[pIndex]);
            index = pIndex;
        }
        else {
            break;
        }
    }
}

// Przesiewanie w dół (shift down) po usunięciu elementu o najwyższym priorytecie
void MaxHeapPriorityQueue::siftDown(size_t index) {
    size_t maxIndex = index;
    while (true) {
        size_t left = leftChild(index);
        size_t right = rightChild(index);

        if (left < size && hasHigherPriority(arr[left], arr[maxIndex])) maxIndex = left;
        if (right < size && hasHigherPriority(arr[right], arr[maxIndex])) maxIndex = right;

        if (maxIndex != index) {
            swap(arr[index], arr[maxIndex]);
            index = maxIndex;
        }
        else {
            break;
        }
    }
}

// Dodanie elementu do kolejki z określonym priorytetem
void MaxHeapPriorityQueue::insert(int e, int p) {
    if (size >= capacity) resize(capacity * 2);
    arr[size] = { e, p, sequenceCounter++ };
    siftUp(size++);
}

// Usunięcie i zwrócenie elementu o najwyższym priorytecie
int MaxHeapPriorityQueue::extractMax() {
    if (size == 0) throw out_of_range("Queue is empty");
    int maxValue = arr[0].value;
    arr[0] = arr[--size];
    if (size > 0) siftDown(0);
    return maxValue;
}

// Zwrócenie elementu o najwyższym priorytecie bez usuwania go z kolejki
int MaxHeapPriorityQueue::peek() const {
    if (size == 0) throw out_of_range("Queue is empty");
    return arr[0].value;
}


// Zmiana priorytetu elementu o wartości e na newP
void MaxHeapPriorityQueue::modifyKey(int e, int newP) {
    int targetIndex = -1;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i].value == e) {
            targetIndex = i;
            break;
        }
    }
    if (targetIndex == -1) throw invalid_argument("Element not found");

    int oldP = arr[targetIndex].priority;
    arr[targetIndex].priority = newP;

    if (newP > oldP) siftUp(targetIndex);
    else if (newP < oldP) siftDown(targetIndex);
}


size_t MaxHeapPriorityQueue::returnSize() const {
    return size;
}

//  Metoda pomocnicza do drukowania zawartości kolejki (do celów testowych)
void MaxHeapPriorityQueue::printQueue() {
    for (size_t i = 0; i < size; ++i) {
        cout << "(" << arr[i].value << ", p:" << arr[i].priority << ") ";
    }
    cout << endl;
}