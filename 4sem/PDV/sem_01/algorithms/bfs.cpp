#include "bfs.h"
#include <unordered_set>
#include "limits.h"

std::shared_ptr<const state> bfs(std::shared_ptr<const state> root) {
    if (root->is_goal()) {
        return root;
    }

    std::vector<std::shared_ptr<const state>> opened_vert;
    std::vector<std::shared_ptr<const state>> copy_opened_vert;
    std::unordered_set<unsigned long long> vert_ids;
    std::vector<std::shared_ptr<const state>> all_goals;

    // add root to queue
    opened_vert.push_back(root);

    // add root's id to vector
    vert_ids.insert(root->get_identifier());

    bool finish_flag = false;

    std::shared_ptr<const state> ret;
    unsigned long long ret_id = ULONG_LONG_MAX;

    while (!opened_vert.empty()) {
        unsigned size = opened_vert.size();
#pragma omp parallel for schedule(dynamic)
        for (unsigned j = 0; j < size; ++j) {
            std::shared_ptr<const state> cur_node = opened_vert.at(j);
            std::vector<std::shared_ptr<const state>> next_states = cur_node->next_states();
            unsigned next_states_size = cur_node->next_states().size();
            for (unsigned i = 0; i < next_states_size; ++i) {
                if (next_states[i]->is_goal() && ret_id > next_states[i]->get_identifier()) {
#pragma omp critical
                    {
                        ret = next_states[i];
                        ret_id = next_states[i]->get_identifier();
                        finish_flag = true;
                    }
                }
                // only if id is not already in vert_ids add to opened_vert
                if (vert_ids.find(next_states[i]->get_identifier()) == vert_ids.end()) {
#pragma omp critical
                    {
                        copy_opened_vert.push_back(next_states[i]);
                        vert_ids.insert(next_states[i]->get_identifier());
                    }
                }
            }
        }
        if (finish_flag) break;
        opened_vert = copy_opened_vert;
        copy_opened_vert.clear();
    }

    return ret;
}
