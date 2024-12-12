#include <stdio.h>
#include <stdlib.h>

// Definition of the Node structure
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function prototypes
void insertFIFO(struct Node** head, struct Node** tail, int data);
void insertLIFO(struct Node** head, struct Node** tail, int data);
void displayFromHead(struct Node* head);
void displayFromTail(struct Node* tail);

int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int choice, data;

    do {
        printf("\nDoubly Linked List Operations:\n");
        printf("1. Insert (FIFO)\n");
        printf("2. Insert (LIFO)\n");
        printf("3. Display from Head\n");
        printf("4. Display from Tail\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert (FIFO): ");
                scanf("%d", &data);
                insertFIFO(&head, &tail, data);
                break;
            case 2:
                printf("Enter data to insert (LIFO): ");
                scanf("%d", &data);
                insertLIFO(&head, &tail, data);
                break;
            case 3:
                displayFromHead(head);
                break;
            case 4:
                displayFromTail(tail);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to insert a new node in FIFO manner
void insertFIFO(struct Node** head, struct Node** tail, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = *tail = newNode;
        return;
    }

    (*tail)->next = newNode;
    newNode->prev = *tail;
    *tail = newNode;
}

// Function to insert a new node in LIFO manner
void insertLIFO(struct Node** head, struct Node** tail, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = *tail = newNode;
        return;
    }

    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}

// Function to display the list from head to tail
void displayFromHead(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Doubly linked list (head to tail): ");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to display the list from tail to head
void displayFromTail(struct Node* tail) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Doubly linked list (tail to head): ");
    struct Node* temp = tail;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}
