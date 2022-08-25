#include <functional>
#include "bst_tree.h"
 
void bst_tree::insert(long long data) {
    node * new_node = new node(data);
    node* cur = root;
 
    node* null = nullptr;
    if(root == nullptr && root.compare_exchange_strong(null, new_node)) return;
 
    while(true){
        node* next = nullptr;
        if(data <= cur->data){
            next = cur->left;
            if(next != nullptr){
                cur = cur->left;
            } else if(next== nullptr && cur->left.compare_exchange_strong(next, new_node)) return;
        } else {
            next = cur->right;
            if(next != nullptr){
                cur = cur->right;
            } else if(next== nullptr && cur->right.compare_exchange_strong(next, new_node)) return;
        }
    }
}
 
bst_tree::~bst_tree() {
    // Rekurzivni funkce pro pruchod stromu a dealokaci pameti prirazene jednotlivym
    // uzlum
    std::function<void(node*)> cleanup = [&](node * n) {
        if(n != nullptr) {
            cleanup(n->left);
            cleanup(n->right);
 
            delete n;
        }
    };
    cleanup(root);
}
