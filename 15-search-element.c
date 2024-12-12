#include <stdio.h>

#define MAX_SIZE 100

// Linear Search Function
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return the index where the target is found
        }
    }
    return -1;  // Return -1 if the element is not found
}

// Binary Search Function (assumes the array is sorted)
int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == target) {
            return mid;  // Return the index where the target is found
        }
        else if (arr[mid] < target) {
            low = mid + 1;  // Search in the right half
        }
        else {
            high = mid - 1;  // Search in the left half
        }
    }
    return -1;  // Return -1 if the element is not found
}

int main() {
    int arr[MAX_SIZE], n, target, choice, result;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements of the array (sorted for binary search):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search: ");
    scanf("%d", &target);

    printf("Choose search method:\n");
    printf("1. Linear Search\n2. Binary Search\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            result = linearSearch(arr, n, target);
            if (result != -1) {
                printf("Element found at index %d using Linear Search.\n", result);
            } else {
                printf("Element not found using Linear Search.\n");
            }
            break;
        case 2:
            result = binarySearch(arr, n, target);
            if (result != -1) {
                printf("Element found at index %d using Binary Search.\n", result);
            } else {
                printf("Element not found using Binary Search.\n");
            }
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}


// output //

// Enter the number of elements: 5
// Enter the elements of the array (sorted for binary search):
// 10
// 20
// 30
// 40
// 50
// Enter the element to search: 40
// Choose search method:
// 1. Linear Search
// 2. Binary Search
// 2
// Element found at index 3 using Binary Search.