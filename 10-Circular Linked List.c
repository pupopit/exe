#include <stdio.h>
#include <stdlib.h>

// Definition of the Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function prototypes
void insert(struct Node** head, int data);
void deleteNode(struct Node** head, int key);
void display(struct Node* head);

int main() {
    struct Node* head = NULL;
    int choice, data;

    do {
        printf("\nCircular Linked List Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insert(&head, data);
                break;
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                deleteNode(&head, data);
                break;
            case 3:
                display(head);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to insert a new node at the end of the circular linked list
void insert(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->next = *head;
}

// Function to delete a node with a given key from the circular linked list
void deleteNode(struct Node** head, int key) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *current = *head, *prev = NULL;

    // If the node to be deleted is the head node
    if ((*head)->data == key) {
        while (current->next != *head) {
            current = current->next;
        }

        if (*head == current) { // Only one node in the list
            free(*head);
            *head = NULL;
        } else {
            current->next = (*head)->next;
            free(*head);
            *head = current->next;
        }
        printf("Element %d deleted successfully.\n", key);
        return;
    }

    // Search for the key to be deleted
    do {
        prev = current;
        current = current->next;
    } while (current != *head && current->data != key);

    if (current == *head) {
        printf("Element not found in the list.\n");
        return;
    }

    prev->next = current->next;
    free(current);
    printf("Element %d deleted successfully.\n", key);
}

// Function to display the circular linked list
void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("Circular Linked List: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}
