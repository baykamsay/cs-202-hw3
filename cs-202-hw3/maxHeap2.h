/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 3
 */

#ifndef __MAXHEAP2_H
#define __MAXHEAP2_H

struct Patient {
    int id, priority, arrivalTime, serviceTime;
};

class HospitalHeap {
public:
    static const int INIT_SIZE = 10;

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
    int currentMaxSize;
};
#endif
