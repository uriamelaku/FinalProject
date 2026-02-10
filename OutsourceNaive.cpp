#include "OutsourceNaive.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// ---------- Compare by ratio w/p (descending) ----------
static bool betterRatio(const Job& a, const Job& b) {
    long long left  = 1LL * a.w * b.p;
    long long right = 1LL * b.w * a.p;

    if (left != right) return left > right; // descending
    return a.p < b.p; // tie-break
}

// ---------- Compute scheduling objective on A: sum w_j * C_j ----------
static long long computeSchedulingCost(vector<Job>& A, int m) {
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
    res.bestSched = numeric_limits<long long>::max();
    res.bestOut   = 0;

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

        // Constraint: sum_{j in R} u_j <= U
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
