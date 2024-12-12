#include <stdio.h>
#include <stdlib.h>

// Definition of the Node structure
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function prototypes
void insert(struct Node** head, struct Node** tail, int data);
void deleteNode(struct Node** head, struct Node** tail, int key);
struct Node* search(struct Node* head, int key);
void reverse(struct Node** head, struct Node** tail);
void display(struct Node* head);

int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int choice, data, key;

    do {
        printf("\nDoubly Linked List Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Reverse\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insert(&head, &tail, data);
                break;
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &key);
                deleteNode(&head, &tail, key);
                break;
            case 3:
                printf("Enter data to search: ");
                scanf("%d", &key);
                struct Node* result = search(head, key);
                if (result) {
                    printf("Element %d found in the list.\n", result->data);
                } else {
                    printf("Element not found in the list.\n");
                }
                break;
            case 4:
                reverse(&head, &tail);
                printf("List reversed successfully.\n");
                break;
            case 5:
                display(head);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to insert a new node at the end of the list
void insert(struct Node** head, struct Node** tail, int data) {
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

// Function to delete a node with a given key
void deleteNode(struct Node** head, struct Node** tail, int key) {
    struct Node* temp = *head;

    while (temp != NULL && temp->data != key) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Element not found in the list.\n");
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        *tail = temp->prev;
    }

    free(temp);
    printf("Element %d deleted successfully.\n", key);
}

// Function to search for a node with a given key
struct Node* search(struct Node* head, int key) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == key) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Function to reverse the doubly linked list
void reverse(struct Node** head, struct Node** tail) {
    struct Node* temp = NULL;
    struct Node* current = *head;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL) {
        *tail = *head;
        *head = temp->prev;
    }
}

// Function to display the list from head to tail
void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Doubly linked list: ");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
