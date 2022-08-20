#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

int numOfNodes, numOfRedNodes;
 
struct node {
    int key;
    struct node* left;
    struct node* right;
    bool red;
    int redNodesBefore;
};
 
struct node* createNewNode(int value);
struct node* addLeft(struct node* root, int value);
struct node* addRight(struct node* root, int value);
struct node* createTree(int** matrix, struct node* node, int value);
 
struct node* createNewNode(int value){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode == NULL){
        fprintf(stderr, "MALLOC ERROR ON LINE %d\n", __LINE__);
    }
    newNode->key = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;    
}
 
struct node* addLeft(struct node* root, int value){
    root->left = createNewNode(value);
    return root->left;
}
 
struct node* addRight(struct node* root, int value){
    root->right = createNewNode(value);
    return root->right;
}
 
struct node* createTree(int** matrix, struct node* node, int value){
 
    if (node == NULL){
        node = createNewNode(value);
        node->redNodesBefore = 0;
        if(value <= numOfRedNodes){
            node->red = true;
        } else {
            node->red = false;
        }
    }
 
    //find left child 
    //check if node has left child 
    int child;
    if(matrix[value-1][0] != 0){
        child = matrix[value-1][0];
        for(int i = 0; i < 3; ++i){
            if(matrix[child-1][i] == value){
                matrix[child-1][i] = 0;
                break;
            } 
        }
        matrix[value-1][0] = 0;
        node->left = createTree(matrix, node->left, child);
    } else if(matrix[value-1][1] != 0){
        child = matrix[value-1][1];
        for(int i = 0; i < 3; ++i){
            if(matrix[child-1][i] == value){
                matrix[child-1][i] = 0;
                break;
            } 
        }
        matrix[value-1][1] = 0;
        node->left = createTree(matrix, node->left, child);
    } else if(matrix[value-1][2] != 0){
        child = matrix[value-1][2];
        for(int i = 0; i < 3; ++i){
            if(matrix[child-1][i] == value){
                matrix[child-1][i] = 0;
                break;
            } 
        }
        matrix[value-1][2] = 0;
        node->left = createTree(matrix, node->left, child);
    } else {
        return node;
    }
     
    //find right child
    //check if node has right child
    if(matrix[value-1][0] != 0 && matrix[value-1][0] != value){
        child = matrix[value-1][0];
        for(int i = 0; i < 3; ++i){
            if(matrix[child-1][i] == value){
                matrix[child-1][i] = 0;
                break;
            } 
        }
        matrix[value-1][0] = 0;
        node->right = createTree(matrix, node->right, child);
    } else if(matrix[value-1][1] != 0 && matrix[value-1][1] != value){
        child = matrix[value-1][1];
        for(int i = 0; i < 3; ++i){
            if(matrix[child-1][i] == value){
                matrix[child-1][i] = 0;
                break;
            } 
        }
        matrix[value-1][1] = 0;
        node->right = createTree(matrix, node->right, child);
    } else if(matrix[value-1][2] != 0 && matrix[value-1][2] != value){
        child = matrix[value-1][2];
        for(int i = 0; i < 3; ++i){
            if(matrix[child-1][i] == value){
                matrix[child-1][i] = 0;
                break;
            } 
        }
        matrix[value-1][2] = 0;
        node->right = createTree(matrix, node->right, child);
    } else {
        return node;
    }
     
    return node; 
}
 
int leftFinalNode = INT_MAX, rightFinalNode = INT_MAX;
int lenDiff = INT_MAX;
 
