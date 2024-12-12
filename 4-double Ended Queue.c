#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Double-Ended Queue Structure
typedef struct {
    int deque[MAX_SIZE];
    int front, rear;
} Deque;

// Initialize the deque
void initializeDeque(Deque *dq) {
    dq->front = -1;
    dq->rear = -1;
}

// Check if the deque is full
int isFull(Deque *dq) {
    return (dq->front == 0 && dq->rear == MAX_SIZE - 1) || (dq->front == dq->rear + 1);
}

// Check if the deque is empty
int isEmpty(Deque *dq) {
    return dq->front == -1;
}

// Insert at the rear
void insertRear(Deque *dq, int value) {
    if (isFull(dq)) {
        printf("Deque Overflow!\n");
        return;
    }
    if (dq->front == -1) { // First element insertion
        dq->front = dq->rear = 0;
    } else if (dq->rear == MAX_SIZE - 1) {
        dq->rear = 0;
    } else {
        dq->rear++;
    }
    dq->deque[dq->rear] = value;
    printf("Inserted %d at the rear\n", value);
}

// Insert at the front
void insertFront(Deque *dq, int value) {
    if (isFull(dq)) {
        printf("Deque Overflow!\n");
        return;
    }
    if (dq->front == -1) { // First element insertion
        dq->front = dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = MAX_SIZE - 1;
    } else {
        dq->front--;
    }
    dq->deque[dq->front] = value;
    printf("Inserted %d at the front\n", value);
}

// Delete from the front
void deleteFront(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow!\n");
        return;
    }
    printf("Deleted %d from the front\n", dq->deque[dq->front]);
    if (dq->front == dq->rear) { // Only one element
        dq->front = dq->rear = -1;
    } else if (dq->front == MAX_SIZE - 1) {
        dq->front = 0;
    } else {
        dq->front++;
    }
}

// Delete from the rear
void deleteRear(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque Underflow!\n");
        return;
    }
    printf("Deleted %d from the rear\n", dq->deque[dq->rear]);
    if (dq->front == dq->rear) { // Only one element
        dq->front = dq->rear = -1;
    } else if (dq->rear == 0) {
        dq->rear = MAX_SIZE - 1;
    } else {
        dq->rear--;
    }
}

// Display the deque
void displayDeque(Deque *dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque elements: ");
    int i = dq->front;
    while (1) {
        printf("%d ", dq->deque[i]);
        if (i == dq->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

// Input Restricted Deque
void inputRestrictedDeque() {
    Deque dq;
    initializeDeque(&dq);
    int choice, value;

    while (1) {
        printf("\nInput Restricted Deque Operations:\n");
        printf("1. Insert at Rear\n2. Delete from Front\n3. Delete from Rear\n4. Display\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insertRear(&dq, value);
                break;
            case 2:
                deleteFront(&dq);
                break;
            case 3:
                deleteRear(&dq);
                break;
            case 4:
                displayDeque(&dq);
                break;
            case 5:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

// Output Restricted Deque
void outputRestrictedDeque() {
    Deque dq;
    initializeDeque(&dq);
    int choice, value;

    while (1) {
        printf("\nOutput Restricted Deque Operations:\n");
        printf("1. Insert at Front\n2. Insert at Rear\n3. Delete from Front\n4. Display\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insertFront(&dq, value);
                break;
            case 2:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insertRear(&dq, value);
                break;
            case 3:
                deleteFront(&dq);
                break;
            case 4:
                displayDeque(&dq);
                break;
            case 5:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nDouble-Ended Queue Types:\n");
        printf("1. Input Restricted Deque\n2. Output Restricted Deque\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputRestrictedDeque();
                break;
            case 2:
                outputRestrictedDeque();
                break;
            case 3:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
