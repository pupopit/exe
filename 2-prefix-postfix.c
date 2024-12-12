#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack structure
typedef struct {
    char arr[MAX_SIZE];
    int top;
} Stack;

// Function to initialize the stack
void initializeStack(Stack *stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// Function to push an element onto the stack
void push(Stack *stack, char value) {
    if (isFull(stack)) {
        printf("Stack Overflow!\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

// Function to pop an element from the stack
char pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

// Function to peek the top element of the stack
char peek(Stack *stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->arr[stack->top];
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to get the precedence of an operator
int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

// Function to reverse a string
void reverseString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Function to convert infix to postfix
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;
    initializeStack(&stack);
    int k = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[k++] = ch;  // Add operands to the result
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[k++] = pop(&stack);
            }
            pop(&stack);  // Pop the '('
        } else if (isOperator(ch)) {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(ch)) {
                postfix[k++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    while (!isEmpty(&stack)) {
        postfix[k++] = pop(&stack);
    }

    postfix[k] = '\0';  // Null-terminate the result
}

// Function to convert infix to prefix
void infixToPrefix(char *infix, char *prefix) {
    Stack stack;
    initializeStack(&stack);
    int k = 0;

    // Reverse the infix expression
    reverseString(infix);

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            prefix[k++] = ch;  // Add operands to the result
        } else if (ch == ')') {
            push(&stack, ch);
        } else if (ch == '(') {
            while (!isEmpty(&stack) && peek(&stack) != ')') {
                prefix[k++] = pop(&stack);
            }
            pop(&stack);  // Pop the ')'
        } else if (isOperator(ch)) {
            while (!isEmpty(&stack) && precedence(peek(&stack)) > precedence(ch)) {
                prefix[k++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    while (!isEmpty(&stack)) {
        prefix[k++] = pop(&stack);
    }

    prefix[k] = '\0';  // Null-terminate the result

    // Reverse the result to get the correct prefix expression
    reverseString(prefix);
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE], prefix[MAX_SIZE];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    infixToPrefix(infix, prefix);
    printf("Prefix Expression: %s\n", prefix);

    return 0;
}