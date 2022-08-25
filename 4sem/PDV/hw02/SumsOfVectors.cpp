#include "SumsOfVectors.h"

#include <algorithm>
#include <iostream>
#include <numeric>

void sumsOfVectors_omp_per_vector(const vector<vector<int8_t>> &data, vector<long> &solution, unsigned long minVectorSize) {
    unsigned long data_size = data.size();
    for (unsigned long i = 0; i < data_size; ++i) {
        long sum = 0;
        unsigned long vector_size = data[i].size();
#pragma omp parallel for reduction(+ \
                                   : sum) default(none) shared(data, i, vector_size)
        for (unsigned long j = 0; j < vector_size; ++j) {
            sum += data[i][j];
        }
        solution[i] = sum;
    }
}

void sumsOfVectors_omp_static(const vector<vector<int8_t>> &data, vector<long> &solution,
                              unsigned long minVectorSize) {
    unsigned long data_size = data.size();
#pragma omp parallel for schedule(static) default(none) shared(data_size, data, solution)
    for (unsigned long i = 0; i < data_size; ++i) {
        long sum = 0;
        unsigned long vector_size = data[i].size();
        for (unsigned long j = 0; j < vector_size; ++j) {
            sum += data[i][j];
        }
        solution[i] = sum;
    }
}

void sumsOfVectors_omp_dynamic(const vector<vector<int8_t>> &data, vector<long> &solution,
                               unsigned long minVectorSize) {
    unsigned long data_size = data.size();
#pragma omp parallel for schedule(dynamic) default(none) shared(data_size, data, solution)
    for (unsigned long i = 0; i < data_size; ++i) {
        long sum = 0;
        unsigned long vector_size = data[i].size();
        for (unsigned long j = 0; j < vector_size; ++j) {
            sum += data[i][j];
        }
        solution[i] = sum;
    }
}

void sumsOfVectors_omp_shuffle(const vector<vector<int8_t>> &data, vector<long> &solution,
                               unsigned long minVectorSize) {
    auto idx_vec_length = data.size();
    std::vector<int> idxs_arr(idx_vec_length);
    std::iota(idxs_arr.begin(), idxs_arr.end(), 0);
    std::random_shuffle(idxs_arr.begin(), idxs_arr.end());

#pragma omp parallel for schedule(static) default(none) shared(idx_vec_length, data, solution, idxs_arr)
    for (unsigned long i = 0; i < idx_vec_length; ++i) {
        long sum = 0;
        unsigned long vector_size = data[idxs_arr[i]].size();
        for (unsigned long j = 0; j < vector_size; ++j) {
            sum += data[idxs_arr[i]][j];
        }
        solution[idxs_arr[i]] = sum;
    }
}
