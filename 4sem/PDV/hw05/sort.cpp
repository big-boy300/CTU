#include "sort.h"

#include <iostream>

void rec_bucket_sort(std::vector<std::string *> &vector_to_sort, const MappingFunction &mappingFunction,
                     unsigned long alphabet_size, unsigned long string_lengths, unsigned long idx);

void radix_par(std::vector<std::string *> &vector_to_sort, const MappingFunction &mappingFunction,
               unsigned long alphabet_size, unsigned long string_lengths) {
    rec_bucket_sort(vector_to_sort, mappingFunction, alphabet_size, string_lengths, 0);
}

void rec_bucket_sort(std::vector<std::string *> &vector_to_sort, const MappingFunction &mappingFunction,
                     unsigned long alphabet_size, unsigned long string_lengths, unsigned long idx) {
    // stop if statement
    if (idx == string_lengths) return;

    // create buckets
    std::vector<std::string *> buckets[alphabet_size];

    // add pointers to buckets(good use of mapping function here)
    for (auto s : vector_to_sort) {
        buckets[mappingFunction((*s).at(idx))].push_back(s);
    }

// recursively call bucket sort
#pragma omp parallel for shared(alphabet_size, buckets, mappingFunction, string_lengths, idx) default(none)
    for (unsigned len = 0; len < alphabet_size; len++) {
#pragma omp task shared(buckets, len, mappingFunction, alphabet_size, string_lengths, idx) default(none)
        rec_bucket_sort(buckets[len], mappingFunction, alphabet_size, string_lengths, idx + 1);
    }

    // concatenate buckets
    unsigned long vector_idx = 0;
    for (unsigned long i = 0; i < alphabet_size; i++) {
        for (auto &j : buckets[i]) {
            vector_to_sort[vector_idx++] = j;
        }
    }
}
