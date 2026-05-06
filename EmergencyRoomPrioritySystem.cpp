#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct Patient {
    int id;
    string name;
    int severity;
    int arrivalTime;
};

class EmergencyHeap {
private:
    vector<Patient> heap;

    int parent(int i) {
        return (i - 1) / 2;
    }
    int leftChild(int i) {
        return 2 * i + 1;
    }
    int rightChild(int i) {
        return 2 * i + 2;
    }

    bool hasHigherPriority(Patient& a, Patient& b) {
        if (a.severity != b.severity)
            return a.severity > b.severity;
        return a.arrivalTime < b.arrivalTime;
    }

    void heapifyUp(int i) {
        while (i > 0 && hasHigherPriority(heap[i], heap[parent(i)])) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int size = heap.size();
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < size && hasHigherPriority(heap[left], heap[largest]))
            largest = left;

        if (right < size && hasHigherPriority(heap[right], heap[largest]))
            largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:

    void insert(Patient p) {
        heap.push_back(p);
        heapifyUp(heap.size() - 1);
        cout << "Added  -> ID=" << p.id
            << " | Name=" << p.name
            << " | Severity=" << p.severity
            << " | Arrival=" << p.arrivalTime << "\n";
    }

    void treatNext() {
        if (heap.empty()) {
            cout << "No patients.\n";
            return;
        }
        Patient p = heap[0];
        cout << "Treating -> ID=" << p.id
            << " | Name=" << p.name
            << " | Severity=" << p.severity
            << " | Arrival=" << p.arrivalTime << "\n";

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);
    }

    void viewNext() {
        if (heap.empty()) {
            cout << "No patients.\n";
            return;
        }

        Patient& p = heap[0];
        cout << "Next   -> ID=" << p.id
            << " | Name=" << p.name
            << " | Severity=" << p.severity
            << " | Arrival=" << p.arrivalTime << "\n";
    }

    void updateSeverity(int id, int newSeverity) {
        for (int i = 0; i < (int)heap.size(); i++) {
            if (heap[i].id == id) {
                int old = heap[i].severity;
                heap[i].severity = newSeverity;

                if (newSeverity > old)
                    heapifyUp(i);
                else
                    heapifyDown(i);

                cout << "Updated -> ID=" << id
                    << " | Name=" << heap[i].name
                    << " | Severity: " << old << " -> " << newSeverity << "\n";
                return;
            }
        }
        cout << "Patient ID=" << id << " not found.\n";
    }

    void displayAll() {
        if (heap.empty()) {
            cout << "No patients.\n";
            return;
        }

        cout << "\nID\tName\t\tSeverity\tArrival\n";
        cout << "------------------------------------------------\n";

        for (Patient& p : heap)
            cout << p.id << "\t" << p.name << "\t\t"
                 << p.severity << "\t\t" << p.arrivalTime << "\n";

        cout << "------------------------------------------------\n";
    }
};

struct STLComparator {
    bool operator()(Patient& a, Patient& b) {
        if (a.severity != b.severity)
            return a.severity < b.severity;
        return a.arrivalTime > b.arrivalTime;
    }
};

void compareWithSTL(vector<Patient>& patients) {
    cout << "\n========== STL Priority Queue ==========\n";

    priority_queue<Patient, vector<Patient>, STLComparator> stlHeap;

    for (Patient& p : patients)
        stlHeap.push(p);

    cout << "ID\tName\t\tSeverity\tArrival\n";
    cout << "------------------------------------------------\n";

    while (!stlHeap.empty()) {
        Patient p = stlHeap.top();
        stlHeap.pop();

        cout << p.id << "\t" << p.name << "\t\t"
            << p.severity << "\t\t" << p.arrivalTime << "\n";
    }

    cout << "=========================================\n";
}

int main() {
    EmergencyHeap er;

    vector<Patient> patients = {
        {1,  "Ahmed",    9,  1},
        {2,  "Sara",     7,  2},
        {3,  "Mohamed",  5,  3},
        {4,  "Nour",     8,  4},
        {5,  "Ali",      6,  5},
        {6,  "Mona",     9,  6},
        {7,  "Omar",     3,  7},
        {8,  "Hana",     7,  8},
        {9,  "Youssef",  4,  9},
        {10, "Layla",    8,  10},
        {11, "Karim",    2,  11},
        {12, "Dina",     6,  12},
        {13, "Tarek",    9,  13},
        {14, "Rana",     5,  14},
        {15, "Samer",    7,  15},
        {16, "Heba",     8,  16},
        {17, "Fares",    1,  17},
        {18, "Rania",    6,  18},
        {19, "Wael",     9,  19},
        {20, "Nadia",    4,  20},
        {21, "Bassem",   8,  21},
        {22, "Lina",     3,  22}
    };

    cout << "========== 1. Insert Patients ==========\n";
    for (Patient& p : patients)
        er.insert(p);

    cout << "\n========== 2. Display All ==========";
    er.displayAll();

    cout << "\n========== 3. View Next ==========\n";
    er.viewNext();

    cout << "\n========== 4. Treat Next 3 ==========\n";
    er.treatNext();
    er.treatNext();
    er.treatNext();

    cout << "\n========== 5. Update Severity ==========\n";
    er.updateSeverity(7, 10);

    cout << "\n========== Display After Update ==========";
    er.displayAll();

    cout << "\n========== View Next After Update ==========\n";
    er.viewNext();

    compareWithSTL(patients);

    return 0;
}
