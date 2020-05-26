/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 3
 */

using namespace std;
#include <iostream>
#include "maxHeap1.h"

HospitalHeap::HospitalHeap() {
    size = 0;
    patients = new Patient * [MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        patients[i] = NULL;
    }
}

HospitalHeap::~HospitalHeap() {
    for (int i = 0; i < MAX_SIZE; i++) {
        patients[i] = NULL;
    }
    delete[] patients;
}

bool HospitalHeap::isEmpty() const {
    return !size;
}

void HospitalHeap::insert(Patient* newPatient) {
    if (size >= MAX_SIZE) {
        cout << "Error: heap full!";
    }

    patients[size] = newPatient;

    // trickle up
    int place = size;
    int parent = (place - 1) / 2;
    while (place > 0 && patients[place]->priority > patients[parent]->priority) {
        Patient* temp = patients[parent];
        patients[parent] = patients[place];
        patients[place] = temp;

        place = parent;
        parent = (place - 1) / 2;
    }
    size++;
}

Patient* HospitalHeap::deleteRoot() {
    if (isEmpty()) {
        cout << "Error: heap empty!";
        return NULL;
    }
    else {
        Patient* root = patients[0];
        patients[0] = patients[--size];
        rebuild(0);
        return root;
    }
}

void HospitalHeap::rebuild(int root) {
    int child = 2 * root + 1; // left child index

    if (child < size) {
        int rightChild = child + 1; // right child index
        if (rightChild < size && (patients[rightChild]->priority > patients[child]->priority ||
            (patients[rightChild]->priority == patients[child]->priority &&
                patients[rightChild]->arrivalTime < patients[child]->arrivalTime))) {
            child = rightChild;
        }

        // trickle down
        if (patients[root]->priority < patients[child]->priority || 
            (patients[root]->priority == patients[child]->priority && 
                patients[root]->arrivalTime > patients[child]->arrivalTime)) {
            Patient* temp = patients[root];
            patients[root] = patients[child];
            patients[child] = temp;

            rebuild(child);
        }
    }
}
