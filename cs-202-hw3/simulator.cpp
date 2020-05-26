/**
 * Author : Baykam Say
 * ID: 21802030
 * Section : 3
 * Assignment : 3
 */

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
//#ifdef Q1
//#include "maxHeap1.h"
//#else
#include "maxHeap2.h"
//#endif // Q1

// return if avgWaitingTime is enough
bool runSim(Patient** allPatients, int numOfPatients, double requiredAvgWaitingTime, int doctorAmount,
    string& report) {
    report = "";
    int totalWaitingTime = 0;
    double avgWaitingTime;
    int currentPatient = 0;
    int currentTime = 0;
    int timePassed;
    HospitalHeap* hospitalQueue = new HospitalHeap();
    int* doctors = new int[doctorAmount]; // elements in doctors are the time until they are available
    for (int i = 0; i < doctorAmount; i++) {
        doctors[i] = 0;
    }

    while (currentPatient < numOfPatients || !hospitalQueue->isEmpty()) {
        // update time
        if (currentPatient < numOfPatients) {
            timePassed = allPatients[currentPatient]->arrivalTime - currentTime;
        } else {
            timePassed = doctors[0];
        }
        for (int i = 0; i < doctorAmount; i++) {
            if (doctors[i] < timePassed) {
                timePassed = doctors[i];
            }
        }
        if (timePassed == 0) {
            timePassed = 1;
        }
        
        currentTime += timePassed;
        for (int i = 0; i < doctorAmount; i++) {
            doctors[i] -= timePassed;
            if (doctors[i] < 0) {
                doctors[i] = 0;
            }
        }

        // add to queue
        while (currentPatient < numOfPatients && 
            allPatients[currentPatient]->arrivalTime == currentTime) {
            hospitalQueue->insert(allPatients[currentPatient++]);
        }

        // get from queue until no doctor is available
        for (int i = 0; i < doctorAmount && !hospitalQueue->isEmpty() ; i++) {
            if (doctors[i] == 0) {
                Patient* patient = hospitalQueue->deleteRoot();
                totalWaitingTime += currentTime - patient->arrivalTime;
                doctors[i] = patient->serviceTime;
                report += "Doctor " + to_string(i) + " takes patient " + to_string(patient->id)
                    + " at minute " + to_string(currentTime) + " (wait: "
                    + to_string(currentTime - patient->arrivalTime) + " mins)\n";
            }
        }
    }

    delete[] doctors;
    delete hospitalQueue;
    avgWaitingTime = (double) totalWaitingTime / numOfPatients;
    avgWaitingTime = round(avgWaitingTime * 100) / 100;
    stringstream strAvgWaitingTime;
    strAvgWaitingTime << avgWaitingTime;
    report += "\nAverage waiting time: " + strAvgWaitingTime.str() + " minutes";
    return avgWaitingTime <= requiredAvgWaitingTime;
}

// arg1: filename, arg2: avg waiting time
int main(int argc, char* argv[]) {
    fstream file(argv[1]);
    int numOfPatients;
    file >> numOfPatients;

    Patient** allPatients = new Patient * [numOfPatients];

    for (int i = 0; i < numOfPatients; i++) {
        allPatients[i] = new Patient();

        file >> allPatients[i]->id;
        file >> allPatients[i]->priority;
        file >> allPatients[i]->arrivalTime;
        file >> allPatients[i]->serviceTime;
    }

    int doctorAmount = 1;
    bool simSuccessful;
    string report;
    do {
        simSuccessful = runSim(allPatients, numOfPatients, stod(argv[2]), doctorAmount, report);
        if (!simSuccessful) {
            doctorAmount++;
        }
    } while (!simSuccessful);

    // print results
    cout << "Minimum number of doctors required: " << doctorAmount << endl << endl;
    cout << "Simulation with " << doctorAmount << " doctors:" << endl << endl;
    cout << report << endl;
    
    // delete allpatients
    for (int i = 0; i < numOfPatients; i++) {
        delete allPatients[i];
    }
    delete[] allPatients;
    return 0;
}