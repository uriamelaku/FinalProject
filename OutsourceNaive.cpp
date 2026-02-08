// OutsourceNaive.cpp
// Naive (exhaustive) solution with rejection/outsourcing
// According to Dana (lecture):
// Constraint: sum_{j in R} u_j <= U
// Objective:  minimize sum_{j in A} w_j * C_j
// (u_j is NOT added to the objective; it is only a budget constraint)

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

struct Job {
    int id;   // 1..n
    int p;    // processing time
    int w;    // weight
    int u;    // outsourcing cost
};

struct Instance {
    int n;
    int m;
    int U;            // outsourcing budget
    vector<Job> jobs;
};

struct Result {
    long long bestSched = numeric_limits<long long>::max(); // objective: minimize this only!
    long long bestOut   = 0;                                // for reporting (must be <= U)
    vector<Job> bestA;  // ordered processed jobs
    vector<Job> bestR;  // outsourced jobs
};

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

// ---------- Compare by ratio w/p (descending) ----------
bool betterRatio(const Job& a, const Job& b) {
    long long left  = 1LL * a.w * b.p;
    long long right = 1LL * b.w * a.p;

    if (left != right) return left > right; // descending
    return a.p < b.p; // tie-break
}

// ---------- Compute scheduling objective on A: sum w_j * C_j ----------
long long computeSchedulingCost(vector<Job>& A, int m) {
    if (A.empty()) return 0;

    // Pick an order for A (WSPT rule)
    sort(A.begin(), A.end(), betterRatio);

    long long sumP = 0;
    long long maxP = 0;
    long long total = 0;

    for (const auto& job : A) {
        sumP += job.p;
        if (job.p > maxP) maxP = job.p;

        long long C_last = sumP + 1LL * (m - 1) * maxP;
        total += 1LL * job.w * C_last;
    }
    return total;
}

// ---------- Naive exhaustive over all rejection sets R ----------
Result solveNaive(const Instance& inst, bool printAllFeasible) {
    Result res;
    int n = inst.n;

    int totalMasks = 1 << n; // n <= 10 in your tests

    for (int mask = 0; mask < totalMasks; mask++) {
        vector<Job> A;
        vector<Job> R;
        long long outCost = 0;

        // Build A and R
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                R.push_back(inst.jobs[i]);
                outCost += inst.jobs[i].u;
            } else {
                A.push_back(inst.jobs[i]);
            }
        }

        // Constraint: budget
        if (outCost > inst.U) continue;

        // Objective: minimize scheduling cost only
        vector<Job> A_ordered = A;
        long long schedCost = computeSchedulingCost(A_ordered, inst.m);

        if (printAllFeasible) {
            cout << "R={";
            for (int i = 0; i < (int)R.size(); i++) {
                cout << "J" << R[i].id << (i+1<(int)R.size() ? "," : "");
            }
            cout << "}  A=";
            for (int i = 0; i < (int)A_ordered.size(); i++) {
                cout << "J" << A_ordered[i].id << (i+1<(int)A_ordered.size() ? "->" : "");
            }
            cout << " | outCost=" << outCost
                 << " schedCost=" << schedCost << "\n";
        }

        // Keep best by schedCost only
        if (schedCost < res.bestSched) {
            res.bestSched = schedCost;
            res.bestOut   = outCost;
            res.bestA     = A_ordered;
            res.bestR     = R;
        }
    }

    return res;
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
