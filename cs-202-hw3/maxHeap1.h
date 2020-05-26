/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 3
 */

#ifndef __MAXHEAP1_H
#define __MAXHEAP1_H

struct Patient {
    int id, priority, arrivalTime, serviceTime;
};

class HospitalHeap {
public:
    static const int MAX_SIZE = 2000;

    HospitalHeap();
    ~HospitalHeap();
    bool isEmpty() const;
    void insert(Patient* newPatient);
    Patient* deleteRoot();

protected:
    void rebuild(int root);

private:
    Patient** patients;
    int size;
};
#endif
