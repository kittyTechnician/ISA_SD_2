#include "Tests.h"
#include "LinkedList.h"
//#include "HeapPQ.h"

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

// Uniwersalny szablon funkcji do uruchamiania testów Kolejek Priorytetowych
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
            vector<int> targetElements(Test::COPIES); // Każda instancja ma swój własny cel
            vector<int> actionValues(Test::COPIES);   // Wartości do operacji wstawiania
            vector<int> actionPrios(Test::COPIES);    // Priorytety do operacji

            // Tworzymy unikalne instancje i dla każdej losujemy inny target
            for (int i = 0; i < Test::COPIES; ++i) {
                // Rozrzucamy seed, aby każda z 20 instancji miała zupełnie inne dane
                int currentSeedMod = reps * 100 + i;

                RandomGenerator valGen(Test::SEED + currentSeedMod, 1, 1000000);
                RandomGenerator prioGen(Test::SEED + 1000 + currentSeedMod, 1, size * 5);
                RandomGenerator targetGen(Test::SEED + 2000 + currentSeedMod, 0, size > 0 ? size - 1 : 0);

                int targetIndex = targetGen.getNext();

                for (int j = 0; j < size; ++j) {
                    int val = valGen.getNext();
                    int prio = prioGen.getNext();
                    instances[i].insert(val, prio);

                    // Zapisujemy wartość, która wylądowała pod wylosowanym dla tej instancji indeksem
                    if (j == targetIndex) {
                        targetElements[i] = val;
                    }
                }

                // Generowanie losowych danych do samej operacji (jeśli to nie modify_key)
                RandomGenerator testValGen(Test::SEED + 3000 + currentSeedMod, 1, 1000000);
                RandomGenerator testPrioGen(Test::SEED + 4000 + currentSeedMod, 1, size * 5);

                actionValues[i] = isModifyKey ? targetElements[i] : testValGen.getNext();
                actionPrios[i] = testPrioGen.getNext();
            }

            // --- WŁAŚCIWY POMIAR CZASU ---
            auto start = chrono::high_resolution_clock::now();

            for (int i = 0; i < Test::COPIES; ++i) {
                // Wykonujemy operację, gdzie każda instancja otrzymuje swój dedykowany zestaw parametrów
                testedfunction(instances[i], actionValues[i], actionPrios[i]);
            }

            auto end = chrono::high_resolution_clock::now();
            // -----------------------------

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
    // Ustawiamy flagę isModifyKey = true
    runTest<LinkedList>("LinkedList_modify_key", "LL_modify_key.csv", [](LinkedList& q, int val, int prio) {
        q.modify_key(val, prio);
        }, true);
}


// ====================================================================================
// Testy dla HeapPQ
// ====================================================================================
//void Test::testHeapPQInsert() {
//    runTest<HeapPQ<int>>("HeapPQ_insert", "Heap_insert.csv", [](HeapPQ<int>& q, int val, int prio) {
//        q.insert(val, prio);
//        });
//}
//
//void Test::testHeapPQExtractMax() {
//    runTest<HeapPQ<int>>("HeapPQ_extract_max", "Heap_extract_max.csv", [](HeapPQ<int>& q, int val, int prio) {
//        if (q.return_size() > 0) q.extract_max();
//        });
//}
//
//void Test::testHeapPQFindMax() {
//    runTest<HeapPQ<int>>("HeapPQ_find_max", "Heap_find_max.csv", [](HeapPQ<int>& q, int val, int prio) {
//        if (q.return_size() > 0) q.find_max();
//        });
//}
//
//void Test::testHeapPQModifyKey() {
//    runTest<HeapPQ<int>>("HeapPQ_modify_key", "Heap_modify_key.csv", [](HeapPQ<int>& q, int val, int prio) {
//        q.modify_key(val, prio);
//        }, true);
//}