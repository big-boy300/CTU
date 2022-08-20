#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NEIGHBOURS_NUM 4

/**
 * assignment
 * https://cw.felk.cvut.cz/brute/data/ae/release/2021z_b4b33alg/alg_cz_2021z/evaluation/input.php?task=caravan
 */

typedef struct {
    int key;
    bool isGreen;
    bool isVisited;
    int curSaturation;
    int packetNum;
    int* neighbours;
} node_t;

// create queue for BFS
typedef struct queue_elem {
    node_t* nodeInfo;
    struct queue_elem* next;
} queue_elem_t;

typedef struct {
    queue_elem_t* head;
    queue_elem_t* tail;
} queue_t;

void queue_init(queue_t** queue) {
    *queue = (queue_t*)malloc(sizeof(queue_t));
    if (*queue == NULL) {
        return;
    }
    (*queue)->head = NULL;
    (*queue)->tail = NULL;
}

void queue_push(queue_t* queue, node_t* node) {
    queue_elem_t* newElem = (queue_elem_t*)malloc(sizeof(queue_elem_t));
    if (newElem == NULL) {
        return;
    } else {
        newElem->nodeInfo = node;
        newElem->next = NULL;
        if (queue->tail) {
            queue->tail->next = newElem;
        } else {
            queue->head = newElem;
        }
        queue->tail = newElem;
    }
}

node_t* queue_pop(queue_t* queue) {
    node_t* ret = NULL;
    if (queue->head) {
        ret = queue->head->nodeInfo;
        queue_elem_t* tmp = queue->head;
        queue->head = queue->head->next;
        free(tmp);
        if (queue->head == NULL) {
            queue->tail = NULL;
        }
    }
    return ret;
}

bool queue_isEmpty(queue_t* queue) {
    return queue->head == NULL;
}

void queue_pushHead(queue_t* queue, node_t* element) {
    queue_elem_t* newNode = (queue_elem_t*)malloc(sizeof(queue_elem_t));
    newNode->nodeInfo = element;
    newNode->next = queue->head;
    queue->head = newNode;
}

queue_t* nodesQueue;
node_t* adjacencyList;

int minPacketsNum = 0;
int villagesNum, routesNum, alliedVillagesNum, saturationCoeff;

void bfs() {
    queue_init(&nodesQueue);
    adjacencyList[0].isVisited = true;
    queue_push(nodesQueue, &adjacencyList[0]);

    while (!queue_isEmpty(nodesQueue)) {
        node_t* curNode = queue_pop(nodesQueue);
        int nodeKey = curNode->key;
        int curSaturation = curNode->curSaturation;
        int packets = curNode->packetNum;

        if (nodeKey == 1) {
            curNode->curSaturation = saturationCoeff;
            curNode->packetNum = 0;
        }

        if (minPacketsNum < curNode->packetNum) {
            minPacketsNum = curNode->packetNum;
        }

        for (int i = 0; i < NEIGHBOURS_NUM; ++i) {
            curSaturation = curNode->curSaturation;
            packets = curNode->packetNum;
            int idx = adjacencyList[nodeKey - 1].neighbours[i];
            if (idx - 1 < 0) {
                break;
            }
            if (!adjacencyList[idx - 1].isVisited && adjacencyList[idx - 1].key > 0) {
                adjacencyList[idx - 1].isVisited = true;
                if (curNode->isGreen) {
                    if (adjacencyList[idx - 1].isGreen) {
                        adjacencyList[idx - 1].curSaturation = saturationCoeff;
                        adjacencyList[idx - 1].packetNum = packets;
                    } else if (!adjacencyList[idx - 1].isGreen) {
                        adjacencyList[idx - 1].curSaturation = curSaturation - 1;
                        adjacencyList[idx - 1].packetNum = packets;
                    }
                } else {
                    if (adjacencyList[idx - 1].isGreen) {
                        if (curSaturation == 0) {
                            adjacencyList[idx - 1].curSaturation = saturationCoeff;
                            adjacencyList[idx - 1].packetNum = packets + 1;
                        } else if (curSaturation > 0) {
                            adjacencyList[idx - 1].curSaturation = saturationCoeff;
                            adjacencyList[idx - 1].packetNum = packets;
                        }
                    } else if (!adjacencyList[idx - 1].isGreen) {
                        if (curSaturation == 0) {
                            adjacencyList[idx - 1].curSaturation = saturationCoeff;
                            adjacencyList[idx - 1].packetNum = packets + 1;
                        } else if (curSaturation > 0) {
                            adjacencyList[idx - 1].curSaturation = curSaturation - 1;
                            adjacencyList[idx - 1].packetNum = packets;
                        }
                    }
                }
                queue_push(nodesQueue, &adjacencyList[idx - 1]);
            } else if (adjacencyList[idx - 1].isVisited && adjacencyList[idx - 1].key > 0) {
                if (packets < adjacencyList[idx - 1].packetNum ||
                    (packets == adjacencyList[idx - 1].packetNum && curSaturation > adjacencyList[idx - 1].curSaturation)) {
                    if (curNode->isGreen) {
                        if (adjacencyList[idx - 1].isGreen) {
                            adjacencyList[idx - 1].curSaturation = saturationCoeff;
                            adjacencyList[idx - 1].packetNum = packets;
                        } else if (!adjacencyList[idx - 1].isGreen) {
                            adjacencyList[idx - 1].curSaturation = curSaturation - 1;
                            adjacencyList[idx - 1].packetNum = packets;
                        }
                    } else {
                        if (adjacencyList[idx - 1].isGreen) {
                            if (curSaturation == 0) {
                                adjacencyList[idx - 1].curSaturation = saturationCoeff;
                                adjacencyList[idx - 1].packetNum = packets + 1;
                            } else if (curSaturation > 0) {
                                adjacencyList[idx - 1].curSaturation = saturationCoeff;
                                adjacencyList[idx - 1].packetNum = packets;
                            }
                        } else if (!adjacencyList[idx - 1].isGreen) {
                            if (curSaturation == 0) {
                                adjacencyList[idx - 1].curSaturation = saturationCoeff;
                                adjacencyList[idx - 1].packetNum = packets + 1;
                            } else if (curSaturation > 0) {
                                adjacencyList[idx - 1].curSaturation = curSaturation - 1;
                                adjacencyList[idx - 1].packetNum = packets;
                            }
                        }
                    }

                    bool alreadyInQ = false;
                    queue_elem_t* cursor = nodesQueue->head;
                    while (cursor) {
                        if (adjacencyList[idx - 1].key == cursor->nodeInfo->key &&
                            adjacencyList[idx - 1].curSaturation == cursor->nodeInfo->curSaturation &&
                            adjacencyList[idx - 1].packetNum == cursor->nodeInfo->packetNum) {
                            alreadyInQ = true;
                            break;
                        } else {
                            alreadyInQ = false;
                        }
                        cursor = cursor->next;
                    }

                    if (!alreadyInQ) {
                        queue_pushHead(nodesQueue, &adjacencyList[idx - 1]);
                    }
                }
            }
        }
    }
}