void findAnswer(struct node* node, struct node* parentNode ){
    if(node == NULL){
        return;
    }
    findAnswer(node->left, node);
    findAnswer(node->right, node);
 
    if(node->red){
        node->redNodesBefore++;
    }
 
    if(node->right == NULL && node->left){ //if node has only left child
        if(node->left->red && !node->red){ //if parent is not red && child is
            node->redNodesBefore = node->left->redNodesBefore;
        } else if(!node->left->red && !node->red){ //if parent is not red && child is not red 
            node->redNodesBefore = node->left->redNodesBefore;
        } else if(node->left->red && node->red){ //parent is red && child is red
            node->redNodesBefore += node->left->redNodesBefore;
        } else if(!node->left->red && node->red){ //parent is red && child is not
            node->redNodesBefore += node->left->redNodesBefore;
        }
    } else if(node->left == NULL && node->right){ //if node has only right child
        if(node->right->red && !node->red){ //if parent is not red && child is
            node->redNodesBefore = node->right->redNodesBefore;
        } else if(!node->right->red && !node->red){ //if parent is not red && child is not red 
            node->redNodesBefore = node->right->redNodesBefore;
        } else if(node->right->red && node->red){ //parent is red && child is red
            node->redNodesBefore += node->right->redNodesBefore;
        } else if(!node->right->red && node->red){ //parent is red && child is not
            node->redNodesBefore += node->right->redNodesBefore;
        }
    } else if(node->left && node->right){ //if node has two children
        node->redNodesBefore += node->left->redNodesBefore + node->right->redNodesBefore;
    }
 
    //find difference
    if(parentNode){
        int otherRedNodes = numOfRedNodes - node->redNodesBefore;
        int tmpLenDiff = abs(otherRedNodes - node->redNodesBefore);
         
        if(tmpLenDiff < lenDiff){
            lenDiff = tmpLenDiff;
            if(node->key < parentNode->key){
                leftFinalNode = node->key;
                rightFinalNode = parentNode->key;
            } else {
                leftFinalNode = parentNode->key;
                rightFinalNode = node->key;
            }
        } else if(tmpLenDiff == lenDiff){
            int tmpLeftFinalNode;
            int tmpRightFinalNode;
            if(node->key < parentNode->key){
                tmpLeftFinalNode = node->key;
                tmpRightFinalNode = parentNode->key;
            } else {
                tmpLeftFinalNode = parentNode->key;
                tmpRightFinalNode = node->key;
            }
            if(leftFinalNode > tmpLeftFinalNode){
                leftFinalNode = tmpLeftFinalNode;
                rightFinalNode = tmpRightFinalNode;
            } else if(leftFinalNode == tmpLeftFinalNode){
                if(rightFinalNode > tmpRightFinalNode ){
                    rightFinalNode = tmpRightFinalNode;
                }
            }
        }
    }
 
}
 
int main(void){
 
    if ((scanf("%d %d", &numOfNodes, &numOfRedNodes)) != 2){
        fprintf(stderr, "SCANF FAILURE ON LINE %d\n", __LINE__);
    }
 
    int** nodesMatrix = (int**) calloc((numOfNodes), sizeof(int*));
    if(nodesMatrix == NULL){
        fprintf(stderr, "CALLOC FAILURE ON LINE %d\n", __LINE__);
    }
    for(int i = 0; i < numOfNodes; ++i){
        nodesMatrix[i] = (int*)calloc(3, sizeof(int));
        if(nodesMatrix[i] == NULL){
            fprintf(stderr, "CALLOC FAILURE ON LINE %d\n", __LINE__);
        }
    }
     
    int tmp1, tmp2;
    //matrix of neighbours of each node 
    for(int i = 0; i < numOfNodes-1; ++i){
        if ((scanf("%d %d", &tmp1, &tmp2)) != 2){
            fprintf(stderr, "SCANF FAILURE ON LINE %d\n", __LINE__);
        }
         
        if(nodesMatrix[tmp1-1][0] == 0){
            nodesMatrix[tmp1-1][0] = tmp2;
        } else if(nodesMatrix[tmp1-1][1] == 0){
            nodesMatrix[tmp1-1][1] = tmp2;
        } else {
            nodesMatrix[tmp1-1][2] = tmp2;
        }
         
        if(nodesMatrix[tmp2-1][0] == 0){
            nodesMatrix[tmp2-1][0] = tmp1;
        } else if(nodesMatrix[tmp2-1][1] == 0){
            nodesMatrix[tmp2-1][1] = tmp1;
        } else {
            nodesMatrix[tmp2-1][2] = tmp1;
        }
    }
     
    //find root
    int futureRoot = 0;
    for(int i = 0; i < numOfNodes; ++i){
        if(nodesMatrix[i][1] != 0 && nodesMatrix[i][2] == 0){
            futureRoot = i;
            break;
        }
    }
 
    //create tree starting with the root
    struct node* root = createTree(nodesMatrix, NULL, futureRoot+1);
    findAnswer(root, NULL);
    printf("%d %d\n", leftFinalNode, rightFinalNode);
 
    for(int i = 0; i < numOfNodes; ++i){
        free(nodesMatrix[i]);
    }
    free(nodesMatrix);
 
    return 0;
}
