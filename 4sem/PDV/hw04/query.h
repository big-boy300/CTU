#ifndef DATABASEQUERIES_QUERY_H
#define DATABASEQUERIES_QUERY_H

#include <atomic>
#include <functional>
#include <vector>

template <typename row_t>
using predicate_t = std::function<bool(const row_t&)>;

template <typename row_t>
bool is_satisfied_for_all(std::vector<predicate_t<row_t>> predicates, std::vector<row_t> data_table);

template <typename row_t>
bool is_satisfied_for_any(std::vector<predicate_t<row_t>> predicates, std::vector<row_t> data_table);

template <typename row_t>
bool is_satisfied_for_all(std::vector<predicate_t<row_t>> predicates, std::vector<row_t> data_table) {
    int row_count = data_table.size();
    int predicates_len = predicates.size();
    bool ret = true;

#pragma omp parallel for shared(ret, predicates_len, row_count, data_table, predicates) default(none)
    for (int i = 0; i < predicates_len; ++i) {
#pragma omp cancellation point for
        auto& pred = predicates[i];
        bool ret_flag = false;
        for (int j = 0; j < row_count; ++j) {
            auto& row = data_table[j];
            bool is_satisfied = pred(row);
            if (is_satisfied) {
                ret_flag = true;
                break;
            }
        }
        if (!ret_flag) {
            ret = false;
#pragma omp cancel for
        }
#pragma omp cancellation point for
    }
    return ret;
}

template <typename row_t>
bool is_satisfied_for_any(std::vector<predicate_t<row_t>> predicates, std::vector<row_t> data_table) {
    int row_count = data_table.size();
    int predicates_len = predicates.size();
    bool ret = false;

    for (int i = 0; i < predicates_len; ++i) {
        auto& pred = predicates[i];
        bool ret_flag = false;
#pragma omp parallel for shared(pred, ret_flag, predicates_len, row_count, data_table, predicates) default(none)
        for (int j = 0; j < row_count; ++j) {
#pragma omp cancellation point for
            auto& row = data_table[j];
            bool is_satisfied = pred(row);
            if (is_satisfied) {
                ret_flag = true;
#pragma omp cancel for
            }
#pragma omp cancellation point for
        }
        if (ret_flag) {
            ret = true;
            break;
        }
    }
    return ret;
}

#endif  // DATABASEQUERIES_QUERY_H