int main() {
    if ((scanf("%d %d %d %d", &villagesNum, &routesNum, &alliedVillagesNum, &saturationCoeff)) != 4) {
        fprintf(stderr, "SCANF FAILURE ON LINE %d\n", __LINE__);
    }

    adjacencyList = (node_t*)malloc(villagesNum * sizeof(node_t));
    if (adjacencyList == NULL) {
        fprintf(stderr, "MALLOC FAILURE ON LINE %d\n", __LINE__);
    }

    for (int i = 0; i < villagesNum; ++i) {
        adjacencyList[i].key = i + 1;
        if (i < alliedVillagesNum) {
            adjacencyList[i].isGreen = true;
        } else {
            adjacencyList[i].isGreen = false;
        }
        adjacencyList[i].isVisited = false;
        if (i < alliedVillagesNum) {
            adjacencyList[i].curSaturation = saturationCoeff;
        } else {
            adjacencyList[i].curSaturation = 0;
        }
        adjacencyList[i].packetNum = 0;
        adjacencyList[i].neighbours = (int*)calloc(4, sizeof(int));
        if (adjacencyList[i].neighbours == NULL) {
            fprintf(stderr, "CALLOC FAILURE ON LINE %d\n", __LINE__);
        }
    }

    int initialPoint, destinationPoint;
    for (int i = 0; i < routesNum; ++i) {
        if ((scanf("%d %d", &initialPoint, &destinationPoint)) != 2) {
            fprintf(stderr, "SCANF FAILURE ON LINE %d\n", __LINE__);
        }

        if (adjacencyList[initialPoint - 1].neighbours[0] == 0) {
            adjacencyList[initialPoint - 1].neighbours[0] = destinationPoint;
        } else if (adjacencyList[initialPoint - 1].neighbours[1] == 0) {
            adjacencyList[initialPoint - 1].neighbours[1] = destinationPoint;
        } else if (adjacencyList[initialPoint - 1].neighbours[2] == 0) {
            adjacencyList[initialPoint - 1].neighbours[2] = destinationPoint;
        } else if (adjacencyList[initialPoint - 1].neighbours[3] == 0) {
            adjacencyList[initialPoint - 1].neighbours[3] = destinationPoint;
        } else {
            printf("NOT ENOUGH SPACE\n");
        }

        if (adjacencyList[destinationPoint - 1].neighbours[0] == 0) {
            adjacencyList[destinationPoint - 1].neighbours[0] = initialPoint;
        } else if (adjacencyList[destinationPoint - 1].neighbours[1] == 0) {
            adjacencyList[destinationPoint - 1].neighbours[1] = initialPoint;
        } else if (adjacencyList[destinationPoint - 1].neighbours[2] == 0) {
            adjacencyList[destinationPoint - 1].neighbours[2] = initialPoint;
        } else if (adjacencyList[destinationPoint - 1].neighbours[3] == 0) {
            adjacencyList[destinationPoint - 1].neighbours[3] = initialPoint;
        } else {
            printf("NOT ENOUGH SPACE\n");
        }
    }

    bfs();
    int packetsFinal = 0;
    int alliances = 0;

    for (int i = 0; i < villagesNum; ++i) {
        if (adjacencyList[i].packetNum > packetsFinal) {
            packetsFinal = adjacencyList[i].packetNum;
        }
        if (adjacencyList[i].packetNum == 0) {
            alliances++;
        }
    }

    printf("%d %d\n", packetsFinal, alliances);

    for (int i = 0; i < villagesNum; ++i) {
        free(adjacencyList[i].neighbours);
    }
    free(adjacencyList);

    return 0;
}
