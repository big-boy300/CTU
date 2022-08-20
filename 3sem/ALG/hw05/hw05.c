#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_FAILURE 101

/**
 * assignment
 * https://cw.felk.cvut.cz/brute/data/ae/release/2021z_b4b33alg/alg_cz_2021z/evaluation/input.php?task=intervalBVS
 */

bool* allNodes;

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} node_t;

node_t* createNode(int value) {
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL) {
        fprintf(stderr, "MALLOC FAILURE!\n");
        exit(MALLOC_FAILURE);
    }
    newNode->key = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node_t* insert(node_t* node, int start, int end) {
    if (start > end) {
        return NULL;
    }
    if (allNodes[start] == true) {
        if (start < end) {
            return insert(node, start + 1, end);
        } else {
            return node;
        }
    } else {
        if (node == NULL && start <= end) {
            node = createNode(start);
            node->right = insert(node->right, start + 1, end);
        } else if (start <= end) {
            if (start > node->key) {
                node->right = insert(node->right, start, end);
            } else if (start < node->key) {
                if (end > node->key) {
                    node->left = insert(node->left, start, node->key - 1);
                    node->right = insert(node->right, node->key + 1, end);
                } else {
                    node->left = insert(node->left, start, end);
                }
            }
        }
    }
    return node;
}

node_t* minValueNode(node_t* node) {
    node_t* curNode = node;
    while (curNode->left != NULL) {
        curNode = curNode->left;
    }
    return curNode;
}

node_t* usualDelete(node_t* node, int value) {
    if (node == NULL) {
        return node;
    }
    if (value < node->key) {
        node->left = usualDelete(node->left, value);
    } else if (value > node->key) {
        node->right = usualDelete(node->right, value);
    } else {
        if (node->left == NULL) {
            return node->right;
        } else if (node->right == NULL) {
            return node->left;
        }
        node_t* tmp = minValueNode(node->right);
        node->key = tmp->key;
        node->right = usualDelete(node->right, tmp->key);
    }
    return node;
}

node_t* postorderDelete(node_t* node, node_t* parent, int start, int end) {
    if (node == NULL) {
        return NULL;
    }
    postorderDelete(node->left, node, start, end);
    postorderDelete(node->right, node, start, end);

    if (node->key >= start && node->key <= end) {
        int tmp = node->key;
        node = usualDelete(node, node->key);

        if (parent) {
            if (tmp > parent->key) {
                parent->right = node == NULL ? NULL : node;
            } else {
                parent->left = node == NULL ? NULL : node;
            }
        }
    }
    return node;
}

int DEPTH = 0;
int NUMBER = 0;

void preorder(node_t* node, node_t* parent, int depth) {
    if (node == NULL) {
        return;
    }
    depth++;
    if (DEPTH < depth) {
        DEPTH = depth;
    }
    preorder(node->left, node, depth);
    preorder(node->right, node, depth);
    NUMBER++;
}

int findDepth(node_t* node) {
    if (node) {
        int leftDepth = findDepth(node->left);
        int rightDepth = findDepth(node->right);
        if (leftDepth > rightDepth) {
            return leftDepth;
        } else {
            return rightDepth;
        }
    } else {
        return 0;
    }
}

int main(void) {
    allNodes = (bool*)malloc(70001 * sizeof(bool));
    for (int i = 0; i < 70001; ++i) {
        allNodes[i] = false;
    }

    int operationsNum;
    if ((scanf("%d\n", &operationsNum)) != 1) {
        fprintf(stderr, "SCANF FAILURE ON LINE %d\n", __LINE__);
    }

    int start, end;
    char operation;
    node_t* root = NULL;
    for (int i = 0; i < operationsNum; ++i) {
        if ((scanf("%c %d %d\n", &operation, &start, &end)) != 3) {
            fprintf(stderr, "SCANF FAILURE ON LINE %d\n", __LINE__);
        }
        if (operation == 'i') {
            root = insert(root, start, end);
            for (int j = start; j <= end; ++j) {
                allNodes[j] = true;
            }
        } else if (operation == 'd') {
            root = postorderDelete(root, NULL, start, end);
            for (int j = start; j <= end; ++j) {
                allNodes[j] = false;
            }
        } else {
            printf("Invalid operation!\n");
        }
    }

    preorder(root, NULL, 0);
    printf("%d %d\n", NUMBER, DEPTH - 1);

    return 0;
}
