#pragma once

#include <vector>

class Test {
public:
    static const int REPETITIONS;
    static const int SEED;
    static const int COPIES;
    static const std::vector<int> SIZES;

    // Testy dla LinkedList
    static void testLinkedListInsert();
    static void testLinkedListExtractMax();
    static void testLinkedListFindMax();
    static void testLinkedListModifyKey();

    // Testy dla Heap
    static void testHeapInsert();
    static void testHeapExtractMax();
    static void testHeapFindMax();
    static void testHeapModifyKey();
};