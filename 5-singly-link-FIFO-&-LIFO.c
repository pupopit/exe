#include <stdio.h>
#include <stdlib.h>

// Node structure for singly linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function to create a new node
Node *createNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to display the linked list
void displayList(Node *head) {
    if (!head) {
        printf("List is empty!\n");
        return;
    }
    printf("Linked List: ");
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// FIFO insertion (insert at the end)
void fifoInsert(Node **head, Node **tail, int value) {
    Node *newNode = createNode(value);
    if (*tail) {
        (*tail)->next = newNode;
    } else {
        *head = newNode;
    }
    *tail = newNode;
    printf("Inserted %d in FIFO order\n", value);
}

// LIFO insertion (insert at the beginning)
void lifoInsert(Node **head, int value) {
    Node *newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
    printf("Inserted %d in LIFO order\n", value);
}

// Deletion in FIFO order (delete from the beginning)
void fifoDelete(Node **head, Node **tail) {
    if (!*head) {
        printf("List is empty! Cannot delete.\n");
        return;
    }
    Node *temp = *head;
    printf("Deleted %d from FIFO order\n", temp->data);
    *head = (*head)->next;
    if (!*head) {
        *tail = NULL;
    }
    free(temp);
}

// Deletion in LIFO order (delete from the beginning)
void lifoDelete(Node **head) {
    if (!*head) {
        printf("List is empty! Cannot delete.\n");
        return;
    }
    Node *temp = *head;
    printf("Deleted %d from LIFO order\n", temp->data);
    *head = (*head)->next;
    free(temp);
}

int main() {
    Node *head = NULL, *tail = NULL;
    int choice, value;

    while (1) {
        printf("\nSingly Linked List Operations:\n");
        printf("1. Insert in FIFO order\n");
        printf("2. Insert in LIFO order\n");
        printf("3. Delete in FIFO order\n");
        printf("4. Delete in LIFO order\n");
        printf("5. Display the list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                fifoInsert(&head, &tail, value);
                break;
            case 2:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                lifoInsert(&head, value);
                break;
            case 3:
                fifoDelete(&head, &tail);
                break;
            case 4:
                lifoDelete(&head);
                break;
            case 5:
                displayList(head);
                break;
            case 6:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
