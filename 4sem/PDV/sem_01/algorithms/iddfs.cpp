#include "iddfs.h"
#include "limits.h"

std::shared_ptr<const state> goal;
unsigned long long goal_id = ULONG_LONG_MAX;

void dls(std::shared_ptr<const state> node, int depth) {
    if (depth == 0) {
        if (node->is_goal() && goal_id > node->get_identifier()) {
#pragma omp critical
            {
                goal = node;
                goal_id = node->get_identifier();
            }
            return;
        }
        return;
    }

    std::vector<std::shared_ptr<const state>> next_states = node->next_states();
    unsigned next_states_size = next_states.size();
    for (unsigned i = 0; i < next_states_size; ++i) {
        if (node->get_predecessor() == nullptr) {
#pragma omp task
            dls(next_states[i], depth - 1);
        } else if (next_states[i]->get_identifier() != node->get_predecessor()->get_identifier()) {
#pragma omp task
            dls(next_states[i], depth - 1);
        }
    }
}

std::shared_ptr<const state> iddfs(std::shared_ptr<const state> root) {
    for (int i = 0; true; ++i) {
#pragma omp parallel
#pragma omp single
        dls(root, i);
        if (goal != nullptr) {
            break;
        }
    }
    return goal;
}
