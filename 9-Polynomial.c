#include <stdio.h>
#include <stdlib.h>

// Definition of the Node structure for polynomial representation
struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
};

// Function prototypes
struct Node* createNode(int coefficient, int exponent);
void appendNode(struct Node** head, int coefficient, int exponent);
void displayPolynomial(struct Node* head);
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2);

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;

    int terms1, terms2, coefficient, exponent;

    // Input for the first polynomial
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &terms1);
    printf("Enter the terms in the format (coefficient exponent):\n");
    for (int i = 0; i < terms1; i++) {
        scanf("%d %d", &coefficient, &exponent);
        appendNode(&poly1, coefficient, exponent);
    }

    // Input for the second polynomial
    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &terms2);
    printf("Enter the terms in the format (coefficient exponent):\n");
    for (int i = 0; i < terms2; i++) {
        scanf("%d %d", &coefficient, &exponent);
        appendNode(&poly2, coefficient, exponent);
    }

    // Add the two polynomials
    result = addPolynomials(poly1, poly2);

    // Display the polynomials
    printf("\nFirst Polynomial: ");
    displayPolynomial(poly1);
    printf("Second Polynomial: ");
    displayPolynomial(poly2);
    printf("Resultant Polynomial: ");
    displayPolynomial(result);

    return 0;
}

// Function to create a new node
struct Node* createNode(int coefficient, int exponent) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Function to append a node to the polynomial
void appendNode(struct Node** head, int coefficient, int exponent) {
    struct Node* newNode = createNode(coefficient, exponent);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to display the polynomial
void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d*x^%d", temp->coefficient, temp->exponent);
        if (temp->next != NULL) {
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            appendNode(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            appendNode(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int sum = poly1->coefficient + poly2->coefficient;
            if (sum != 0) {
                appendNode(&result, sum, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    // Append remaining terms of poly1
    while (poly1 != NULL) {
        appendNode(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    // Append remaining terms of poly2
    while (poly2 != NULL) {
        appendNode(&result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }

    return result;
}



//Output:- 

//Enter the terms in the format (coefficient exponent):
4 3
3 2
2 0