#include "Common.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// random in range [a,b]
int rnd(int a, int b) {
    return a + rand() % (b - a + 1);
}

Instance generateRandomInstance() {
    Instance inst;

    // number of jobs (Dana: naive works for 8-10)
    inst.n = rnd(8,10);

    // machines
    inst.m = rnd(2,4);

    // generate jobs
    inst.jobs.clear();
    for(int i=0;i<inst.n;i++){
        Job j;
        j.id = i+1;
        j.p = rnd(1,10);
        j.w = rnd(1,10);
        j.u = rnd(1,10);
        inst.jobs.push_back(j);
    }

    // generate budget U (0..30 like Dana said)
    inst.U = rnd(0,30);

    return inst;
}

// ---------- Print instance ----------
void printInstance(const Instance& inst) {
    cout << "=== Instance ===\n";
    cout << "n=" << inst.n << ", m=" << inst.m << ", U=" << inst.U << "\n\n";

    cout << left << setw(6) << "Job"
         << setw(6) << "p"
         << setw(6) << "w"
         << setw(6) << "u"
         << "\n";
    cout << "----------------------\n";

    for (const auto& job : inst.jobs) {
        cout << left << setw(6) << ("J" + to_string(job.id))
             << setw(6) << job.p
             << setw(6) << job.w
             << setw(6) << job.u
             << "\n";
    }
    cout << "\n";
}

// ---------- Print best result ----------
void printResult(const Instance& inst, const Result& r) {
    cout << "=== BEST SOLUTION (Naive) ===\n";

    cout << "Outsourced R = {";
    for (int i = 0; i < (int)r.bestR.size(); i++) {
        cout << "J" << r.bestR[i].id << (i+1<(int)r.bestR.size() ? "," : "");
    }
    cout << "}\n";

    cout << "Processed A order = ";
    for (int i = 0; i < (int)r.bestA.size(); i++) {
        cout << "J" << r.bestA[i].id << (i+1<(int)r.bestA.size() ? " -> " : "");
    }
    cout << "\n";

    cout << "Outsourcing cost (constraint) = " << r.bestOut
         << " <= U=" << inst.U << "\n";

    cout << "Objective: Scheduling cost (sum w*C) = " << r.bestSched << "\n";
}
