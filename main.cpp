// main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "OutsourceNaive.cpp"

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

int main() {
    srand(time(NULL));

    int experiments = 20; // תגדיל אחרי זה ל-100 או 500

    for(int t=1; t<=experiments; t++){
        cout << "========== Experiment " << t << " ==========\n";

        Instance inst = generateRandomInstance();
        printInstance(inst);

        Result best = solveNaive(inst,false);
        printResult(inst,best);

        cout << "\n\n";
    }
}
