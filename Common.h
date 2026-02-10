#pragma once
#include <vector>

struct Job {
    int id;   // 1..n
    int p;    // processing time
    int w;    // weight
    int u;    // outsourcing cost
};

struct Instance {
    int n;
    int m;
    int U;               // outsourcing budget
    std::vector<Job> jobs;
};

struct Result {
    long long bestSched; // objective: minimize this only!
    long long bestOut;   // for reporting (must be <= U)
    std::vector<Job> bestA;  // ordered processed jobs
    std::vector<Job> bestR;  // outsourced jobs
};

// random in range [a,b]
int rnd(int a, int b);

Instance generateRandomInstance();

void printInstance(const Instance& inst);
void printResult(const Instance& inst, const Result& r);
