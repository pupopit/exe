#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Simple Queue Implementation
void simpleQueue() {
    int queue[MAX_SIZE], front = -1, rear = -1;
    int choice, value;

    while (1) {
        printf("\nSimple Queue Operations:\n");
        printf("1. Insert\n2. Remove\n3. Display\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (rear == MAX_SIZE - 1) {
                    printf("Queue Overflow!\n");
                } else {
                    printf("Enter the value to insert: ");
                    scanf("%d", &value);
                    if (front == -1) front = 0;
                    queue[++rear] = value;
                    printf("Inserted %d\n", value);
                }
                break;
            case 2:
                if (front == -1 || front > rear) {
                    printf("Queue Underflow!\n");
                } else {
                    printf("Removed %d\n", queue[front++]);
                }
                break;
            case 3:
                if (front == -1 || front > rear) {
                    printf("Queue is empty!\n");
                } else {
                    printf("Queue elements: ");
                    for (int i = front; i <= rear; i++) {
                        printf("%d ", queue[i]);
                    }
                    printf("\n");
                }
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

// Circular Queue Implementation
void circularQueue() {
    int queue[MAX_SIZE], front = -1, rear = -1;
    int choice, value;

    while (1) {
        printf("\nCircular Queue Operations:\n");
        printf("1. Insert\n2. Remove\n3. Display\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if ((rear + 1) % MAX_SIZE == front) {
                    printf("Queue Overflow!\n");
                } else {
                    printf("Enter the value to insert: ");
                    scanf("%d", &value);
                    if (front == -1) front = 0;
                    rear = (rear + 1) % MAX_SIZE;
                    queue[rear] = value;
                    printf("Inserted %d\n", value);
                }
                break;
            case 2:
                if (front == -1) {
                    printf("Queue Underflow!\n");
                } else {
                    printf("Removed %d\n", queue[front]);
                    if (front == rear) {
                        front = rear = -1;
                    } else {
                        front = (front + 1) % MAX_SIZE;
                    }
                }
                break;
            case 3:
                if (front == -1) {
                    printf("Queue is empty!\n");
                } else {
                    printf("Queue elements: ");
                    int i = front;
                    while (1) {
                        printf("%d ", queue[i]);
                        if (i == rear) break;
                        i = (i + 1) % MAX_SIZE;
                    }
                    printf("\n");
                }
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

// Priority Queue Implementation
void priorityQueue() {
    int queue[MAX_SIZE], n = 0;
    int choice, value, i, j;

    while (1) {
        printf("\nPriority Queue Operations:\n");
        printf("1. Insert\n2. Remove\n3. Display\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (n == MAX_SIZE) {
                    printf("Queue Overflow!\n");
                } else {
                    printf("Enter the value to insert: ");
                    scanf("%d", &value);
                    i = n - 1;
                    while (i >= 0 && queue[i] > value) {
                        queue[i + 1] = queue[i];
                        i--;
                    }
                    queue[i + 1] = value;
                    n++;
                    printf("Inserted %d\n", value);
                }
                break;
            case 2:
                if (n == 0) {
                    printf("Queue Underflow!\n");
                } else {
                    printf("Removed %d\n", queue[0]);
                    for (i = 0; i < n - 1; i++) {
                        queue[i] = queue[i + 1];
                    }
                    n--;
                }
                break;
            case 3:
                if (n == 0) {
                    printf("Queue is empty!\n");
                } else {
                    printf("Queue elements: ");
                    for (i = 0; i < n; i++) {
                        printf("%d ", queue[i]);
                    }
                    printf("\n");
                }
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nQueue Types:\n");
        printf("1. Simple Queue\n2. Circular Queue\n3. Priority Queue\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                simpleQueue();
                break;
            case 2:
                circularQueue();
                break;
            case 3:
                priorityQueue();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}