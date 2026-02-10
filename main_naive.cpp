#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Common.h"
#include "OutsourceNaive.h"

using namespace std;

int main() {
    srand(time(NULL));

    int experiments = 2; // תגדיל אחרי זה ל-100 או 500

    for(int t=1; t<=experiments; t++){
        cout << "========== Experiment " << t << " ==========\n";

        Instance inst = generateRandomInstance();
        printInstance(inst);

        Result best = solveNaive(inst,false);
        printResult(inst,best);

        cout << "\n\n";
    }
}
