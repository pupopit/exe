#include <stdio.h>
#include <stdlib.h>

// Define the structure of a B-Tree node
typedef struct BTreeNode {
    int *keys;          // Array of keys
    int t;              // Minimum degree
    struct BTreeNode **C; // Array of child pointers
    int n;              // Current number of keys
    int leaf;           // Is true if the node is a leaf
} BTreeNode;

// Function to create a new B-Tree node
BTreeNode* createNode(int t, int leaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->t = t;
    newNode->leaf = leaf;
    newNode->keys = (int*)malloc((2 * t - 1) * sizeof(int));
    newNode->C = (BTreeNode**)malloc(2 * t * sizeof(BTreeNode*));
    newNode->n = 0;
    return newNode;
}

// Function to split a child node of the given parent
void splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    int t = y->t;
    BTreeNode* z = createNode(t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys from y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children from y to z if y is not a leaf
    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    // Shift children of parent to make room for the new child
    for (int j = parent->n; j >= i + 1; j--)
        parent->C[j + 1] = parent->C[j];

    // Link the new child to the parent
    parent->C[i + 1] = z;

    // Move a key from y to the parent
    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[t - 1];
    parent->n += 1;
}

// Function to insert a new key into a non-full node
void insertNonFull(BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        // Find the position for the new key
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n += 1;
    } else {
        // Find the child where the key belongs
        while (i >= 0 && k < x->keys[i])
            i--;

        i++;
        if (x->C[i]->n == 2 * x->t - 1) {
            splitChild(x, i, x->C[i]);
            if (k > x->keys[i])
                i++;
        }
        insertNonFull(x->C[i], k);
    }
}

// Function to insert a new key into the B-Tree
BTreeNode* insert(BTreeNode* root, int k, int t) {
    if (root == NULL) {
        root = createNode(t, 1);
        root->keys[0] = k;
        root->n = 1;
        return root;
    }

    if (root->n == 2 * t - 1) {
        BTreeNode* s = createNode(t, 0);
        s->C[0] = root;
        splitChild(s, 0, root);

        int i = 0;
        if (s->keys[0] < k)
            i++;
        insertNonFull(s->C[i], k);

        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

// Function to print the B-Tree
void printTree(BTreeNode* root, int level) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            if (!root->leaf)
                printTree(root->C[i], level + 1);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf)
            printTree(root->C[root->n], level + 1);
    }
}

int main() {
    int t;
    printf("Enter the minimum degree of the B-Tree: ");
    scanf("%d", &t);

    BTreeNode* root = NULL;
    int choice, key;

    while (1) {
        printf("\n1. Insert\n2. Print Tree\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                root = insert(root, key, t);
                break;
            case 2:
                printf("B-Tree: ");
                printTree(root, 0);
                printf("\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
