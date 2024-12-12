#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 4 // Maximum number of keys in a node (change based on degree of the tree)

// Node structure for the B+ Tree
typedef struct BPlusTreeNode {
    int keys[MAX];            // Array of keys
    struct BPlusTreeNode* children[MAX + 1]; // Array of child pointers
    struct BPlusTreeNode* next; // Pointer to the next leaf node (for leaf nodes only)
    bool isLeaf;             // True if the node is a leaf node
    int n;                   // Current number of keys in the node
} BPlusTreeNode;

// Function to create a new B+ Tree node
BPlusTreeNode* createNode(bool isLeaf) {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->isLeaf = isLeaf;
    node->n = 0;
    node->next = NULL;
    for (int i = 0; i < MAX + 1; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Function to split a node and adjust the parent
void splitChild(BPlusTreeNode* parent, int i, BPlusTreeNode* child) {
    int mid = MAX / 2;

    // Create a new node to hold the keys after the midpoint
    BPlusTreeNode* newChild = createNode(child->isLeaf);
    newChild->n = MAX - mid - 1;

    // Copy keys and children from child to newChild
    for (int j = 0; j < newChild->n; j++) {
        newChild->keys[j] = child->keys[mid + 1 + j];
    }
    if (!child->isLeaf) {
        for (int j = 0; j <= newChild->n; j++) {
            newChild->children[j] = child->children[mid + 1 + j];
        }
    }

    // Update the number of keys in the original child
    child->n = mid;

    // Shift parent's children and keys to make space for the new child
    for (int j = parent->n; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = newChild;

    for (int j = parent->n - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = child->keys[mid];
    parent->n++;

    // For leaf nodes, update the next pointer
    if (child->isLeaf) {
        newChild->next = child->next;
        child->next = newChild;
    }
}

// Function to insert a new key into a non-full node
void insertNonFull(BPlusTreeNode* node, int key) {
    int i = node->n - 1;

    if (node->isLeaf) {
        // Shift keys to make space for the new key
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        // Find the child that will receive the new key
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        // Split the child if it's full
        if (node->children[i]->n == MAX) {
            splitChild(node, i, node->children[i]);

            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Function to insert a key into the B+ Tree
BPlusTreeNode* insert(BPlusTreeNode* root, int key) {
    if (root == NULL) {
        root = createNode(true);
        root->keys[0] = key;
        root->n = 1;
        return root;
    }

    if (root->n == MAX) {
        BPlusTreeNode* newRoot = createNode(false);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);

        int i = 0;
        if (key > newRoot->keys[0]) {
            i++;
        }
        insertNonFull(newRoot->children[i], key);
        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

// Function to print the B+ Tree
void printTree(BPlusTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i < root->n; i++) {
            printf("%d ", root->keys[i]);
        }
        printf("| ");
        if (!root->isLeaf) {
            for (int i = 0; i <= root->n; i++) {
                printTree(root->children[i]);
            }
        }
    }
}

int main() {
    BPlusTreeNode* root = NULL;
    int choice, key;

    while (1) {
        printf("\n1. Insert\n2. Print Tree\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("B+ Tree: ");
                printTree(root);
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