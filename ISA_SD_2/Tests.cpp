#include "Tests.h"
#include "LinkedList.h"
#include "MaxHeapPriorityQueue.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
#include <functional>
#include <vector>

using namespace std;

const int Test::REPETITIONS = 10; // 10 powtórzeń dla każdego testu
const int Test::SEED = 6767;      // stały seed
const int Test::COPIES = 20;      // mniejsza liczba kopii (optymalizacja czasu generowania list)
const vector<int> Test::SIZES = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };


// Generator liczb losowych
class RandomGenerator {
private:
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
public:
    RandomGenerator(int seed, int min, int max) : generator(seed), distribution(min, max) {}
    int getNext() { return distribution(generator); }
};

// szablon funkcji do uruchamiania testów
template <typename QueueType>
static void runTest(const string& testName, const string& fileName, function<void(QueueType&, int, int)> testedfunction, bool isModifyKey = false) {

    cout << "\nTest: " << testName << "\n";

    ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku " << fileName << "\n";
        return;
    }

    file << "Rozmiar Testu;Sredni Czas [ns]\n";

    for (int size : Test::SIZES) {
        double totalTime = 0.0;

        for (int reps = 0; reps < Test::REPETITIONS; ++reps) {
            vector<QueueType> instances(Test::COPIES);
            vector<int> targetElements(Test::COPIES); // każda instancja ma swój własny cel
            vector<int> actionValues(Test::COPIES);   // wartości do operacji wstawiania
            vector<int> actionPrios(Test::COPIES);    // priorytety do operacji

            // unikalne instancje
            for (int i = 0; i < Test::COPIES; ++i) {
                // inny seed dla każdej instancji
                int currentSeedMod = reps * 100 + i;

                RandomGenerator valGen(Test::SEED + currentSeedMod, 1, 1000000);
                RandomGenerator prioGen(Test::SEED + 1000 + currentSeedMod, 1, size * 5);
                RandomGenerator targetGen(Test::SEED + 2000 + currentSeedMod, 0, size > 0 ? size - 1 : 0);

                int targetIndex = targetGen.getNext();

                for (int j = 0; j < size; ++j) {
                    int val = valGen.getNext();
                    int prio = prioGen.getNext();
                    instances[i].insert(val, prio);

					// wartość docelowa dla modify_key
                    if (j == targetIndex) {
                        targetElements[i] = val;
                    }
                }

                // generowanie losowych danych do samej operacji
                RandomGenerator testValGen(Test::SEED + 3000 + currentSeedMod, 1, 1000000);
                RandomGenerator testPrioGen(Test::SEED + 4000 + currentSeedMod, 1, size * 5);

                actionValues[i] = isModifyKey ? targetElements[i] : testValGen.getNext();
                actionPrios[i] = testPrioGen.getNext();
            }

            // start pomiaru czasu
            auto start = chrono::high_resolution_clock::now();

            for (int i = 0; i < Test::COPIES; ++i) {
                // każda instancja otrzymuje swój dedykowany zestaw parametrów
                testedfunction(instances[i], actionValues[i], actionPrios[i]);
            }

            auto end = chrono::high_resolution_clock::now();
			// koniec pomiaru czasu

            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            totalTime += (static_cast<double>(duration) / Test::COPIES);
        }

        double averageTime = totalTime / Test::REPETITIONS;

        file << size << ";" << static_cast<long long>(averageTime) << "\n";
        cout << "   Test = " << size << " \tzakonczony. Srednia: " << static_cast<long long>(averageTime) << " ns\n";
    }
    file.close();
}


// ====================================================================================
// Testy dla LinkedList
// ====================================================================================
void Test::testLinkedListInsert() {
    runTest<LinkedList>("LinkedList_insert", "LL_insert.csv", [](LinkedList& q, int val, int prio) {
        q.insert(val, prio);
        });
}

void Test::testLinkedListExtractMax() {
    runTest<LinkedList>("LinkedList_extract_max", "LL_extract_max.csv", [](LinkedList& q, int val, int prio) {
        if (q.return_size() > 0) q.extract_max();
        });
}

void Test::testLinkedListFindMax() {
    runTest<LinkedList>("LinkedList_find_max", "LL_find_max.csv", [](LinkedList& q, int val, int prio) {
        if (q.return_size() > 0) q.find_max();
        });
}

void Test::testLinkedListModifyKey() {
    // flaga isModifyKey = true
    runTest<LinkedList>("LinkedList_modify_key", "LL_modify_key.csv", [](LinkedList& q, int val, int prio) {
        q.modify_key(val, prio);
        }, true);
}


// ====================================================================================
// Testy dla Heap
// ====================================================================================
void Test::testHeapInsert() {
    runTest<MaxHeapPriorityQueue>("Heap_insert", "Heap_insert.csv", [](MaxHeapPriorityQueue& q, int val, int prio) {
        q.insert(val, prio);
        });
}

void Test::testHeapExtractMax() {
    runTest<MaxHeapPriorityQueue>("Heap_extract_max", "Heap_extract_max.csv", [](MaxHeapPriorityQueue& q, int val, int prio) {
        if (q.returnSize() > 0) q.extractMax();
        });
}

void Test::testHeapFindMax() {
    runTest<MaxHeapPriorityQueue>("Heap_find_max", "Heap_find_max.csv", [](MaxHeapPriorityQueue& q, int val, int prio) {
        if (q.returnSize() > 0) q.peek();
        });
}

void Test::testHeapModifyKey() {
    runTest<MaxHeapPriorityQueue>("Heap_modify_key", "Heap_modify_key.csv", [](MaxHeapPriorityQueue& q, int val, int prio) {
        q.modifyKey(val, prio);
        }, true);
}